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

#ifndef xeumeuleu_translate_hpp
#define xeumeuleu_translate_hpp

#define XEUMEULEU_TRANSCODER_ENCODING "utf-8"

#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <vector>
#include <string>

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
        : transcoder_( create() )
        , s_         ( transcode( str ) )
        , ch_        ( &s_[0] )
    {}
    explicit translate( const XMLCh* const ch )
        : transcoder_( create() )
        , ch_        ( ch )
    {}
    translate( const translate& rhs )
        : transcoder_( create() )
        , s_         ( rhs.s_ )
        , ch_        ( s_.empty() ? rhs.ch_ : &s_[0] )
    {}
    //@}

    //! @name Operators
    //@{
    operator const XMLCh*() const
    {
        return ch_;
    }
    operator std::string() const
    {
        if( ! ch_ )
            return std::string();
        XMLSize_t written = 0;
        const XMLSize_t size = XERCES_CPP_NAMESPACE::XMLString::stringLen( ch_ );
        std::vector< XMLByte > s( size * sizeof( XMLCh ) + 4 );
        XMLSize_t done = 0;
        while( done < size )
        {
            Count_t read = 0;
            written += transcoder_->transcodeTo(
                ch_ + done, size - done,
                &s[written], s.size() - written,
                read, XERCES_CPP_NAMESPACE::XMLTranscoder::UnRep_RepChar );
            if( read == 0 )
                throw xml::exception( "failed to transcode string" );
            done += read;
            if( s.size() - written < size - done )
                s.resize( s.size() * 2 );
        }
        s.resize( written + 4 );
        return std::string( reinterpret_cast< const char* >( &s[0] ), written );
    }

    bool operator==( const XMLCh* const ch ) const
    {
        return XERCES_CPP_NAMESPACE::XMLString::equals( ch, ch_ );
    }
    bool operator==( const std::string& str ) const
    {
        return translate( str ) == ch_;
    }
    bool operator!=( const XMLCh* const ch ) const
    {
        return ! XERCES_CPP_NAMESPACE::XMLString::equals( ch, ch_ );
    }
    bool operator!=( const std::string& str ) const
    {
        return translate( str ) != ch_;
    }
    //@}

private:
    //! @name Helpers
    //@{
    XERCES_CPP_NAMESPACE::XMLTranscoder* create() const
    {
        XERCES_CPP_NAMESPACE::XMLTransService::Codes result;
        XERCES_CPP_NAMESPACE::Janitor< XERCES_CPP_NAMESPACE::XMLTranscoder > transcoder
            = XERCES_CPP_NAMESPACE::XMLPlatformUtils::fgTransService->makeNewTranscoderFor(
                XEUMEULEU_TRANSCODER_ENCODING, result, 16 * 1024 );
        if( result != XERCES_CPP_NAMESPACE::XMLTransService::Ok )
            throw xml::exception( std::string( "unable to create transcoder for " ) + XEUMEULEU_TRANSCODER_ENCODING );
        return transcoder.release();
    }
    std::vector< XMLCh > transcode( const std::string& str ) const
    {
        const XMLByte* in = reinterpret_cast< const XMLByte* >( str.c_str() );
        const XMLSize_t length = str.length();
        XMLSize_t written = 0;
        std::vector< XMLCh > s( length + 1 );
        std::vector< unsigned char > sizes;
        XMLSize_t done = 0;
        while( done < length )
        {
            sizes.resize( s.size() - written );
            Count_t read = 0;
            written += transcoder_->transcodeFrom(
                in + done, length - done,
                &s[0] + written, s.size() - written,
                read, &sizes[0] );
            if( read == 0 )
                throw xml::exception( "failed to transcode string" );
            done += read;
            if( ( s.size() - written ) * sizeof( XMLCh ) < length - done )
                s.resize( 2 * s.size() );
        }
        s.resize( written + 1 );
        return s;
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    translate& operator=( const translate& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    XERCES_CPP_NAMESPACE::Janitor< XERCES_CPP_NAMESPACE::XMLTranscoder > transcoder_;
    const std::vector< XMLCh > s_;
    const XMLCh* const ch_;
    //@}
};

inline bool operator==( const XMLCh* const ch, const translate& tr )
{
    return tr == ch;
}
inline bool operator==( const std::string& str, const translate& tr )
{
    return tr == str;
}

inline bool operator!=( const XMLCh* const ch, const translate& tr )
{
    return tr != ch;
}
inline bool operator!=( const std::string& str, const translate& tr )
{
    return tr != str;
}

inline std::string operator+( const translate& tr, const std::string& str )
{
    return std::string( tr ) + str;
}
inline std::string operator+( const std::string& str, const translate& tr )
{
    return str + std::string( tr );
}

}

#endif // xeumeuleu_translate_hpp
