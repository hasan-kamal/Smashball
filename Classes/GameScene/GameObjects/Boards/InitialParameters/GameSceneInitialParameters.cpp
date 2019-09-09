//
//  GameSceneInitialParameters.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 07/10/16.
//
//

#include "GameSceneInitialParameters.hpp"

GameSceneInitialParameters::GameSceneInitialParameters(){
    this->gravityX = 0.0f;
    this->gravityY = -10.0f;
    this->hasLeftWall = true;
    this->hasRightWall = true;
    this->hasUpWall = true;
    this->hasBottomWall = true;
}

GameSceneInitialParameters::GameSceneInitialParameters(string s){
    
}
