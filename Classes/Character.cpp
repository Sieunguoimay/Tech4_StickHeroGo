#include "Character.h"

Character::Character(Layer * pLayer)
	:m_pLayer(pLayer)
{
	m_sprite = Sprite::create("main_character.png");
	m_pLayer->addChild(m_sprite);
	CCLOG("Created player");
}

Character::~Character()
{
	m_pLayer->removeChild(m_sprite, true);
	CCLOG("Deleted player");
}

void Character::moveToNextPillar(Pillar * pPillar)
{
	auto action = MoveTo::create(1.0f, Vec2(
		pPillar->getSprite()->getPosition().x+pPillar->getSprite()->getContentSize().width/2-m_sprite->getContentSize().width/2,
		pPillar->getSprite()->getPosition().y + pPillar->getSprite()->getContentSize().height / 2 
		+ m_sprite->getContentSize().height / 2));
	m_sprite->runAction(action);
}

void Character::init(const Vec2 & pos)
{
	m_sprite->setPosition(pos);
}
