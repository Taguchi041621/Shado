#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	鍵
	//--------------------------------------------------------------------------------------
	KeyItem::KeyItem(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_KeyPos(StartPos)
	{}
	void KeyItem::OnCreate(){
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetPosition(m_KeyPos);
		PtrTransform->SetScale(0.50,1.00,0.50);

		//タグ
		AddTag(L"KeyItem");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		////描画するテクスチャを設定
		//PtrDraw->SetTextureResource(L"UI_Key_TX");
		PtrDraw->SetDrawActive(false);

		auto group = GetStage()->GetSharedObjectGroup(L"KeyGroup");
		group->IntoGroup(GetThis<KeyItem>());

		//影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		//-------------------------------------------------
		//影の作成
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		GetStage()->AddGameObject<ShadowKey>(
			DataDir + L"KeyAni\\",
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			GetThis<GameObject>()
			);
	}

	void KeyItem::OnUpdate()
	{
		//OnTriggerEnter();
	}
	//鍵が当たったとき
	void KeyItem::OnTriggerEnter() {
	}

	//-----------------------------------------------------------------------------------------------------------
	//ステージ開始時にカメラが追いかける見えないオブジェクト
	//-----------------------------------------------------------------------------------------------------------
	TargetObjectToStart::TargetObjectToStart(const shared_ptr<Stage>& StagePtr)
		: GameObject(StagePtr),m_TargetPos(0.0f,0.0f,0.0f)
	{}
	//初期化
	void TargetObjectToStart::OnCreate() {
		auto trans = GetComponent<Transform>();
		trans->SetWorldPosition(Vec3(0.0f, 0.0f, 0.0f));
		trans->SetScale(Vec3(0.1f, 0.1f, 0.1f));
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		//見えないようにする
		drawComp->SetDrawActive(false);
		//ゴールの場所とイデアの場所を取得
		GoalPos = GetStage()->GetSharedGameObject<ShadowGoal>(L"ShadowGoal")->GetComponent<Transform>()->GetWorldPosition();
		PlayerPos = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();

	}
	void TargetObjectToStart::OnUpdate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		Vec3 pos;
		//ゴールに行く
		if (m_Move == 0) {
			m_Lerp += App::GetApp()->GetElapsedTime() / 3.0f;

			pos.x = (1 - m_Lerp)*m_TargetPos.x + m_Lerp*GoalPos.x;
			pos.y = (1 - m_Lerp)*m_TargetPos.y + m_Lerp*GoalPos.y;
			pos.z = (1 - m_Lerp)*m_TargetPos.z + m_Lerp*GoalPos.z;
			if (m_Lerp > 1.0f) {
				m_Lerp = 0;
				m_Move = 1;
			}
		}
		//イデアに行く
		if (m_Move == 1) {
			m_Lerp += App::GetApp()->GetElapsedTime() / 1.0f;

			pos.x = (1 - m_Lerp)*GoalPos.x + m_Lerp *PlayerPos.x;
			pos.y = (1 - m_Lerp)*GoalPos.y + m_Lerp *PlayerPos.y;
			pos.z = (1 - m_Lerp)*GoalPos.z + m_Lerp *PlayerPos.z;
			if (m_Lerp > 1.0f) {
				m_Move = 2;
			}
		}
		//イデアまで行った、もしくはリスタートの場合
		if (m_Move == 2.0f || ScenePtr->GetRespawnFlag()) {
			auto camera = dynamic_pointer_cast<MyCamera>(GetStage()->GetView()->GetTargetCamera());
			camera->SetStartFlag(true);
			ScenePtr->SetStartFlag(true);
			auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
			camera->SetTargetObject(player);
			GetStage()->RemoveGameObject<TargetObjectToStart>(GetThis<TargetObjectToStart>());
		}
		GetComponent<Transform>()->SetPosition(pos);
	}
}