#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameObjects/Balls/AbstractBall.hpp"
#include "GameObjects/Boards/AbstractBoard.hpp"
#include "GameObjects/Balls/TennisBall.hpp"
#include "GameObjects/Boards/HingeBoard.hpp"
#include "GameObjects/Boards/StaticBoard.hpp"
#include "GameObjects/Boards/SpikyBoard.hpp"
#include "GameOverLayer.hpp"
#include "GameObjects/Terrains/ErraticTerrain.hpp"
#include <string>
#include "ui/CocosGUI.h"
#include "GamePauseLayer.hpp"
#include "ComboManagerLayer.hpp"
#include "Powerups/TimeFreezerBird.hpp"
#include "PowerupPopupSelectionLayer.hpp"
#include "PrematureGameOverLayer.hpp"
#include "GameObjects/Boards/InitialParameters/StaticBoardInitialParameters.hpp"
#include "GameObjects/Boards/InitialParameters/HingeBoardInitialParameters.hpp"
#include "GameObjects/Boards/InitialParameters/SpikyBoardInitialParameters.hpp"
#include "GameObjects/Boards/InitialParameters/GameSceneInitialParameters.hpp"
#include "GameObjects/Boards/InitialParameters/RectangularObstructionInitialParameters.hpp"
#include "GameObjects/Boards/InitialParameters/TriangularHingedObstructionInitialParameters.hpp"
#include "GameObjects/Boards/InitialParameters/TriangularObstructionInitialParameters.hpp"
#include "GameObjects/Boards/InitialParameters/RectangularHingedObstructionInitialParameters.hpp"
#include "GameObjects/Boards/InitialParameters/WormholeBarInitialParameters.hpp"
#include "GameObjects/Boards/InitialParameters/WormholePairInitialParameters.hpp"
#include "GameObjects/Wormholes/Wormhole.hpp"
#include "GameObjects/Vortex/Vortex.hpp"
#include "GameObjects/Wormholes/WormholePair.hpp"
#include "GameObjects/Obstructions/RectangularObstruction.hpp"
#include "GameObjects/Obstructions/RectangularHingedObstruction.hpp"
#include "GameObjects/Obstructions/TriangularObstruction.hpp"
#include "GameObjects/Obstructions/TriangularHingedObstruction.hpp"
#include "GameObjects/Obstructions/AbstractObstruction.hpp"
#include "../HighscoreManager.hpp"

using namespace cocos2d;
using namespace std;

class GameScene : public cocos2d::Layer, public b2ContactListener
{
public:
    static cocos2d::Scene* createScene(string stage_configs, string filename, GameSceneInitialParameters *GameSceneInitialParameters);
    
    virtual bool init(string stage_configs, string filename, GameSceneInitialParameters *GameSceneInitialParameters);
    virtual void onExit();
    
    // a selector callback
    void pauseClickedCallback(Ref* pSender);
    void powerupClickedCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    //CREATE_FUNC(GameScene); not using this one because we want to pass the filename as well
    static GameScene* create(string stage_configs, string filename, GameSceneInitialParameters *gameSceneInitialParameters)
    {
        GameScene *pRet = new(std::nothrow) GameScene();
        if (pRet && pRet->init(stage_configs, filename, gameSceneInitialParameters))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    
    b2World *world;
    b2Body *chainBoundBody;
    
    void update(float dt);
    
    //touch event callbacks
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    double touchTime;
    
    //scaling ratio
    float worldToPixelScale;
    
    //Game Objects
    vector<AbstractBall*> balls_in_game;
    vector<AbstractBall*> deflated_balls;
    vector<AbstractBoard*> boards_in_game;
    vector<AbstractGameObject*> terrains_in_game;
    vector<AbstractObstruction*> obstructions_in_game;
    vector<WormholePair*> wormholes_in_game;
    AbstractBall *closestBall; //when there are multiple balls, this is used to select which ball to apply impulse on
    
    void instantiateGameObjects(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, float heightInWorld, string stage_configurations);
    
    //contact listener functions
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
    //score variables and functions
    long long score;
    char scoreString[50];
    Label *scoreLabel;
    
    //timer variables
    Label *timerLabel;
    void updateTimer(float dt);
    int timerReading;
    char timerString[50];
    
    //Gameover layer and restart
    GameOverLayer *gameOverLayer;
    void restartGame();
    bool isGameOver = false;
    
    //padding
    float padding;
    
    //text label for debugging
    Label *labelText;
    
    //stage description file relative path
    string stage_configurations;
    string stageDescriptionFile;
    
    //In-game menu options
    cocos2d::ui::Button *buttonPause, *buttonPowerup;
    
    //pausing mechanism
    void pauseNodeAndDescendants(Node *node);
    void resumeNodeAndDescendants(Node *node);
    bool isPause = false; //only for accessing, dont override
    void pauseGameScene(); //use this to pause gamescene
    void resumeGameScene(); //use this to resume gamescene
    GamePauseLayer *gamePauseLayer;
    
    //for quitting game
    void quitGame();
    
    //combo manager layer
    ComboManagerLayer *comboManagerLayer;
    
    //Powerup mechanism
    PowerupPopupSelectionLayer *powerupPopupSelectionLayer;
    vector<PowerupPopupSelectionLayer*> powerups_in_game;
    void instantiateAndApplyPowerup(string powerupName);
    void haltTimerForSeconds(float haltDurationSeconds);
    
    //Offset vector to be added to origin
    Vec2 offsetOriginToBeAdded;
    float widthWorld = 5.0;
    float heightWorld = 2.6;
    
    //ball destruction variables and methods
    void destroyBallWithBody(b2Body *ballBodyToBeDestroyed);
    vector<AbstractBall*> balls_scheduled_for_removal;
    void prematureGameOver();
    void prematureRestart();
    PrematureGameOverLayer *prematureGameOverLayer;
    
    //ball health variables
    Sprite *health_meter;
    void ball_health_label_update();
};

#endif // __HELLOWORLD_SCENE_H__
