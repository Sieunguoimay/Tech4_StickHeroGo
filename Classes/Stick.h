#pragma once
#include"cocos2d.h"
class Stick {
	const float m_enLongatingSpeed = 120.0f;
	const float m_maxLength = 500;
	float m_length;

	enum StickAnimationStates {
		START,
		ENLONGATING,
		ENLONGATED,
		FALLING,
		FELL,
		DONE
	};
	StickAnimationStates m_state = StickAnimationStates::START;
	cocos2d::Layer*m_pLayer;
	cocos2d::DrawNode*m_drawer;
public:
	Stick(cocos2d::Layer*pLayer);
	~Stick();

	inline cocos2d::DrawNode*getDrawer()const { return m_drawer; }
	inline const bool&hasFell()const { return (m_state == StickAnimationStates::FELL); }
	inline const bool&hasEnlogated()const { return (m_state == StickAnimationStates::ENLONGATED); }
	inline const float&getLength()const { return m_length; }

	inline void startEnlongating() { m_state = StickAnimationStates::ENLONGATING; }
	inline void stopEnlongating() { m_state = StickAnimationStates::ENLONGATED; }

	void update(float deltaTime);

	void fall();
};
