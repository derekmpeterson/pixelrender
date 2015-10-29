//
//  LightStripSegment.cpp
//  pixelrender
//
//  Created by Derek Peterson on 10/29/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#include "LightStripSegment.h"
#include "FrameBuffer.h"

LightStripSegment::LightStripSegment( uint16_t i_pixelCount, Vector3d i_position, Vector3d i_direction )
{
    m_pixelCount = i_pixelCount;
    m_position = i_position;
    m_direction = i_direction;
    m_pixels.resize( i_pixelCount );
    
    FrameBuffer* pFrameBuffer = FrameBuffer::Instance();
    
    RGBA pColor = RGBA( 0, 0, 0, 0 );
    Vector3d pPixelPos = m_position;
    for( int i = 0; i < m_pixelCount; i++ )
    {
        m_pixels[i] = new Pixel( pColor, pPixelPos );
        pFrameBuffer->AddPixel( m_pixels[i] );
        pPixelPos += m_direction;
    }
};

LightStripSegment::LightStripSegment()
{
    FrameBuffer* pFrameBuffer = FrameBuffer::Instance();
    
    for( int i = 0; i < m_pixelCount; i++ )
    {
        pFrameBuffer->RemovePixel( m_pixels[i] );
        delete m_pixels[i];
        m_pixels[i] = NULL;
    }
};