#pragma once
#include"cocos2d.h"
#include"list.h"
USING_NS_CC;

class Background:public Layer{
	Background();

public:
	static Background*create();
	
	virtual ~Background()override;

	bool init();
	void moveAlongCamera(Camera*camera);

private:
	Sprite*m_pSpriteSky;
};
