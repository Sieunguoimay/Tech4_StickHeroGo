#include "Clouds.h"
#include"utils/Utils.h"

Clouds * Clouds::createClouds()
{
	auto cloud = new Clouds();
	if (cloud) {
		cloud->path = "cloud.png";
		cloud->initClouds();
		cloud->autorelease();
		return cloud;
	}
	CC_SAFE_DELETE(cloud);
	return nullptr;
}

Clouds::~Clouds()
{
	CCLOG("Clouds Layer Deleted");
}

void Clouds::initClouds()
{
	this->scheduleUpdate();
    this->setContentSize(Director::getInstance()->getVisibleSize());
    
	for (int i = 0; i < 5; i++)
		generateClouds(Vec2(0.0f,0.0f));
	
	m_floatingSpeed = 4.0f;
	m_selfMovement = 0;
	this->m_movingRatio = 0.4f;
	CCLOG("Clouds Layer Created");
}

void Clouds::update(float deltaTime)
{
    
	m_selfMovement += m_floatingSpeed * deltaTime;
    
	for (auto it = m_clouds.first(); it != m_clouds.tail; it = it->next) {
		auto pos = this->convertToWorldSpace(it->data->getPosition());
        CCLOG("positionX : %f",pos.x);
		auto size = it->data->GetSize();
        CCLOG("size.width : %f",size.width);
		if (pos.x - size.width / 2 < 0) {
			//this->removeChild(it->data,true);
			it = m_clouds.erase(it);
            
			generateClouds(Vec2(-_position.x+m_visibleSize.width,0.0f));
            
		}
	}
}

void Clouds::UpdatePosition(const Vec2 & pos)
{
	if (m_selfMovement > 10000) {
		for (auto it = m_clouds.first(); it != m_clouds.tail; it = it->next)
			it->data->setPosition(it->data->getPosition() - Vec2(m_selfMovement, 0));
		m_selfMovement = 0;
	}
	this->setPosition(pos.x*m_movingRatio-m_selfMovement,_position.y);
}

void Clouds::ResetPosition()
{
	for (auto it = m_clouds.first(); it != m_clouds.tail; it = it->next)
		it->data->setPosition(it->data->getPosition() + Vec2(_position.x+ m_selfMovement, 0));
	this->setPosition(0, _position.y);
}

void Clouds::generateClouds(const Vec2&offset)
{
	Vec2 r_pos(
		Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, 0.0f, 1.0f)*m_visibleSize.width,
		Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, 0.5f, 1.0f)*m_visibleSize.height);

	float r_scale = Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, 0.3f, 1.2f);

	auto cloud = GameSprite::createGameSpriteWithFrameName(path.c_str());
	cloud->setPosition(offset+r_pos);
	cloud->setScale(r_scale);
	this->addChild(cloud);
	m_clouds.push_back(cloud);
}
