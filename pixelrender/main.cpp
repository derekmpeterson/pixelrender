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
#include "Photon.h"
#include "LightStripSegment.h"
#include "RotMat.h"

typedef std::vector<Photon*> PhotonVector;

int main(int argc, const char * argv[]) {
    srand( (int) time(NULL) );
    ShowRenderer* pShowRenderer = ShowRenderer::Instance();
    
    // LightStrip config is hardcoded and ugly for now.  Eventually this will be loaded in from a config file.
    PhotonVector pPhotons;
    
    Photon* pLightsTwo = new Photon( "192.168.1.195" ); // left big window
    LightStrip* pLightsTwo_Strip1 = new LightStrip( 160 );
    pLightsTwo_Strip1->AddSegment( new LightStripSegment( 50, Vector3d( 126, 0, 174 ), Vector3d( 1.3, 0, 0 ) ) );
    pLightsTwo_Strip1->AddSegment( new LightStripSegment( 53, Vector3d( 195, 0, 174 ), Vector3d( 0, 1.3, 0 ) ) );
    pLightsTwo_Strip1->AddSegment( new LightStripSegment( 50, Vector3d( 195, 70, 174 ), Vector3d( -1.3, 0, 0 ) ) );
    pLightsTwo->AddLightStrip( pLightsTwo_Strip1 );
    pPhotons.push_back(pLightsTwo);
    
    Photon* pLightsOne = new Photon( "192.168.1.143" ); // right back window
    LightStrip* pLightsOne_Strip1 = new LightStrip( 160 );
    pLightsOne_Strip1->AddSegment( new LightStripSegment( 22, Vector3d( 228, 0, 38 ), Vector3d( 0, 0, -1.3 ) ) );
    pLightsOne_Strip1->AddSegment( new LightStripSegment( 53, Vector3d( 228, 0, 10 ), Vector3d( 0, 1.3, 0 ) ) );
    pLightsOne_Strip1->AddSegment( new LightStripSegment( 22, Vector3d( 228, 70, 10 ), Vector3d( 0, 0, 1.3 ) ) );
    pLightsOne_Strip1->AddSegment( new LightStripSegment( 53, Vector3d( 228, 70, 38 ), Vector3d( 0, -1.3, 0 ) ) );
    pLightsOne->AddLightStrip( pLightsOne_Strip1 );
    
    LightStrip* pLightsOne_Strip2 = new LightStrip( 50 ); // green strand
    pLightsOne_Strip2->AddSegment( new LightStripSegment( 50, Vector3d( 204, 0, 0 ), Vector3d( -2.4, 0, 0 ) ) );
    pLightsOne->AddLightStrip( pLightsOne_Strip2 );
    pPhotons.push_back(pLightsOne);
    
    Photon* pPhotonOne = new Photon( "192.168.1.147" ); // left back window
    LightStrip* pPhotonOne_Strip1 = new LightStrip( 160 );
    pPhotonOne_Strip1->AddSegment( new LightStripSegment( 22, Vector3d( 228, 0, 158 ), Vector3d( 0, 0, -1.3 ) ) );
    pPhotonOne_Strip1->AddSegment( new LightStripSegment( 53, Vector3d( 228, 0, 130 ), Vector3d( 0, 1.3, 0 ) ) );
    pPhotonOne_Strip1->AddSegment( new LightStripSegment( 22, Vector3d( 228, 70, 130 ), Vector3d( 0, 0, -1.3 ) ) );
    pPhotonOne_Strip1->AddSegment( new LightStripSegment( 53, Vector3d( 228, 70, 158 ), Vector3d( 0, -1.3, 0 ) ) );
    pPhotonOne->AddLightStrip( pPhotonOne_Strip1 );
    pPhotons.push_back(pPhotonOne);
    
    Photon* pPirateRaptor = new Photon( "192.168.1.150" ); // ghosts
    LightStrip* pPirateRaptor_Strip1 = new LightStrip( 0 );
    pPirateRaptor->AddLightStrip( pPirateRaptor_Strip1 );
    LightStrip* pPirateRaptor_Strip2 = new LightStrip( 50 );
    pPirateRaptor_Strip2->AddSegment( new LightStripSegment( 50, Vector3d( 0, 200, 0 ), Vector3d( 10, -1, 10 ) ) );
    pPirateRaptor->AddLightStrip( pPirateRaptor_Strip2 );
    pPhotons.push_back(pPirateRaptor);
    
    std::cout << "Initialized the grid." << std::endl;
    
    pShowRenderer->Start( "thisIsHalloween" );
    while(1)
    {
        double dt = 1.0f / 30.0f; // We should probably set a desired framerate, but calculate the actual delta...
        pShowRenderer->Render( dt );
        
        for ( int i = 0; i < pPhotons.size(); i++ )
        {
            Photon* pPhoton = pPhotons[i];
            if (pPhoton)
            {
                pPhoton->Render();
            }
        }
        
        // Sleep for dt seconds
        usleep( (int)( CLOCKS_PER_SEC * dt ) );
    }
    return 0;
}
