#pragma once
#include"GameSprite.h"
class Character :public GameSprite{
	float m_fallPoint;
	bool m_fallNow;
	MoveBy* m_moveAction;
public:
	~Character();
	static Character*createCharacter();
	void initCharacter();
	void update(float deltaTime)override;
	void MoveToTarget(float distance,float fallingDistance);
};
