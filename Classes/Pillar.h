#pragma once
#include"GameSprite.h"
#include"Stick.h"
#include"GameLayer.h"
class Pillar: public GameSprite{
	bool m_spawned;
	Stick*m_pStick;
public:
	static Pillar*createPillar(GameLayer*layer);
	~Pillar()override;
	void initPillar(GameLayer*layer);
	void setPosition(const Vec2&pos)override;

	//public usage
	bool HasDone();
	bool ReadyForSpawning();
	inline Stick*GetStick() const { return m_pStick; }
	inline const Vec2&GetTopRightPoint() { return _position + Vec2(_contentSize.width*_scaleX, _contentSize.height) / 2; }
};
