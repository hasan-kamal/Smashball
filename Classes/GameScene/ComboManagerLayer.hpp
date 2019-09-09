//
//  ComboManagerLayer.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 31/07/16.
//
//

#ifndef ComboManagerLayer_hpp
#define ComboManagerLayer_hpp

#include "cocos2d.h"
using namespace cocos2d;

class GameScene;

class ComboManagerLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ComboManagerLayer);
    
    //combo controllers
    double thresholdTime = 1.0;
    int thresholdCount = 1;
    
    //general variables and methods
    double timeElapsedSinceLastPlusFifty;
    int numHitsInLoop;
    bool isLoopRunning = false; //very important variable, tells if there is a combo loop running right now
    
    void startLoop();
    void endLoop();
    
    void updateTimeElapsed(float dt);
    long long getComboMultiplier(long long deltaScore);
    
    //visual representation
    Label *comboLabel;
    char comboLabelString[50];
};

#endif /* ComboManagerLayer_hpp */
