//
//  Pixel.h
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __pixelrender__Pixel__
#define __pixelrender__Pixel__

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "Vector3d.h"

class Pixel
{
public:
    Pixel( uint8_t i_r, uint8_t i_g, uint8_t i_b, uint8_t i_bri, Vector3d i_position ) :
    m_r( i_r ), m_g( i_g ), m_b( i_b ), m_bri( i_bri ), m_position( i_position ) {};
    ~Pixel() { };
    
    uint8_t GetR() { return m_r; };
    uint8_t GetG() { return m_g; };
    uint8_t GetB() { return m_b; };
    uint8_t GetBri() { return m_bri; };
    Vector3d GetPosition() { return m_position; };
    
    void SetR( uint8_t i_r ) { assert( i_r <= 255 ); m_r = i_r; };
    void SetG( uint8_t i_g ) { assert( i_g <= 255 ); m_g = i_g; };
    void SetB( uint8_t i_b ) { assert( i_b <= 255 ); m_b = i_b; };
    void SetBri( uint8_t i_bri ) { m_bri = i_bri; };
    void SetPosition( Vector3d i_position ) { m_position = i_position; };
private:
    uint8_t m_r, m_g, m_b, m_bri;
    Vector3d m_position;
};

#endif /* defined(__pixelrender__Pixel__) */
