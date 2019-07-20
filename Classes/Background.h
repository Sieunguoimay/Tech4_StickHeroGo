#pragma once
#include"GameSprite.h"
#include"Wave.h"



class Background:public GameSprite{
	CREATE_FUNC(Background);

	Sprite* m_pSpriteGrass;

	Wave*m_pWave1;
	Wave*m_pWave2;
	Wave*m_pWave3;

	//List<Cloud*>m_pClouds;

	//void generateCloud(bool atCreateTime = false);

public:
	static Background*createBackground(Layer*pZoomingLayer,Platform*pPlatform);
	~Background()override;
	bool initBackground(Layer*pZoomingLayer, Platform*pPlatform);
	virtual void update(float deltaTime)override;
	
	void moveAlongCamera(float movingTime, const Vec2&distance);
};
