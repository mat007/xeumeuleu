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

#include "xeumeuleu_pch.h"
#include "xistream.h"
#include "input.h"
#include "chained_exception.h"
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/util/XMLException.hpp>
#include <xercesc/dom/DOMException.hpp>

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

#define TRY try {
#define CATCH } \
            catch( const OutOfMemoryException& ) { throw xml::exception( "Out of memory" ); } \
            catch( const XMLException& e ) { throw chained_exception( e ); } \
            catch( const DOMException& e ) { throw chained_exception( e ); }

// -----------------------------------------------------------------------------
// Name: xistream constructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xistream::xistream( std::auto_ptr< input > pInput )
    : pInput_( pInput )
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
        pInput_->start( tag );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::end
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
void xistream::end()
{
    TRY
        pInput_->end();
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::operator>>
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
xistream& xistream::operator>>( std::string& value )
{
    TRY
        pInput_->read( value );
        return *this;
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::operator>>
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
xistream& xistream::operator>>( float& value )
{
    TRY
        pInput_->read( value );
        return *this;
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::operator>>
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
xistream& xistream::operator>>( double& value )
{
    TRY
        pInput_->read( value );
        return *this;
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::operator>>
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
xistream& xistream::operator>>( int& value )
{
    TRY
        pInput_->read( value );
        return *this;
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::operator>>
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
xistream& xistream::operator>>( bool& value )
{
    TRY
        pInput_->read( value );
        return *this;
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xistream::attribute( const std::string& name, std::string& value ) const
{
    TRY
        pInput_->attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xistream::attribute( const std::string& name, float& value ) const
{
    TRY
        pInput_->attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xistream::attribute( const std::string& name, double& value ) const
{
    TRY
        pInput_->attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xistream::attribute( const std::string& name, int& value ) const
{
    TRY
        pInput_->attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::attribute
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xistream::attribute( const std::string& name, bool& value ) const
{
    TRY
        pInput_->attribute( name, value );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::visit
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
void xistream::visit( const visitor& v )
{
    TRY
        pInput_->visit( v );
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::optional
// Created: MAT 2006-01-07
// -----------------------------------------------------------------------------
void xistream::optional()
{
    TRY
        pInput_->optional();
    CATCH
}

// -----------------------------------------------------------------------------
// Name: xistream::branch
// Created: MAT 2006-03-19
// -----------------------------------------------------------------------------
std::auto_ptr< input > xistream::branch() const
{
    TRY
        return pInput_->branch();
    CATCH
}
