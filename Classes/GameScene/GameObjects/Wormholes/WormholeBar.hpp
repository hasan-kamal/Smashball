//
//  WormholeBar.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 30/09/16.
//
//

#ifndef WormholeBar_hpp
#define WormholeBar_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"
#include "../Boards/InitialParameters/WormholeBarInitialParameters.hpp"

using namespace cocos2d;

class WormholeBar : public AbstractGameObject{
public:
    
    b2Body *sensorBody, *concreteBody;
    b2Body *topSeparatorBody, *bottomSeparatorBody;
    Sprite *spriteMain, *spriteGlow;
    Sprite *spriteShadow;
    
    bool orientation; // 0 denotes left-oriented
    double heightHalf;
    double widthHalf;
    double sensorBodyWidthToTotalWidthRatio;
    double lightGlowWidth;
    double lightPaddingWidth;
    double heightTopSeparatorInWorld;
    b2Vec2 initialPosition;
    double density;
    double restitution;
    
    
    WormholeBar(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, WormholeBarInitialParameters *wormholeBarInitialParameters);
    ~WormholeBar();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    
    void enable();
    void disable();
};


#endif /* WormholeBar_hpp */
