//
//  SpikeFixtureInitialParameters.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 25/09/16.
//
//

#include "SpikeFixtureInitialParameters.hpp"

SpikeFixtureInitialParameters::SpikeFixtureInitialParameters(){
    this->leftOriented = false;
    this->baseWidth = 0.08;
    this->baseHeight = 0.08;
    this->distanceFromCenter = 0.70;
    this->restitution = 0.5;
    this->friction = 0.5;
}

SpikeFixtureInitialParameters::SpikeFixtureInitialParameters(char s[]){
    //Format:
//    leftOriented,baseWidth,baseHeight,distanceFromCenter,restitution,
//    friction
    
    char *token = strtok (s,",");
    int i = 0;
    while (token != NULL)
    {
        //printf ("%s\n",token);
        if(i==0){
            this->leftOriented = int(atof(token));
        }else if(i==1){
            this->baseWidth = atof(token);
        }else if(i==2){
            this->baseHeight = atof(token);
        }else if(i==3){
            this->distanceFromCenter = atof(token);
        }else if(i==4){
            this->restitution = atof(token);
        }else if(i==5){
            this->friction = atof(token);
        }
        
        i++;
        token = strtok (NULL,",");
    }
}
