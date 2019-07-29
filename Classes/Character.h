#pragma once
#include"GameSprite.h"
enum CharacterState {
	CS_STANDING,
	CS_RUNNING,
	CS_STAND,
	CS_RUN,
	CS_FALL,
	CS_FALL_START,
	CS_FALLING,
	CS_DIED,
	CS_DONE
};
class Character :public GameSprite{
	float m_fallPoint;
	int m_state;
	MoveBy* m_moveAction;
	RepeatForever*m_animateActions[2];
	float m_xTarget;
public:
	~Character();
	static Character*createCharacter();
	void initCharacter();
	void update(float deltaTime)override;
	void MoveToTarget(float distance,float fallingDistance);
	inline int GetState()const { return m_state; }
	inline float GetXTarget()const { return _position.x+m_xTarget; }
};
