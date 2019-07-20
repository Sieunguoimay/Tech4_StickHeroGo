#include "Wave.h"
#include"utils/Utils.h"
Wave * Wave::createWave(const char * path)
{
	auto wave = new Wave();
	if (wave&&wave->initWithFile(path)) {
		wave->initWave();
		wave->autorelease();
		return wave;
	}
	CC_SAFE_DELETE(wave);
	return nullptr;
}

void Wave::initWave()
{
	this->scheduleUpdate();

	m_pSprite1 = GameSprite::createGameSpriteWithTexture(this->getTexture());
	this->addChild(m_pSprite1);
	m_pSprite1->setPosition(m_pSprite1->getContentSize() / 2);
	m_pSprite2 = GameSprite::createGameSpriteWithTexture(this->getTexture());
	this->addChild(m_pSprite2);
	m_pSprite2->setPosition(m_pSprite1->getPosition() + Vec2(m_pSprite1->GetWidth(), 0.0f));

	m_angle = 0.0f;
	m_oscillationSpeed = 90.0f;
	CCLOG("Wave Created");
}

Wave::~Wave()
{
	CCLOG("Wave Deleted");
}

void Wave::update(float deltaTime)
{
	m_angle += m_oscillationSpeed*deltaTime;
	if (m_angle >= 360.0f)m_angle = 0.0f;
	float scale = Utils::map(std::cos(CC_DEGREES_TO_RADIANS(m_angle)),-1.0f,1.0f,0.6f,1.4f);
	this->setScaleY(scale);
}

void Wave::UpdatePosition(const Vec2 & pos)
{
	this->setPosition(pos);

	if (this->convertToWorldSpace(m_pSprite1->getPosition()).x + m_pSprite1->GetWidth() / 2 < 0) {
		m_pSprite1->setPosition(m_pSprite2->getPosition() + Vec2(m_pSprite2->GetWidth(), 0.0f));
	}
	if (this->convertToWorldSpace(m_pSprite2->getPosition()).x + m_pSprite2->GetWidth() / 2 < 0) {
		m_pSprite2->setPosition(m_pSprite1->getPosition() + Vec2(m_pSprite1->GetWidth(), 0.0f));
	}

}

void Wave::ResetPosition()
{
	m_pSprite1->setPosition(m_pSprite1->getPosition() + Vec2(_position.x,0.0f));
	m_pSprite2->setPosition(m_pSprite2->getPosition() + Vec2(_position.x, 0.0f));
	this->setPosition(0.0f, _position.y);
}
