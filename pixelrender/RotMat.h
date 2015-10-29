//
//  RotMat.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/29/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#ifndef RotMat_hpp
#define RotMat_hpp

#include <stdio.h>
#include "Vector3d.h"

class RotMat
{
public:
    RotMat( Vector3d i_xAxis, Vector3d i_yAxis, Vector3d i_zAxis) : m_xAxis( i_xAxis ), m_yAxis( i_yAxis ), m_zAxis( i_zAxis ) {};
    RotMat() : m_xAxis( Vector3d( 1.0f, 0.0f, 0.0f ) ), m_yAxis( Vector3d( 0.0f, 1.0f, 0.0f ) ), m_zAxis( Vector3d( 0.0f, 0.0f, 1.0f ) ) {};
    ~RotMat() {};
    
    Vector3d GetXAxis() { return m_xAxis; };
    Vector3d GetYAxis() { return m_yAxis; };
    Vector3d GetZAxis() { return m_zAxis; };
    
    void SetXAxis( Vector3d i_xAxis ) { m_xAxis = i_xAxis; };
    void SetYAxis( Vector3d i_yAxis ) { m_yAxis = i_yAxis; };
    void SetZAxis( Vector3d i_zAxis ) { m_zAxis = i_zAxis; };

    Vector3d operator* ( const Vector3d i_vector )
    {
        Vector3d pVector;
        pVector.SetX( i_vector.GetX() * m_xAxis.GetX() + i_vector.GetY() * m_xAxis.GetY() + i_vector.GetZ() * m_xAxis.GetZ() );
        pVector.SetY( i_vector.GetX() * m_yAxis.GetX() + i_vector.GetY() * m_yAxis.GetY() + i_vector.GetZ() * m_yAxis.GetZ() );
        pVector.SetZ( i_vector.GetX() * m_zAxis.GetX() + i_vector.GetY() * m_zAxis.GetY() + i_vector.GetZ() * m_zAxis.GetZ() );
        
        return pVector;
    }
    
private:
    Vector3d m_xAxis;
    Vector3d m_yAxis;
    Vector3d m_zAxis;
};

#endif /* RotMat_hpp */
