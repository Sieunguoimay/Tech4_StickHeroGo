#pragma once
#include"GameLayer.h"
#include"Pillar.h"
USING_NS_CC;

class MoveAlongCallback {
protected:
	float m_movingRatio = 0.8f;
public:
	virtual void UpdatePosition(const Vec2&pos)=0;
	virtual void ResetPosition()=0;
};

enum PlatformStates {
	PFS_NONE,
	PFS_SPAWN_PILLAR
};
class Platform:public GameLayer {
	CREATE_FUNC(Platform);
	std::vector<Pillar*>m_pillars;
	int m_pillarCountSoFar;
	int m_nextPillarIndex;
	bool m_moveFlag;
	int m_state;
	float m_futurePosX;

	void resetPosition();
	std::vector<MoveAlongCallback*>m_callbacks;
	Sequence*m_pMoveAction;
	float calculateDistanceToNext(int pillarIndex);
public:
	static Platform*createPlatform();
	~Platform()override;
	bool init()override;
	void update(float deltaTime)override;

	//public usage
	float MoveAndCalculateScale(float distance = -1);
	inline float GetFuturePosX() const {return m_futurePosX;}
	inline Pillar*GetCurrentPillar() const { if (m_nextPillarIndex >0)return m_pillars[m_nextPillarIndex - 1]; return nullptr; }
	inline Pillar* GetNextPillar() const { if (m_nextPillarIndex >= 0)return m_pillars[m_nextPillarIndex]; return nullptr; }
	inline Pillar*GetFirstPillar() const { return m_pillars[0]; }
	inline Pillar*GetLastPillar() const { return m_pillars.back(); }
	inline void RegisterMoveAlongCallback(MoveAlongCallback*callback) { m_callbacks.push_back(callback); }
	inline int GetState()const { return m_state; }
	inline int GetPillarCount() const { return m_pillarCountSoFar; }
	void FirstMovementOnGameStart();
	void AddRulerToCurrentPilar();
};

