#pragma once
#include"GameLayer.h"
#include"Character.h"

struct Follower :public GameSprite{
	CREATE_GAME_SPRITE_WITH_FRAME_NAME(Follower);
	RepeatForever* m_animateActions[2];
};

class Followers {
	Node*m_pParent;
	Character*m_pLeader;

	std::vector<Follower*>m_animals;
	class GameParticleSystem*m_particleSystem;
public:
	Followers(Node*pParent, Character*pLeader);
	~Followers();
	
	Follower* SpawnFollower();
	void AddFollower(Follower*follower, std::function<void()>callback);
	void Update(float deltaTime);
};