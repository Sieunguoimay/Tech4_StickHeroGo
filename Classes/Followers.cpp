#include "Followers.h"
#include"GameParticleSystem.h"
#include"utils/Definitions.h"
#include"Platform.h"
Followers::Followers(Platform* pParent, Character * pLeader)
	:m_pParent(pParent), m_pLeader(pLeader) 
{
	m_particleSystem = GameParticleSystem::createParticleSystem("particle_texture_smoke.png");
	m_particleSystem->SetColor(255, 200, 100)
		.SetMeanDistance(30.0f)
		.SetMeanTime(1.0f)
		.SetEmittingRate(200.0f)
		.SetDistanceVar(30.f);

	m_pParent->addChild(m_particleSystem,GAME_LAYER_2);
	CCLOG("Followers created");
}
Followers::~Followers()
{
	CCLOG("Followers deleted");
}

Follower * Followers::SpawnFollower()
{
	auto follower = Follower::createGameSpriteWithFrameName("dog_stand_0.png");
	m_pParent->addChild(follower);
	follower->setFlipX(true);
	return follower;
}

void Followers::AddFollower(Follower*follower, std::function<void()>callback)
{
	float currentSpace = m_pLeader->getPosition().x + m_pParent->getPosition().x;


	follower->setFlipX(false);

	follower->setPosition(m_pLeader->getPosition().x - currentSpace/(m_animals.size()+2),
		m_pLeader->getPosition().y-m_pLeader->GetHeight()/2+follower->GetHeight()/2);
	m_animals.push_back(follower);
	m_particleSystem->SetCallback(callback).Emit(0.1f,follower->getPosition());



	follower->addChild(SpriteBatchNode::create("dog_run.png"));
	follower->addChild(SpriteBatchNode::create("dog_stand.png"));

	//standing
	auto animation_stand = Animation::create();
	for (int i = 0; i < 7; i++) {
		auto s = String::createWithFormat("dog_stand_%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(s->getCString());
		animation_stand->addSpriteFrame(frame);
	}
	animation_stand->setDelayPerUnit(0.1f);
	animation_stand->setRestoreOriginalFrame(true);
	follower->m_animateActions[CS_STANDING] = RepeatForever::create(Animate::create(animation_stand));
	follower->m_animateActions[CS_STANDING]->retain();

	//running
	auto animation_run = Animation::create();
	for (int i = 0; i < 7; i++) {
		auto s = String::createWithFormat("dog_run_%d.png", i);
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
		float furtureSpace = m_pLeader->GetNextDistance() + m_pLeader->getPosition().x - m_pParent->GetFuturePosX();
		CCLOG("position %f", furtureSpace);
		for (int i = 0, n = m_animals.size(); i < n; i++) {
			auto& a = m_animals[i];
			a->stopAllActions();
			a->runAction(Sequence::create(DelayTime::create(0.1f*(n-i)),MoveTo::create(1.0f, Vec2(m_pLeader->getPosition().x+m_pLeader->GetNextDistance()-furtureSpace/(n+1)*(n-i),
				m_pLeader->getPosition().y - m_pLeader->GetHeight() / 2 + a->GetHeight() / 2)),

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

