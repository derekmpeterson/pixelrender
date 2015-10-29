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
#include "FlashFX.h"
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include "ImpulseFlashFX.h"
#include "ImpulseSwipeFX.h"

using namespace std;

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
    m_impulseFX = NULL;
};

void ShowRenderer::Start( std::string i_command )
{
    m_activeFX.clear();
    
    
    if ( std::strcmp( i_command.c_str(), "firelight" ) == 0 )
    {
        this->AddFX( new FirelightFX(
                                     AABB(
                                          Vector3d( 150, 0, 150 ),
                                          RotMat( Vector3d( 0.0f, 0.0f, -1.0f ), Vector3d( 0.0f, 1.0f, 0.0f ), Vector3d( 1.0f, 0.0f, 0.0f ) ),
                                          Vector3d( -500, -500, -500 ),
                                          Vector3d( 500, 500, 500 )
                                          ),
                                     0.0f ) );
    }
    else
    {
        m_beats.clear();
        ifstream pFile;
        std::string pFilename = "/Users/derek/dev/sparknet/showData/" + i_command + "_beats.csv";
        pFile.open( pFilename );
        string line;
        if ( pFile.is_open() )
        {
            while ( getline ( pFile, line ) )
            {
                float beat = stof( line );
                m_beats.push_back( beat );
            }
            pFile.close();
        } else {
            cout << "Error opening beats file." << endl;
        }
        
        m_events.clear();
        pFilename = "/Users/derek/dev/sparknet/showData/" + i_command + "_labels.csv";
        pFile.open( pFilename );
        if ( pFile.is_open() )
        {
            while ( getline ( pFile, line ) )
            {
                size_t lastTab = line.find_last_of( '\t' );
                size_t firstTab = line.find_last_of( '\t', lastTab - 1 );
                
                float pTime = stof( line.substr(0, firstTab) );
                std::string pCommand = line.substr( lastTab + 1 );

                ShowEvent pEvent = ShowEvent( pTime, pCommand );
                m_events.push_back( pEvent );
            }
            pFile.close();
        } else {
            cout << "Error opening events file." << endl;
        }
        
        ChangeMode( "flash" );
        
        
        m_startTime = std::chrono::high_resolution_clock::now();
        system ( "killall afplay" );
        std::string pPlayCommand = "afplay /Users/derek/dev/sparknet/showData/" + i_command + ".mp3 > /dev/null 2>&1 &";
        system ( pPlayCommand.c_str() );
    }
}

void ShowRenderer::Render( double i_dt)
{
    std::chrono::high_resolution_clock::duration pShowTime = std::chrono::high_resolution_clock::now() - m_startTime;
    float pShowSeconds = ((float) pShowTime.count()) / ((float) std::chrono::high_resolution_clock::period::den);
    
    if ( m_events.size() > 0 )
    {
        while ( m_events[0].m_time <= pShowSeconds )
        {
            if ( m_events.size() <= 0 )
                break;
            
            float pTime = m_events[0].m_time;
            if ( strcmp( m_events[0].m_command.substr( 0, 5 ).c_str(), "mode " ) == 0 )
                ChangeMode( m_events[0].m_command.substr( 5 ) );
            cout << m_events[0].m_command << endl;
            
            m_events.erase ( m_events.begin(), m_events.begin()+1 );
        }
    }
    
    if ( m_beats.size() > 0 )
    {
        while ( m_beats[0] <= pShowSeconds )
        {
            if ( m_beats.size() <= 0 )
                break;
            
            float beat = m_beats[0];
            float pNextBeat = beat + 1.0f;
            if ( m_beats.size() > 1 )
                pNextBeat = m_beats[1];
            float pTimeToNextBeat = pNextBeat - beat;
            if ( pTimeToNextBeat > 0.0f )
            {
                if ( m_impulseFX )
                {
                    m_impulseFX->Impulse( RGBA( 255, 0, 0, 255 ), pTimeToNextBeat * 0.5f );
                }
            }
            
            m_beats.erase ( m_beats.begin(), m_beats.begin()+1 );
        }
    }
    
    FrameBuffer* pFrameBuffer = FrameBuffer::Instance();
    
    for ( int i = 0; i < m_activeFX.size(); i++ )
    {
        if ( m_activeFX[i]->IsActive() )
        {
            m_activeFX[i]->Update( i_dt );
        } else {
            RemoveFX( m_activeFX[i] );
        }
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

void ShowRenderer::ChangeMode( string i_mode )
{
    if ( m_impulseFX )
    {
        m_impulseFX->SetActive( false );
        m_impulseFX = NULL; // Pointer will be deleted in m_activeFX
    }
    if ( strcmp( i_mode.c_str(), "flash" ) == 0 )
    {
        m_impulseFX = new ImpulseFlashFX(
                                         AABB(
                                              Vector3d( 114, 100, 87 ),
                                              RotMat( Vector3d( 0.0f, 0.0f, -1.0f ), Vector3d( 0.0f, 1.0f, 0.0f ), Vector3d( 1.0f, 0.0f, 0.0f ) ),
                                              Vector3d( -120, -120, -120 ),
                                              Vector3d( 120, 120, 120 )
                                              ),
                                         0.0f );
        AddFX( m_impulseFX );
        
    }
    else if ( strcmp( i_mode.c_str(), "chase" ) == 0 )
    {
        m_impulseFX = new ImpulseSwipeFX(
                                         AABB(
                                              Vector3d( 114, 100, 87 ),
                                              RotMat( Vector3d( 0.0f, 0.0f, -1.0f ), Vector3d( 0.0f, 1.0f, 0.0f ), Vector3d( 1.0f, 0.0f, 0.0f ) ),
                                              Vector3d( -120, -120, -120 ),
                                              Vector3d( 120, 120, 120 )
                                              ),
                                         0.0f );
        AddFX( m_impulseFX );
    }
}