//
//  MarchFX.cpp
//  pixelrender
//
//  Created by Derek Peterson on 10/29/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#include "MarchFX.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

MarchFX::MarchFX(RGBA i_color, AABB i_extents, float i_speed ) : m_color( i_color ), m_extents( i_extents ), m_speed( i_speed )
{
    
    m_tickRate = 0.0f;
    m_tickCounter = 0.0f;
    m_marchSize = 5;
    m_marchSkip = 1 * m_marchSize;
    m_marchSpeed = 1.0f;

    CreateMarchBoxPair( Vector3d( 0.0f, 0.0f, 0.0f ) );
}

MarchFX::~MarchFX()
{
    for ( int i = 0; i < m_marchBoxes.size(); i++ )
    {
        delete m_marchBoxes[i];
        m_marchBoxes[i] = NULL;
    }
}

void MarchFX::Update(double i_dt)
{
    m_tickCounter += i_dt;
    if ( m_tickCounter >= m_tickRate )
    {
        m_tickCounter = 0.0f;
        
        for ( int i = 0; i < m_marchBoxes.size(); i++ )
        {
            MarchBox* pMarchBox = m_marchBoxes[i];
            pMarchBox->m_extents.SetPosition( pMarchBox->m_extents.GetPosition() + m_extents.GetRotation().GetZAxis() * m_marchSpeed );
            
            FrameBuffer* pFrameBuffer = FrameBuffer::Instance();
            for ( int c = 0; c < pFrameBuffer->GetPixelCount(); c++ )
            {
                Pixel* pPixel = pFrameBuffer->GetPixelAt( c );
                if ( pPixel && pMarchBox->m_extents.InBounds( pPixel->GetPosition() ) )
                {
                    pPixel->SetColor( pMarchBox->m_color );
                }
            }
        }
    }
    Vector3d moveDir = ( m_extents.GetRotation().GetZAxis() * m_speed * i_dt );
    m_extents.SetPosition( m_extents.GetPosition() + moveDir );
}

bool MarchFX::IsActive()
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

void MarchFX::CreateMarchBoxPair( Vector3d i_position ) {
    AABB pMarchExtent = AABB( i_position, m_extents.GetRotation(), Vector3d( m_extents.GetMinExtents().GetX(), m_extents.GetMinExtents().GetY(), -m_marchSize * m_marchSpeed ), Vector3d( m_extents.GetMaxExtents().GetX(), m_extents.GetMaxExtents().GetY(), m_marchSize * m_marchSpeed ) );
    MarchBox* pMarchBox = new MarchBox( pMarchExtent, m_color );
    
    
    Vector3d pOffset = m_extents.GetRotation() * Vector3d( 0.0f, 0.0f, -m_marchSkip * m_marchSpeed );
    AABB pSkipExtent = AABB( i_position + pOffset, m_extents.GetRotation(), Vector3d( m_extents.GetMinExtents().GetX(), m_extents.GetMinExtents().GetY(), -m_marchSkip * m_marchSpeed ), Vector3d( m_extents.GetMaxExtents().GetX(), m_extents.GetMaxExtents().GetY(), m_marchSkip * m_marchSpeed ) );
    MarchBox* pSkipBox = new MarchBox( pSkipExtent, RGBA( 0, 0, 255, 255 ) );
    
    m_marchBoxes.push_back(pMarchBox);
    m_marchBoxes.push_back(pSkipBox);
}