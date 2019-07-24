#include "OnScreenInfoDisplay.h"
#include"utils/Definitions.h"

Reward* Reward::createReward() {
	auto reward = new Reward();
	if (reward && reward->initWithFile("reward_perfect.png")) {
		reward->initReward();
		reward->autorelease();
		return reward;
	}
	CC_SAFE_DELETE(reward);
	return NULL;
}
void Reward::initReward() {

}


bool OnScreenInfoDisplay::init()
{
	if (!Layer::init())return false;

	m_pTextScore = Label::createWithSystemFont("0", "Calibri", 30.0f);
	this->addChild(m_pTextScore);
	m_pTextScore->setPosition(m_visibleSize.width / 2, m_visibleSize.height * 0.8f);


	m_rewards[ST_PERFECT] = Sprite::create("reward_perfect.png");
	m_rewards[ST_PERFECT_BG] = Sprite::create("reward_perfect_2.png");
	this->addChild(m_rewards[ST_PERFECT],GAME_LAYER_1);
	this->addChild(m_rewards[ST_PERFECT_BG], GAME_LAYER_0);
	m_rewards[ST_PERFECT]->setPosition(m_visibleSize.width / 2, m_visibleSize.height * 5.0f / 8.0f);
	m_rewards[ST_PERFECT_BG]->setPosition(m_visibleSize.width / 2, m_visibleSize.height * 5.0f / 8.0f);
	m_rewards[ST_PERFECT]->setVisible(false);
	m_rewards[ST_PERFECT_BG]->setVisible(false);


	m_pStarParticleSystem = GameParticleSystem::createParticleSystemByType(PS_STARS);
	m_pStarParticleSystem->SetSize(20.0f).SetScaleVar(1.8f).SetMeanDistance(70.0f);
	this->addChild(m_pStarParticleSystem);

	CCLOG("OnScreenInfoDisplay created");
	return true;
}

OnScreenInfoDisplay::~OnScreenInfoDisplay()
{
	CCLOG("OnScreenInfoDisplay deleted");
}

void OnScreenInfoDisplay::ShowRewardForEachPillar(int reward)
{
	m_pStarParticleSystem->Emit(0.2f, m_rewards[ST_PERFECT]->getPosition());

	m_rewards[ST_PERFECT]->setVisible(true);
	m_rewards[ST_PERFECT_BG]->setVisible(true);
	m_rewards[ST_PERFECT]->setOpacity(255);

	m_rewards[ST_PERFECT_BG]->setOpacity(255);
	m_rewards[ST_PERFECT_BG]->setRotation(0.0f);
	m_rewards[ST_PERFECT_BG]->setScale(1.0f);

	m_rewards[ST_PERFECT]->runAction(Sequence::create(
		ScaleTo::create(0.05f,1.4f),
		ScaleTo::create(0.2f,1.0f),
		DelayTime::create(0.2f),
		FadeTo::create(1.0f, 0),
		CallFunc::create([this]() {
			m_rewards[ST_PERFECT]->setVisible(false);
			}), nullptr
	));
	m_rewards[ST_PERFECT_BG]->runAction(Spawn::create(
		RotateBy::create(1.45f, 180.0f),
		Sequence::create(
			DelayTime::create(1.0f),
			Spawn::create(
				FadeTo::create(0.45f, 0.0f),
				ScaleTo::create(0.45f, 0.8f),
				nullptr),
			CallFunc::create([this]() {
				m_rewards[ST_PERFECT_BG]->setVisible(false);
				})
			,nullptr),nullptr
	));

}
