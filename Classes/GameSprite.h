#pragma once
#include"MiscSupport.h"

class GameSprite :public Sprite,public MiscSupport {
public:
	static GameSprite*createGameSprite(const char*sprite_file_name);
	static GameSprite*createGameSpriteWithTexture(Texture2D*texture);
	
	inline const Size&GetSize() { return Size(_contentSize.width*_scaleX, _contentSize.height*_scaleY); }
	inline float GetWidth() { return _contentSize.width*_scaleX; }
};
