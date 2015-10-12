//
//  FirelightFX.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/11/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
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
    FirelightFX(AABB i_extents, Vector3d i_velocity);
    ~FirelightFX();
    virtual void Update(double i_dt);
    
private:
    AABB m_extents;
    Vector3d m_velocity;
    double m_tickRate;
    double m_tickCounter;
};

#endif /* FirelightFX_hpp */
