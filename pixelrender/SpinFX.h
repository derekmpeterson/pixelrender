//
//  SpinFX.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/29/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#ifndef SpinFX_hpp
#define SpinFX_hpp

#include <stdio.h>

#include "FX.h"
#include "AABB.h"
#include "FrameBuffer.h"

class SpinFX : public FX
{
public:
    SpinFX(RGBA i_color, AABB i_extents, Vector3d i_velocity);
    ~SpinFX();
    virtual void Update(double i_dt);
    virtual bool IsActive();
    
private:
    AABB m_extents;
    Vector3d m_velocity;
    double m_tickRate;
    double m_tickCounter;
    RGBA m_color;
};

#endif /* SpinFX_hpp */
