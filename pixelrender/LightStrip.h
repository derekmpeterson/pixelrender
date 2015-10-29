//
//  LightStrip.h
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __pixelrender__LightStrip__
#define __pixelrender__LightStrip__

#include <stdio.h>
#include <vector>
#include <string>
#include "Pixel.h"
#include "Vector3d.h"
#include "UDPClient.h"
#include "LightStripSegment.h"

class LightStrip
{
public:
    LightStrip( uint16_t i_pixelCount );
    ~LightStrip();
    
    std::vector<LightStripSegment*> GetSegments() { return m_segments; };
    void AddSegment(LightStripSegment* i_segment) {
        m_segments.push_back(i_segment);
    }
private:
    uint16_t m_pixelCount;
    
    std::vector<LightStripSegment*> m_segments;
    
};

#endif /* defined(__pixelrender__LightStrip__) */
