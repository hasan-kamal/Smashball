//
//  DataInputLayer.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/01/17.
//
//

#ifndef DataInputLayer_hpp
#define DataInputLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <regex>
using namespace cocos2d;
using namespace std;

class LevelTestingDesigner;
class DataInputLayer : public cocos2d::Layer
{
private:
    void done_clicked();
public:
    
    virtual bool init(LevelTestingDesigner *l);
    
    // implement the "static create()" method manually
    //CREATE_FUNC(GameScene); not using this one because we want to pass the filename as well
    static DataInputLayer* create(LevelTestingDesigner *lev_testing_designer)
    {
        DataInputLayer *pRet = new(std::nothrow) DataInputLayer();
        if (pRet && pRet->init(lev_testing_designer))
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
    
    Label *format_label;
    Label *example_label;
    Label *regex_label;
    cocos2d::ui::TextField *text_field;
    cocos2d::ui::Button *button_done;
    
    bool is_showing;
    LevelTestingDesigner *level_testing_designer;
    
    //touch event callbacks
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
    void take_input(string format_for_user, string example, string reg_exp);
    void dismiss();
    string last_regex;
};

#endif /* DataInputLayer_hpp */
