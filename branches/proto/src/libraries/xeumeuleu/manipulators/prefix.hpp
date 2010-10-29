/*
 *   Copyright (c) 2010, Mathieu Champlon
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

#ifndef xeumeuleu_prefix_hpp
#define xeumeuleu_prefix_hpp

#include <string>

namespace xml
{
// =============================================================================
/** @class  prefix_manipulator
    @brief  Prefix manipulator
*/
// Created: MAT 2010-07-19
// =============================================================================
template< typename T >
class prefix_manipulator
{
public:
    //! @name Constructors/Destructor
    //@{
    prefix_manipulator( const std::string& ns, T& value )
        : ns_   ( ns )
        , value_( value )
    {}
    //@}

private:
    //! @name Copy/Assignment
    //@{
    prefix_manipulator& operator=( const prefix_manipulator& ); //!< Assignment operator
    //@}

public:
    //! @name Member data
    //@{
    std::string ns_;
    T& value_;
    //@}
};

// -----------------------------------------------------------------------------
// Name: prefix
// Created: MAT 2006-01-06
// -----------------------------------------------------------------------------
template< typename T >
prefix_manipulator< const T > prefix( const std::string& ns, const T& value )
{
    return prefix_manipulator< const T >( ns, value );
}

// -----------------------------------------------------------------------------
// Name: prefix
// Created: MAT 2006-01-06
// -----------------------------------------------------------------------------
template< typename T >
prefix_manipulator< T > prefix( const std::string& ns, T& value )
{
    return prefix_manipulator< T >( ns, value );
}

}

#endif // xeumeuleu_prefix_hpp
