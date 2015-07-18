//
//  FrameBuffer.cpp
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "FrameBuffer.h"

// Global static pointer used to ensure a single instance of the class.
FrameBuffer* FrameBuffer::m_pInstance = NULL;


FrameBuffer::FrameBuffer( int i_xSize, int i_ySize, int i_zSize ) :
m_xSize( i_xSize ), m_ySize( i_ySize ), m_zSize( i_zSize )
{
};

FrameBuffer::~FrameBuffer()
{
};

FrameBuffer* FrameBuffer::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new FrameBuffer( 100, 10, 10 );
    return m_pInstance;
}
