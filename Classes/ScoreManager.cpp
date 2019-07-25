#include"ScoreManager.h"

ScoreManager::ScoreManager() {
	m_pUserDefault = UserDefault::sharedUserDefault();
	m_highScore = m_pUserDefault->getIntegerForKey(m_keyHighScore,0);
	m_perfectCount = 0;
	m_score = 0;
	CCLOG("ScoreManager created");
}
ScoreManager::~ScoreManager() {
	m_pUserDefault = nullptr;
	CCLOG("ScoreManager deleted");
}

void ScoreManager::SaveData()
{
	if(m_highScore<m_score){
		m_pUserDefault->setIntegerForKey(m_keyHighScore, m_score);
		m_pUserDefault->flush();
	}
}
