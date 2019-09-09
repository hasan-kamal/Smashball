//
//  AbstractBoard.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 06/07/16.
//
//

#ifndef AbstractBoard_hpp
#define AbstractBoard_hpp

#include "../AbstractGameObject.hpp"
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "../Balls/AbstractBall.hpp"
#include <vector>

using namespace cocos2d;
using namespace std;

class AbstractBoard: public AbstractGameObject{
public:
    b2Body *boardBody;
    
    Sprite *boardSpriteUpper;
    Sprite *boardSpriteMiddle;
    Sprite *boardSpriteLower;
    virtual long long boardCollidedReturnScoreUpdate(b2Contact *contact, float worldToPixelScale, Vec2 offsetOriginToBeAdded, const vector<AbstractBall*>& balls_in_game) = 0;
};

#endif /* AbstractBoard_hpp */
