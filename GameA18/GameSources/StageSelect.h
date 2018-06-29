#pragma once
#include "stdafx.h"

namespace basecross
{
	class StageSelect : public Stage
	{
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();
		//枠の作成
		void CreateFrame();

		//フェードの作成
		void CreateFadeOutSprite();
		void CreateFadeSprite();
		bool m_SelectFlag;

		//ドア
		void CreateDoor();
		//ステージ番号の作成
		void StageNumberSprite();

		int m_StageNumber;
		bool onectrl;

		int m_MaxStageNumber;
		
		float m_CoolTime;
		wstring DataDir;

	public:
		//構築と破棄
		StageSelect() :Stage() {}
		virtual ~StageSelect() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}
	};

	//--------------------------------------------------------------------------------------
	//	Door
	//--------------------------------------------------------------------------------------
	class StageSelectDoor : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//スケールのZの固定値
		float m_ScaleZ;
		//自身の番号を持つ
		wstring m_DoorNum;
		//このオブジェクトのみで使用するスクエアメッシュ
		shared_ptr<MeshResource> m_SquareMeshResource;
		Mat4x4 m_ToAnimeMatrix;

		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;

		bool m_SelectFlag;
		bool m_OpenFlag;
		bool m_RemoveFlag;
		float m_RemoveTime = 0.0f;
	public:
		//構築と破棄
		StageSelectDoor(const shared_ptr<Stage>& StagePtr,
			const wstring BaseDir,
			const Vec3& Scale,
			const Vec3& Position,
			const Vec3& Rotation,
			const wstring DoorNum
			);

		virtual ~StageSelectDoor();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate();
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}
		virtual void OnUpdate2();

		void SetSelectFlag(bool f) { m_SelectFlag = f; }
		bool GetSelectFlag() { return m_SelectFlag; }

		void SetRemoveFlag(bool f) { m_RemoveFlag = f; }
		//扉の大きさ変え
		float deflection = 0.001f;

		void Open();
		void StyleChange();
	};
}