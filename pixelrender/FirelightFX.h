//
//  FirelightFX.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/11/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//
//  Causes all Pixels within its bounding box to flicker like a candle
//
//

#ifndef FirelightFX_hpp
#define FirelightFX_hpp

#include <stdio.h>
#include "FX.h"
#include "AABB.h"
#include "FrameBuffer.h"

class FirelightFX : public FX
{
public:
    FirelightFX(AABB i_extents, float m_speed);
    ~FirelightFX();
    virtual void Update(double i_dt);
    virtual bool IsActive();
    
private:
    AABB m_extents;
    float m_speed;
    double m_tickRate;
    double m_tickCounter;
};

#endif /* FirelightFX_hpp */
