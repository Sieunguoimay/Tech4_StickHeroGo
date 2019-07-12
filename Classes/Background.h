#pragma once
#include"cocos2d.h"
#include"list.h"
#include"PointerHolder.h"
USING_NS_CC;

class Cloud :public Sprite, public PointerHolder{
	Cloud();
public:
	~Cloud()override;
	static Cloud* create();
	bool init()override;
	void update(float deltaTime)override;
};

class Background:public Layer{
	Background();

public:
	static Background*create();
	
	virtual ~Background()override;
	bool init();
	virtual void update(float deltaTime)override;
	void moveAgainstCamera(float movingTime, const Vec2&distance);
private:
	Sprite* m_pSpriteSky;
	Sprite* m_pSpriteGrass;
	Sprite* m_pSpriteWave1;
	Sprite* m_pSpriteWave2;
	Sprite* m_pSpriteWave3;

	List<Cloud*>m_pClouds;

	void generateCloud(bool atCreateTime = false);
};
