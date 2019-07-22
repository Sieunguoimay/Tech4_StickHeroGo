#pragma once
#include"GameSprite.h"
#include"utils/list.h"
#include"Particle.h"
enum {
	PS_STARS,
	PS_WATER,
	PS_SMOKE,
	PS_TOTAL_NUM
};
enum ParticleSystemStates {
	PSS_IDLE,
	PSS_EMIT,
	PSS_EMITTED
};
class GameParticleSystem :public SpriteBatchNode , public MiscSupport{
	int m_state;
	float m_emittingDuration;
	Vec2 m_pos;
	float m_angleDirStart;
	float m_angleDirEnd;
	void putParticle();

	float m_emittingRate;
	float m_size;
	float m_meanTime ;
	float m_meanDistance ;
	float m_distanceVar;
	Color3B m_colorOverlay;

	std::function<void()>m_callback;

	GameParticleSystem&operator=(const GameParticleSystem&);
	GameParticleSystem(const GameParticleSystem&);
	GameParticleSystem(){}

	static GameParticleSystem* s_instances[PS_TOTAL_NUM];
	static GameParticleSystem* createParticleSystem(const char*source_texture);
	void initParticleSystem();


	static Layer*s_pParentLayer;
public:

	static GameParticleSystem*GetInstance(int type);
	static void Init(Layer*parent) { s_pParentLayer = parent; }
	static void CleanUp();

	~GameParticleSystem()override;
	void update(float deltaTime)override;
	void Emit(float duration, const Vec2&pos);

	inline GameParticleSystem&SetMeanTime(float time) { m_meanTime = time; return *this; }
	inline GameParticleSystem&SetMeanDistance(float distance) { m_meanDistance = distance; return *this; }
	inline GameParticleSystem&SetDistanceVar(float distance) { m_distanceVar = distance; return *this;}
	inline GameParticleSystem&SetColor(byte r, byte b, byte g) { m_colorOverlay.r = r; m_colorOverlay.b = b; m_colorOverlay.g = g; return *this;}
	inline GameParticleSystem&SetAngleDirStart(float angle) { m_angleDirStart = angle; return *this;}
	inline GameParticleSystem&SetAngleDirEnd(float angle) { m_angleDirEnd = angle; return *this; }
	inline GameParticleSystem&SetSize(float size) { m_size = size; return *this; }
	inline GameParticleSystem&SetEmittingRate(float emittingRate) { m_emittingRate = emittingRate; return *this; }
	inline GameParticleSystem&SetCallback(std::function<void()>callback) {m_callback = callback; return *this; }
};
