#pragma once
#include"cocos2d.h"
USING_NS_CC;
class MiscSupport {
protected:
	Size m_visibleSize;
	Vec2 m_origin;

public:
	MiscSupport() {
		m_visibleSize = Director::getInstance()->getVisibleSize();
		m_origin = Director::getInstance()->getVisibleOrigin();
	
	}
};