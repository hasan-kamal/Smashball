//
//  TimeFreezerBird.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 02/08/16.
//
//

#ifndef TimeFreezerBird_hpp
#define TimeFreezerBird_hpp
#include "AbstractPowerup.hpp"
#include "../GameScene.hpp"

using namespace cocos2d;

class TimeFreezerBird : public AbstractPowerup{
public:
    TimeFreezerBird(Layer *parentCocosLayer, float worldToPixelScale, Vec2 haltPositionVector, GameScene *gameSceneCaller);
    ~TimeFreezerBird();
    
    //for appropriate callbacks
    GameScene *gameScene;
    
    //visual properties
    float heightInWorld = 0.30;
    Vec2 stopPos;
    
    //implement interface
    void updateState(float dt, float worldToPixelScale) override;
    void startPowerup() override;
    
    //Sprite
    Sprite *mysprite;
};

#endif /* TimeFreezerBird_hpp */
