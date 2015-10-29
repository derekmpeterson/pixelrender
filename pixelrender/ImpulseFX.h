//
//  ImpulseFX.h
//  
//
//  Created by Derek Peterson on 10/29/15.
//
//

#ifndef ____ImpulseFX__
#define ____ImpulseFX__

#include <stdio.h>
#include "Pixel.h"
#include "FX.h"

class ImpulseFX : public FX
{
public:
    virtual void Impulse( RGBA i_color, float i_impulseLength );
    
    void SetActive( bool i_active ) {
        m_active = i_active;
    }
    bool m_active;
private:
};


#endif /* defined(____ImpulseFX__) */
