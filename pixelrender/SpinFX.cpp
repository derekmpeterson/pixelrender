//
//  SpinFX.cpp
//  pixelrender
//
//  Created by Derek Peterson on 10/29/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#include "SpinFX.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

SpinFX::SpinFX(RGBA i_color, AABB i_extents, Vector3d i_velocity ) : m_color( i_color ), m_extents( i_extents ), m_velocity( i_velocity )
{
    
    m_tickRate = 0.0f;
    m_tickCounter = 0.0f;
}

SpinFX::~SpinFX()
{
    
}

void SpinFX::Update(double i_dt)
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
                pPixel->FadeColor( m_color, 0.25f );
            }
        }
    }
    m_extents.SetPosition( m_extents.GetPosition() + ( m_velocity * i_dt ) );
}

bool SpinFX::IsActive()
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