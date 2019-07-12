#include "Background.h"

//Background::Background(Layer * pLayer)
//{
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	
//
//	this = Sprite::create("sky.png");
//	if (m_spriteSky == nullptr) {CCLOG("Error: failed to load file sky.png");}
//	else {
//		m_spriteSky->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//		pLayer->addChild(m_spriteSky);
//	}
//
//
//}

//layer->m_spriteGrass = Sprite::create("background_grass.png");
//layer->m_spriteGrass->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//layer->addChild(layer->m_spriteGrass);
//

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
	auto visibleSize = Director::getInstance()->getVisibleSize();

	m_pSpriteSky = Sprite::create("sky.png");
	m_pSpriteSky->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(m_pSpriteSky);

	return true;
}

void Background::moveAlongCamera(Camera * camera)
{
	//m_spriteSky->setPosition(camera->getPosition());
	//m_spriteGrass->setPosition(camera->getPosition());
}
