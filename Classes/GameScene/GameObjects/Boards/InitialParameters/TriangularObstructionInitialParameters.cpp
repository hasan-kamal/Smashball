//
//  TriangularObstructionInitialParameters.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#include "TriangularObstructionInitialParameters.hpp"
#include <string.h>

TriangularObstructionInitialParameters::TriangularObstructionInitialParameters(){
    this->baseWidth = 0.25;
    this->height = 0.75;
    this->initialPosition.set(2.5, 1.3);
    this->angleInclinationInitial = -1.0;
    this->density = 300.0;
    this->restitution = 0.7;
    this->amplitudeOscillationX = 0.0;
    this->frequencyOscillationX = 0.0;
    this->amplitudeOscillationY = 0.0;
    this->frequencyOscillationY = 0.0;
}

TriangularObstructionInitialParameters::TriangularObstructionInitialParameters(char s[]){
    //Format:
//    baseWidth,height,initialPosition.x,initialPosition.y,angleInclinationInitial,
//    density,restitution,amplitudeOscillationX,frequencyOscillationX,
//    amplitudeOscillationY,frequencyOscillationY
    
    char *token = strtok (s,",");
    int i = 0;
    while (token != NULL)
    {
        //printf ("%s\n",token);
        if(i==0){
            this->baseWidth = atof(token);
        }else if(i==1){
            this->height = atof(token);
        }else if(i==2){
            this->initialPosition.x = atof(token);
        }else if(i==3){
            this->initialPosition.y = atof(token);
        }else if(i==4){
            this->angleInclinationInitial = atof(token);
        }else if(i==5){
            this->density = atof(token);
        }else if(i==6){
            this->restitution = atof(token);
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
