#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	用途: オブジェクトの影
	//--------------------------------------------------------------------------------------
	ShadowObject::ShadowObject(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, weak_ptr<GameObject> Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f)
	{
	}
	
	ShadowObject::~ShadowObject() {}
	//初期化
	void ShadowObject::OnCreate() {
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;
		auto PtrTransform = AddComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		auto PtrObb = AddComponent<CollisionObb>();
		PtrObb->SetFixed(true);
		//PtrObb->SetDrawActive(true);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		auto obj = m_Obj.lock();
		PtrDraw->SetMeshResource(obj->GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		//真っ黒
		PtrDraw->SetColorAndAlpha(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		PtrDraw->SetTextureResource(L"Shadow_Blur_TX");
	}

	//変化
	void ShadowObject::OnUpdate() {
		GetComponent<Transform>()->SetPosition(ShadowLocation());
		if (GetStage()->GetSharedGameObject<Player>(L"Player")->GetFadeFlag()) {
			m_RemoveTime += App::GetApp()->GetElapsedTime();
			if (m_RemoveTime >= 0.6f) {
				GetStage()->RemoveGameObject<ShadowObject>(GetThis<ShadowObject>());
			}
		}
	}
	void ShadowObject::OnUpdate2() {
	}

	//物体とライトの位置から、影の位置を導き出す
	Vec3 ShadowObject::ShadowLocation() {
		auto obj = m_Obj.lock();
		//実体ブロックのポジション
		auto ObjPos = obj->GetComponent<Transform>()->GetPosition();
		//ライトのコントローラーを持ってくる
		auto ptrMyLight = GetStage()->GetSharedGameObject<LightController>(L"LightController");
		//角度を取り出す
		auto LightAngle = ptrMyLight->GetLightAngle();

		//ライトの角度と対応した実態ブロックの壁までの距離から影の位置を出す
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * tanf(LightAngle.x);
		m_kagePos.y = ObjPos.y - ObjPos.z * tanf(LightAngle.y);
		m_kagePos.z = 0;

		//ライトの角度を別変数で持つ
		auto AngleX = LightAngle.x;
		auto AngleY = LightAngle.y;
		//マイナスの値だったらプラスにする
		if (AngleX < 0) {
			AngleX *= -1.0f;
		}
		if (AngleY < 0) {
			AngleY *= -1.0f;
		}
		//スケールにアングルの値足す
		GetComponent<Transform>()->SetScale(m_Scale.x + AngleX, m_Scale.y + AngleY, m_ScaleZ);

		return m_kagePos;
	}
	//------------------------------------------------------------------------------------------
	///ゴールの役割をする影
	//------------------------------------------------------------------------------------------
	ShadowGoal::ShadowGoal(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& m_Scale, const Vec3& Rotation, weak_ptr<GameObject> Obj)
		: SS5ssae(StagePtr, BaseDir, L"DoorSS_0605.ssae", L"Lock"),
		m_Scale(m_Scale),m_Rotation(Rotation),m_Obj(Obj), m_ScaleZ(0.05f)
	{
		m_ToAnimeMatrixDark.affineTransformation(
			Vec3(1.8f, 1.5f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0.0f, 0.0f)
		);
		m_ToAnimeMatrixLight.affineTransformation(
			Vec3(0.0000018f, 0.0000014f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0.0f, 0.0f)
		);
	}

	void ShadowGoal::OnCreate() {
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;

		auto PtrTransform = GetComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(10);
		//アニメーションのループ設定
		SetLooped(true);
		//アニメーションにかけるメトリックスの設定
		SetToAnimeMatrix(m_ToAnimeMatrixDark);
		SetAlphaActive(true);
		GetStage()->SetSharedGameObject(L"ShadowGoal", GetThis<ShadowGoal>());
	}

	void ShadowGoal::OnUpdate() {
		OnTriggerEnter();
		GetComponent<Transform>()->SetPosition(ShadowLocation());

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
		if (m_LightFlag){
			m_LightFlag = false;
			SetFps(60.0f);
			ChangeAnimation(L"Unlock");
			SetLooped(false);
		}
	}

	void ShadowGoal::OnTriggerEnter(){
		OBB t;
		t.m_Center = this->GetComponent<Transform>()->GetWorldPosition();
		t.m_Center.y = t.m_Center.y - 0.2f;//ドアの判定位置を下げる
		t.m_Center.z = 0;
		t.m_Size = this->GetComponent<Transform>()->GetScale() * 0.3f;
		OBB p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale() * 0.5f;
		//プレイヤーがゴールに触れたかを調べる判定
		if (HitTest::OBB_OBB(t, p) && !flag) {
			if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetGameOverFlag()) {
				GetStage()->GetSharedGameObject<Player>(L"Player")->InGoal();
				flag = true;
			}
		}
	}

	//物体とライトの位置から、影の位置を導き出す
	Vec3 ShadowGoal::ShadowLocation() {
		auto obj = m_Obj.lock();
		//実体ブロックのポジション
		auto ObjPos = obj->GetComponent<Transform>()->GetPosition();
		//ライトのコントローラーを持ってくる
		auto ptrMyLight = GetStage()->GetSharedGameObject<LightController>(L"LightController");
		//角度を取り出す
		auto LightAngle = ptrMyLight->GetLightAngle();

		//ライトの角度と対応した実態ブロックの壁までの距離から影の位置を出す
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * tanf(LightAngle.x);
		m_kagePos.y = ObjPos.y - ObjPos.z * tanf(LightAngle.y);

		m_kagePos.z = 0;

		return m_kagePos;
	}
	//------------------------------------------------------------------------------------------
	///鍵の役割をする影
	//------------------------------------------------------------------------------------------
	ShadowKey::ShadowKey(const shared_ptr<Stage>& StagePtr,const wstring BaseDir,
		const Vec3& Scale, const Vec3& Rotation, weak_ptr<GameObject> Obj)
		: SS5ssae(StagePtr, BaseDir, L"KeySS_0522.ssae", L"anime_1"),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f)
	{
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.9f, 0.9f, 0.7f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, 0.6f, 0.0f)
			);
	}

	void ShadowKey::OnCreate() {
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;

		auto PtrTransform = GetComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(30.0f);
		//アニメーションのループ設定
		SetLooped(true);

		SetAlphaActive(true);
		//アニメーションにかけるメトリックスの設定
		SetToAnimeMatrix(m_ToAnimeMatrix);
	}

	void ShadowKey::OnUpdate() {
		OnTriggerEnter();
		//鍵が取られたら
		if (m_GoGoal) {
			//計算のための時間加算
			m_Lerp += App::GetApp()->GetElapsedTime()*2.5f;
			//回転のための時間加算
			m_spin += App::GetApp()->GetElapsedTime();
			//ベジエ曲線最終位置の設定
			p1 = GetStage()->GetSharedGameObject<ShadowGoal>(L"ShadowGoal")->
				GetComponent<Transform>()->GetWorldPosition() + Vec3(0.0f,3.0f, 0.0f);
			//回る
			GetComponent<Transform>()->SetRotation(Vec3(0.0f, 0.0f, m_spin*30.0f));
			//位置計算
			m_Position.x = (1 - m_Lerp)*p0.x + m_Lerp*p1.x;
			m_Position.y = (1 - m_Lerp)*p0.y + m_Lerp*p1.y;
			GetComponent<Transform>()->SetPosition(m_Position);
			//動きが終わったら
			if (m_Lerp >= 1.0f) {
				//ゴールのアニメ起動のフラグを立てる
				GetStage()->GetSharedGameObject<ShadowGoal>(L"ShadowGoal")->SetLightFlag(true);
				//鍵を消す
				GetStage()->RemoveGameObject<ShadowKey>(GetThis<ShadowKey>());
			}
		}
		else {
			GetComponent<Transform>()->SetPosition(ShadowLocation());
		}

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
	}
	//当たったかの判定
	void ShadowKey::OnTriggerEnter() {
		//鍵
		OBB t;
		t.m_Center = this->GetComponent<Transform>()->GetWorldPosition();
		t.m_Center.z = 0;
		t.m_Size = this->GetComponent<Transform>()->GetScale() * 0.6f;
		//イデア
		OBB p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale() * 0.5f;
		//プレイヤーが鍵に触れたかを調べる判定
		if (HitTest::OBB_OBB(t, p) && !m_GoGoal) {
			//プレイヤーの所持鍵数を増やす
			GetStage()->GetSharedGameObject<Player>(L"Player")->AddKey();
			//ゴールに向かうフラグを立てる
			m_GoGoal = true;
			//ベジエ曲線初期位置の設定
			p0 = GetComponent<Transform>()->GetWorldPosition();

			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"KeySound");
			m_AudioObjectPtr->Start(L"KeySound", XAUDIO2_NO_LOOP_REGION, 0.6f);
		}
	}
	//物体とライトの位置から、影の位置を導き出す
	Vec3 ShadowKey::ShadowLocation() {
		auto obj = m_Obj.lock();
		//実体ブロックのポジション
		auto ObjPos = obj->GetComponent<Transform>()->GetPosition();
		//ライトのコントローラーを持ってくる
		auto ptrMyLight = GetStage()->GetSharedGameObject<LightController>(L"LightController");
		//角度を取り出す
		auto LightAngle = ptrMyLight->GetLightAngle();

		//ライトの角度と対応した実態ブロックの壁までの距離から影の位置を出す
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * tanf(LightAngle.x);
		m_kagePos.y = ObjPos.y - ObjPos.z * tanf(LightAngle.y);

		m_kagePos.z = 0;

		return m_kagePos;
	}
}