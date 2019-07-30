#include"ScoreManager.h"

ScoreManager::ScoreManager() {
	m_pUserDefault = UserDefault::sharedUserDefault();
	m_highScore = m_pUserDefault->getIntegerForKey(m_keyHighScore, 0);
	m_followerNum = m_pUserDefault->getIntegerForKey(m_keyFollowerNum,0);
	m_perfectCount = 0;
	m_score = 0;
	CCLOG("ScoreManager created %d",m_followerNum);
}
ScoreManager::~ScoreManager() {
	m_pUserDefault = nullptr;
	CCLOG("ScoreManager deleted");
}

void ScoreManager::SaveData()
{
	m_pUserDefault->setIntegerForKey(m_keyFollowerNum, m_followerNum);
	if(m_highScore<m_score){
		m_pUserDefault->setIntegerForKey(m_keyHighScore, m_score);
		m_pUserDefault->flush();
	}
}
