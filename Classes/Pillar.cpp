#include "Pillar.h"
USING_NS_CC;

Pillar::Pillar(cocos2d::Layer * pLayer, float randValue)
	:m_pLayer(pLayer)
{
	CCLOG("Created a pillar");

	m_pillarSprite= Sprite::create("pillar.png");
	m_pillarSprite->setContentSize(Size(m_pillarSprite->getContentSize().width*randValue, m_pillarSprite->getContentSize().height));
	m_pillarBody = PhysicsBody::createBox(m_pillarSprite->getContentSize());

	m_pillarBody->setDynamic(false);
	m_pillarSprite->setPhysicsBody(m_pillarBody);

	pLayer->addChild(m_pillarSprite);

	m_pStick = Stick::create();
	pLayer->addChild(m_pStick);
}

Pillar::~Pillar()
{
	m_pLayer->removeChild(m_pillarSprite);
	m_pLayer->removeChild(m_pStick);
	CCLOG("Deleted a pillar");
}

void Pillar::init(const cocos2d::Vec2 & pos)
{
	m_pillarSprite->setPosition(pos);
	auto&size = m_pillarSprite->getContentSize();
	m_pStick->setPosition(pos + Vec2(size.width / 2, size.height / 2));
}

bool Pillar::checkOnCamera(const cocos2d::Size & visibleSize, const cocos2d::Vec2 & camPos)
{
	auto&pos = m_pillarSprite->getPosition();
	auto size = m_pillarSprite->getContentSize();

	if (pos.x + size.width / 2+ m_pStick->getLength() < camPos.x - visibleSize.width / 2) 
		return false;

	if (pos.x - size.width / 2 > camPos.x + visibleSize.width / 2) 
		return false;
	

	/*if (pos.y + size.height / 2 < camPos.y - visibleSize.height / 2)
		return false;
	if (pos.y - size.height / 2 > camPos.y + visibleSize.height / 2)
		return false;*/

	return true;
}

