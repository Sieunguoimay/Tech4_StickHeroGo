#pragma once
#include"GameLayer.h"
#include"GameSprite.h"
#include"GameParticleSystem.h"
enum RewardType {
	ST_PERFECT,
	ST_GREAT,
	ST_GOOD,

	ST_PERFECT_BG,
	ST_GREAT_BG,
	ST_GOOD_BG,

	ST_TOTAL_NUM
};

class Reward :public GameSprite{
public:
	static Reward* createReward();
	void initReward();
};

class OnScreenInfoDisplay :public GameLayer{
	Label*m_pTextScore;
	Sprite* m_rewards[ST_TOTAL_NUM];
	GameParticleSystem* m_pStarParticleSystem;
public:
	CREATE_FUNC(OnScreenInfoDisplay);
	bool init()override;
	~OnScreenInfoDisplay()override;
	void SetScore(int score) { m_pTextScore->setString(std::to_string(score)); }
	void ShowRewardForEachPillar(int reward);
};
