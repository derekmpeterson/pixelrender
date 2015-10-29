//
//  FlashFX.cpp
//  
//
//  Created by Derek Peterson on 10/29/15.
//
//

#include "FlashFX.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

FlashFX::FlashFX(RGBA i_color, AABB i_extents, float i_speed, int i_flashCount, float i_flashSpeed ) : m_color( i_color ), m_extents( i_extents ), m_speed( i_speed ), m_flashCount( i_flashCount ), m_flashSpeed( i_flashSpeed )
{
    
    m_tickRate = m_flashSpeed;
    m_tickCounter = m_tickRate;
    m_on = true;
    m_performedCount = 0;
}

FlashFX::~FlashFX()
{
    
}

void FlashFX::Update(double i_dt)
{
    m_tickCounter += i_dt;
    if ( m_tickCounter >= m_tickRate && m_performedCount < m_flashCount )
    {
        m_tickCounter = 0.0f;
        
        FrameBuffer* pFrameBuffer = FrameBuffer::Instance();
        for ( int i = 0; i < pFrameBuffer->GetPixelCount(); i++ )
        {
            Pixel* pPixel = pFrameBuffer->GetPixelAt( i );
            if ( pPixel && m_extents.InBounds( pPixel->GetPosition() ) )
            {
                if ( m_on )
                    pPixel->SetColor( m_color );
                else
                    pPixel->SetColor( RGBA( 0, 0, 0, 0 ) );
            }
        }
        if ( m_on )
        {
            m_on = false;
        } else {
            m_on = true;
            m_performedCount++;
        }
    }
    Vector3d moveDir = ( m_extents.GetRotation().GetZAxis() * m_speed * i_dt );
    m_extents.SetPosition( m_extents.GetPosition() + moveDir );
}

bool FlashFX::IsActive()
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
    
    if ( m_performedCount >= m_flashCount )
        return false;
    
    return true;
}
