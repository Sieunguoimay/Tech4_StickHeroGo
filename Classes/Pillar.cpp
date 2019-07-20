#include "Pillar.h"

Pillar * Pillar::createPillar(GameLayer*layer)
{
	auto pillar = new Pillar();
	if (pillar&&pillar->initWithFile("pillar.png")) {
		pillar->initPillar(layer);
		pillar->autorelease();
		return pillar;
	}
	CC_SAFE_DELETE(pillar);
	return pillar;
}

Pillar::~Pillar()
{
	CCLOG("Pillar deleted");
}

void Pillar::initPillar(GameLayer*layer)
{
	m_spawned = false;
	m_pStick = Stick::createStick();
	layer->addChild(m_pStick);

	CCLOG("Pillar created %d",this->getChildrenCount());
}

void Pillar::setPosition(const Vec2 & pos)
{
	GameSprite::setPosition(pos);
	m_pStick->setPosition(this->GetTopRightPoint());
}


bool Pillar::HasDone()
{
	auto worldPos = getParent()->convertToWorldSpace(_position);
	if (worldPos.x +_contentSize.width/2 < 0) {
		CCLOG("One pillar off screen %f %f", worldPos.x, worldPos.y);
		return true;
	}
	return false;
}

bool Pillar::ReadyForSpawning()
{
	if (!m_spawned) {
		auto worldPos = getParent()->convertToWorldSpace(_position);
		if (worldPos.x -_contentSize.width/2 < m_visibleSize.width) {
			CCLOG("One pillar on screen %f %f", worldPos.x, worldPos.y);
			m_spawned = true;
			return true;
		}
	}
	return false;
}
