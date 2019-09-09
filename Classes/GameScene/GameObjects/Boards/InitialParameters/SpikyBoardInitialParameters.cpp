//
//  SpikyBoardInitialParameters.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 25/09/16.
//
//

#include "SpikyBoardInitialParameters.hpp"
#include <iostream>
using namespace std;

SpikyBoardInitialParameters::SpikyBoardInitialParameters(){
    this->isOriented = false;
    this->orientation = 1;
    this->heightHalf = 0.75;
    this->widthHalf = 0.05;
    this->initialPosition.set(1.0, 1.3);
    this->angleInclinationInitial = 1.5;
    this->bonusRadius = 0.12;
    this->boardDensity = 200.0;
    this->boardRestitution = 0.7;
    this->paddingGap = 0.02;
    this->maxMotorTorque = 5.0;
    this->motorSpeed = 0.0;
    this->amplitudeOscillationX = 0.0;
    this->frequencyOscillationX = 0.0;
    this->amplitudeOscillationY = 0.0;
    this->frequencyOscillationY = 0.0;
    
    for(int i=0; i<2; i++)
        params_for_spikes.push_back(new SpikeFixtureInitialParameters());
    params_for_spikes[1]->leftOriented = true;
    params_for_spikes[1]->distanceFromCenter = 0.30;
}

SpikyBoardInitialParameters::~SpikyBoardInitialParameters(){
    //for(int i=0; i<this->numSpikes; i++)
        //delete paramsForSpikes[i];
}

SpikyBoardInitialParameters::SpikyBoardInitialParameters(char s[], const vector<SpikeFixtureInitialParameters*>& spikeFixtureP){
    //Format:
//    isOriented,orientation,heightHalf,widthHalf,initialPosition.x,initialPosition.y
//    angleInclinationInitial,bonusRadius,boardDensity,boardRestitution,paddingGap
//    maxMotorTorque,motorSpeed,amplitudeOscillationX,frequencyOscillationX
//    amplitudeOscillationY,frequencyOscillationY,numSpikes
    
    int numSpikes = 0;
    
    char *token = strtok (s,",");
    int i = 0;
    while (token != NULL)
    {
        //printf ("%s\n",token);
        if(i==0){
            this->isOriented = int(atof(token));
        }else if(i==1){
            this->orientation = int(atof(token));
        }else if(i==2){
            this->heightHalf = atof(token);
        }else if(i==3){
            this->widthHalf = atof(token);
        }else if(i==4){
            this->initialPosition.x = atof(token);
        }else if(i==5){
            this->initialPosition.y = atof(token);
        }else if(i==6){
            this->angleInclinationInitial = atof(token);
        }else if(i==7){
            this->bonusRadius = atof(token);
        }else if(i==8){
            this->boardDensity = atof(token);
        }else if(i==9){
            this->boardRestitution = atof(token);
        }else if(i==10){
            this->paddingGap = atof(token);
        }else if(i==11){
            this->maxMotorTorque = atof(token);
        }else if(i==12){
            this->motorSpeed = atof(token);
        }else if(i==13){
            this->amplitudeOscillationX = atof(token);
        }else if(i==14){
            this->frequencyOscillationX = atof(token);
        }else if(i==15){
            this->amplitudeOscillationY = atof(token);
        }else if(i==16){
            this->frequencyOscillationY = atof(token);
        }else if(i==17){
            numSpikes = int(atof(token));
        }
        
        i++;
        token = strtok (NULL,",");
    }
    
    for(int i=0; i<numSpikes; i++)
        params_for_spikes.push_back(spikeFixtureP[i]);
}
