//
//  ImpulseFlashFX.h
//  
//
//  Created by Derek Peterson on 10/29/15.
//
//

#ifndef ____ImpulseFlashFX__
#define ____ImpulseFlashFX__

#include <stdio.h>
#include "ImpulseFX.h"
#include "AABB.h"
#include "FrameBuffer.h"

class ImpulseFlashFX : public ImpulseFX
{
public:
    ImpulseFlashFX(AABB i_extents, float i_speed);
    ~ImpulseFlashFX();
    virtual void Update(double i_dt);
    virtual void Impulse(RGBA i_color, float i_impulseLength);
    virtual bool IsActive();
    
private:
    AABB m_extents;
    float m_speed;
   
};

#endif /* defined(____ImpulseFlashFX__) */
