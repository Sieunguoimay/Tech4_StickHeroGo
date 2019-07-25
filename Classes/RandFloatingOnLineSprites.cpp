#include "RandFloatingOnLineSprites.h"
#include"utils/Utils.h"



RandFloatingOnLineSprites* RandFloatingOnLineSprites::Create(float y, const char* file_name)
{
	auto s = new RandFloatingOnLineSprites();
	if (s && s->initWithFile(file_name)) {
		s->initFloatingOnLineSprites(y);
		s->autorelease();
		return s;
	}
	CC_SAFE_DELETE(s);
	return nullptr;
}

void RandFloatingOnLineSprites::initFloatingOnLineSprites(float y)
{
	m_y = y;
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_movingRatio = 0.4f;

	auto sprite = GameSprite::createGameSpriteWithTexture(this->getTexture());
	sprite->setPosition(Vec2(0,y)+ sprite->getContentSize()/2);
	this->addChild(sprite);
	m_sprites.push(sprite);

	CCLOG("RandFloatingOnLineSprites created %d %f",this->getChildrenCount(), CCRANDOM_0_1());
}

RandFloatingOnLineSprites::~RandFloatingOnLineSprites()
{
	CCLOG("RandFloatingOnLineSprites created");
}


void RandFloatingOnLineSprites::putSprite()
{
	if (m_sprites.size() == 0)return;
	float r_x = Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, m_sprites.back()->GetWidth() / 4, m_sprites.back()->GetWidth());
	auto sprite = GameSprite::createGameSpriteWithTexture(this->getTexture());
	sprite->setPosition(Vec2(m_sprites.back()->getPosition().x + r_x, m_y)+sprite->getContentSize() / 2);
	m_sprites.push(sprite);
	this->addChild(sprite);
}

void RandFloatingOnLineSprites::UpdatePosition(const Vec2& pos)
{
	this->setPosition(pos*m_movingRatio);


	auto front_pos = this->convertToWorldSpace(m_sprites.front()->getPosition());
	auto back_pos = this->convertToWorldSpace(m_sprites.back()->getPosition());
	if (front_pos.x + m_sprites.front()->getContentSize().width/2 < 0) {
		this->removeChild(m_sprites.front(), false);
		m_sprites.pop();
	}
	if (back_pos.x - m_sprites.back()->getContentSize().width / 2 < m_visibleSize.width) {
		//it's time to spawn new sprite
		putSprite();
	}
}

void RandFloatingOnLineSprites::ResetPosition()
{
	auto children = this->getChildren();
	for (auto& a : children)
		a->setPosition(a->getPosition() + Vec2(_position.x, 0.0f));
	this->setPosition(0.0f, m_y);
}
