#pragma once
#include"GameLayer.h"
#include"GameSprite.h"
#include"GameParticleSystem.h"
#include <cocos-ext.h>
enum RewardType {
	ST_GOOD,
	ST_GREAT,
	ST_PERFECT,
	ST_TOTAL_NUM
};

class Reward :public GameLayer{
	Sprite* m_bg1;
	Sprite* m_bg2;
	Label* m_label;
	Label* m_labelPerfectScore;
public:
	CREATE_FUNC(Reward);
	void initReward(const char*name, const char*title);

	void Show(int perfectCount,int gainScore);
};


class OnScreenInfoDisplay :public GameLayer{
	Label* m_pTextScore;

	Label*m_pTextHistoryHigh;

	Reward* m_rewards[ST_TOTAL_NUM];

	GameParticleSystem* m_pStarParticleSystem;
public:
	CREATE_FUNC(OnScreenInfoDisplay);
	bool init()override;
	~OnScreenInfoDisplay()override;
	void SetScore(int score) { m_pTextScore->setString(std::to_string(score)); }
	void SetHistoryHigh(int highScore) { m_pTextHistoryHigh->setString(String::createWithFormat("History high %d", highScore)->getCString()); }
	void ShowRewardForEachPillar(int reward,int perfectCount,int gainScore);
};
