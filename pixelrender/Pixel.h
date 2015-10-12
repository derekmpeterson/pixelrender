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

struct RGBA
{
public:
    RGBA( float i_r, float i_g, float i_b, float i_bri ) : m_r( i_r ), m_g( i_g ), m_b( i_b ), m_bri( i_bri ) {};
    ~RGBA() {};
    
    float GetR() { return m_r; };
    float GetG() { return m_g; };
    float GetB() { return m_b; };
    float GetBri() { return m_bri; };
    
    void SetR( float i_r ) { m_r = i_r; };
    void SetG( float i_g ) { m_g = i_g; };
    void SetB( float i_b ) { m_b = i_b; };
    void SetBri( float i_bri ) { m_bri = i_bri; };
private:
    float m_r, m_g, m_b, m_bri;
};

struct RGBAFade
{
public:
    RGBAFade( RGBA i_startColor, RGBA i_endColor, double i_duration ) : m_startColor( i_startColor ), m_endColor( i_endColor ), m_duration( i_duration ) {
        m_elapsed = 0.0f;
    };
    ~RGBAFade() {};
    
    RGBA GetColor();
    
    void Update( double i_dt );
    float GetPercentElapsed();
private:
    RGBA m_startColor;
    RGBA m_endColor;
    double m_duration, m_elapsed;
};

class Pixel
{
public:
    Pixel( RGBA i_color, Vector3d i_position );
    ~Pixel() { };
    
    Vector3d GetPosition() { return m_position; };
    void SetPosition( Vector3d i_position ) { m_position = i_position; };
    
    RGBA GetColor() { return m_color; };
    void SetColor( RGBA i_color );
    void FadeColor( RGBA i_color, double i_duration );
    
    void Update( double i_dt );
private:
    RGBA m_color;
    RGBAFade* m_fadeColor;
    Vector3d m_position;
};

#endif /* defined(__pixelrender__Pixel__) */
