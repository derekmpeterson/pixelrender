//
//  AABB.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/11/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#ifndef AABB_hpp
#define AABB_hpp

#include <stdio.h>
#include "Vector3d.h"
#include "RotMat.h"

struct AABB
{
private:
    Vector3d m_position;
    Vector3d m_minExtents;
    Vector3d m_maxExtents;
    RotMat m_rotation;
public:
    AABB( Vector3d i_position, RotMat i_rotation, Vector3d i_minExtents, Vector3d i_maxExtents ) : m_position( i_position ), m_rotation( i_rotation ), m_minExtents( i_minExtents ), m_maxExtents( i_maxExtents ) {};
    ~AABB() {};
    
    void SetPosition( Vector3d i_position ) { m_position = i_position; };
    void SetMinExtents( Vector3d i_minExtents ) { m_minExtents = i_minExtents; };
    void SetMaxExtents( Vector3d i_maxExtents ) { m_maxExtents = i_maxExtents; };
    void SetRotation( RotMat i_rotation ) { m_rotation = i_rotation; };
    
    Vector3d GetPosition() { return m_position; };
    Vector3d GetMinExtents() { return m_minExtents; };
    Vector3d GetMaxExtents() { return m_maxExtents; };
    RotMat GetRotation() { return m_rotation; };
    
    bool InBounds( Vector3d i_point ) {
        Vector3d pTmpMinExtents = m_rotation * m_minExtents;
        Vector3d pTmpMaxExtents = m_rotation * m_maxExtents;
        Vector3d pMinExtents = Vector3d(
                                        pTmpMinExtents.GetX() < pTmpMaxExtents.GetX() ? pTmpMinExtents.GetX() : pTmpMaxExtents.GetX(),
                                        pTmpMinExtents.GetY() < pTmpMaxExtents.GetY() ? pTmpMinExtents.GetY() : pTmpMaxExtents.GetY(),
                                        pTmpMinExtents.GetZ() < pTmpMaxExtents.GetZ() ? pTmpMinExtents.GetZ() : pTmpMaxExtents.GetZ()
                                        );
        Vector3d pMaxExtents = Vector3d(
                                        pTmpMinExtents.GetX() > pTmpMaxExtents.GetX() ? pTmpMinExtents.GetX() : pTmpMaxExtents.GetX(),
                                        pTmpMinExtents.GetY() > pTmpMaxExtents.GetY() ? pTmpMinExtents.GetY() : pTmpMaxExtents.GetY(),
                                        pTmpMinExtents.GetZ() > pTmpMaxExtents.GetZ() ? pTmpMinExtents.GetZ() : pTmpMaxExtents.GetZ()
                                        );
        Vector3d pWorldMinExtents = m_position + pMinExtents;
        Vector3d pWorldMaxExtents = m_position + pMaxExtents;
        if ( i_point.GetX() >= pWorldMinExtents.GetX() &&
            i_point.GetY() >= pWorldMinExtents.GetY() &&
            i_point.GetZ() >= pWorldMinExtents.GetZ() &&
            i_point.GetX() <= pWorldMaxExtents.GetX() &&
            i_point.GetY() <= pWorldMaxExtents.GetY() &&
            i_point.GetZ() <= pWorldMaxExtents.GetZ() )
            return true;
        else
            return false;
    }
};

#endif /* AABB_hpp */
