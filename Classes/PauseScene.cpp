#include "PauseScene.h"

USING_NS_CC;

bool PauseScene::init()
{
	if(!Layer::init())
		return false;
	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto title = MenuItemFont::create("Pause Scene");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4));


	auto button1 = MenuItemFont::create("Resume game", CC_CALLBACK_1(PauseScene::menuResumeGameCallback, this));
	button1->setPosition(Vec2(visibleSize.width / 2, title->getPosition().y - title->getContentSize().height*2));

	auto button2 = MenuItemFont::create("Go to home menu", CC_CALLBACK_1(PauseScene::menuBackToHomeCallback, this));
	button1->setPosition(Vec2(visibleSize.width / 2, button1->getPosition().y - button1->getContentSize().height * 2));

	auto menu = Menu::create( title, button1, button2, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	return true;
}

cocos2d::Scene * PauseScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PauseScene::create();
	scene->addChild(layer);
	return scene;
}

void PauseScene::menuResumeGameCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
}

void PauseScene::menuBackToHomeCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}
