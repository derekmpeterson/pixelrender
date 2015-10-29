//
//  Photon.hpp
//  pixelrender
//
//  Created by Derek Peterson on 10/29/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#ifndef Photon_hpp
#define Photon_hpp

#include <stdio.h>
#include <vector>
#include "LightStrip.h"

class Photon
{
public:
    Photon( std::string i_ipAddress );
    ~Photon();
    std::vector<LightStrip*> GetStrips() { return m_lightStrips; };
    
    void Render();
    
    void AddLightStrip( LightStrip* i_lightStrip ) {
        m_lightStrips.push_back( i_lightStrip );
    }
private:
    std::vector<LightStrip*> m_lightStrips;
        
    std::string m_ipAddress;
    std::string m_lastPacket;
    
    boost::asio::io_service m_ioservice;
    UDPClient* m_client;
    
    char SafeValue( float i_value );

    
};

#endif /* Photon_hpp */
