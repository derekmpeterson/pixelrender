//
//  Pixel.cpp
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "Pixel.h"

RGBA RGBAFade::GetColor() {
    float percent = this->GetPercentElapsed();
    
    float rDiff = m_endColor.GetR() - m_startColor.GetR();
    float gDiff = m_endColor.GetG() - m_startColor.GetG();
    float bDiff = m_endColor.GetB() - m_startColor.GetB();
    float briDiff = m_endColor.GetBri() - m_startColor.GetBri();
    
    float r = m_startColor.GetR() + ( rDiff * percent );
    float g = m_startColor.GetG() + ( gDiff * percent );
    float b = m_startColor.GetB() + ( bDiff * percent );
    float bri = m_startColor.GetBri() + ( briDiff * percent );
    
    return RGBA( r, g, b, bri );
}

void RGBAFade::Update( double i_dt )
{
    m_elapsed += i_dt;
}

Pixel::Pixel( RGBA i_color, Vector3d i_position ) :
m_color( i_color ), m_position( i_position )
{
    m_fadeColor = NULL;
}

void Pixel::FadeColor( RGBA i_color, double i_duration ) {
    if ( m_fadeColor )
        delete m_fadeColor;
    m_fadeColor = new RGBAFade( m_color, i_color, i_duration );
}

void Pixel::SetColor( RGBA i_color )
{
    if ( m_fadeColor )
    {
        delete m_fadeColor;
        m_fadeColor = NULL;
    }
    m_color = i_color;
}

float RGBAFade::GetPercentElapsed()
{
    float percent = m_elapsed / m_duration;
    if ( percent > 1.0f )
        percent = 1.0f;
    return percent;
}

void Pixel::Update( double i_dt )
{
    if ( m_fadeColor )
    {
        if ( m_fadeColor->GetPercentElapsed() >= 1.0f )
        {
            delete m_fadeColor;
            m_fadeColor = NULL;
        }
        else
        {
            m_fadeColor->Update( i_dt );
            m_color = m_fadeColor->GetColor();
        }
    }
}
