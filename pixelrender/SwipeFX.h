//
//  SwipeFX.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/11/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//
//
//  SwipeFX moves, causing Pixels to light up while within its bounding box
//  and fade out when it leaves the area
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
    SwipeFX(RGBA i_color, AABB i_extents, float i_speed);
    ~SwipeFX();
    virtual void Update(double i_dt);
    virtual bool IsActive();
    
private:
    AABB m_extents;
    float m_speed;
    double m_tickRate;
    double m_tickCounter;
    RGBA m_color;
};

#endif /* SwipeFX_hpp */
