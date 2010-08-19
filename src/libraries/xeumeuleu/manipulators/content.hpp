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

#ifndef xeumeuleu_content_hpp
#define xeumeuleu_content_hpp

#include <string>

namespace xml
{
// =============================================================================
/** @class  content_manipulator
    @brief  Content manipulator
    @par Using example
    @code
    xml::xistream& xis = ...;
    T value;
    xis >> xml::content( "node", value );

    xml::xostream& xos = ...;
    T value;
    xos << xml::content( "node", value );
    @endcode
*/
// Created: MAT 2006-01-03
// =============================================================================
template< typename T >
class content_manipulator
{
public:
    //! @name Constructors/Destructor
    //@{
    content_manipulator( const std::string& tag, T& value )
        : tag_  ( tag )
        , value_( value )
    {}
    //@}

private:
    //! @name Copy/Assignment
    //@{
    content_manipulator& operator=( const content_manipulator& ); //!< Assignment operator
    //@}

public:
    //! @name Member data
    //@{
    std::string tag_;
    T& value_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: content
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
template< typename T >
content_manipulator< const T > content( const std::string& tag, const T& value )
{
    return content_manipulator< const T >( tag, value );
}

// -----------------------------------------------------------------------------
// Name: content
// Created: MAT 2006-01-03
// -----------------------------------------------------------------------------
template< typename T >
content_manipulator< T > content( const std::string& tag, T& value )
{
    return content_manipulator< T >( tag, value );
}

}

#endif // xeumeuleu_content_hpp
