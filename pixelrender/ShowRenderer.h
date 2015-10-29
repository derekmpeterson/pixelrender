//
//  ShowRenderer.h
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __pixelrender__ShowRenderer__
#define __pixelrender__ShowRenderer__

#include <stdio.h>
#include "FrameBuffer.h"

#include <vector>
#include <chrono>
#include <string>
#include "FX.h"
#include "ImpulseFX.h"

typedef std::vector<FX*> FXVector;

struct ShowEvent
{
public:
    ShowEvent( float i_time, std::string i_command ) : m_time( i_time ), m_command( i_command ) {};
    float m_time;
    std::string m_command;
};

class ShowRenderer
{
public:
    ShowRenderer();
    ~ShowRenderer() { };
    
    static ShowRenderer* Instance();
    
    void Start( std::string i_command );
    void Render( double i_dt );
    
    void AddFX( FX* i_fx );
    void RemoveFX( FX* i_fx );
    
    void ChangeMode( std::string i_mode );
    
private:
    static ShowRenderer* m_pInstance;
    FXVector m_activeFX;
    
    std::vector<float> m_beats;
    std::vector<ShowEvent> m_events;
    std::chrono::high_resolution_clock::time_point m_startTime;
    ImpulseFX* m_impulseFX;
};

#endif /* defined(__pixelrender__ShowRenderer__) */
