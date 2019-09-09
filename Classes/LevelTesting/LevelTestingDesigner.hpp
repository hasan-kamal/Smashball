//
//  LevelTestingDesigner.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/01/17.
//
//

#ifndef LevelTestingDesigner_hpp
#define LevelTestingDesigner_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DataInputLayer.hpp"
#include <string>

using namespace cocos2d;
using namespace std;

struct static_board_wrapper{
    string param;
};

struct hinge_board_wrapper{
    string param;
};

struct spiky_board_wrapper{
    string param;
    vector<string> spike_params;
};

struct wormhole_wrapper{
    string param1, param2;
};

struct obstruction_wrapper{
    string name, param;
};

struct display_for_user{
    string type, format, example, regex_string;
};

class LevelTestingDesigner : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelTestingDesigner);
    
    //final string that will be returned as answer
    string stage_config_string;
    
    //input to be taken from user
    vector<string> ball_input;
    vector<static_board_wrapper> static_board_input;
    vector<hinge_board_wrapper> hinge_board_input;
    vector<spiky_board_wrapper> spiky_board_input;
    vector<wormhole_wrapper> wormhole_input;
    vector<obstruction_wrapper> obstruction_input;
    
    cocos2d::ui::Button *button_approve, *button_cancel;
    void cancel_clicked();
    void approve_clicked();
    void button_clicked(int index);
    void add_object(string entered_text);
    
    vector<display_for_user> display_items;
    vector<cocos2d::ui::Button*> buttons;
    int num_objects_added = 0;
    string object_type;
    
    DataInputLayer *data_input_layer;
    void update_num_objects_label();
    vector<string> split(const string& s, const string& delim, const bool keep_empty);
    
    Label *num_objects_label;
    string to_str(int x);
};


#endif /* LevelTestingDesigner_hpp */
