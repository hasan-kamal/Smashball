//
//  LevelTestingDesigner.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/01/17.
//
//

#include "LevelTestingDesigner.hpp"
#include "../Colors.hpp"
#include "../FileOperation.h"
#include "../IntroductionSceneStuff/IntroductionScene.hpp"
#include "../GlobalConfigs.hpp"

USING_NS_CC;
#include <iostream>
using namespace std;

Scene* LevelTestingDesigner::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelTestingDesigner::create();
    //Hasan:: this create method in itself invokes the init method defined below
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

string LevelTestingDesigner::to_str(int x){
    char s[50];
    sprintf(s, "%d", x);
    return string(s);
}

// on "init" you need to initialize your instance
bool LevelTestingDesigner::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto winSize = Director::getInstance()->getWinSize();
    
    auto background = DrawNode::create();
    background->drawSolidRect(origin, Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height), Colors::clouds);
    this->addChild(background);
    
    float padding = (frameSize.width*1.0/100);
    
    //button_cancel
    button_cancel = cocos2d::ui::Button::create();
    button_cancel->setTouchEnabled(true);
    button_cancel->loadTextures("close_thin.png", "close_thin.png");
    button_cancel->setAnchorPoint(Vec2(1.0, 0));
    button_cancel->setScale(visibleSize.height*9.0/100/button_cancel->getContentSize().height);
    button_cancel->setPosition(Vec2(origin.x + visibleSize.width - padding/2, origin.y + padding/2));
    button_cancel->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                this->cancel_clicked();
                break;
            case ui::Widget::TouchEventType::ENDED:{
                break;
            }
            default:
                break;
        }
    });
    this->addChild(button_cancel, 1);
    
    //button_approve
    button_approve = cocos2d::ui::Button::create();
    button_approve->setTouchEnabled(true);
    button_approve->loadTextures("tick.png", "tick.png");
    button_approve->setAnchorPoint(Vec2(1.0, 0));
    button_approve->setScale(visibleSize.height*9.0/100/button_approve->getContentSize().height);
    button_approve->setPosition(Vec2(origin.x + visibleSize.width - padding - button_cancel->getContentSize().width*button_cancel->getScale(), origin.y + padding/2));
    button_approve->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                this->approve_clicked();
                break;
            case ui::Widget::TouchEventType::ENDED:{
                break;
            }
            default:
                break;
        }
    });
    this->addChild(button_approve, 1);
    
    //heading label
    auto heading_label = Label::createWithTTF("Select object", "fonts/Trirong-Light.ttf", 25);
    heading_label->setAnchorPoint(Vec2(0.5, 1.0));
    heading_label->setPosition(Vec2(origin.x + visibleSize.width/2.0, origin.y + 0.95*visibleSize.height));
    heading_label->setColor(Color3B(Colors::asbestos));
    this->addChild(heading_label);
    
    string reg_exp_floating_point = "[-+]?[0-9]*\\.?[0-9]+";
    string reg_exp_digit = "[0-9]+";
    
    //prepare display_items
        //ball
        display_items.push_back( display_for_user{"ball", "<ball_name>", "TennisBall", "TennisBall"} );
        
        //static_board
        display_items.push_back( display_for_user{"static_board", "orientation,heightHalf,widthHalf\n,initialPosition.x,initialPosition.y,angleInclinationInitial\n,bonusRadius,boardDensity,boardRestitution\n,paddingGap,amplitudeOscillationX, frequencyOscillationX\n, amplitudeOscillationY,frequencyOscillationY", "0,0.75,0.05,4.0,1.3,0.0,0.12,200.0,0.7,0.02,0.0,0.0,0.0,0.0", "(("+reg_exp_floating_point+"),){13}"+reg_exp_floating_point} );
        
        //hinge_board
        display_items.push_back( display_for_user{"hinge_board", "    isOriented,orientation,heightHalf\n,widthHalf,initialPosition.x,initialPosition.y\n,angleInclinationInitial,bonusRadius,boardDensity\n,boardRestitution,paddingGap, maxMotorTorque\n, motorSpeed, amplitudeOscillationX,frequencyOscillationX\n, amplitudeOscillationY, frequencyOscillationY", "1,1,0.75,0.05,1.0,1.3,0.0,0.12,200.0,0.7,0.02,5.0,0.0,0.0,0.0,0.0,0.0", "(("+reg_exp_floating_point+"),){16}"+reg_exp_floating_point} );
        
        //spiky_board
        string reg_spiky = "((("+reg_exp_floating_point+"),){1}"+reg_exp_floating_point+")--"+reg_exp_digit;
        reg_spiky = reg_spiky + "(--"+"(("+reg_exp_floating_point+"),){1}"+reg_exp_floating_point+")*";
    
        display_items.push_back( display_for_user{"spiky_board", "isOriented,orientation,heightHalf\n,widthHalf,initialPosition.x,initialPosition.y\n,angleInclinationInitial,bonusRadius,boardDensity\n,boardRestitution,paddingGap,maxMotorTorque\n,motorSpeed,amplitudeOscillationX,frequencyOscillationX\n,amplitudeOscillationY,frequencyOscillationY--numSpikes--\n\nleftOriented,baseWidth,baseHeight,distanceFromCenter,restitution,friction--\n\n^above line should appear numSpikes times delimited with --", "0,1,0.75,0.05,3.0,1.3,1.5,0.12,200.0,0.7,0.02,5.0,0.0,0.5,1.0,0.0,0.0\n--2--\n0,0.08,0.08,0.70,0.5,0.5--0,0.08,0.08,0.20,0.5,0.5", reg_spiky} );
    
        //wormhole
        display_items.push_back( display_for_user{"wormhole", "orientation,heightHalf,widthHalf\n,sensorBodyWidthToTotalWidthRatio,lightGlowWidth,lightPaddingWidth\n,heightTopSeparatorInWorld,initialPosition.x,initialPosition.y\n,density,restitution--orientation,heightHalf,widthHalf\n,sensorBodyWidthToTotalWidthRatio,lightGlowWidth,lightPaddingWidth\n,heightTopSeparatorInWorld,initialPosition.x,initialPosition.y\n,density,restitution", "0,0.25,0.04,0.5,0.05,0.01,0.02,4.5,1.3,300.0,0.7\n--\n1,0.25,0.04,0.5,0.05,0.01,0.02,2.5,1.3,300.0,0.7", "(("+reg_exp_floating_point+"),){10}"+reg_exp_floating_point+"--"+"(("+reg_exp_floating_point+"),){10}"+reg_exp_floating_point} );
        
        //rectangular_obstruction
        display_items.push_back( display_for_user{"rectangular_obstruction", "heightHalf,widthHalf,initialPosition.x\n,initialPosition.y,angleInclinationInitial,boardDensity\n,boardRestitution,amplitudeOscillationX,frequencyOscillationX\n,amplitudeOscillationY,frequencyOscillationY", "0.45,0.04,3.0,1.3,0.0,200.0,0.7,0.5,0.5,0.5,0.5", "(("+reg_exp_floating_point+"),){10}"+reg_exp_floating_point} );
        
        //rectangular_hinged_obstruction
        display_items.push_back( display_for_user{"rectangular_hinged_obstruction", "heightHalf,widthHalf,initialPosition.x\n,initialPosition.y,angleInclinationInitial,boardDensity\n,boardRestitution,amplitudeOscillationX,frequencyOscillationX\n,amplitudeOscillationY,frequencyOscillationY, maxMotorTorque,\nmotorSpeed", "0.45,0.04,2.75,1.3,0.0,200.0,0.7,0.0,0.0,0.5,1.5,5.0,0.0", "(("+reg_exp_floating_point+"),){12}"+reg_exp_floating_point} );
    
        //triangular_obstruction
        display_items.push_back( display_for_user{"triangular_obstruction", "baseWidth,height,initialPosition.x\n,initialPosition.y,angleInclinationInitial,density\n,restitution,amplitudeOscillationX,frequencyOscillationX\n,amplitudeOscillationY,frequencyOscillationY", "0.25,0.75,2.5,1.3,-0.3,300.0,0.7,0.0,0.0,0.5,1.0", "(("+reg_exp_floating_point+"),){10}"+reg_exp_floating_point} );
    
    
        //triangular_hinged_obstruction
        display_items.push_back( display_for_user{"triangular_hinged_obstruction", "baseWidth,height,initialPosition.x\n,initialPosition.y,angleInclinationInitial,density\n,restitution,amplitudeOscillationX,frequencyOscillationX\n,amplitudeOscillationY,frequencyOscillationY, maxMotorTorque\n,motorSpeed", "0.25,0.75,2.5,1.3,-0.3,300.0,0.7,0.0,0.0,0.5,1.0,5.0,0.0", "(("+reg_exp_floating_point+"),){12}"+reg_exp_floating_point} );
    
    
    //create object labels
    int x = 0;
    for(auto item : display_items){
        auto button = cocos2d::ui::Button::create();
        
        button->setTitleText(item.type);
        button->setTitleColor(Color3B(Colors::silver));
        button->setAnchorPoint(Vec2(0.5, 1.0));
        
        if(buttons.size()==0)
            button->setPosition(heading_label->getPosition() - 1.2*Vec2(0, heading_label->getContentSize().height));
        else if(buttons.size()>0)
            button->setPosition(buttons.at(buttons.size()-1)->getPosition() - 2.0*Vec2(0, buttons.at(buttons.size()-1)->getContentSize().height));
        
        button->setTag(x);
        button->addTouchEventListener([&, x](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                    this->button_clicked(x);
                    break;
                default:
                    break;
            }
        });
        x++;
        
        buttons.push_back(button);
    }
    
    //add buttons to scene
    for(auto button : buttons)
        this->addChild(button);
    
    //Data input layer
    data_input_layer = DataInputLayer::create(this);
    this->addChild(data_input_layer, 1);
    
    //label to display number of objects
    num_objects_label = Label::create();
    num_objects_label->setAnchorPoint(Vec2(1.0, 1.0));
    num_objects_label->setPosition(origin+visibleSize);
    num_objects_label->setColor(Color3B(Colors::silver));
    this->addChild(num_objects_label);
    update_num_objects_label();
    
    return true;
}

void LevelTestingDesigner::button_clicked(int index){
    object_type = display_items.at(index).type;
    data_input_layer->take_input(display_items.at(index).format, display_items.at(index).example, display_items.at(index).regex_string);
}

void LevelTestingDesigner::update_num_objects_label(){
    num_objects_label->setString("objects added: "+to_str(num_objects_added));
}

void LevelTestingDesigner::approve_clicked(){
    stage_config_string = "";
    
    //ball
    stage_config_string = stage_config_string + to_str(ball_input.size()) + "\n";
    for(string s : ball_input)
        stage_config_string = stage_config_string + s + "\n";
    
    //boards
    stage_config_string = stage_config_string + to_str(static_board_input.size()+hinge_board_input.size()+spiky_board_input.size()) + "\n";
    
    for(static_board_wrapper s : static_board_input)
        stage_config_string = stage_config_string + "StaticBoard" + "\n" + s.param + "\n";
    
    for(hinge_board_wrapper h : hinge_board_input)
        stage_config_string = stage_config_string + "HingeBoard" + "\n" + h.param + "\n";
    
    for(spiky_board_wrapper s : spiky_board_input){
        stage_config_string = stage_config_string + "SpikyBoard" + "\n" + s.param + "," + to_str(s.spike_params.size()) +"\n" + to_str(s.spike_params.size()) + "\n";
        for(string str : s.spike_params)
            stage_config_string = stage_config_string + str + "\n";
    }
        
    //wormhole
    stage_config_string = stage_config_string + to_str(wormhole_input.size()) + "\n";
    for(wormhole_wrapper w : wormhole_input)
        stage_config_string = stage_config_string + w.param1 + "\n" + w.param2 + "\n";
    
    //obstruction
    stage_config_string = stage_config_string + to_str(obstruction_input.size()) + "\n";
    for(obstruction_wrapper o : obstruction_input)
        stage_config_string = stage_config_string + o.name + "\n" + o.param + "\n";
    
    cout<<"-------"<<endl;
    cout<<stage_config_string<<endl;
    cout<<"-------"<<endl;
    
    if(num_objects_added>0){
        FileOperation::saveFile(GlobalConfigs::CUSTOM_STAGE_FILENAME, stage_config_string);
        this->cancel_clicked();
    }
}

void LevelTestingDesigner::add_object(string entered_text){
    
    /*
     vector<string> ball_input;
     vector<static_board_wrapper> static_board_input;
     vector<hinge_board_wrapper> hinge_board_input;
     vector<spiky_board_wrapper> spiky_board_input;
     vector<wormhole_wrapper> wormhole_input;
     vector<obstruction_wrapper> obstruction_input;
    */
    
    if(object_type.compare(display_items.at(0).type)==0){
        
        //ball to be added
        ball_input.push_back(entered_text);
    
    }else if(object_type.compare(display_items.at(1).type)==0){
        
        //static_board to be added
        static_board_wrapper s;
        s.param = entered_text;
        static_board_input.push_back(s);
        
    }else if(object_type.compare(display_items.at(2).type)==0){
    
        //hinge_board to be added
        hinge_board_wrapper h;
        h.param = entered_text;
        hinge_board_input.push_back(h);
        
    }else if(object_type.compare(display_items.at(3).type)==0){
        
        //spiky_board to be added
        spiky_board_wrapper s;
        vector<string> tokens = split(entered_text, "--", true);
        s.param = tokens.at(0);
        for(int i=0; i<atoi(tokens.at(1).c_str()); i++)
            s.spike_params.push_back(tokens.at(i+2));
        
    }else if(object_type.compare(display_items.at(4).type)==0){
        
        //wormhole to be added
        wormhole_wrapper w;
        string delim = "--";
        w.param1 = entered_text.substr(0, entered_text.find(delim));
        int x = entered_text.find(delim) + delim.length();
        w.param2 = entered_text.substr(x, entered_text.size() - x);
        
    }else if(object_type.compare(display_items.at(5).type)==0){
        
        //rectangular_obstruction to be added
        obstruction_wrapper o;
        o.name = "RectangularObstuction";
        o.param = entered_text;
        obstruction_input.push_back(o);
        
    }else if(object_type.compare(display_items.at(6).type)==0){
        
        //rectangular_hinged_obstruction to be added
        obstruction_wrapper o;
        o.name = "RectangularHingedObstuction";
        o.param = entered_text;
        obstruction_input.push_back(o);
    
    }else if(object_type.compare(display_items.at(7).type)==0){
        
        //triangular_obstruction to be added
        obstruction_wrapper o;
        o.name = "TriangularObstuction";
        o.param = entered_text;
        obstruction_input.push_back(o);
        
    }else{
        
        //triangular_hinged_obstruction to be added
        obstruction_wrapper o;
        o.name = "TriangularHingedObstuction";
        o.param = entered_text;
        obstruction_input.push_back(o);
        
    }
    
    num_objects_added++;
    update_num_objects_label();
}

vector<string> LevelTestingDesigner::split(const string& s, const string& delim, const bool keep_empty = true) {
    vector<string> result;
    if (delim.empty()) {
        result.push_back(s);
        return result;
    }
    string::const_iterator substart = s.begin(), subend;
    while (true) {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        string temp(substart, subend);
        if (keep_empty || !temp.empty()) {
            result.push_back(temp);
        }
        if (subend == s.end()) {
            break;
        }
        substart = subend + delim.size();
    }
    return result;
}

void LevelTestingDesigner::cancel_clicked()
{
    auto introductionScene = IntroductionScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, introductionScene, Color3B(Color4F(255-236, 255-240, 255-240, 1.0))));
}
