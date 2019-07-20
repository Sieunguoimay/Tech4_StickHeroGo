#pragma once
#include"GameSprite.h"
class Character :public GameSprite{
public:
	~Character();
	static Character*createCharacter();
	void initCharacter();
	void update(float deltaTime)override;
	void MoveToTarget(const Vec2&target);
};
