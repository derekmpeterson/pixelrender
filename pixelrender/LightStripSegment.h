//
//  LightStripSegment.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/29/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#ifndef LightStripSegment_hpp
#define LightStripSegment_hpp

#include <stdio.h>
#include <vector>
#include "Pixel.h"

class LightStripSegment
{
public:
    LightStripSegment( uint16_t i_pixelCount, Vector3d i_position, Vector3d i_direction );
    LightStripSegment();
    
    std::vector<Pixel*> GetPixels() { return m_pixels; };
private:
    uint16_t m_pixelCount;
    Vector3d m_position;
    Vector3d m_direction;
    std::vector<Pixel*> m_pixels;
};

#endif /* LightStripSegment_hpp */
