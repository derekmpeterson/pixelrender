//
//  SwipeFX.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/11/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#ifndef SwipeFX_hpp
#define SwipeFX_hpp

#include <stdio.h>
#include "FX.h"
#include "AABB.h"
#include "FrameBuffer.h"

class SwipeFX : public FX
{
public:
    SwipeFX(RGBA i_color, AABB i_extents, Vector3d i_velocity);
    ~SwipeFX();
    virtual void Update(double i_dt);
    
private:
    AABB m_extents;
    Vector3d m_velocity;
    double m_tickRate;
    double m_tickCounter;
    RGBA m_color;
};

#endif /* SwipeFX_hpp */