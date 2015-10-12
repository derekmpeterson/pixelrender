//
//  LightStrip.h
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#ifndef __pixelrender__LightStrip__
#define __pixelrender__LightStrip__

#include <stdio.h>
#include <vector>
#include <string>
#include "Pixel.h"
#include "Vector3d.h"
#include "UDPClient.h"

class LightStrip
{
public:
    LightStrip( uint16_t i_pixelCount, Vector3d i_position, Vector3d i_direction, std::string i_ipAddress );
    ~LightStrip();
    
    std::vector<Pixel*> GetPixels() { return m_pixels; };
    
    void Render();
private:
    uint16_t m_pixelCount;
    Vector3d m_position;
    Vector3d m_direction;
    std::vector<Pixel*> m_pixels;
    
    std::string m_ipAddress;
    std::string m_lastPacket;
    
    boost::asio::io_service m_ioservice;
    UDPClient* m_client;
    
    char SafeValue( float i_value );
};

#endif /* defined(__pixelrender__LightStrip__) */
