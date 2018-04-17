#pragma once
#include "stdafx.h"

namespace basecross {	
	class KeyItem : public GameObject {
		Vec3 m_KeyPos;
	public:
		KeyItem(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~KeyItem() {}
		//‰Šú‰»
		virtual void OnCreate() override;
	};
}