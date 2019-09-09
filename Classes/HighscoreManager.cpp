//
//  HighscoreManager.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 11/10/16.
//
//

#include "HighscoreManager.hpp"

void HighscoreManager::saveHighscore(string stageFileName, long long newScoreToSave){
    string KEY = "highscore";
    KEY = KEY + stageFileName;
    UserDefault::getInstance()->setIntegerForKey(KEY.c_str(), (int)newScoreToSave);
}

long long HighscoreManager::getHighscore(string stageFileName){
    string KEY = "highscore";
    KEY = KEY + stageFileName;
    int high_score = UserDefault::getInstance()->getIntegerForKey(KEY.c_str(), 0);
    return high_score;
}
