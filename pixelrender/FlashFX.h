//
//  FlashFX.h
//  
//
//  Created by Derek Peterson on 10/29/15.
//
//

#ifndef ____FlashFX__
#define ____FlashFX__

#include <stdio.h>

#include "FX.h"
#include "AABB.h"
#include "FrameBuffer.h"

class FlashFX : public FX
{
public:
    FlashFX(RGBA i_color, AABB i_extents, float i_speed, int i_flashCount, float i_flashSpeed);
    ~FlashFX();
    virtual void Update(double i_dt);
    virtual bool IsActive();
    
private:
    AABB m_extents;
    float m_speed;
    double m_tickRate;
    double m_tickCounter;
    RGBA m_color;
    bool m_on;
    int m_flashCount;
    int m_performedCount;
    float m_flashSpeed;
};

#endif /* defined(____FlashFX__) */
