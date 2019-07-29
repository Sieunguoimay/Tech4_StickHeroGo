#pragma once
#include"cocos2d.h"
USING_NS_CC;

enum {
	START,
	ENLONGATING,
	ENLONGATED,
	FALLING,
	FELL,
	DONE
};

class Stick:public DrawNode {
	CREATE_FUNC(Stick);
	
	
	const float m_enLongatingSpeed = 120.0f;
	const float m_maxLength = 500;
	float m_length;
	int m_state;

public:
	static Stick*createStick();
	bool init()override;
	~Stick();

	void update(float deltaTime);
	inline void SetState(int state) { if(m_state !=DONE) m_state = state; }
	inline int GetState() { return m_state; }
	inline float GetLength() { return m_length; }
	
};
