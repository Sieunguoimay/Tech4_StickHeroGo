#pragma once
#include"cocos2d.h"
USING_NS_CC;
class ScoreManager {

	UserDefault* m_pUserDefault;

	const char* m_keyHighScore = "HIGH_SCORE";
	const char* m_keyFollowerNum= "DOG_NUM";

	int m_followerNum;
	int m_score;
	int m_highScore;
	int m_perfectCount;

public:
	
	ScoreManager();
	~ScoreManager();
	
	void SaveData();
	
	inline int GetScore()const { return m_score; }
	inline void SetScore(int newScore) { m_score = newScore; }

	inline int GetFollowerNum()const { return m_followerNum; }
	inline void SetFollowerNum(int followerNum) { if(m_followerNum < followerNum) m_followerNum = followerNum; }

	inline int GetHighScore()const { return m_highScore; }
	inline void SetPerfectCount(int count) { m_perfectCount = count; }
	
	inline int GetPerfectCount()const { return m_perfectCount; }
	inline void AddScore(int score) { m_score += score; }
	inline void IncPerfectCount() { m_perfectCount++; }
};
