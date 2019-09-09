//
//  RectangularHingedObstructionInitialParameters.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#include "RectangularHingedObstructionInitialParameters.hpp"

RectangularHingedObstructionInitialParameters::RectangularHingedObstructionInitialParameters(){
    this->heightHalf = 0.55;
    this->widthHalf = 0.04;
    this->initialPosition.set(0.5, 1.3);
    this->angleInclinationInitial = 0.0;
    this->boardDensity = 300.0;
    this->boardRestitution = 0.7;
    this->amplitudeOscillationX = 0.0;
    this->frequencyOscillationX = 0.0;
    this->amplitudeOscillationY = 0.0;
    this->frequencyOscillationY = 0.0;
    this->maxMotorTorque = 5.0;
    this->motorSpeed = 0.0;
}

RectangularHingedObstructionInitialParameters::RectangularHingedObstructionInitialParameters(char s[]){
    //Format:
//    heightHalf,widthHalf,initialPosition.x,initialPosition.y,angleInclinationInitial,
//    boardDensity,boardRestitution,amplitudeOscillationX,frequencyOscillationX,
//    amplitudeOscillationY,frequencyOscillationY, maxMotorTorque, motorSpeed
    
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
        }else if(i==11){
            this->maxMotorTorque = atof(token);
        }else if(i==12){
            this->motorSpeed = atof(token);
        }
        
        i++;
        token = strtok (NULL,",");
    }
}
