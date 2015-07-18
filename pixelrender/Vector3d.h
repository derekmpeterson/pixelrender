//
//  Vector3d.h
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __pixelrender__Vector3d__
#define __pixelrender__Vector3d__

#include <stdio.h>
#include <stdint.h>

class Vector3d
{
public:
    Vector3d() : m_X( 0 ), m_Y( 0 ), m_Z( 0 ) { };
    Vector3d( uint8_t i_X, uint8_t i_Y, uint8_t i_Z ) : m_X( i_X ), m_Y( i_Y ), m_Z( i_Z ) { };
    uint8_t GetX() const { return m_X; };
    uint8_t GetY() const { return m_Y; };
    uint8_t GetZ() const { return m_Z; };
    void SetX( uint8_t i_X ) { m_X = i_X; };
    void SetY( uint8_t i_Y ) { m_Y = i_Y; };
    void SetZ( uint8_t i_Z ) { m_Z = i_Z; };
    
    Vector3d& operator+=( const Vector3d& other ) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        this->SetX( this->GetX() + other.GetX() );
        this->SetY( this->GetY() + other.GetY() );
        this->SetZ( this->GetZ() + other.GetZ() );
        return *this; // return the result by reference
    }
private:
    uint8_t m_X, m_Y, m_Z;
};

#endif /* defined(__pixelrender__Vector3d__) */
