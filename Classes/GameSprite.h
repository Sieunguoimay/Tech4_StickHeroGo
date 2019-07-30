#pragma once
#include"MiscSupport.h"
#define CREATE_GAME_SPRITE_WITH_TEXTURE_FUNC(__TYPE__) \
static __TYPE__* createGameSpriteWithTexture(Texture2D*texture) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithTexture(texture)) \
    { \
		pRet->initGameSprite(); \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define CREATE_GAME_SPRITE_WITH_FRAME_NAME(__TYPE__) \
static __TYPE__* createGameSpriteWithFrameName(const char*frame_name) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithSpriteFrameName(frame_name)) \
    { \
		pRet->initGameSprite(); \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}
class GameSprite :public Sprite,public MiscSupport {
public:
	CREATE_GAME_SPRITE_WITH_FRAME_NAME(GameSprite);
	static GameSprite*createGameSprite(const char*sprite_file_name);
	static GameSprite*createGameSpriteWithTexture(Texture2D*texture);
	virtual void initGameSprite(){}

	inline const Size GetSize() { return Size(_contentSize.width*_scaleX, _contentSize.height*_scaleY); }
	inline float GetWidth() { return _contentSize.width * _scaleX; }
	inline float GetHeight() { return _contentSize.height * _scaleY; }
};
