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
		m_LightPosition(0.01f, 0.01f, -0.1f)
	{
	}

	ShadowObject::~ShadowObject() {}
	//初期化
	void ShadowObject::OnCreate() {
		m_Scale.z = m_ScaleZ;
		AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//影のポジションを出す
		auto kagePos = ShadowLocation();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(kagePos);

		auto PtrObb = AddComponent<CollisionObb>();
		PtrObb->SetFixed(true);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetMeshResource(m_Mesh);
		PtrDraw->SetOwnShadowActive(true);
		PtrDraw->SetTextureResource(L"Oreng_TX");
	}

	//変化
	void ShadowObject::OnUpdate() {
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
	}

	//物体の位置から、影の位置を導き出す
	Vec3 ShadowObject::ShadowLocation() {
		//実体ブロックのポジション
		auto ObjPos = m_Obj.GetComponent<Transform>()->GetPosition();
		//マルチライトを取得
		auto MultiLightPtr = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
		Vec3 LightPos;
		if (MultiLightPtr) {
			//メインライトを持ってくる
			auto mainIndex = MultiLightPtr->GetMainIndex();
			//メインライトのポジションを出す
			LightPos = MultiLightPtr->GetLight(mainIndex).m_Directional;
		}

		auto LightHeight = AddComponent<Shadowmap>()->GetLightHeight();
		//ライトの角度を出す
		auto AngleX = atan2(LightPos.x, LightPos.z);
		auto AngleY = atan2(LightPos.y, LightPos.z);

		//実体ブロックから壁までのY距離を単位変位値に乗算して、実体ブロックからの影のXYのずれを算出し代入
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * AngleX;
		m_kagePos.y = ObjPos.y - ObjPos.z * AngleY;
		m_kagePos.z = 0;

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
	//前の位置と今の位置を比べてVec3を返す
	Vec3 ShadowObject::GetPoorBefor() {
		//前のポジションと今のポジションの差を出す
		PoorBefor = ShadowLocation() - GetComponent<Transform>()->GetBeforePosition();
		//差を返す
		return PoorBefor;
	}
}