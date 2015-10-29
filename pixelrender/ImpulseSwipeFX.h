//
//  ImpulseSwipeFX.h
//  
//
//  Created by Derek Peterson on 10/29/15.
//
//

#ifndef ____ImpulseSwipeFX__
#define ____ImpulseSwipeFX__

#include <stdio.h>

#include "ImpulseFX.h"
#include "AABB.h"
#include "FrameBuffer.h"

class ImpulseSwipeFX : public ImpulseFX
{
public:
    ImpulseSwipeFX(AABB i_extents, float i_speed);
    ~ImpulseSwipeFX();
    virtual void Update(double i_dt);
    virtual void Impulse(RGBA i_color, float i_impulseLength);
    virtual bool IsActive();
    
private:
    AABB m_extents;
    float m_speed;
    int m_dir;
    
};


#endif /* defined(____ImpulseSwipeFX__) */
