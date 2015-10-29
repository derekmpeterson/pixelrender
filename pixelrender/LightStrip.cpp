//
//  LightStrip.cpp
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "LightStrip.h"
#include "FrameBuffer.h"
#include <assert.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iostream>

LightStrip::LightStrip( uint16_t i_pixelCount )
{
    m_pixelCount = i_pixelCount;
};

LightStrip::~LightStrip()
{
    for( int i = 0; i < m_segments.size(); i++ )
    {
        delete m_segments[i];
        m_segments[i] = NULL;
    }
};