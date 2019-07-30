#pragma once
#include"GameLayer.h"
#include"Character.h"

struct Follower :public GameSprite{
	CREATE_GAME_SPRITE_WITH_FRAME_NAME(Follower);
	RepeatForever* m_animateActions[2];
};

class Followers {
	class Platform*m_pParent;
	Character*m_pLeader;

	std::vector<Follower*>m_animals;
	class GameParticleSystem*m_particleSystem;
public:
	Followers(Platform*pParent, Character*pLeader, int initialNum, float initialSpace);
	~Followers();
	
	Follower* SpawnFollower();
	void AddFollower(Follower*follower, std::function<void()>callback, float initialSpace = -1.0f);
	void Update(float deltaTime);
	int GetFollowerNum()const { return m_animals.size(); }
};