//
//  MarchFX.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/29/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#ifndef MarchFX_hpp
#define MarchFX_hpp

#include <stdio.h>
#include "FX.h"
#include "AABB.h"
#include "FrameBuffer.h"

struct MarchBox
{
public:
    MarchBox( AABB i_extents, RGBA i_color ) : m_extents( i_extents ), m_color( i_color ) {};
    AABB m_extents;
    RGBA m_color;
};

class MarchFX : public FX
{
public:
    MarchFX(RGBA i_color, AABB i_extents, float i_speed);
    ~MarchFX();
    virtual void Update(double i_dt);
    virtual bool IsActive();
    
private:
    void CreateMarchBoxPair( Vector3d i_position );
    
    AABB m_extents;
    float m_speed;
    double m_tickRate;
    double m_tickCounter;
    RGBA m_color;
    int m_marchSize;
    int m_marchSkip;
    float m_marchSpeed;
    
    std::vector<MarchBox*> m_marchBoxes;
};

#endif /* MarchFX_hpp */
