#pragma once
#include"GameLayer.h"
#include"GameSprite.h"
#include"utils/List.h"
#include"Platform.h"

class Clouds :public SpriteBatchNode, public MiscSupport, public MoveAlongCallback {
	List<GameSprite*>m_clouds;
	void generateClouds(const Vec2&offset);
	float m_selfMovement;
	float m_floatingSpeed;
public:

	//Implementation of GameLayer
	static Clouds*createClouds();
	~Clouds()override;
	void initClouds();
	void update(float deltaTime)override;

	//Implementation of MoveAlongCallback
	void UpdatePosition(const Vec2&pos)override;
	void ResetPosition()override;
};