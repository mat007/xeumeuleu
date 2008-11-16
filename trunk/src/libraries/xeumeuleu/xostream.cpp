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
xostream::xostream( output& output )
    : output_( output )
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
// Name: xostream::write
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void xostream::write( const char* value )
{
    write( std::string( value ) );
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void xostream::write( const std::string& value )
{
    TRY
        output_.write( value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void xostream::write( float value )
{
    TRY
        output_.write( value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void xostream::write( double value )
{
    TRY
        output_.write( value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void xostream::write( int value )
{
    TRY
        output_.write( value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MAT 2007-01-25
// -----------------------------------------------------------------------------
void xostream::write( long value )
{
    TRY
        output_.write( value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MAT 2007-09-18
// -----------------------------------------------------------------------------
void xostream::write( long long value )
{
    TRY
        output_.write( value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
void xostream::write( bool value )
{
    TRY
        output_.write( value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void xostream::write( unsigned int value )
{
    TRY
        output_.write( value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MCO 2006-12-13
// -----------------------------------------------------------------------------
void xostream::write( unsigned long value )
{
    TRY
        output_.write( value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MAT 2007-09-18
// -----------------------------------------------------------------------------
void xostream::write( unsigned long long value )
{
    TRY
        output_.write( value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xostream::write
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
void xostream::write( const xistream& xis )
{
    TRY
        xis.copy( output_ );
    CATCH
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
// Name: xostream::instruction
// Created: MCO 2008-08-17
// -----------------------------------------------------------------------------
void xostream::instruction( const std::string& target, const std::string& data )
{
    TRY
        output_.instruction( target, data );
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
