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
#include "FX.h"

typedef std::vector<FX*> FXVector;

class ShowRenderer
{
public:
    ShowRenderer();
    ~ShowRenderer() { };
    
    static ShowRenderer* Instance();
    
    void Start();    
    void Render( double i_dt );
    
    void AddFX( FX* i_fx );
    void RemoveFX( FX* i_fx );
    
private:
    static ShowRenderer* m_pInstance;
    FXVector m_activeFX;
    
    double m_events[50000];
    int m_lastEvent;
    std::chrono::high_resolution_clock::time_point m_startTime;
};

#endif /* defined(__pixelrender__ShowRenderer__) */
