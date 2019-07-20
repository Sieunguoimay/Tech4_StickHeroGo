#pragma once
#include"GameSprite.h"
#include"Platform.h"
class Wave :public SpriteBatchNode, public MiscSupport,public MoveAlongCallback{
	GameSprite*m_pSprite1;
	GameSprite*m_pSprite2;
	float m_angle;
	float m_oscillationSpeed;
public:
	static Wave*createWave(const char*path);
	void initWave();
	~Wave();
	void update(float deltaTime)override;

	virtual void UpdatePosition(const Vec2&pos)override ;
	virtual void ResetPosition()override ;

};