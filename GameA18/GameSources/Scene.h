/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;
		//--------------------------------------------------------------------------------------
		/*!
		@brief リソースの作成
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void CreateResourses();

		//ゲームステージの作成用変数
		int m_StageNumber=1;

		bool m_StartFlag;

		bool m_RespawnFlag;

		float StageCameraPosZ;
		float StageCameraAngle;
		bool m_PauseFlag;

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		void SetStageNumber(int n) {
			m_StageNumber = n;
		}

		int GetStageNumber() {
			return m_StageNumber;
		}

		void SetStartFlag(bool f) {
			m_StartFlag = f;
		}

		bool GetStartFlag() {
			return m_StartFlag;
		}

		void SetRespawnFlag(bool f) {
			m_RespawnFlag = f;
		}

		bool GetRespawnFlag() {
			return m_RespawnFlag;
		}

		void SetCameraPosZ(float p) {
			StageCameraPosZ = p;
		}

		float GetCameraPosZ() {
			return StageCameraPosZ;
		}

		void SetCameraAngle(float a) {
			StageCameraAngle = a;
		}

		float GetCameraAngle() {
			return StageCameraAngle;
		}

		bool GetPauseFlag() { return m_PauseFlag; }
		void SetPauseFlag(bool f) { m_PauseFlag = f; }
	};

}

//end basecross
