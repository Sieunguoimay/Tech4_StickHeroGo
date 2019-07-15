#include "Background.h"
#include"Utils.h"
#include"ActionRunner.h"
Background * Background::create()
{
	auto background = new Background();
	if (background&&background->init()) {
		background->autorelease();
		return background;
	}
	CC_SAFE_DELETE(background);
	return nullptr;
}


Background::Background()
{
	CCLOG("Created background");

}

Background::~Background()
{
	CCLOG("Deleted background");
}



bool Background::init()
{
	scheduleUpdate();

	const auto visibleSize = Director::getInstance()->getVisibleSize();

	m_pSpriteSky = Sprite::create("sky.png");
	m_pSpriteSky->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(m_pSpriteSky);


	m_pSpriteGrass = Sprite::create("background_grass.png");
	m_pSpriteGrass->setPosition(visibleSize.width / 2, m_pSpriteGrass->getContentSize().height/2);
	addChild(m_pSpriteGrass);



	m_pSpriteWave3 = Sprite::create("wave3.png");
	m_pSpriteWave3->setPosition(visibleSize.width / 2, m_pSpriteWave3->getContentSize().height / 2 + 30);
	addChild(m_pSpriteWave3);

	m_pSpriteWave2 = Sprite::create("wave2.png");
	m_pSpriteWave2->setPosition(visibleSize.width / 2, m_pSpriteWave2->getContentSize().height / 2+15);
	addChild(m_pSpriteWave2);

	m_pSpriteWave1 = Sprite::create("wave1.png");
	m_pSpriteWave1->setPosition(visibleSize.width / 2, m_pSpriteWave1->getContentSize().height / 2 - 1);
	m_pSpriteWave1->setGlobalZOrder(1);
	addChild(m_pSpriteWave1);
	for(int i = 0; i<4; i++)
		generateCloud(true);
	return true;
}


void Background::update(float deltaTime)
{
	const auto& visibleSize = Director::getInstance()->getVisibleSize();
	const auto& camPos = Camera::getDefaultCamera()->getPosition();

	for (auto a = m_pClouds.first(); a != m_pClouds.tail; a = a->next) {
		const auto& cloud = a->data;
		const auto& pos = a->data->getPosition();
		const auto& size = a->data->getContentSize();
		if (pos.x + size.width / 2 <visibleSize.width / 2) {
			this->removeChild(cloud);
			a = m_pClouds.erase(a);
			generateCloud();
		}
	}
}


void Background::moveAlongCamera(float movingTime, const Vec2& distance)
{
	//for (auto a = m_pClouds.first(); a != m_pClouds.tail; a = a->next) {

	//	auto action = new MoveToTarget(movingTime, a->data->getPosition() - distance, a->data);

	//	a->data->AddPointer((void**)&(action->m_pNode));
	//	
	//	ActionRunner::getInstance()->addAction(action);

	//}
}

void Background::generateCloud(bool atCreateTime)
{
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto camPos = Camera::getDefaultCamera()->getPosition();
	float rightEdge = camPos.x + visibleSize.width / 2;

	if (atCreateTime) rightEdge = camPos.x - visibleSize.width / 2;
	if (m_pClouds.size() < 4) {
		auto cloud = Cloud::create();
		if (cloud != nullptr) {
			this->addChild(cloud);
			const float x = rightEdge + Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, 0.0f, visibleSize.width)+ cloud->getContentSize().width / 2;
			const float y = Utils::map(CCRANDOM_0_1(), 0, 1.0f, camPos.y - visibleSize.height / 4, camPos.y + visibleSize.height / 2);
			const float scale = Utils::map(CCRANDOM_0_1(), 0, 1.0f, 0.5f, 3.0f);
			cloud->setScale(scale);
			cloud->setPosition(x, y);
			m_pClouds.push_back(cloud);
		}
	}
}


Cloud::Cloud() {
	CCLOG("Cloud created");
}
Cloud::~Cloud()
{
	CCLOG("Clound deleted");
}
Cloud* Cloud::create()
{
	auto cloud = new Cloud();
	if (cloud && cloud->initWithFile("cloud.png")) {
		cloud->autorelease();
		return cloud;
	}
	CC_SAFE_DELETE(cloud);
	return nullptr;
}

bool Cloud::init()
{
	return false;
}

void Cloud::update(float deltaTime)
{
}
