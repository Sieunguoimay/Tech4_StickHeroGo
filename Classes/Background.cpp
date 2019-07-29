#include "Background.h"
#include"utils/Utils.h"
#include"utils/Definitions.h"
Background * Background::createBackground(Layer*pZoomingLayer, Platform*pPlatform)
{
	auto background = new Background();
	if (background&&background->initWithSpriteFrameName("sky.png")) {
		background->initBackground(pZoomingLayer,pPlatform);
		background->autorelease();
		return background;
	}
	CC_SAFE_DELETE(background);
	return nullptr;
}

Background::~Background()
{
	CCLOG("Deleted background");
}


bool Background::initBackground(Layer*pZoomingLayer, Platform*pPlatform)
{
	scheduleUpdate();
	_position += m_visibleSize / 2;
	
	
	m_pSpriteGrass = Sprite::createWithSpriteFrameName("background_grass.png");
	m_pSpriteGrass->setPosition(m_visibleSize.width / 2, m_pSpriteGrass->getContentSize().height/2);
	this->addChild(m_pSpriteGrass);

	m_pWave3 = Wave::createWave("wave3.png",80.0f,0.4f,0.6f);
	pZoomingLayer->addChild(m_pWave3);
	pPlatform->RegisterMoveAlongCallback(m_pWave3);

	m_pWave2 = Wave::createWave("wave2.png",90.0f,0.5f,0.8f);
	pZoomingLayer->addChild(m_pWave2);
	pPlatform->RegisterMoveAlongCallback(m_pWave2);

	
	m_pWave1 = Wave::createWave("wave1.png",100.0f,0.6f,1.0f);
	pZoomingLayer->addChild(m_pWave1, GAME_LAYER_2);
	pPlatform->RegisterMoveAlongCallback(m_pWave1);


	m_pMountain = RandFloatingOnLineSprites::create();
	m_pMountain->AddSpriteBatchNode("mountain1.png");
	m_pMountain->AddSpriteBatchNode("mountain2.png");
	m_pMountain->AddSpriteBatchNode("mountain3.png");
	m_pMountain->initFloatingOnLineSprites(m_pSpriteGrass->getContentSize().height);
	this->addChild(m_pMountain);
	pPlatform->RegisterMoveAlongCallback(m_pMountain);


	m_pTree = RandFloatingOnLineSprites::create();
	m_pTree->AddSpriteBatchNode("tree.png");
	m_pTree->initFloatingOnLineSprites(m_pSpriteGrass->getContentSize().height-5);
	this->addChild(m_pTree);
	pPlatform->RegisterMoveAlongCallback(m_pTree);

	CCLOG("Created background %d",this->getChildrenCount());
	return true;
}


void Background::update(float deltaTime)
{
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

//void Background::generateCloud(bool atCreateTime)
//{
//	const auto visibleSize = Director::getInstance()->getVisibleSize();
//	const auto camPos = Camera::getDefaultCamera()->getPosition();
//	float rightEdge = camPos.x + visibleSize.width / 2;
//
//	if (atCreateTime) rightEdge = camPos.x - visibleSize.width / 2;
//	if (m_pClouds.size() < 4) {
//		auto cloud = Cloud::create();
//		if (cloud != nullptr) {
//			m_pGameSceneLayer->addChild(cloud);
//			const float x = rightEdge + Utils::map(CCRANDOM_0_1(), 0.0f, 1.0f, 0.0f, visibleSize.width)+ cloud->getContentSize().width / 2;
//			const float y = Utils::map(CCRANDOM_0_1(), 0, 1.0f, camPos.y - visibleSize.height / 4, camPos.y + visibleSize.height / 2);
//			//const float scale = Utils::map(CCRANDOM_0_1(), 0, 1.0f, 0.5f, 3.0f);
//			//cloud->setScale(scale);
//			cloud->setPosition(x, y);
//			m_pClouds.push_back(cloud);
//		}
//	}
//}

