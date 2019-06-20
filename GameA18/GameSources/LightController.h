#pragma once
#include "stdafx.h"

namespace basecross {
	class LightController :public GameObject {
		//���C�g�̈ʒu
		Vec3 m_LightPosition;
		//���C�g�̊�{����
		float m_LightDistance;
		//���C�g�̍ő�p�x
		float m_MaxAngle;
		//���C�g�̊p�x
		Vec3 m_LightAngle;
		//���C�g������������
		float m_Speed;
		//�X�e�B�b�N��������Ƃ��̃X�s�[�h������
		Vec2 m_Lingering;

		bool SoundPlay;

		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;

	public:
		LightController(const shared_ptr<Stage>& StagePtr);
		virtual ~LightController() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}

		Vec3 GetLightAngle();
	};
}