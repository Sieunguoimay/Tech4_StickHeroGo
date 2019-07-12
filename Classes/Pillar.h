#pragma once
#include"cocos2d.h"
#include"Stick.h"

class Pillar {
public:
	Pillar(cocos2d::Layer*pLayer, float randValue = 1.0f);
	~Pillar();
	void init(const cocos2d::Vec2& pos);
	inline cocos2d::Sprite*getSprite() { return m_pillarSprite; }
	bool checkOnCamera(const cocos2d::Size& visibleSize, const cocos2d::Vec2& camPos);
	inline bool hasSpawnedOne() { return m_spawnedOne; }
	inline void setHasSpawnedOne(bool spawned) { m_spawnedOne = spawned; }
	inline Stick*getStick() { return m_pStick; }
private:
	bool m_spawnedOne = false;
	cocos2d::Layer*m_pLayer;
	cocos2d::Sprite*m_pillarSprite;
	cocos2d::PhysicsBody*m_pillarBody;

	//on each pillar stands a stick
	Stick*m_pStick;

};
