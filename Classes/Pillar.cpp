#include "Pillar.h"
#include"utils/Definitions.h"


Pillar * Pillar::createPillar(GameLayer*layer, bool hasNoRect)
{
	auto pillar = new Pillar();
	if (pillar&&pillar->initWithSpriteFrameName("pillar.png")) {
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

void Pillar::initPillar(GameLayer*layer, const Vec2&pos, float scaleX, bool hasNoRect, int flagNumber)
{

	m_spawned = false;
	m_pStick = Stick::createStick();
	layer->addChild(m_pStick,GAME_LAYER_1);

	this->setPosition(pos);
	
	m_width1 = 10;
	m_width2 = 20;
	if(!hasNoRect){
		m_rect = DrawNode::create();
		m_rect->drawSolidRect(Vec2(-m_width2, -4), Vec2(m_width2, 0), Color4F(1.0f, 1.0f, 0.0f, 1.0f));
		m_rect->drawSolidRect(Vec2(-m_width1, -4), Vec2(m_width1, 0), Color4F(1.0f, 0.5f, 0.0f, 1.0f));
		m_rect->setPosition(Vec2(GetWidth() / 2, GetHeight()));
		this->addChild(m_rect);
	}else m_rect = nullptr;

	
	Sprite* flag = nullptr;
	if (flagNumber>0&&flagNumber%10==0) {
		flag = Sprite::createWithSpriteFrameName("flag.png");
		flag->setPosition(Vec2(_contentSize.width / 2, _contentSize.height) + Vec2((flag->getContentSize().width-m_width1-7) / scaleX/ 2, flag->getContentSize().height / 2));
		this->addChild(flag,GAME_LAYER_1);
		auto* label = Label::createWithSystemFont(std::to_string(flagNumber), GAME_TEXT_FONT,15);
		flag->addChild(label);
		label->setPosition(-Vec2(49, 44)+flag->getContentSize());
	}

	this->setScaleX(scaleX);
	if(m_rect!=nullptr) m_rect->setScaleX(1.0f / _scaleX);
	if (flag != nullptr) {
		flag->setScaleX(1.0f / _scaleX);
	}
	m_pStick->setPosition(this->GetTopRightPoint().x - 5.0f,this->GetTopRightPoint().y);
	m_ruler = nullptr;

}

void Pillar::setPosition(const Vec2 & pos)
{
	GameSprite::setPosition(pos);
}

void Pillar::AddRuler(float length)
{
	m_ruler = DrawNode::create();

	float segmentLength = 10;
	float segmentMargin = 5;
	int n = length / (segmentLength+ segmentMargin);
	for (int i = 0; i < n+1; i++) {
		m_ruler->drawSolidRect(Vec2(0, length-i*(segmentLength + segmentMargin)- segmentMargin),
			Vec2(5,length- std::min(i * (segmentLength + segmentMargin)+ segmentLength,length)- segmentMargin),
			Color4F(1.0f, 1.0f, 1.0f, 0.8f));
	}
	
	m_ruler->drawSolidRect(Vec2(-segmentLength+2.5f, length), Vec2(segmentLength + 2.5f, length+5), Color4F(1.0f, 1.0f, 1.0f, 0.8f));

	m_ruler->setPosition(m_pStick->getPosition());
	m_pStick->getParent()->addChild(m_ruler);

	m_ruler->setOpacity(0);
	m_ruler->runAction(FadeTo::create(0.3f, 255));
}

void Pillar::RemoveRuler()
{
	if(m_ruler!=nullptr)
		m_ruler->runAction(FadeTo::create(0.3f, 0));
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

void Pillar::RemoveRect()
{
	if(m_rect!=nullptr)
		m_rect->runAction(Sequence::create(
			FadeTo::create(0.5f, 0.0f),
			CallFunc::create([this]() {
				this->removeChild(m_rect, false);
			}), nullptr
		));
}

void Pillar::SetFollower(Follower * pFollower)
{
	m_pFollower = pFollower;
	if(m_pFollower!=nullptr)
		m_pFollower->setPosition(_position.x, _position.y + _contentSize.height / 2+m_pFollower->getContentSize().height/2);
}
