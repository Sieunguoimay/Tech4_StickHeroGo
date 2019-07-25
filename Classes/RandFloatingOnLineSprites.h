#pragma once
#include"GameSprite.h"
#include"Platform.h"

class RandFloatingOnLineSprites :public SpriteBatchNode, public MoveAlongCallback {
	std::queue<GameSprite*>m_sprites;
	Size m_visibleSize;
	float m_y;

	void putSprite();

public:

	static RandFloatingOnLineSprites* Create(float y, const char* file_name);
	void initFloatingOnLineSprites(float y);
	~RandFloatingOnLineSprites();


	void UpdatePosition(const Vec2& pos) override;
	void ResetPosition()override;
};
