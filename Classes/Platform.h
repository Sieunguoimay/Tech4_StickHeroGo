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

class Platform:public GameLayer {
	CREATE_FUNC(Platform);
	std::vector<Pillar*>m_pillars;
	int m_pillarCountSoFar;
	int m_nextPillarIndex;
	bool m_moveFlag;

	void resetPosition();
	std::vector<MoveAlongCallback*>m_callbacks;
	Sequence*m_pMoveAction;
public:
	static Platform*createPlatform();
	~Platform()override;
	bool init()override;
	void update(float deltaTime)override;

	//public usage
	float MoveAndCalculateScale();
	inline Pillar*GetCurrentPillar() { if (m_nextPillarIndex >0)return m_pillars[m_nextPillarIndex - 1]; return nullptr; }
	inline Pillar* GetNextPillar() { if (m_nextPillarIndex >= 0)return m_pillars[m_nextPillarIndex]; return nullptr; }
	inline Pillar*GetFirstPillar() { return m_pillars[0]; }
	inline void RegisterMoveAlongCallback(MoveAlongCallback*callback) { m_callbacks.push_back(callback); }
	inline void StopMoving(){this->stopAction(m_pMoveAction); }
	void FirstMovementOnGameStart();
};

