#pragma once
#include"cocos2d.h"
#include"Pillar.h"
USING_NS_CC;
class Character {
	Layer*m_pLayer;
	Sprite*m_sprite;
public:
	Character(Layer*pLayer);
	~Character();

	void moveToNextPillar(Pillar*pPillar);
	void init(const Vec2&pos);
	inline Sprite*getSprite() const { return m_sprite; }
};
