//
//  WormholeBarInitialParameters.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 11/10/16.
//
//

#include "WormholeBarInitialParameters.hpp"

WormholeBarInitialParameters::WormholeBarInitialParameters(){
    this->orientation = 0; // 0 denotes left-oriented
    this->heightHalf = 0.25;
    this->widthHalf = 0.04;
    this->sensorBodyWidthToTotalWidthRatio = 0.5;
    this->lightGlowWidth = 0.05;
    this->lightPaddingWidth = 0.01;
    this->heightTopSeparatorInWorld = 0.02;
    Vec2 initialPosition;
    this->density = 300.0;
    this->restitution = 0.7;
}

WormholeBarInitialParameters::WormholeBarInitialParameters(char s[]){
    //Format:
//    orientation,heightHalf,widthHalf,sensorBodyWidthToTotalWidthRatio,lightGlowWidth,
//    lightPaddingWidth,heightTopSeparatorInWorld,initialPosition.x,initialPosition.y,
//    density,restitution
    
    char *token = strtok (s,",");
    int i = 0;
    while (token != NULL)
    {
        //printf ("%s\n",token);
        if(i==0){
            this->orientation = int(atof(token));
        }else if(i==1){
            this->heightHalf = atof(token);
        }else if(i==2){
            this->widthHalf = atof(token);
        }else if(i==3){
            this->sensorBodyWidthToTotalWidthRatio = atof(token);
        }else if(i==4){
            this->lightGlowWidth = atof(token);
        }else if(i==5){
            this->lightPaddingWidth = atof(token);
        }else if(i==6){
            this->heightTopSeparatorInWorld = atof(token);
        }else if(i==7){
            this->initialPosition.x = atof(token);
        }else if(i==8){
            this->initialPosition.y = atof(token);
        }else if(i==9){
            this->density = atof(token);
        }else if(i==10){
            this->restitution = atof(token);
        }
        
        i++;
        token = strtok (NULL,",");
    }

}
