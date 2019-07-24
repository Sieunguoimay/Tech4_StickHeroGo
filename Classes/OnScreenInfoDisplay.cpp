#include "OnScreenInfoDisplay.h"
#include"utils/Definitions.h"


void Reward::initReward(const char* name, const char* title) {
	m_bg1 = Sprite::create((std::string(name)+".png").c_str());
	m_bg2 = Sprite::create((std::string(name) + "_2.png").c_str());
	m_label = Label::createWithSystemFont(title, "Calibri", 30.0f);
	m_labelPerfectScore = Label::createWithSystemFont("x2 +24", "Calibri", 20.0f);

	this->addChild(m_bg1, GAME_LAYER_0);
	this->addChild(m_bg2, GAME_LAYER_NEG_1);
	m_bg1->addChild(m_label);
	m_bg1->addChild(m_labelPerfectScore);
	m_bg1->setCascadeOpacityEnabled(true);

	m_label->setPosition(Vec2(0.0f, m_label->getContentSize().height / 2) + m_bg1->getContentSize() / 2);
	m_labelPerfectScore->setPosition(Vec2(0.0f, -m_label->getContentSize().height / 2) + m_bg1->getContentSize() / 2);

	this->setPosition(m_visibleSize.width / 2, m_visibleSize.height * 5.0f / 8.0f);

	m_bg1->setVisible(false);
	m_bg2->setVisible(false);
}


void Reward::Show(int perfectCount, int gainScore) {

	m_bg1->setVisible(true);
	m_bg2->setVisible(true);

	m_bg1->setOpacity(255);
	m_bg2->setOpacity(255);

	m_bg2->setRotation(0.0f);
	m_bg2->setScale(1.1f);


	m_bg1->runAction(Sequence::create(
		ScaleTo::create(0.05f, 1.4f),
		ScaleTo::create(0.2f, 1.0f),
		DelayTime::create(0.2f),
		FadeTo::create(1.0f, 0),
		CallFunc::create([this]() {
			m_bg1->setVisible(false); })
		, nullptr));

	m_bg2->runAction(Spawn::create(
		RotateBy::create(1.45f, 180.0f),
		Sequence::create(
			DelayTime::create(1.0f),
			Spawn::create(
				FadeTo::create(0.45f, 0.0f),
				ScaleTo::create(0.45f, 0.8f),
				nullptr),
			CallFunc::create([this]() {
				m_bg2->setVisible(false);
				})
			, nullptr), nullptr
	));

	CCLOG("perfectCount %d", perfectCount);

	char s[10];
	if(perfectCount>0)
		sprintf(s, "x%d +%d", perfectCount, gainScore);
	else
		sprintf(s, "+%d", gainScore);
	m_labelPerfectScore->setString(s);

}







bool OnScreenInfoDisplay::init()
{
	if (!Layer::init())return false;

	m_pTextScore = Label::createWithSystemFont("0", "Calibri", 30.0f);
	this->addChild(m_pTextScore);
	m_pTextScore->setPosition(m_visibleSize.width / 2, m_visibleSize.height * 0.8f);


	m_rewards[ST_PERFECT] = Reward::create();
	m_rewards[ST_PERFECT]->initReward("reward_perfect", "PERFECT");
	this->addChild(m_rewards[ST_PERFECT]);


	m_rewards[ST_GREAT] = Reward::create();
	m_rewards[ST_GREAT]->initReward("reward_great", "GREAT");
	this->addChild(m_rewards[ST_GREAT]);

	m_rewards[ST_GOOD] = Reward::create();
	m_rewards[ST_GOOD]->initReward("reward_good", "GOOD");
	this->addChild(m_rewards[ST_GOOD]);


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

void OnScreenInfoDisplay::ShowRewardForEachPillar(int reward, int perfectCount, int gainScore)
{
	m_pStarParticleSystem->Emit(0.2f, m_rewards[ST_PERFECT]->getPosition());
	if(reward<ST_TOTAL_NUM) m_rewards[reward]->Show(perfectCount,gainScore);


}
