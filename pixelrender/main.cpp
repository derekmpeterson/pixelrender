//
//  main.cpp
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <ctime>
#include <time.h>
#include <string>
#include <random>
#include "FrameBuffer.h"
#include "ShowRenderer.h"
#include "LightStrip.h"
#include "SwipeFX.h"
#include "FirelightFX.h"

typedef std::vector<LightStrip*> LightStripVector;

int main(int argc, const char * argv[]) {
    srand( (int) time(NULL) );
    ShowRenderer* pShowRenderer = ShowRenderer::Instance();
    
    // LightStrip config is hardcoded and ugly for now.  Eventually this will be loaded in from a config file.
    LightStripVector pLightStrips;
    pLightStrips.push_back( new LightStrip( 115, Vector3d( 0, 0, 0 ), Vector3d( 1, 0, 0 ), "192.168.1.147" ) );
    pLightStrips.push_back( new LightStrip( 19
                                           , Vector3d( 40, 0, 0 ), Vector3d( -1, 1, 0 ), "192.168.1.150" ) );
    
    std::cout << "Initialized the grid." << std::endl;
    
    pShowRenderer->Start();
    while(1)
    {
        double dt = 1.0f / 30.0f; // We should probably set a desired framerate, but calculate the actual delta...
        pShowRenderer->Render( dt );
        
        for ( int i = 0; i < pLightStrips.size(); i++ )
        {
            LightStrip* pLightStrip = pLightStrips[i];
            if (pLightStrip)
            {
                pLightStrip->Render();
            }
        }
        
        // Sleep for dt seconds
        usleep( (int)( CLOCKS_PER_SEC * dt ) );
    }
    return 0;
}
