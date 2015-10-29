//
//  ImpulseSwipeFX.cpp
//  
//
//  Created by Derek Peterson on 10/29/15.
//
//

#include "ImpulseSwipeFX.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ShowRenderer.h"
#include "SwipeFX.h"

ImpulseSwipeFX::ImpulseSwipeFX(AABB i_extents, float i_speed ) : m_extents( i_extents ), m_speed( i_speed )
{
    m_active = true;
    m_dir = 1;
}

ImpulseSwipeFX::~ImpulseSwipeFX()
{
    
}

void ImpulseSwipeFX::Update(double i_dt)
{
    Vector3d moveDir = ( m_extents.GetRotation().GetZAxis() * m_speed * i_dt );
    m_extents.SetPosition( m_extents.GetPosition() + moveDir );
}

void ImpulseSwipeFX::Impulse( RGBA i_color, float i_impulseLength )
{
    ShowRenderer* pShowRenderer = ShowRenderer::Instance();
    if ( pShowRenderer )
    {
        AABB pSwipeExtents = m_extents;
        
        RotMat pRotMat = pSwipeExtents.GetRotation();
        pRotMat.SetZAxis( pRotMat.GetZAxis() * (float)m_dir );
        pRotMat.SetXAxis( pRotMat.GetXAxis() * (float)m_dir );
        pSwipeExtents.SetRotation( pRotMat );
        
        Vector3d pMinExtents = pSwipeExtents.GetMinExtents();
        Vector3d pMaxExtents = pSwipeExtents.GetMaxExtents();
        Vector3d pPosition = pSwipeExtents.GetPosition();
        pPosition = pPosition + ( pSwipeExtents.GetRotation().GetZAxis() * pMinExtents.GetZ() );
        pSwipeExtents.SetPosition( pPosition );
        
        pMinExtents.SetZ( -16.6f );
        pMaxExtents.SetZ( 16.6f );
        pSwipeExtents.SetMinExtents( pMinExtents );
        pSwipeExtents.SetMaxExtents( pMaxExtents );
        
        pShowRenderer->AddFX( new SwipeFX( i_color, pSwipeExtents, 1000.0f ) );
        
        pPosition = pPosition + ( pSwipeExtents.GetRotation().GetZAxis() * ( i_impulseLength * -1000.0f ) );
        pSwipeExtents.SetPosition( pPosition );
        pShowRenderer->AddFX( new SwipeFX( RGBA( 0.0f, 0.0f, 0.0f, 0.0f ), pSwipeExtents, 1000.0f ) );
    }
    if (m_dir == 1)
        m_dir = -1;
    else
        m_dir = 1;
}

bool ImpulseSwipeFX::IsActive()
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
    
    return m_active;
}