//
//  FX.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/11/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#ifndef FX_hpp
#define FX_hpp

#include <stdio.h>

class FX
{
public:
    virtual void Update( double i_dt );
    virtual bool IsActive();
private:
    
};

#endif /* FX_hpp */
