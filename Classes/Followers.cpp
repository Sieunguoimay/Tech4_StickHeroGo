#include "Followers.h"
#include"GameParticleSystem.h"
#include"utils/Definitions.h"
Followers::Followers(Node * pParent, Character * pLeader)
	:m_pParent(pParent), m_pLeader(pLeader) 
{
	m_particleSystem = GameParticleSystem::createParticleSystem("particle_texture_smoke.png");
	m_particleSystem->SetColor(255, 200, 100)
		.SetMeanDistance(70.0f)
		.SetMeanTime(1.0f)
		.SetEmittingRate(200.0f)
		.SetDistanceVar(70.f);

	m_pParent->addChild(m_particleSystem,GAME_LAYER_2);
	CCLOG("Followers created");
}
Followers::~Followers()
{
	CCLOG("Followers deleted");
}

Follower * Followers::SpawnFollower()
{
	auto follower = Follower::createGameSpriteWithFrameName("main_character.png");
	m_pParent->addChild(follower);
	return follower;
}

void Followers::AddFollower(Follower*follower, std::function<void()>callback)
{
	follower->setPosition(m_pLeader->getPosition().x - follower->getContentSize().width, m_pLeader->getPosition().y);
	m_animals.push_back(follower);
	m_particleSystem->SetCallback(callback).Emit(0.1f,follower->getPosition());

	follower->addChild(SpriteBatchNode::create("main_character_run.png"));
	follower->addChild(SpriteBatchNode::create("main_character_stand.png"));

	//standing
	auto animation_stand = Animation::create();
	for (int i = 0; i < 6; i++) {
		auto s = String::createWithFormat("main_character_stand_%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(s->getCString());
		animation_stand->addSpriteFrame(frame);
	}
	animation_stand->setDelayPerUnit(0.1f);
	animation_stand->setRestoreOriginalFrame(true);
	follower->m_animateActions[CS_STANDING] = RepeatForever::create(Animate::create(animation_stand));
	follower->m_animateActions[CS_STANDING]->retain();

	//running
	auto animation_run = Animation::create();
	for (int i = 0; i < 8; i++) {
		auto s = String::createWithFormat("main_character_run_%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(s->getCString());
		animation_run->addSpriteFrame(frame);
	}
	animation_run->setDelayPerUnit(0.1f);
	animation_run->setRestoreOriginalFrame(true);
	follower->m_animateActions[CS_RUNNING] = RepeatForever::create(Animate::create(animation_run));
	follower->m_animateActions[CS_RUNNING]->retain();

}

void Followers::Update(float deltaTime)
{
	if (m_pLeader->GetState() == CS_RUN) {
		for (auto&a : m_animals) {
			a->stopAllActions();
			a->runAction(Sequence::create(MoveTo::create(1.0f, Vec2(m_pLeader->GetXTarget() - a->getContentSize().width, a->getPosition().y)),
				CallFunc::create([this,a]() {
					a->stopAllActions();
					a->runAction(a->m_animateActions[CS_STANDING]);
			}),nullptr));
			a->runAction(a->m_animateActions[CS_RUNNING]);
		}
	}
	else if (m_pLeader->GetState() == CS_STAND) {
		CCLOG("Followers: stand now");
	}
}

