//
//  Renderer.h
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __pixelrender__Renderer__
#define __pixelrender__Renderer__

#include <stdio.h>
#include "FrameBuffer.h"

class Renderer
{
public:
    Renderer() { };
    ~Renderer() { };
    
    void Render( FrameBuffer* i_frameBuffer );
};

#endif /* defined(__pixelrender__Renderer__) */
