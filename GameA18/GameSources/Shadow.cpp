#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	用途: オブジェクトの影
	//--------------------------------------------------------------------------------------
	ShadowObject::ShadowObject(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, const wstring& Mesh, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Mesh(Mesh), m_Obj(Obj), m_ScaleZ(1.0f),
		m_LightAngle(0.0f, 0.0f, 0.0f), m_LightDistance(0.1f)
	{
	}

	ShadowObject::~ShadowObject() {}
	//初期化
	void ShadowObject::OnCreate() {
		//ライトの位置を代入
		auto MultiLightPtr = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
		auto mainIndex = MultiLightPtr->GetMainIndex();
		m_LightPosition = MultiLightPtr->GetLight(mainIndex).m_Directional;
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;
		AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		auto PtrObb = AddComponent<CollisionObb>();
		PtrObb->SetFixed(true);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetMeshResource(m_Mesh);
		PtrDraw->SetOwnShadowActive(true);
		PtrDraw->SetTextureResource(L"Oreng_TX");
	}

	//変化
	/*void ShadowObject::OnUpdate() {
		//ライトを右スティックで動かす
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//右スティックが動いていたら
			if (CntlVec[0].fThumbRX != 0 || CntlVec[0].fThumbRY != 0) {
				//マルチライトを持ってくる
				auto PtrLight = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
				//マルチライトの中のメインライトを持ってくる
				auto mainIndex = PtrLight->GetMainIndex();
				//Elapsedタイムの取得
				auto ElapsedTime = App::GetApp()->GetElapsedTime();
				//X方向にステックが倒れていたら
				if (m_LightPosition.x <= 0.1f && CntlVec[0].fThumbRX > 0.4f) {
					m_LightPosition.x += CntlVec[0].fThumbRX/10.0f * ElapsedTime;
				}
				else if (m_LightPosition.x >= -0.1f && CntlVec[0].fThumbRX < -0.4f) {
					m_LightPosition.x += CntlVec[0].fThumbRX/10.0f * ElapsedTime;
				}
				//Y方向にスティックが倒れていたら
				if (m_LightPosition.y <= 0.1f && CntlVec[0].fThumbRY > 0.4f) {
					m_LightPosition.y += CntlVec[0].fThumbRY/10.0f * ElapsedTime;
				}
				else if (m_LightPosition.y >= -0.1f && CntlVec[0].fThumbRY < -0.4f) {
					m_LightPosition.y += CntlVec[0].fThumbRY/10.0f * ElapsedTime;
				}
				//変更したライトのポジションを反映
				PtrLight->GetLight(mainIndex).SetPositionToDirectional(m_LightPosition);
			}
		}

		//ライトの位置から影の位置を計算し、ポジションを変える
		//Vec3 ShadowToMe = ShadowLocation() - GetComponent<Transform>()->GetPosition();
		//GetComponent<Rigidbody>()->SetVelocity(ShadowToMe*10.0f);
		GetComponent<Transform>()->SetPosition(ShadowLocation());
	}*/
	void ShadowObject::OnUpdate() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//右スティックが動いていたら
			if (CntlVec[0].fThumbRX != 0 || CntlVec[0].fThumbRY != 0) {
				//マルチライトを持ってくる
				auto PtrLight = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
				//マルチライトの中のメインライトを持ってくる
				auto mainIndex = PtrLight->GetMainIndex();
				//Elapsedタイムの取得
				auto ElapsedTime = App::GetApp()->GetElapsedTime();
				//X方向にステックが倒れていたら
				if (m_LightAngle.x >= -0.9f && CntlVec[0].fThumbRX > 0.4f) {
					m_LightAngle.x += -CntlVec[0].fThumbRX * ElapsedTime;
				}
				else if (m_LightAngle.x <= 0.9f && CntlVec[0].fThumbRX < -0.4f) {
					m_LightAngle.x += -CntlVec[0].fThumbRX * ElapsedTime;
				}
				//Y方向にスティックが倒れていたら
				if (m_LightAngle.y >= -0.9f && CntlVec[0].fThumbRY > 0.4f) {
					m_LightAngle.y += -CntlVec[0].fThumbRY * ElapsedTime;
				}
				else if (m_LightAngle.y <= 0.9f && CntlVec[0].fThumbRY < -0.4f) {
					m_LightAngle.y += -CntlVec[0].fThumbRY * ElapsedTime;
				}
				//---------------------------------------------------------------------------------------
				//角度からポジション出す
				m_LightPosition.x = -m_LightDistance * sinf(m_LightAngle.x);
				float xZ = -m_LightDistance * cosf(m_LightAngle.x);
				//X軸に角度を反映させた後のZ軸を基準にY軸方向の計算をする
				m_LightPosition.y = xZ * sinf(m_LightAngle.y);
				m_LightPosition.z = xZ * cosf(m_LightAngle.y);
				//変更したライトのポジションを反映
				PtrLight->GetLight(mainIndex).SetPositionToDirectional(m_LightPosition);
			}
		}
		//影のポジションの更新
		GetComponent<Transform>()->SetPosition(ShadowLocation());
	}

	//物体とライトの位置から、影の位置を導き出す
	Vec3 ShadowObject::ShadowLocation() {
		//実体ブロックのポジション
		auto ObjPos = m_Obj.GetComponent<Transform>()->GetPosition();
		//ライトの角度と対応した実態ブロックの壁までの距離から影の位置を出す
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * m_LightAngle.x;
		m_kagePos.y = ObjPos.y - ObjPos.z * m_LightAngle.y;
		m_kagePos.z = 0;

		//ライトの角度を別変数で持つ
		auto AngleX = m_LightAngle.x;
		auto AngleY = m_LightAngle.y;

		if (AngleX < 0) {
			AngleX *= -1.0f;
		}
		if (AngleY < 0) {
			AngleY *= -1.0f;
		}

		//スケールにアングルの値足す
		GetComponent<Transform>()->SetScale(m_Scale.x + AngleX, m_Scale.y + AngleY, m_ScaleZ);
		//m_kagePos.x += m_Scale.x - m_Obj.GetComponent<Transform>()->GetScale().x;
		//m_kagePos.y += m_Scale.x - m_Obj.GetComponent<Transform>()->GetScale().y;

		return m_kagePos;
	}
	//前の位置と今の位置を比べてVec3を返す
	Vec3 ShadowObject::GetPoorBefor() {
		//前のポジションと今のポジションの差を出す
		PoorBefor = ShadowLocation() - GetComponent<Transform>()->GetBeforePosition();
		//差を返す
		return PoorBefor;
	}
}