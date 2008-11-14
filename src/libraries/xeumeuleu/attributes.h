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

#ifndef _xeumeuleu_attributes_h_
#define _xeumeuleu_attributes_h_

#include "adapter.h"
#include "name_caller.h"

namespace xml
{
// =============================================================================
/** @class  attributes_visitor
    @brief  Attributes visitor
*/
// Created: MAT 2007-08-01
// =============================================================================
template< typename T >
class attributes_visitor : public adapter< T >
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit attributes_visitor( T functor )
        : adapter< T >( functor )
    {}
    //@}
};

// -----------------------------------------------------------------------------
// Name: operator>>
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
template< typename T >
xistream& operator>>( xistream& xis, const attributes_visitor< T >& manipulator )
{
    xis.attributes( manipulator );
    return xis;
}

// -----------------------------------------------------------------------------
// Name: attributes
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
template< typename F >
attributes_visitor< F > attributes( F functor )
{
    return attributes_visitor< F >( functor );
}

// -----------------------------------------------------------------------------
// Name: attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
template< typename T >
attributes_visitor< name_caller0< T > > attributes( T& instance, void (T::*method)( const std::string&, xistream& ) )
{
    return attributes_visitor< name_caller0< T > >( name_caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
template< typename T >
attributes_visitor< const_name_caller0< T > > attributes( const T& instance, void (T::*method)( const std::string&, xistream& ) const )
{
    return attributes_visitor< const_name_caller0< T > >( const_name_caller0< T >( instance, method ) );
}

// -----------------------------------------------------------------------------
// Name: attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1 >
attributes_visitor< name_caller1< T, Arg1&, T1 > > attributes( T& instance, void (T::*method)( const std::string&, xistream&, T1 ), Arg1& value )
{
    return attributes_visitor< name_caller1< T, Arg1&, T1 > >( name_caller1< T, Arg1&, T1 >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1 >
attributes_visitor< const_name_caller1< T, Arg1&, T1 > > attributes( const T& instance, void (T::*method)( const std::string&, xistream&, T1 ) const, Arg1& value )
{
    return attributes_visitor< const_name_caller1< T, Arg1&, T1 > >( const_name_caller1< T, Arg1&, T1 >( instance, method, value ) );
}

// -----------------------------------------------------------------------------
// Name: attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
attributes_visitor< name_caller2< T, Arg1&, T1, Arg2&, T2 > > attributes( T& instance, void (T::*method)( const std::string&, xistream&, T1, T2 ), Arg1& value1, Arg2& value2 )
{
    return attributes_visitor< name_caller2< T, Arg1&, T1, Arg2&, T2 > >( name_caller2< T, Arg1&, T1, Arg2&, T2 >( instance, method, value1, value2 ) );
}

// -----------------------------------------------------------------------------
// Name: attributes
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
template< typename T, typename Arg1, typename T1, typename Arg2, typename T2 >
attributes_visitor< const_name_caller2< T, Arg1&, T1, Arg2&, T2 > > attributes( const T& instance, void (T::*method)( const std::string&, xistream&, T1, T2 ) const, Arg1& value1, Arg2& value2 )
{
    return attributes_visitor< const_name_caller2< T, Arg1&, T1, Arg2&, T2 > >( const_name_caller2< T, Arg1&, T1, Arg2&, T2 >( instance, method, value1, value2 ) );
}

}

#endif // _xeumeuleu_attributes_h_
