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

#ifndef xeumeuleu_ns_hpp
#define xeumeuleu_ns_hpp

#include <xeumeuleu/streams/xistream.hpp>
#include <xeumeuleu/streams/xostream.hpp>
#include <string>

namespace xml
{
// =============================================================================
/** @class  ns
    @brief  Namespace manipulator
    @par    Using example
    @code
    xml::xistream& xis = ...;
    xis >> xml::ns( "namespace_name" ) >> ...

    xml::xostream& xos = ...;
    xos << xml::ns( "prefix", "namespace_name" ) << ...
    @endcode
*/
// Created: MAT 2010-06-30
// =============================================================================
class ns
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit ns( const std::string& name )
        : name_( name )
    {}
    ns( const std::string& prefix, const std::string& name )
        : prefix_( prefix )
        , name_  ( name )
    {}
    //@}

    //! @name Operators
    //@{
    friend xistream& operator>>( xistream& xis, const ns& n )
    {
        xis.ns( n.name_ );
        return xis;
    }
    friend xostream& operator<<( xostream& xos, const ns& n )
    {
        xos.ns( n.prefix_, n.name_ );
        return xos;
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    ns& operator=( const ns& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const std::string prefix_;
    std::string name_;
    //@}
};

}

#endif // xeumeuleu_ns_hpp
