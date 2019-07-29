#pragma once
#include"GameSprite.h"
#include"Stick.h"
#include"GameLayer.h"
#include"Followers.h"
class Pillar: public GameSprite{
	bool m_spawned;
	Stick*m_pStick;

	DrawNode*m_rect;
	float m_width1;
	float m_width2;

	Follower*m_pFollower;
public:
	static Pillar*createPillar(GameLayer*layer,bool hasNoRect = false);
	~Pillar()override;
	void initPillar(GameLayer*layer,const Vec2&pos,float scaleX, bool hasNoRect, int flagNumber);

	void setPosition(const Vec2&pos)override;

	//public usage
	bool HasDone();
	bool ReadyForSpawning();
	inline Stick*GetStick() const { return m_pStick; }
	inline const Vec2&GetTopRightPoint() { return _position + Vec2(_contentSize.width*_scaleX, _contentSize.height) / 2; }
	inline float GetWidth1()const { return m_width1; }
	inline float GetWidth2()const { return m_width2; }
	void RemoveRect();
	void SetFollower(Follower*pFollower);
	inline Follower*GetFollower(){ return m_pFollower; }
};
