#include "GameParticleSystem.h"
#include"utils/Utils.h"
#include"utils/Definitions.h"
GameParticleSystem* GameParticleSystem::s_instances[PS_TOTAL_NUM] = { nullptr };
Layer*GameParticleSystem::s_pParentLayer = nullptr;

GameParticleSystem * GameParticleSystem::GetInstance(int type)
{
	if (type > PS_TOTAL_NUM) return nullptr;
	if (s_instances[type] == nullptr) {
		switch (type) {
		case PS_STARS: 
			s_instances[type] = createParticleSystem("particle_texture.png");
			break;
		case PS_SMOKE:
			s_instances[type] = createParticleSystem("particle_texture_smoke.png");
			break;
		case PS_WATER:
			s_instances[type] = createParticleSystem("particle_texture_water.png");
			break;
		}
		s_pParentLayer->addChild(s_instances[type]);
		s_instances[type]->setGlobalZOrder(GAME_LAYER_2);
	}
	return s_instances[type];
}

void GameParticleSystem::CleanUp()
{
	for (int i = 0; i < PS_TOTAL_NUM; i++) {
		s_pParentLayer->removeChild(s_instances[i], true);
		s_instances[i] = nullptr;
	}
}





GameParticleSystem * GameParticleSystem::createParticleSystem(const char * source_texture)
{
	auto particleSystem = new GameParticleSystem();
	if (particleSystem&&particleSystem->initWithFile(source_texture)) {
		particleSystem->initParticleSystem();
		particleSystem->autorelease();
		return particleSystem;
	}
	CC_SAFE_DELETE(particleSystem);
	return nullptr;
}

void GameParticleSystem::initParticleSystem()
{
	this->scheduleUpdate();
	m_meanTime = 1.0f;
	m_meanDistance = 100.0f;
	m_colorOverlay = Color3B(255,255,255);
	m_angleDirStart = 0.0f;
	m_angleDirEnd = 360.0f;
	m_size = 20.0f;
	m_emittingRate = Director::getInstance()->getFrameRate();
	m_distanceVar = 20.0f;
	m_callback = nullptr;
	m_state = PSS_IDLE;
	CCLOG("ParticleSystem created");
}

GameParticleSystem::~GameParticleSystem()
{
	CCLOG("ParticleSystem deleted");
}



void GameParticleSystem::update(float deltaTime)
{
	if (m_state = PSS_EMIT) {
		int n = std::max((int)(deltaTime* m_emittingRate),1);

		if (m_emittingDuration > 0) {
			m_emittingDuration = std::max(m_emittingDuration-deltaTime,0.0f);
			for(int i = 0; i<n; i++)
				putParticle();
		}
		else {
			m_state = PSS_EMITTED;
		}
	}

	if (m_state == PSS_EMITTED&&this->getChildrenCount() == 0) {
		m_state = PSS_IDLE;
		if (m_callback != nullptr) {
			m_callback();
			m_callback = nullptr;
		}
	}
}

void GameParticleSystem::Emit(float duration, const Vec2&pos)
{
	m_emittingDuration = duration;
	m_state = PSS_EMIT;
	m_pos = pos;
	m_emittingRate = std::max(Director::getInstance()->getFrameRate(),m_emittingRate);
}


void GameParticleSystem::putParticle()
{

	float timeVar = 0.5f;

	float r_time = Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, m_meanTime - timeVar / 2, m_meanTime + timeVar / 2);
	float r_distance = Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, m_meanDistance- m_distanceVar / 2, m_meanDistance + m_distanceVar / 2);
	float r_angleDir = Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, m_angleDirStart , m_angleDirEnd);
	float r_pos = Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, 0.0f, 20.0f);
	float r_scale = Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, 0.5f, 1.2f);


	Vec2 dir(std::cos(CC_DEGREES_TO_RADIANS(r_angleDir)), std::sin(CC_DEGREES_TO_RADIANS(r_angleDir)));


	Particle*p = Particle::createGameSpriteWithTexture(this->getTexture());
	p->setPosition(m_pos+ dir*r_pos);
	p->setScale(r_scale*m_size / p->getContentSize().width);
	p->setColor(m_colorOverlay);

	auto moveBy = MoveBy::create(r_time, dir*r_distance);
	auto easeOut = EaseOut::create(moveBy,1.5f);
	p->runAction(Sequence::create(
		Spawn::create(
			easeOut,
			FadeTo::create(r_time, 0.5f), nullptr),
		CallFunc::create([this,p]() {
			removeChild(p,false);
		}),nullptr
	));
	this->addChild(p);

}