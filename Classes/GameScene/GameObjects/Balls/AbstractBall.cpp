//
//  AbstractBall.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 15/07/16.
//
//

#include "AbstractBall.hpp"

void AbstractBall::reduce_health(int amount){
    health = health - amount;
}
