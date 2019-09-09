//
//  StaticBoardInitialParameters.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 25/09/16.
//
//

#include "StaticBoardInitialParameters.hpp"

StaticBoardInitialParameters::StaticBoardInitialParameters(){
    this->orientation = 0;
    this->heightHalf = 0.75;
    this->widthHalf = 0.05;
    this->initialPosition.set(4.0, 1.3);
    this->angleInclinationInitial = 0.0;
    this->bonusRadius = 0.12;
    this->boardDensity = 200.0;
    this->boardRestitution = 0.7;
    this->paddingGap = 0.02;
    this->amplitudeOscillationX = 0.0;
    this->frequencyOscillationX = 0.0;
    this->amplitudeOscillationY = 0.0;
    this->frequencyOscillationY = 0.0;
}

StaticBoardInitialParameters::StaticBoardInitialParameters(char s[]){
    //Format:
//    orientation,heightHalf,widthHalf,initialPosition.x,initialPosition.y,
//    angleInclinationInitial,bonusRadius,boardDensity,boardRestitution,
//    paddingGap,amplitudeOscillationX, frequencyOscillationX, amplitudeOscillationY, frequencyOscillationY
    
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
            this->initialPosition.x = atof(token);
        }else if(i==4){
            this->initialPosition.y = atof(token);
        }else if(i==5){
            this->angleInclinationInitial = atof(token);
        }else if(i==6){
            this->bonusRadius = atof(token);
        }else if(i==7){
            this->boardDensity = atof(token);
        }else if(i==8){
            this->boardRestitution = atof(token);
        }else if(i==9){
            this->paddingGap = atof(token);
        }else if(i==10){
            this->amplitudeOscillationX = atof(token);
        }else if(i==11){
            this->frequencyOscillationX = atof(token);
        }else if(i==12){
            this->amplitudeOscillationY = atof(token);
        }else if(i==13){
            this->frequencyOscillationY = atof(token);
        }
        
        i++;
        token = strtok (NULL,",");
    }

}
