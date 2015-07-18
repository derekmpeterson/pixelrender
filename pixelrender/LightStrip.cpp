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

LightStrip::LightStrip( uint16_t i_pixelCount, Vector3d i_position, Vector3d i_direction, std::string i_ipAddress ) :
m_ipAddress( i_ipAddress ), m_socket( m_ioService ), m_resolver( m_ioService )
{
    m_pixelCount = i_pixelCount;
    m_position = i_position;
    m_direction = i_direction;
    m_pixels.resize( i_pixelCount );
    
    FrameBuffer* pFrameBuffer = FrameBuffer::Instance();

    Vector3d pPixelPos = m_position;
    for( int i = 0; i < m_pixelCount; i++ )
    {
        m_pixels[i] = new Pixel( 0, 255, 0, 255, m_position );
        pFrameBuffer->m_pixels[pPixelPos.GetX()][pPixelPos.GetY()][pPixelPos.GetZ()] = m_pixels[i];
        pPixelPos += m_direction;
    }
    
    std::cout << "Connecting to socket..." << std::endl;
    asio::connect( m_socket, m_resolver.resolve( { m_ipAddress, "23" } ) );
    std::cout << "Done!" << std::endl;
};

LightStrip::~LightStrip()
{
    for( int i = 0; i < m_pixelCount; i++ )
    {
        delete m_pixels[i];
        m_pixels[i] = NULL;
    }
};

void LightStrip::Render()
{
    std::string pPacket = "";
    for( int i = 0; i < m_pixels.size(); i++ )
    {
        Pixel* pPixel = m_pixels[i];
        assert( pPixel );
        pPacket.push_back( this->SafeValue( pPixel->GetR() ) );
        pPacket.push_back( this->SafeValue( pPixel->GetG() ) );
        pPacket.push_back( this->SafeValue( pPixel->GetB() ) );
        pPacket.push_back( this->SafeValue( pPixel->GetBri() ) );
    }
    pPacket = '^' + pPacket + '$';
    
    if ( pPacket != this->m_lastPacket )
    {
        this->m_lastPacket = pPacket;
        std::cout << "New packet: " << pPacket.length() << std::endl;
        
        // Send the packet using the socket that's already open
        asio::write( m_socket, asio::buffer( pPacket, pPacket.length() ) );
    }
};

char LightStrip::SafeValue( char i_value )
{
    switch( i_value )
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
            return i_value;
            break;
    }
};