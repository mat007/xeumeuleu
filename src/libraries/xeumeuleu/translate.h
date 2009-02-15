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

#ifndef _xeumeuleu_translate_h_
#define _xeumeuleu_translate_h_

#include "xerces.h"
#include <string>
#include <iosfwd>

namespace xml
{
// =============================================================================
/** @class  translate
    @brief  String translation helpers
*/
// Created: MAT 2006-01-04
// =============================================================================
class translate
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit translate( const std::string& str )
        : ch_   ( XERCES_CPP_NAMESPACE::XMLString::transcode( str.c_str() ) )
        , owner_( true )
    {}
    explicit translate( const XMLCh* const ch )
        : ch_   ( ch )
        , owner_( false )
    {}
    ~translate()
    {
        if( owner_ )
            XERCES_CPP_NAMESPACE::XMLString::release( const_cast< XMLCh** >( &ch_ ) );
    }
    //@}

    //! @name Operators
    //@{
    operator const XMLCh* const() const
    {
        return ch_;
    }
    operator std::string() const
    {
        if( ! ch_ )
            return std::string();
        char* c = XERCES_CPP_NAMESPACE::XMLString::transcode( ch_ );
        if( ! c )
            return std::string();
        const std::string str( c );
        XERCES_CPP_NAMESPACE::XMLString::release( &c );
        return str;
    }

    bool operator==( const XMLCh* const ch ) const
    {
        return XERCES_CPP_NAMESPACE::XMLString::equals( ch, ch_ );
    }
    bool operator==( const std::string& str ) const
    {
        return translate( str ) == ch_;
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    translate( const translate& );            //!< Copy constructor
    translate& operator=( const translate& ); //!< Assignment operator
    //@}

private:
    //! @name Data members
    //@{
    const XMLCh* const ch_;
    bool owner_;
    //@}
};

inline bool operator==( const XMLCh* const ch, const translate& tr )
{
    return tr.operator ==( ch );
}
inline bool operator==( const std::string& str, const translate& tr )
{
    return tr.operator ==( str );
}

inline std::string operator+( const translate& tr, const std::string& str )
{
    return tr.operator std::string() + str;
}

}

#endif // _xeumeuleu_translate_h_
