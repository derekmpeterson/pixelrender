//
//  LightStrip.cpp
//  pixelrender
//
//  Created by Derek Peterson on 3/7/15.
//  Copyright (c) 2015 Derek Peterson. All rights reserved.
//

#include "LightStrip.h"
#include "FrameBuffer.h"
#include <assert.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iostream>

LightStrip::LightStrip( uint16_t i_pixelCount, Vector3d i_position, Vector3d i_direction, std::string i_ipAddress )
{
    m_pixelCount = i_pixelCount;
    m_position = i_position;
    m_direction = i_direction;
    m_ipAddress = i_ipAddress;
    m_pixels.resize( i_pixelCount );
    
    FrameBuffer* pFrameBuffer = FrameBuffer::Instance();

    RGBA pColor = RGBA( 0, 0, 0, 0 );
    Vector3d pPixelPos = m_position;
    for( int i = 0; i < m_pixelCount; i++ )
    {
        m_pixels[i] = new Pixel( pColor, pPixelPos );
        pFrameBuffer->AddPixel( m_pixels[i] );
        pPixelPos += m_direction;
    }
    
    //std::cout << "Connecting to socket..." << std::endl;
    m_client = new UDPClient( m_ioservice, m_ipAddress, "8888" );
    //std::cout << "Connected" << std::endl;
};

LightStrip::~LightStrip()
{
    FrameBuffer* pFrameBuffer = FrameBuffer::Instance();
    
    for( int i = 0; i < m_pixelCount; i++ )
    {
        pFrameBuffer->RemovePixel( m_pixels[i] );
        delete m_pixels[i];
        m_pixels[i] = NULL;
    }
    
    delete m_client;
};

void LightStrip::Render()
{
    std::string pPacket = "";
    for( int i = 0; i < m_pixels.size(); i++ )
    {
        Pixel* pPixel = m_pixels[i];
        assert( pPixel );
        pPacket.push_back( this->SafeValue( pPixel->GetColor().GetR() ) );
        pPacket.push_back( this->SafeValue( pPixel->GetColor().GetG() ) );
        pPacket.push_back( this->SafeValue( pPixel->GetColor().GetB() ) );
        pPacket.push_back( this->SafeValue( pPixel->GetColor().GetBri() ) );
    }
    pPacket = '^' + pPacket + '$';
    
    if ( pPacket != this->m_lastPacket )
    {
        this->m_lastPacket = pPacket;
        //std::cout << "New packet: " << pPacket.length() << std::endl;
        
        // Send the packet using the socket that's already open
        m_client->send( pPacket );
    }
};

char LightStrip::SafeValue( float i_value )
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
        default:
            return charValue;
            break;
    }
};