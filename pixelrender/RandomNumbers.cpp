//
//  RandomNumbers.cpp
//  pixelrender
//
//  Created by Derek Peterson on 10/11/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#include "RandomNumbers.h"
#include <cstdlib>

int RandomInt( int i_min, int i_max ) {
    return i_min + ( rand() * ( i_max - i_min ) );
}

float RandomFloat( float i_min, float i_max ) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = i_max - i_min;
    float r = random * diff;
    return i_min + r;
}