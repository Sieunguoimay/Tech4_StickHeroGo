#include "Wave.h"
#include"utils/Utils.h"
Wave * Wave::createWave(const char * path, float oscillationSpeed, float oscillationRangeRatio, float movingRatio)
{
	auto wave = new Wave();
	if (wave&&wave->initWithFile(path)) {
		wave->m_oscillationSpeed = oscillationSpeed;
		wave->m_movingRatio = movingRatio;
		wave->m_oscillationRangeRatio = oscillationRangeRatio;
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

	for (int i = 0; i < 3; i++) {
		auto sprite = GameSprite::createGameSpriteWithTexture(this->getTexture());
		this->addChild(sprite);
		sprite->setPosition(i==0
			? (-Vec2(0.0f, 2.0f) +sprite->getContentSize() / 2 )
			: (m_pSprites.back()->getPosition() + Vec2(m_pSprites.back()->GetWidth(), 0.0f)));
		m_pSprites.push_back(sprite);
	}

	m_angle = 0.0f;
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
	float scale = Utils::map(std::cos(CC_DEGREES_TO_RADIANS(m_angle)),-1.0f,1.0f
		,1.0f- m_oscillationRangeRatio/2.0f,1.0f+ m_oscillationRangeRatio/2.0f);
	this->setScaleY(scale);
}

void Wave::UpdatePosition(const Vec2 & pos)
{
	this->setPosition(pos*m_movingRatio);

	auto leftMostSprite = *m_pSprites.begin();
	auto topRight = this->convertToWorldSpace(leftMostSprite->getPosition() + leftMostSprite->GetSize()/2);
	if (topRight.x < 0) {
		leftMostSprite->setPosition(m_pSprites.back()->getPosition() + Vec2(m_pSprites.back()->GetWidth(), 0.0f));
		m_pSprites.erase(m_pSprites.begin());
		m_pSprites.push_back(leftMostSprite);
	}


	//if (this->convertToWorldSpace(m_pSprite1->getPosition()).x + m_pSprite1->GetWidth() / 2 < 0) {
	//	m_pSprite1->setPosition(m_pSprite2->getPosition() + Vec2(m_pSprite2->GetWidth(), 0.0f));
	//}
	//if (this->convertToWorldSpace(m_pSprite2->getPosition()).x + m_pSprite2->GetWidth() / 2 < 0) {
	//	m_pSprite2->setPosition(m_pSprite1->getPosition() + Vec2(m_pSprite1->GetWidth(), 0.0f));
	//}

}

void Wave::ResetPosition()
{
	for(auto&sprite:m_pSprites)
		sprite->setPosition(sprite->getPosition() + Vec2(_position.x,0.0f));

	this->setPosition(0.0f, _position.y);
}
