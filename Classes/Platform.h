#pragma once
#include"GameLayer.h"
#include"Pillar.h"
#include"utils/list.h"
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
	List<Pillar*>m_pillars;
	int m_pillarCountSoFar;
	ListNode<Pillar*>*m_currentPillar;
	bool m_moveFlag;
	int m_state;
	float m_futurePosX;

	void resetPosition();
	std::vector<MoveAlongCallback*>m_callbacks;
	Sequence*m_pMoveAction;
	float calculateDistanceToNext(ListNode<Pillar*>*node);
public:
	static Platform*createPlatform();
	~Platform()override;
	bool init()override;
	void update(float deltaTime)override;
	void DeleteOutOfScreenPillar();
	//public usage
	float MoveAndCalculateScale(float distance = -1);
	inline float GetFuturePosX() const {return m_futurePosX;}
	inline Pillar* GetCurrentPillar() const { if (m_currentPillar != m_pillars.head) return m_currentPillar->data; return nullptr; }
	inline Pillar* GetNextPillar() const { return m_currentPillar->next->data; }
	inline Pillar*GetFirstPillar() { return m_pillars.first()->data; }
	inline Pillar*GetLastPillar() { return m_pillars.last()->data; }
	inline void RegisterMoveAlongCallback(MoveAlongCallback*callback) { m_callbacks.push_back(callback); }
	inline int GetState()const { return m_state; }
	inline int GetPillarCount() const { return m_pillarCountSoFar; }
	void FirstMovementOnGameStart();
	void AddRulerToCurrentPilar();
};

