//
//  GlobalConfigs.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/01/17.
//
//

#ifndef GlobalConfigs_hpp
#define GlobalConfigs_hpp

#include <stdio.h>
#include <string>
using namespace std;

class GlobalConfigs{
public:
    const static int NUM_STAGES_PER_CHAPTER;
    const static int NUM_COLS_PER_CHAPTER;
    const static string APP_VERSION;
    const static string CUSTOM_STAGE_FILENAME;
    const static string DEFAULT_CUSTOM_STAGE_CONFIG;
    const static int INITIAL_BALL_HEALTH;
    const static int SPIKE_DAMAGE;
};

#endif /* GlobalConfigs_hpp */
