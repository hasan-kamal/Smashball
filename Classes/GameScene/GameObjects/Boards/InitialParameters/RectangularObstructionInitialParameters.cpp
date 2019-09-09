//
//  RectangularObstructionInitialParameters.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#include "RectangularObstructionInitialParameters.hpp"
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

RectangularObstructionInitialParameters::RectangularObstructionInitialParameters(){
    this->heightHalf = 0.55;
    this->widthHalf = 0.04;
    this->initialPosition.set(1.0, 1.3);
    this->angleInclinationInitial = 0.0;
    this->boardDensity = 200.0;
    this->boardRestitution = 0.7;
    this->amplitudeOscillationX = 0.5;
    this->frequencyOscillationX = 0.5;
    this->amplitudeOscillationY = 0.5;
    this->frequencyOscillationY = 0.5;
}

RectangularObstructionInitialParameters::RectangularObstructionInitialParameters(char s[]){
    //Format:
//    heightHalf,widthHalf,initialPosition.x,initialPosition.y,angleInclinationInitial,
//    boardDensity,boardRestitution,amplitudeOscillationX,frequencyOscillationX,
//    amplitudeOscillationY,frequencyOscillationY
    
    char *token = strtok (s,",");
    int i = 0;
    while (token != NULL)
    {
        //printf ("%s\n",token);
        if(i==0){
            this->heightHalf = atof(token);
        }else if(i==1){
            this->widthHalf = atof(token);
        }else if(i==2){
            this->initialPosition.x = atof(token);
        }else if(i==3){
            this->initialPosition.y = atof(token);
        }else if(i==4){
            this->angleInclinationInitial = atof(token);
        }else if(i==5){
            this->boardDensity = atof(token);
        }else if(i==6){
            this->boardRestitution = atof(token);
        }else if(i==7){
            this->amplitudeOscillationX = atof(token);
        }else if(i==8){
            this->frequencyOscillationX = atof(token);
        }else if(i==9){
            this->amplitudeOscillationY = atof(token);
        }else if(i==10){
            this->frequencyOscillationY = atof(token);
        }
        
        i++;
        token = strtok (NULL,",");
    }
}
