#pragma once
#include"GameSprite.h"
#include"Platform.h"
class Wave :public GameLayer,public MoveAlongCallback{
	std::vector<Sprite*>m_pSprites;
	std::string path;
	float m_angle;
	float m_oscillationSpeed;
	float m_oscillationRangeRatio;
	float m_movingRatio;
public:
	static Wave*createWave(const char*path, float oscillationSpeed,float m_oscillationRangeRatio, float movingRatio);
	void initWave();
	~Wave();
	void update(float deltaTime)override;

	virtual void UpdatePosition(const Vec2&pos)override ;
	virtual void ResetPosition()override ;

	inline void SetOscillationSpeed(float oscillationSpeed) { m_oscillationSpeed = oscillationSpeed; }
};