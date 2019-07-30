/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include"GameScene.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }



	//auto playButton = MenuItemImage::create("cloud.png", "cloud.png", CC_CALLBACK_1(MainMenu::menuEnterGameCallback, this));
	//playButton->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
 //   auto menu = Menu::create(playButton,NULL);
 //   menu->setPosition(Vec2::ZERO);
 //   this->addChild(menu, 1);

	auto background = Sprite::create("splash.png");
	if (background == nullptr) {
		CCLOG("Error: failed to load file sky.png");
	}
	else {
		background->setPosition(m_origin + m_visibleSize/2);
		addChild(background);
	}

	this->runAction(Sequence::create(DelayTime::create(1.2f), CallFunc::create([]() {
		Director::getInstance()->pushScene(TransitionCrossFade::create(0.5f, GameScene::createScene()));
		}), nullptr));

	CCLOG("MainMenu created");
    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void MainMenu::menuEnterGameCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f,GameScene::createScene()));
}

/*

/////////////////////////////
// 2. add a menu item with "X" image, which is clicked to quit the program
//    you may modify it.

// add a "close" icon to exit the progress. it's an autorelease object
auto closeItem = MenuItemImage::create(
"CloseNormal.png",
"CloseSelected.png",
CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

if (closeItem == nullptr ||
closeItem->getContentSize().width <= 0 ||
closeItem->getContentSize().height <= 0)
{
problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
}
else
{
float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
float y = origin.y + closeItem->getContentSize().height / 2;
closeItem->setPosition(Vec2(x, y));
}




auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
if (label == nullptr)
{
problemLoading("'fonts/Marker Felt.ttf'");
}
else
{
// position the label on the center of the screen
label->setPosition(Vec2(origin.x + visibleSize.width/2,
origin.y + visibleSize.height - label->getContentSize().height));

// add the label as a child to this layer
this->addChild(label, 1);
}

// add "HelloWorld" splash screen"
auto sprite = Sprite::create("HelloWorld.png");
if (sprite == nullptr)
{
problemLoading("'HelloWorld.png'");
}
else
{
// position the sprite on the center of the screen
sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

// add the sprite as a child to this layer
this->addChild(sprite, 0);
}

*/