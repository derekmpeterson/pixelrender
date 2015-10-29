//
//  ImpulseFlashFX.cpp
//  
//
//  Created by Derek Peterson on 10/29/15.
//
//

#include "ImpulseFlashFX.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ShowRenderer.h"
#include "FlashFX.h"

ImpulseFlashFX::ImpulseFlashFX(AABB i_extents, float i_speed ) : m_extents( i_extents ), m_speed( i_speed )
{
    m_active = true;
}

ImpulseFlashFX::~ImpulseFlashFX()
{
    
}

void ImpulseFlashFX::Update(double i_dt)
{
    Vector3d moveDir = ( m_extents.GetRotation().GetZAxis() * m_speed * i_dt );
    m_extents.SetPosition( m_extents.GetPosition() + moveDir );
}

void ImpulseFlashFX::Impulse( RGBA i_color, float i_impulseLength )
{
    ShowRenderer* pShowRenderer = ShowRenderer::Instance();
    if ( pShowRenderer )
    {
        pShowRenderer->AddFX( new FlashFX(
                                          i_color,
                                          m_extents,
                                          m_speed,
                                          1,
                                          i_impulseLength ) );
    }
}

bool ImpulseFlashFX::IsActive()
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