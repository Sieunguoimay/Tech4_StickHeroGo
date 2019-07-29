#pragma once
#include"GameSprite.h"
class Particle: public GameSprite{
	float m_timeToLive;
public:
	CREATE_GAME_SPRITE_WITH_FRAME_NAME(Particle);
	void initGameSprite()override;
	~Particle()override;
	
	float Update(float deltaTime);


	inline void SetTimeToLive(float time) { m_timeToLive = time; }
};