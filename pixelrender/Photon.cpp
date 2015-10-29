//
//  Photon.cpp
//  pixelrender
//
//  Created by Derek Peterson on 10/29/15.
//  Copyright © 2015 Derek Peterson. All rights reserved.
//

#include "Photon.h"

Photon::Photon(std::string i_ipAddress) : m_ipAddress ( i_ipAddress ) {
    //std::cout << "Connecting to socket..." << std::endl;
    m_client = new UDPClient( m_ioservice, m_ipAddress, "8888" );
    //std::cout << "Connected" << std::endl;
}

Photon::~Photon() {
    delete m_client;
    
    for ( int i = 0; i < m_lightStrips.size(); i++ ) {
        delete m_lightStrips[i];
        m_lightStrips[i] = NULL;
    }
}

void Photon::Render()
{
    // When rendering LightStrips, we create a packet string to send to PixelServer
    // running on the Photon or Spark Core.
    std::string pPacket = "";
    
    for (int s = 0; s < m_lightStrips.size(); s++ )
    {
        LightStrip* pLightStrip = m_lightStrips[s];
        if (pLightStrip)
        {
            for ( int i = 0; i < pLightStrip->GetSegments().size(); i++ )
            {
                LightStripSegment* pSegment = pLightStrip->GetSegments()[i];
                for( int c = 0; c < pSegment->GetPixels().size(); c++ )
                {
                    Pixel* pPixel = pSegment->GetPixels()[c];
                    assert( pPixel );
                    pPacket.push_back( this->SafeValue( pPixel->GetColor().GetR() ) );
                    pPacket.push_back( this->SafeValue( pPixel->GetColor().GetG() ) );
                    pPacket.push_back( this->SafeValue( pPixel->GetColor().GetB() ) );
                    pPacket.push_back( this->SafeValue( pPixel->GetColor().GetBri() ) );
                }
            }
            if ( m_lightStrips.size() > 0)
                pPacket.push_back((char) 44);
        }
    }
    pPacket = '^' + pPacket + '$';
    
    // Only send the packet if it's different than the last sent packet.
    // Prevents unnecessary network data
    if ( pPacket != this->m_lastPacket )
    {
        this->m_lastPacket = pPacket;
        //std::cout << "New packet: " << pPacket.length() << std::endl;
        //std::cout << pPacket << std::endl;
        // Send the packet using the socket that's already open
        m_client->send( pPacket );
    }
};

// Strip special characters used by PixelServer to parse packets.
// Replaces them with a very similar character.
char Photon::SafeValue( float i_value )
{
    char charValue = (char) i_value;
    switch( charValue )
    {
        case 0:         // We can't null terminate in the middle of our packet!
            return 1;
            break;
        case 94:        // We're using ^ as a significant tag
            return 95;
            break;
        case 36:        // We're using $ as a significant tag
            return 36;
            break;
        case 44:        // We're using , as a significant tag
            return 43;
            break;
        default:
            return charValue;
            break;
    }
};