//
//  Renderer.cpp
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "Renderer.h"
#include "Pixel.h"
#include <random>

void Renderer::Render( FrameBuffer* i_frameBuffer)
{
    for( int x = 0; x < i_frameBuffer->GetXSize(); x++ )
    {
        for( int y = 0; y < i_frameBuffer->GetYSize(); y++ )
        {
            for( int z = 0; z < i_frameBuffer->GetZSize(); z++ )
            {
                Pixel* pPixel = i_frameBuffer->m_pixels[x][y][z];
                if ( pPixel )
                {
                    uint8_t r = rand() % 255;
                    uint8_t g = rand() % 255;
                    uint8_t b = rand() % 255;
                    uint8_t bri = rand() % 255;
                    
                    pPixel->SetR( r );
                    pPixel->SetG( g );
                    pPixel->SetB( b );
                    pPixel->SetBri( bri );
                }
            }
        }
    }
}