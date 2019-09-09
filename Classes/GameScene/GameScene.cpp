#include "GameScene.hpp"
#include "../IntroductionSceneStuff/IntroductionScene.hpp"
#include "../Colors.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

USING_NS_CC;

void GameScene::onExit(){
    Layer::onExit();

    int i;
    for(i=0; i<balls_in_game.size(); i++){
        delete balls_in_game[i];
    }
    
    for(i=0; i<boards_in_game.size(); i++){
        delete boards_in_game[i];
    }
    
    for(i=0; i<terrains_in_game.size(); i++){
        delete terrains_in_game[i];
    }
    
    for(i=0; i<powerups_in_game.size(); i++){
        delete powerups_in_game[i];
    }
    
    for(i=0; i<wormholes_in_game.size(); i++){
        delete wormholes_in_game[i];
    }
    
    for(i=0; i<obstructions_in_game.size(); i++){
        delete obstructions_in_game[i];
    }
    
    delete world;
}

Scene* GameScene::createScene(string stage_configs, string filename, GameSceneInitialParameters *gameSceneInitialParameters)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create(stage_configs, filename, gameSceneInitialParameters);
    //Hasan:: this create method in itself invokes the init method defined below
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init(string stage_configs, string filename, GameSceneInitialParameters *gameSceneInitialParameters)
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize(); //real screen size in pixels
    
    worldToPixelScale = visibleSize.width/widthWorld;
    offsetOriginToBeAdded.set(0, (visibleSize.height - worldToPixelScale*heightWorld)/2.0);
    padding = (frameSize.width*1.0/100);
    
    //buttonPause
    buttonPause = cocos2d::ui::Button::create();
    buttonPause->setTouchEnabled(true);
    buttonPause->loadTextures("pause_light.png", "pause_light.png");
    buttonPause->setAnchorPoint(Vec2(1.0, 0));
    buttonPause->setScale(visibleSize.height*10.0/100/buttonPause->getContentSize().height);
    buttonPause->setPosition(Vec2(origin.x + visibleSize.width - padding/2, origin.y + padding/2));
    buttonPause->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                this->pauseClickedCallback(this);
                break;
            case ui::Widget::TouchEventType::ENDED:{
                break;
            }
            default:
                break;
        }
    });
    this->addChild(buttonPause, 1);
    
    //score label
    scoreLabel = Label::createWithTTF("0", "fonts/Roboto-Light.ttf", 20);
    scoreLabel->setColor(Color3B(52, 73, 80));
    scoreLabel->setAnchorPoint(Vec2(1.0, 1.0));
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width - padding, origin.y + visibleSize.height - padding));
    scoreLabel->setAlignment(TextHAlignment::RIGHT);
    this->addChild(scoreLabel, 1);
    
    auto background = DrawNode::create();
    background->drawSolidRect(origin, Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height), Colors::clouds);
    this->addChild(background);
    
    scheduleUpdate();
    
    //box2d world
    b2Vec2 gravity = b2Vec2(gameSceneInitialParameters->gravityX, gameSceneInitialParameters->gravityY);
    world = new b2World(gravity);

    //chain shape
    b2Vec2 gameBounds[4];
    gameBounds[0].Set(0.0, 0.0);
    gameBounds[1].Set(widthWorld, 0.0);
    gameBounds[2].Set(widthWorld, heightWorld);
    gameBounds[3].Set(0.0, heightWorld);
    
    b2ChainShape chainShapeBound;
    chainShapeBound.CreateLoop(gameBounds, 4);
    
    b2FixtureDef boundFixture;
    boundFixture.shape = &chainShapeBound;
    boundFixture.restitution = 0.5;
    
    b2BodyDef boundBodyDef;
    boundBodyDef.type = b2_staticBody;
    boundBodyDef.userData = nullptr;
    boundBodyDef.position.Set(0.0, 0.0);
    
    chainBoundBody = world->CreateBody(&boundBodyDef);
    chainBoundBody->CreateFixture(&boundFixture);

    //touch listener
    auto touchEventListener = EventListenerTouchOneByOne::create();
    touchEventListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchEventListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchEventListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEventListener, this);
    
    //set contact listener
    world->SetContactListener(this);
    
    touchTime = -1.0;
    score = 0;
    
    //timer initialization
    this->schedule(schedule_selector(GameScene::updateTimer), 1.0f);
    timerReading = 61;
    timerLabel = Label::createWithTTF("1:00", "fonts/Roboto-Light.ttf", 20);
    timerLabel->setColor(Color3B(52, 73, 80));
    timerLabel->setAnchorPoint(Vec2(0, 1));
    timerLabel->setPosition(Vec2(origin.x + padding, origin.y + visibleSize.height - padding));
    timerLabel->setAlignment(TextHAlignment::LEFT);
    this->addChild(timerLabel, 1);
    
    //game over layer
    gameOverLayer = GameOverLayer::create();
    gameOverLayer->gameScene = this;
    this->addChild(gameOverLayer, 3);
    
    //store stage_configurations for future reference
    this->stage_configurations.assign(stage_configs);
    this->stageDescriptionFile.assign(filename);
    
    //game pause layer
    gamePauseLayer = GamePauseLayer::create();
    gamePauseLayer->gameScene = this;
    this->addChild(gamePauseLayer, 4);
    
    //powerupPopupSelectionLayer
    powerupPopupSelectionLayer = PowerupPopupSelectionLayer::create();
    powerupPopupSelectionLayer->gameScene = this;
    this->addChild(powerupPopupSelectionLayer, 5);
    
    //combo manager layer
    this->comboManagerLayer = ComboManagerLayer::create();
    this->addChild(comboManagerLayer);
    
    this->instantiateGameObjects(world, this, worldToPixelScale, heightWorld, this->stage_configurations);
    //very important, all AbstractGameObjects are assigned here
    
    //tapered line
    auto taperedLineSprite = Sprite::create("tapered_line.png");
    taperedLineSprite->setScale(visibleSize.width*0.25/taperedLineSprite->getContentSize().width);
    taperedLineSprite->setPosition(Vec2(this->offsetOriginToBeAdded.x + origin.x + visibleSize.width/2, this->offsetOriginToBeAdded.y + origin.y + heightWorld*worldToPixelScale));
    taperedLineSprite->setOpacity(50);
    this->addChild(taperedLineSprite);
    
    //premature gameover layer
    prematureGameOverLayer = PrematureGameOverLayer::create();
    prematureGameOverLayer->gameScene = this;
    this->addChild(prematureGameOverLayer, 3);
    
//    //ball health label
//    ball_health_label = Label::createWithTTF("", "fonts/Roboto-Light.ttf", 20);
//    ball_health_label->setColor(Color3B(52, 73, 80));
//    ball_health_label->setAnchorPoint(Vec2(0.5, 1));
//    ball_health_label->setPosition(Vec2(origin.x + visibleSize.width/2.0, origin.y + visibleSize.height - padding));
//    ball_health_label->setAlignment(TextHAlignment::CENTER);
//    this->addChild(ball_health_label, 1);
//    
    float bar_height = visibleSize.height*2.0/100.0;
    float bar_width = visibleSize.width*12.0/100.0;
    
    //empty_health_meter
    auto empty_health_meter = Sprite::create("midnight_blue.png");
    empty_health_meter->setScale(bar_width/empty_health_meter->getContentSize().width, bar_height/empty_health_meter->getContentSize().height);
    empty_health_meter->setAnchorPoint(Vec2(0.5, 1.0));
    empty_health_meter->setPosition(Vec2(origin.x + visibleSize.width/2.0, origin.y + visibleSize.height - padding));
    empty_health_meter->setOpacity(20);
    this->addChild(empty_health_meter);
    
    //health_meter
    health_meter = Sprite::create("emerald.png");
    health_meter->setScale(bar_width/health_meter->getContentSize().width, bar_height/health_meter->getContentSize().height);
    health_meter->setAnchorPoint(Vec2(0.0, 1.0));
    health_meter->setPosition(empty_health_meter->getPosition()-Vec2(bar_width/2.0, 0));
    this->addChild(health_meter);
    health_meter->setOpacity(200);
    
    //glowing health meter
    auto fadeOut = FadeTo::create(0.5f, 150);
    auto fadeIn = FadeTo::create(0.5f, 200);
    auto seq = Sequence::create(fadeOut, fadeIn, NULL);
    auto repeatSeq = RepeatForever::create(seq);
    repeatSeq->setTag(100);
    this->health_meter->runAction(repeatSeq);
    
    ball_health_label_update();

    return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){
    
    //start noting time elapsed
    touchTime = 0.0;
    
    //select which ball to apply impulse on
    //depending on which ball is closer to
    //initial touch location on touch_began
    auto origin = Director::getInstance()->getVisibleOrigin();
    Vec2 ballLocation, diff;
    
    closestBall = balls_in_game[0];
    ballLocation.set(balls_in_game[0]->ballBody->GetPosition().x*worldToPixelScale + origin.x, balls_in_game[0]->ballBody->GetPosition().y*worldToPixelScale + origin.y);
    diff = touch->getStartLocation()-ballLocation;
    
    float minDistFromInitialTouch = (touch->getStartLocation()-ballLocation).length();
    int i;
    
    for(i=0; i<balls_in_game.size(); i++){
        ballLocation.set(balls_in_game[i]->ballBody->GetPosition().x*worldToPixelScale + origin.x, balls_in_game[i]->ballBody->GetPosition().y*worldToPixelScale + origin.y);
        diff = touch->getStartLocation()-ballLocation;
        if(diff.length()<minDistFromInitialTouch){
            closestBall = balls_in_game[i];
            minDistFromInitialTouch = diff.length();
        }
    }

    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event){

}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event){
    
    
    //generating and scaling the impulse vector for proper swipe
    float scale_factor = 0.04;
    if(touchTime<=0.0){
        touchTime = Director::getInstance()->getSecondsPerFrame();
        if(touchTime<=0.0)
            touchTime = 0.01;
    }
    float scale_impulse_x = scale_factor/touchTime;
    float scale_impulse_y = scale_factor/touchTime;
    auto origin = Director::getInstance()->getVisibleOrigin();
    b2Vec2 impulse_vector = b2Vec2((touch->getLocation().x - touch->getStartLocation().x)*scale_impulse_x, (touch->getLocation().y - touch->getStartLocation().y)*scale_impulse_y);
    
    //apply impulse to was-closest ball
    if(closestBall && !isGameOver)
        closestBall->gotHitApplyImpulse(impulse_vector);
    closestBall = nullptr;
    
    //set touchtime to negative
    touchTime = -1.0;
}

void GameScene::update(float dt){
    int positionIterations = 10;  // Location
    int velocityIterations = 10; // Velocity
    
    
    // Simulate the physical movement by time, study here http://www.box2d.org/manual.html and here  http://www.iforce2d.net/b2dtut/worlds
    
    // Each Step happens in dt seconds , this dt in file AppDelegate.cpp is defined by command director->setAnimationInterval(1.0 / 60); you try replacing 1/60 = 1/1 , it falls very slow
    
    world->Step(dt, velocityIterations, positionIterations);
    
    //remove ball bodies that are scheduled to be removed
    int i;
    for(i=0; i<balls_scheduled_for_removal.size(); i++)
        world->DestroyBody(balls_scheduled_for_removal[i]->ballBody);
    balls_scheduled_for_removal.clear();
    
    //ask wormholes to update themselves, basically pass them the list of
    //balls to perform teleportation if they have it scheduled
    for(i=0; i<wormholes_in_game.size(); i++){
        wormholes_in_game[i]->updateStateForTeleportation(dt, balls_in_game);
    }
    
    // Navigate all bodies of world
    for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext())
        // Consider which body is attached to Sprite
        if (body->GetUserData())
        {
            // return the ball sprite
            AbstractGameObject *gameObject = (AbstractGameObject *) body->GetUserData();
            // Set the position again for this Sprite follow the position of body ( body is gradually falling by time), remember to multiply with RATIO to convert into pixel
            gameObject->updateState(dt, worldToPixelScale, this->offsetOriginToBeAdded);
        }
    world->ClearForces(); // Clear forces of Body
    //world->DrawDebugData();  // Draw shapes to check collision in debug mode
   
    if(touchTime>=0.0)
        touchTime+=dt;
    
    sprintf(scoreString, "%lld", score);
    scoreLabel->setString(scoreString);
    
    if(timerReading<=60){
        sprintf(timerString, ( (timerReading%60)/10==0?"%d:0%d":"%d:%d" ), timerReading/60, timerReading%60);
        timerLabel->setString(timerString);
    }
    
    comboManagerLayer->updateTimeElapsed(dt);
}

void GameScene::powerupClickedCallback(Ref *pSender){
    if(isGameOver)
        return;

    if(isPause){
        this->resumeGameScene();
        powerupPopupSelectionLayer->dismiss();
    }else{
        this->pauseGameScene();
        powerupPopupSelectionLayer->show();
    }
}

void GameScene::pauseClickedCallback(Ref* pSender)
{
    if(isGameOver)
        return;
    
    if(isPause){
        this->resumeGameScene();
        gamePauseLayer->dismiss();
    }else{
        this->pauseGameScene();
        gamePauseLayer->show();
    }
}

//helper function to pause gamescene, use this to pause game
void GameScene::pauseGameScene(){
    this->isPause = true;
    this->pauseNodeAndDescendants(this);
    this->resumeNodeAndDescendants(buttonPause); //otherwise we would not be able to resume!
    this->resumeNodeAndDescendants(gameOverLayer);
    this->resumeNodeAndDescendants(gamePauseLayer);
    //this->resumeNodeAndDescendants(buttonPowerup);
    this->resumeNodeAndDescendants(powerupPopupSelectionLayer);
}

//helper function to resume gamescene, use this to resume game
void GameScene::resumeGameScene(){
    this->isPause = false;
    this->resumeNodeAndDescendants(this);
}

// recursive function to pause a node and all its children except pause-related nodes themselves
void GameScene::pauseNodeAndDescendants(Node *node)
{
    node->pause();
    for(const auto &child : node->getChildren())
    {
        this->pauseNodeAndDescendants(child);
    }
}

// recursive function to resume a node and all its children except pause-related nodes themselves
void GameScene::resumeNodeAndDescendants(Node *node)
{
    node->resume();
    for(const auto &child : node->getChildren())
    {
        this->resumeNodeAndDescendants(child);
    }
}

void GameScene::quitGame(){
    //if(this->stageDescriptionFile.compare("stagefiles/stage-classic.txt")==0){
    //}else{
    //}
    auto introductionScene = IntroductionScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, introductionScene, Color3B(Color4F(255-236, 255-240, 255-240, 1.0))));
}

//contact listener functions
void GameScene::BeginContact(b2Contact *contact){
    int i;
    for(i=0; i<boards_in_game.size(); i++){
        if(contact->GetFixtureA()->GetBody()==boards_in_game[i]->boardBody || contact->GetFixtureB()->GetBody()==boards_in_game[i]->boardBody){
            long long deltaScore = boards_in_game[i]->boardCollidedReturnScoreUpdate(contact, worldToPixelScale, this->offsetOriginToBeAdded, balls_in_game);
            score += (deltaScore*comboManagerLayer->getComboMultiplier(deltaScore));
            
        }
    }
}

void GameScene::EndContact(b2Contact* contact){

}

void GameScene::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
    //presolve is called after collision detection but before collision resolution
    
    //let wormholes know a contact has happened, in case they might have to react
    for(int i=0; i<wormholes_in_game.size(); i++){
        wormholes_in_game[i]->checkIfContactWithWormhole(contact, balls_in_game);
    }
}

void GameScene::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
    
}

void GameScene::updateTimer(float dt){
    if(timerReading>0)
        timerReading--;
    else{
        isGameOver = true;
        gameOverLayer->show(score, stageDescriptionFile);
        this->unschedule(schedule_selector(GameScene::updateTimer));
        if(score>HighscoreManager::getHighscore(stageDescriptionFile))
            HighscoreManager::saveHighscore(stageDescriptionFile, score);
    }
}


void GameScene::restartGame(){
    isGameOver = false;
    timerReading = 61;
    timerLabel->setString("1:00");
    score = 0;
    
    gameOverLayer->dismiss();
    this->schedule(schedule_selector(GameScene::updateTimer), 1.0f);
    
    if(balls_in_game.size()==0){
        //must have got over because ball was destroyed
        //so inflate the ball back again because we are restarting
        //this works properly only when one ball is there
        for(auto ball : deflated_balls){
            ball->inflateBall(world);
            balls_in_game.push_back(ball);
            this->ball_health_label_update();
        }
        deflated_balls.clear();
    }
}

void GameScene::instantiateGameObjects(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, float heightInWorld, string stage_configs){

    //string filename = "stagefiles/stage1.txt";
    //string contentString = FileUtils::getInstance()->getStringFromFile(filename);
    stringstream content(stage_configs);
    
    int i;
    string classFileName;
    //initialize balls
    int numBalls;
    content>>numBalls;
    for(i=0; i<numBalls; i++){
        content>>classFileName;
        if(classFileName.compare("TennisBall")==0){
            balls_in_game.push_back(new TennisBall(world, parentCocosLayer, worldToPixelScale));
        }
    }
    
    //initialize boards
    int numBoards;
    content>>numBoards;
    for(i=0; i<numBoards; i++){
        content>>classFileName;
        if(classFileName.compare("StaticBoard")==0){
            
            char s1[100];
            content>>s1;
            //char s1[] = "1,0.75,0.05,0.7,1.3,0.0,0.12,200.0,0.7,0.02,0.1,1.0,0.1,1.0";
            StaticBoardInitialParameters p(s1);
            boards_in_game.push_back(new StaticBoard(world, parentCocosLayer, worldToPixelScale, this->heightWorld, this->offsetOriginToBeAdded, &p));
        
        }else if(classFileName.compare("HingeBoard")==0){
            
            char s1[100];
            content>>s1;
            //char s1[] = "1,1,0.75,0.05,0.7,1.3,0.0,0.12,200.0,0.7,0.02,5.0,0.0,0.1, 1.0, 0.1, 1.0";
            HingeBoardInitialParameters p(s1);
            boards_in_game.push_back(new HingeBoard(world, parentCocosLayer, worldToPixelScale, this->offsetOriginToBeAdded, &p));
            
        }else if(classFileName.compare("SpikyBoard")==0){
            
//            char spike1string[100];
//            content>>spike1string;
//            //char spike1string[] = "0,0.08,0.08,0.70,0.5,0.5";
//            SpikeFixtureInitialParameters sp1(spike1string);
//            
//            char spike2string[100];
//            content>>spike2string;
//            //char spike2string[] = "0,0.08,0.08,0.20,0.5,0.5";
//            SpikeFixtureInitialParameters sp2(spike2string);
//            
//            SpikeFixtureInitialParameters *x[50];
//            x[0] = &sp1;
//            x[1] = &sp2;
            
            //char s1[] = "0,1,0.75,0.05,1.0,1.3,1.5,0.12,200.0,0.7,0.02,5.0,0.0,0.5,1.0,0.0,0.0,2";
            char s1[100];
            content>>s1;
            
            int numSpikes;
            content>>numSpikes;
            
            //SpikeFixtureInitialParameters *x[50];
            vector<SpikeFixtureInitialParameters*> x;
            char spikeString[100];
            for(int i=0; i<numSpikes; i++){
                content>>spikeString;
                //SpikeFixtureInitialParameters kk(spikeString);
                x.push_back(new SpikeFixtureInitialParameters(spikeString));
                //x[i] = &kk;
            }
            
            SpikyBoardInitialParameters p(s1, x);
            
            boards_in_game.push_back(new SpikyBoard(world, parentCocosLayer, worldToPixelScale, this->offsetOriginToBeAdded, this, &p));
            
            for(int i=0; i<numSpikes; i++){
                delete x[i];
            }
        }
    }

//    //initialize terrains
//    content>>numTerrains;
//    for(i=0; i<numTerrains; i++){
//        content>>classFileName;
//        if(classFileName.compare("ErraticTerrain")==0){
//            this->terrainsInGame[i] = new ErraticTerrain(world, parentCocosLayer, worldToPixelScale);
//        }
//    }
    
    //initialize wormholes
    int numWormholes;
    content>>numWormholes;
    for(i=0; i<numWormholes; i++){
        content>>classFileName;
        
        //char s1[] = "0,0.25,0.04,0.5,0.05,0.01,0.02,1.25,1.0,300.0,0.7";
        char s1[100];
        content>>s1;
        WormholeBarInitialParameters b1(s1);
        
        //char s2[] = "1,0.25,0.04,0.5,0.05,0.01,0.02,2.25,2.0,300.0,0.7";
        char s2[100];
        content>>s2;
        WormholeBarInitialParameters b2(s2);
        
        WormholePairInitialParameters w(&b1, &b2);
        
        if(classFileName.compare("Wormhole")==0){
            wormholes_in_game.push_back(new WormholePair(world, parentCocosLayer, worldToPixelScale, offsetOriginToBeAdded, &w));
        }
    }
    
    
    //obstructions
    int numObstructions;
    content>>numObstructions;
    for(i=0; i<numObstructions; i++){
        content>>classFileName;
        
        
        if(classFileName.compare("RectangularObstruction")==0){
            
            char s[100];
            content>>s;
            //char s[] = "0.45,0.04,3.0,1.3,0.0,200.0,0.7,0.5,0.5,0.5,0.5";
            RectangularObstructionInitialParameters rr(s);
            obstructions_in_game.push_back(new RectangularObstruction(world, parentCocosLayer, worldToPixelScale, offsetOriginToBeAdded, &rr));
            
        }else if(classFileName.compare("RectangularHingedObstruction")==0){
            
            char s[100];
            content>>s;
            //char s[] = "0.45,0.04,1.5,1.5,0.0,200.0,0.7,0.5,0.5,0.5,0.5, 5.0, 0.0";
            RectangularHingedObstructionInitialParameters r(s);
            obstructions_in_game.push_back(new RectangularHingedObstruction(world, parentCocosLayer, worldToPixelScale, offsetOriginToBeAdded, &r));
            
        }else if(classFileName.compare("TriangularObstruction")==0){
            
            char s[100];
            content>>s;
            //char s[] = "0.25,0.75,2.5,1.3,-0.3,300.0,0.7,0.0,0.0,0.5,1.0";
            TriangularObstructionInitialParameters t(s);
            obstructions_in_game.push_back(new TriangularObstruction(world, parentCocosLayer, worldToPixelScale, offsetOriginToBeAdded, &t));
            
        }else if(classFileName.compare("TriangularHingedObstruction")==0){
            
            char s[100];
            content>>s;
            //char s[] = "0.25,0.75,2.5,1.3,-0.3,300.0,0.7,0.0,0.0,0.5,1.0,5.0,0.0";
            TriangularHingedObstructionInitialParameters t(s);
            obstructions_in_game.push_back(new TriangularHingedObstruction(world, parentCocosLayer, worldToPixelScale, offsetOriginToBeAdded, &t));
            
        }
        
    }
}

void GameScene::instantiateAndApplyPowerup(string powerupName){
    if(powerupName.compare("TimeFreezerBird")==0){
//        powerups_in_game[numPowerups] = new TimeFreezerBird(this, this->worldToPixelScale, timerLabel->getPosition(), this);
//        power[numPowerups]->startPowerup();
//        numPowerups++;
    }
}

void GameScene::haltTimerForSeconds(float haltDurationSeconds){
    
}

void GameScene::destroyBallWithBody(b2Body *ballBodyToBeDestroyed){
    int i;
    for(i=0; i<balls_in_game.size() && balls_in_game[i]->ballBody!=ballBodyToBeDestroyed; i++){}
    AbstractBall *ballDeflated = balls_in_game[i];
    ballDeflated->deflateBall();
    
    deflated_balls.push_back(ballDeflated);
    
    balls_scheduled_for_removal.push_back(ballDeflated);
    balls_in_game.erase(remove(balls_in_game.begin(), balls_in_game.end(), ballDeflated), balls_in_game.end());
    this->prematureGameOver();
}

void GameScene::prematureGameOver(){
//    isGameOver = true;
//    prematureGameOverLayer->show(score);
//    this->unschedule(schedule_selector(GameScene::updateTimer));
    isGameOver = true;
    gameOverLayer->show(score, stageDescriptionFile);
    this->unschedule(schedule_selector(GameScene::updateTimer));
    if(score>HighscoreManager::getHighscore(stageDescriptionFile))
        HighscoreManager::saveHighscore(stageDescriptionFile, score);
}

void GameScene::prematureRestart(){
//    isGameOver = false;
//    //timerReading = 61;
//    //timerLabel->setString("1:00");
//    //score = 0;
//    
//    AbstractBall *ballToBeInflated = ballsInGame[numBalls];
//    ballToBeInflated->inflateBall(world);
//    numBalls++;
//    
//    prematureGameOverLayer->dismiss();
//    this->schedule(schedule_selector(GameScene::updateTimer), 1.0f);
    this->restartGame();
}

void GameScene::ball_health_label_update(){
    if(balls_in_game.size()<=0)
        return;
    
//    char s[50];
//    sprintf(s, "%d", balls_in_game.at(0)->health);
//    ball_health_label->setString(s);
//    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float full_bar_height = visibleSize.height*2.0/100.0;
    float full_bar_width = visibleSize.width*12.0/100.0;
    
    if(balls_in_game.at(0)->health>=0)
        health_meter->setScale(full_bar_width*balls_in_game.at(0)->health/GlobalConfigs::INITIAL_BALL_HEALTH/health_meter->getContentSize().width, full_bar_height/health_meter->getContentSize().height);
    else
        health_meter->setScale(0.0, full_bar_height/health_meter->getContentSize().height);
}
