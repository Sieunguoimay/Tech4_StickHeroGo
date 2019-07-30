#include "GameSprite.h"

GameSprite * GameSprite::createGameSprite(const char * sprite_file_name)
{
	auto gameSprite = new GameSprite();
	if (gameSprite&&gameSprite->initWithFile(sprite_file_name)) {
		gameSprite->autorelease();
		return gameSprite;
	}
	CC_SAFE_DELETE(gameSprite);
	return nullptr;
}

GameSprite * GameSprite::createGameSpriteWithTexture(Texture2D * texture)
{
	auto gameSprite = new GameSprite();
	if (gameSprite&&gameSprite->initWithTexture(texture)) {
		gameSprite->autorelease();
		return gameSprite;
	}
	CC_SAFE_DELETE(gameSprite);
	return nullptr;
}

