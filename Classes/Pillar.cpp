#include "Pillar.h"
#include"utils/Definitions.h"


Pillar * Pillar::createPillar(GameLayer*layer, bool hasNoRect)
{
	auto pillar = new Pillar();
	if (pillar&&pillar->initWithFile("pillar.png")) {
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
	layer->addChild(m_pStick);

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
		flag = Sprite::create("flag.png");
		flag->setPosition(Vec2(_contentSize.width / 2, _contentSize.height) + Vec2((flag->getContentSize().width-m_width1-7) / scaleX/ 2, flag->getContentSize().height / 2));
		this->addChild(flag);
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
}

void Pillar::setPosition(const Vec2 & pos)
{
	GameSprite::setPosition(pos);
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
