//
//  FirelightFX.cpp
//  pixelrender
//
//  Created by Derek Peterson on 10/11/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#include "FirelightFX.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "RandomNumbers.h"
#include "FrameBuffer.h"

FirelightFX::FirelightFX(AABB i_extents, float i_speed ) : m_extents( i_extents ), m_speed( i_speed )
{  
    m_tickRate = 0.3f;
    m_tickCounter = 0.0f;
}

FirelightFX::~FirelightFX()
{
    
}

void FirelightFX::Update(double i_dt)
{
    m_tickCounter += i_dt;
    if ( m_tickCounter >= m_tickRate )
    {
        m_tickCounter = 0.0f;
        
        FrameBuffer* pFrameBuffer = FrameBuffer::Instance();
        for ( int i = 0; i < pFrameBuffer->GetPixelCount(); i++ )
        {
            Pixel* pPixel = pFrameBuffer->GetPixelAt( i );
            if ( pPixel && m_extents.InBounds( pPixel->GetPosition() ) )
            {
                uint8_t r, g, b, bri;
                if ( (int) pPixel->GetColor().GetBri() > 180 )
                    bri = (uint8_t) RandomInt( 0, 127 );
                else
                    bri = (uint8_t) RandomInt( 0, 255 );
                
                if ( bri > 127 )
                {
                    r = 210;
                    g = 118;
                    b = 20;
                } else {
                    r = 210;
                    g = 105;
                    b = 0;
                }
                
                RGBA pColor = RGBA( r, g, b, bri );
                pPixel->FadeColor( pColor, m_tickRate );
            }
        }
    }
    Vector3d moveDir = ( m_extents.GetRotation().GetZAxis() * m_speed * i_dt );
    m_extents.SetPosition( m_extents.GetPosition() + moveDir );
}

bool FirelightFX::IsActive()
{
    if ( std::abs( m_extents.GetPosition().GetX() ) > FrameBuffer::Instance()->GetXSize() )
    {
        return false;
    }
    if ( std::abs( m_extents.GetPosition().GetY() ) > FrameBuffer::Instance()->GetYSize() )
    {
        return false;
    }
    if ( std::abs( m_extents.GetPosition().GetZ() ) > FrameBuffer::Instance()->GetZSize() )
    {
        return false;
    }
    
    return true;
}