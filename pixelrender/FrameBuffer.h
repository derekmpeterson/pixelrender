//
//  FrameBuffer.h
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __pixelrender__FrameBuffer__
#define __pixelrender__FrameBuffer__

#include <stdio.h>
#include <map>

#include "Pixel.h"

typedef std::map<uint8_t,std::map<uint8_t,std::map<uint8_t,Pixel*>>> PixelGrid3d;

class FrameBuffer
{
public:
    static FrameBuffer* Instance();
    int GetXSize() { return m_xSize; };
    int GetYSize() { return m_ySize; };
    int GetZSize() { return m_zSize; };
    
    PixelGrid3d m_pixels;
private:
    FrameBuffer( int i_xSize, int i_ySize, int i_zSize );
    FrameBuffer(FrameBuffer const&){};             // copy constructor is private
    FrameBuffer& operator=(FrameBuffer const&) { return *this; };  // assignment operator is private

    ~FrameBuffer();
    int m_xSize, m_ySize, m_zSize;
    
    static FrameBuffer* m_pInstance;
};

#endif /* defined(__pixelrender__FrameBuffer__) */
