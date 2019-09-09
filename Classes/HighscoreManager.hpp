//
//  HighscoreManager.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 11/10/16.
//
//

#ifndef HighscoreManager_hpp
#define HighscoreManager_hpp

#include "cocos2d.h"
#include <iostream>
using namespace std;
using namespace cocos2d;

class HighscoreManager{
public:
    static void saveHighscore(string stageFileName, long long newScoreToSave);
    static long long getHighscore(string stageFileName);
};

#endif /* HighscoreManager_hpp */
