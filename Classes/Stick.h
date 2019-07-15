#pragma once
#include"cocos2d.h"
class Stick:public cocos2d::DrawNode {
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
	Stick();

public:
	CREATE_FUNC(Stick);
	bool init()override;
	~Stick();

	inline cocos2d::DrawNode*getDrawer() { return this; }
	inline const bool& isFalling()const { return (m_state == FALLING); }
	inline const bool&hasFell()const { return (m_state == StickAnimationStates::FELL); }
	inline const bool&hasEnlogated()const { return (m_state == StickAnimationStates::ENLONGATED); }
	inline const float&getLength()const { return m_length; }

	inline void startEnlongating() { if(m_state == START) m_state = StickAnimationStates::ENLONGATING; }
	inline void stopEnlongating() { if (m_state == ENLONGATING) m_state = StickAnimationStates::ENLONGATED; }

	void update(float deltaTime);

	void fall();
};
