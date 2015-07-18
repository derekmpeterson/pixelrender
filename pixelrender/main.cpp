//
//  main.cpp
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <string>
#include <random>
#include "FrameBuffer.h"
#include "Renderer.h"
#include "LightStrip.h"

int main(int argc, const char * argv[]) {
    srand( (int) time(NULL) );
    Renderer* pRenderer = new Renderer();
    FrameBuffer* pFrameBuffer = FrameBuffer::Instance();

    LightStrip* pLightStrip = new LightStrip( 36, Vector3d( 50, 5, 5 ), Vector3d( 1, 0, 0 ), "192.168.1.129" );
    
    std::cout << "Initialized the grid." << std::endl;
    
    while(1)
    {
        pRenderer->Render( pFrameBuffer );
        pLightStrip->Render();
        usleep( (int)( 1000000.0f / 10.0f ) );
    }
    return 0;
}
