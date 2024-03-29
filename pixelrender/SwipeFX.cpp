//
//  SwipeFX.cpp
//  pixelrender
//
//  Created by Derek Peterson on 10/11/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#include "SwipeFX.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

SwipeFX::SwipeFX(RGBA i_color, AABB i_extents, float i_speed ) : m_color( i_color ), m_extents( i_extents ), m_speed( i_speed )
{
   
    m_tickRate = 0.0f;
    m_tickCounter = 0.0f;
}

SwipeFX::~SwipeFX()
{
    
}

void SwipeFX::Update(double i_dt)
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
                pPixel->FadeColor( m_color, 0.05f );
                //pPixel->SetColor( m_color );
            }
        }
    }
    Vector3d moveDir = ( m_extents.GetRotation().GetZAxis() * m_speed * i_dt );
    m_extents.SetPosition( m_extents.GetPosition() + moveDir );
}

bool SwipeFX::IsActive()
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