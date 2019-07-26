#pragma once
#include"GameSprite.h"
#include"Platform.h"

class RandFloatingOnLineSprites :public GameLayer, public MoveAlongCallback {
	std::vector<SpriteBatchNode*>m_spriteBatchNodes;
	std::queue<GameSprite*>m_sprites;
	float m_y;

	void putSprite();

public:
	CREATE_FUNC(RandFloatingOnLineSprites);
	//static RandFloatingOnLineSprites* Create(float y, const char* file_name);
	void AddSpriteBatchNode(const char*file_name);
	void initFloatingOnLineSprites(float y);
	~RandFloatingOnLineSprites();


	void UpdatePosition(const Vec2& pos) override;
	void ResetPosition()override;
};
