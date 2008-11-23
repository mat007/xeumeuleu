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

#include "xistream.h"
#include "input.h"
#include "chained_exception.h"
#include "xostream.h"
#include "xerces.h"

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

#define TRY try {
#define CATCH } \
            catch( const OutOfMemoryException& ) { throw xml::exception( "Out of memory" ); } \
            catch( const XMLException& e ) { error( chained_exception( e ).what() ); throw; } \
            catch( const DOMException& e ) { error( chained_exception( e ).what() ); throw; }

// -----------------------------------------------------------------------------
// Name: xistream constructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xistream::xistream( std::auto_ptr< input > input )
    : input_( input )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xistream destructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xistream::~xistream()
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: xistream::start
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void xistream::start( const std::string& tag )
{
    TRY
        input_->start( tag );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::end
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void xistream::end()
{
    TRY
        input_->end();
    CATCH
}

#define READ( type ) void xistream::read( type& value ) const \
                     { \
                         TRY \
                             input_->read( value ); \
                         CATCH \
                     }
READ( std::string )
READ( bool )
READ( short )
READ( int )
READ( long )
READ( long long )
READ( float )
READ( double )
READ( long double )
READ( unsigned short )
READ( unsigned int )
READ( unsigned long )
READ( unsigned long long )

// -----------------------------------------------------------------------------
// Name: xistream::read
// Created: MAT 2007-09-09
// -----------------------------------------------------------------------------
void xistream::read( xostream& xos ) const
{
    xos << *this;
}

#define ATTRIBUTE( type ) void xistream::attribute( const std::string& name, type& value ) const \
                      { \
                          TRY \
                              input_->attribute( name, value ); \
                          CATCH \
                      }
ATTRIBUTE( std::string )
ATTRIBUTE( bool )
ATTRIBUTE( short )
ATTRIBUTE( int )
ATTRIBUTE( long )
ATTRIBUTE( long long )
ATTRIBUTE( float )
ATTRIBUTE( double )
ATTRIBUTE( long double )
ATTRIBUTE( unsigned short )
ATTRIBUTE( unsigned int )
ATTRIBUTE( unsigned long )
ATTRIBUTE( unsigned long long )

// -----------------------------------------------------------------------------
// Name: xistream::branch
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
std::auto_ptr< input > xistream::branch( bool clone ) const
{
    TRY
        return input_->branch( clone );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::copy
// Created: MCO 2007-05-28
// -----------------------------------------------------------------------------
void xistream::copy( output& destination ) const
{
    TRY
        input_->copy( destination );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::error
// Created: MAT 2007-09-20
// -----------------------------------------------------------------------------
void xistream::error( const std::string& message ) const
{
    input_->error( message );
}

// -----------------------------------------------------------------------------
// Name: xistream::nodes
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xistream::nodes( const visitor& v ) const
{
    TRY
        input_->nodes( v );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
void xistream::attributes( const visitor& v ) const
{
    TRY
        input_->attributes( v );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::optional
// Created: MAT 2006-01-07
// -----------------------------------------------------------------------------
void xistream::optional()
{
    TRY
        input_->optional();
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::has_child
// Created: MAT 2008-11-23
// -----------------------------------------------------------------------------
bool xistream::has_child( const std::string& name ) const
{
    TRY
        return input_->has_child( name );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::has_attribute
// Created: MAT 2008-11-23
// -----------------------------------------------------------------------------
bool xistream::has_attribute( const std::string& name ) const
{
    TRY
        return input_->has_attribute( name );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::has_content
// Created: MAT 2008-11-23
// -----------------------------------------------------------------------------
bool xistream::has_content() const
{
    TRY
        return input_->has_content();
    CATCH
}
