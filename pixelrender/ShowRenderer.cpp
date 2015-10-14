//
//  ShowRenderer.cpp
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "ShowRenderer.h"

#include "SwipeFX.h"
#include "FirelightFX.h"
#include <random>
#include <iostream>

// Global static pointer used to ensure a single instance of the class.
ShowRenderer* ShowRenderer::m_pInstance = NULL;

ShowRenderer* ShowRenderer::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new ShowRenderer();
    return m_pInstance;
}

ShowRenderer::ShowRenderer()
{
    // Let's add a bunch of SwipeFX as a demo show
    this->AddFX( new SwipeFX(
                             RGBA( 255, 0, 255, 255 ),
                             AABB(
                                  Vector3d( 0, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 0, 0, 0, 0 ),
                             AABB(
                                  Vector3d( -50, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 255, 0, 0, 255 ),
                             AABB(
                                  Vector3d( -150, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 0, 0, 0, 0 ),
                             AABB(
                                  Vector3d( -200, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 255, 127, 0, 255 ),
                             AABB(
                                  Vector3d( -300, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 0, 0, 0, 0 ),
                             AABB(
                                  Vector3d( -350, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 0, 255, 0, 255 ),
                             AABB(
                                  Vector3d( -450, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 0, 0, 0, 0 ),
                             AABB(
                                  Vector3d( -500, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 0, 255, 255, 255 ),
                             AABB(
                                  Vector3d( -600, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 0, 0, 0, 0 ),
                             AABB(
                                  Vector3d( -650, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 0, 0, 255, 255 ),
                             AABB(
                                  Vector3d( -750, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
    
    this->AddFX( new SwipeFX(
                             RGBA( 0, 0, 0, 0 ),
                             AABB(
                                  Vector3d( -800, 0, 0 ),
                                  Vector3d( -6, -15, -15 ),
                                  Vector3d( 6, 15, 15 )
                                  ),
                             Vector3d( 100, 0, 0 ) ) );
};

void ShowRenderer::Start()
{
    m_startTime = std::chrono::high_resolution_clock::now();
}

void ShowRenderer::Render( double i_dt)
{
    FrameBuffer* pFrameBuffer = FrameBuffer::Instance();
    
    for ( int i = 0; i < m_activeFX.size(); i++ )
    {
        m_activeFX[i]->Update( i_dt );
    }
    
    pFrameBuffer->Update( i_dt );
}

void ShowRenderer::AddFX( FX* i_fx )
{
    m_activeFX.push_back(i_fx);
}

void ShowRenderer::RemoveFX( FX* i_fx )
{
    FXVector::iterator position = std::find( m_activeFX.begin(), m_activeFX.end(), i_fx );
    if ( position != m_activeFX.end() )
        m_activeFX.erase( position );
}