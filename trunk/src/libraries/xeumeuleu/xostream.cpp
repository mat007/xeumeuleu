/*
 *   Copyright (c) 2006, Mathieu Champlon
 *   All rights reserved.
 *
 *   Redistribution  and use  in source  and binary  forms, with  or without
 *   modification, are permitted provided  that the following conditions are
 *   met :
 *
 *   . Redistributions  of  source  code  must  retain  the  above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   . Redistributions in  binary form  must reproduce  the above  copyright
 *     notice, this list of conditions  and the following disclaimer in  the
 *     documentation and/or other materials provided with the distribution.
 *
 *   . Neither  the name  of  the  copyright  holders  nor the names  of the
 *     contributors may be used to endorse  or promote products derived from
 *     this software without specific prior written permission.
 *
 *   THIS SOFTWARE  IS  PROVIDED  BY THE  COPYRIGHT HOLDERS  AND CONTRIBUTORS
 *   ``AS IS''  AND ANY  EXPRESS OR  IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
 *   LIMITED TO, THE IMPLIED  WARRANTIES  OF MERCHANTABILITY AND  FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE THE COPYRIGHT
 *   OWNERS OR CONTRIBUTORS  BE LIABLE FOR ANY  DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL   DAMAGES  (INCLUDING,  BUT  NOT
 *   LIMITED TO,  PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES;  LOSS OF USE,
 *   DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED  AND ON  ANY
 *   THEORY  OF  LIABILITY,  WHETHER IN  CONTRACT,  STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY  WAY  OUT OF  THE USE
 *   OF THIS SOFTWARE, EVEN  IF  ADVISED OF  THE POSSIBILITY  OF SUCH DAMAGE.
 */

#include "xostream.h"
#include "output.h"
#include "xobufferstream.h"
#include "chained_exception.h"
#include "xistream.h"
#include "xerces.h"

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

#define TRY try {
#define CATCH } \
            catch( const OutOfMemoryException& ) { throw xml::exception( "Out of memory" ); } \
            catch( const XMLException& e ) { throw chained_exception( e ); } \
            catch( const DOMException& e ) { throw chained_exception( e ); }

// -----------------------------------------------------------------------------
// Name: xostream constructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xostream::xostream( output& o )
    : output_( o )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xostream destructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xostream::~xostream()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xostream::start
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void xostream::start( const std::string& tag )
{
    TRY
        output_.start( tag );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::end
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void xostream::end()
{
    TRY
        output_.end();
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( const char* value )
{
    return *this << std::string( value );
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( const std::string& value )
{
    TRY
        output_.write( value );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( float value )
{
    TRY
        output_.write( value );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( double value )
{
    TRY
        output_.write( value );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( int value )
{
    TRY
        output_.write( value );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MAT 2007-01-25
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( long value )
{
    TRY
        output_.write( value );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MAT 2007-09-18
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( long long value )
{
    TRY
        output_.write( value );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( bool value )
{
    TRY
        output_.write( value );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( unsigned int value )
{
    TRY
        output_.write( value );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( unsigned long value )
{
    TRY
        output_.write( value );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MAT 2007-09-18
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( unsigned long long value )
{
    TRY
        output_.write( value );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MAT 2006-03-07
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( const xobufferstream& xobs )
{
    TRY
        xobs.attach( output_ );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::operator<<
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
xostream& xostream::operator<<( const xistream& xis )
{
    TRY
        xis.copy( output_ );
    CATCH
    return *this;
}

// -----------------------------------------------------------------------------
// Name: xostream::cdata
// Created: MCO 2007-03-14
// -----------------------------------------------------------------------------
void xostream::cdata( const std::string& content )
{
    TRY
        output_.cdata( content );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MAT 2006-01-06
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, const char* value )
{
    attribute( name, std::string( value ) );
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, const std::string& value )
{
    TRY
        output_.attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, float value )
{
    TRY
        output_.attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, double value )
{
    TRY
        output_.attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, int value )
{
    TRY
        output_.attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MAT 2007-01-25
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, long value )
{
    TRY
        output_.attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MAT 2007-09-18
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, long long value )
{
    TRY
        output_.attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, bool value )
{
    TRY
        output_.attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, unsigned int value )
{
    TRY
        output_.attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, unsigned long value )
{
    TRY
        output_.attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::attribute
// Created: MAT 2007-09-18
// -----------------------------------------------------------------------------
void xostream::attribute( const std::string& name, unsigned long long value )
{
    TRY
        output_.attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::branch
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
std::auto_ptr< output > xostream::branch()
{
    TRY
        return output_.branch();
    CATCH
}
