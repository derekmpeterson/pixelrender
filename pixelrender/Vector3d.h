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
    Vector3d( float i_X, float i_Y, float i_Z ) : m_X( i_X ), m_Y( i_Y ), m_Z( i_Z ) { };
    float GetX() const { return m_X; };
    float GetY() const { return m_Y; };
    float GetZ() const { return m_Z; };
    void SetX( float i_X ) { m_X = i_X; };
    void SetY( float i_Y ) { m_Y = i_Y; };
    void SetZ( float i_Z ) { m_Z = i_Z; };
    
    Vector3d& operator+=( const Vector3d& other ) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        this->SetX( this->GetX() + other.GetX() );
        this->SetY( this->GetY() + other.GetY() );
        this->SetZ( this->GetZ() + other.GetZ() );
        return *this; // return the result by reference
    }
    
    Vector3d operator+( const Vector3d& other )
    {
        Vector3d newVector( this->GetX() + other.GetX(), this->GetY() + other.GetY(), this->GetZ() + other.GetZ() );
        return newVector;
    }
    
    Vector3d& operator*=( const float scalar )
    {
        this->SetX( this->GetX() * scalar );
        this->SetY( this->GetY() * scalar );
        this->SetZ( this->GetZ() * scalar );
        return *this;
    }
    
    Vector3d& operator*=( const double scalar )
    {
        this->SetX( this->GetX() * scalar );
        this->SetY( this->GetY() * scalar );
        this->SetZ( this->GetZ() * scalar );
        return *this;
    }
    
    Vector3d operator* ( float scalar )
    {
        Vector3d newVector = *this;
        newVector *= scalar;
        
        return newVector;
    }
    
    Vector3d operator* ( double scalar )
    {
        Vector3d newVector = *this;
        newVector *= scalar;
        
        return newVector;
    }
    
private:
    float m_X, m_Y, m_Z;
};

#endif /* defined(__pixelrender__Vector3d__) */
