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

#ifndef _xeumeuleu_attribute_h_
#define _xeumeuleu_attribute_h_

#include "xistream.h"
#include "xostream.h"
#include <string>

namespace xml
{
// =============================================================================
/** @class  attribute_manipulator
    @brief  Attribute manipulator
*/
// Created: MAT 2006-01-05
// =============================================================================
template< typename T >
class attribute_manipulator
{
public:
    //! @name Constructors/Destructor
    //@{
    attribute_manipulator( const std::string& name, T& value )
        : name_ ( name )
        , value_( value )
    {}
    //@}

    //! @name Operators
    //@{
    xistream& operator()( xistream& xis ) const
    {
        xis.attribute( name_, value_ );
        return xis;
    }
    xostream& operator()( xostream& xos ) const
    {
        xos.attribute( name_, value_ );
        return xos;
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    attribute_manipulator& operator=( const attribute_manipulator& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    std::string name_;
    T& value_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: operator>>
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
template< typename T >
xistream& operator>>( xistream& xis, const attribute_manipulator< T >& manipulator )
{
    return manipulator( xis );
}

// -----------------------------------------------------------------------------
// Name: operator<<
// Created: MAT 2006-01-05
// -----------------------------------------------------------------------------
template< typename T >
xostream& operator<<( xostream& xos, const attribute_manipulator< T >& manipulator )
{
    return manipulator( xos );
}

// -----------------------------------------------------------------------------
// Name: attribute
// Created: MAT 2006-01-06
// -----------------------------------------------------------------------------
template< typename T >
attribute_manipulator< const T > attribute( const std::string& name, const T& value )
{
    return attribute_manipulator< const T >( name, value );
}

// -----------------------------------------------------------------------------
// Name: attribute
// Created: MAT 2006-01-06
// -----------------------------------------------------------------------------
template< typename T >
attribute_manipulator< T > attribute( const std::string& name, T& value )
{
    return attribute_manipulator< T >( name, value );
}

}

#endif // _xeumeuleu_attribute_h_
