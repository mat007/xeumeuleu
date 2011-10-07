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

#ifndef xeumeuleu_beautifier_hpp
#define xeumeuleu_beautifier_hpp

#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>

namespace xml
{
namespace detail
{
    const XMLCh OPEN_ANGLE[] = { XERCES_CPP_NAMESPACE::chOpenAngle, XERCES_CPP_NAMESPACE::chNull };
    const XMLCh CLOSE_ANGLE[] = { XERCES_CPP_NAMESPACE::chCloseAngle, XERCES_CPP_NAMESPACE::chNull };
    const XMLCh FORWARD_SLASH[] = { XERCES_CPP_NAMESPACE::chForwardSlash, XERCES_CPP_NAMESPACE::chNull };
    const XMLCh OPEN_ANGLE_FORWARD_SLASH[] = { XERCES_CPP_NAMESPACE::chOpenAngle, XERCES_CPP_NAMESPACE::chForwardSlash, XERCES_CPP_NAMESPACE::chNull };
    const XMLCh CDATA_START[] = { XERCES_CPP_NAMESPACE::chOpenAngle, XERCES_CPP_NAMESPACE::chBang, XERCES_CPP_NAMESPACE::chNull };
    const XMLCh CDATA_END[] = { XERCES_CPP_NAMESPACE::chCloseSquare, XERCES_CPP_NAMESPACE::chCloseSquare, XERCES_CPP_NAMESPACE::chCloseAngle, XERCES_CPP_NAMESPACE::chNull };

    const XMLCh NEW_LINE[] = { XERCES_CPP_NAMESPACE::chLF, XERCES_CPP_NAMESPACE::chNull };
    const XMLCh SPACE[] = { XERCES_CPP_NAMESPACE::chSpace, XERCES_CPP_NAMESPACE::chNull };

    const unsigned int BLOCK_SIZE = 8;
    const unsigned int INDENT = 2;

    class bytes
    {
    public:
        XMLByte data[BLOCK_SIZE];
        Count_t size;
    };
}
// =============================================================================
/** @class  beautifier
    @brief  beautifier

    Decorates written data to pretty-print the output
*/
// Created: MAT 2006-01-05
// =============================================================================
class beautifier : public XERCES_CPP_NAMESPACE::XMLFormatTarget
{
public:
    //! @name Constructors/Destructor
    //@{
    beautifier( XERCES_CPP_NAMESPACE::XMLFormatTarget& target, const std::string& encoding, const XMLCh* new_line )
        : target_    ( target )
        , transcoder_( create( encoding ) )
        , level_     ( -1 )
        , cdata_     ( false )
        , inline_    ( false )
    {
        transcode( detail::OPEN_ANGLE, open_angle_ );
        transcode( detail::CLOSE_ANGLE, close_angle_ );
        transcode( detail::FORWARD_SLASH, forward_slash_ );
        transcode( detail::OPEN_ANGLE_FORWARD_SLASH, open_angle_forward_slash_ );
        transcode( detail::CDATA_START, cdata_start_ );
        transcode( detail::CDATA_END, cdata_end_ );
        transcode( new_line ? new_line : detail::NEW_LINE , new_line_ );
        transcode( detail::SPACE, space_ );
    }
    virtual ~beautifier()
    {
        delete transcoder_; // $$$$ MCO 2007-03-16: delete ?
    }
    //@}

    //! @name Operations
    //@{
    virtual void writeChars( const XMLByte* const data, const Count_t count, XERCES_CPP_NAMESPACE::XMLFormatter* const formatter )
    {
        pre( data, count, formatter );
        target_.writeChars( data, count, formatter );
        post( data, count, formatter );
    }

    virtual void flush()
    {
        target_.flush();
    }
    //@}

private:
    //! @name Helpers
    //@{
    XERCES_CPP_NAMESPACE::XMLTranscoder* create( const std::string& encoding ) const
    {
        XERCES_CPP_NAMESPACE::XMLTransService::Codes code = XERCES_CPP_NAMESPACE::XMLTransService::Ok;
        XERCES_CPP_NAMESPACE::XMLTranscoder* transcoder =
            XERCES_CPP_NAMESPACE::XMLPlatformUtils::fgTransService->makeNewTranscoderFor( encoding.c_str(), code, detail::BLOCK_SIZE );
        if( code != XERCES_CPP_NAMESPACE::XMLTransService::Ok )
            throw exception( "internal error while creating transcoder" );
        return transcoder;
    }
    void transcode( const XMLCh* const data, detail::bytes& b ) const
    {
        const Count_t size = XERCES_CPP_NAMESPACE::XMLString::stringLen( data );
        Count_t handled = 0;
        b.size = transcoder_->transcodeTo( data, size, b.data, detail::BLOCK_SIZE, handled, XERCES_CPP_NAMESPACE::XMLTranscoder::UnRep_Throw );
    }
    bool equals( const XMLByte* const data, Count_t count, const detail::bytes& b ) const
    {
        if( count != b.size )
            return false;
        for( Count_t i = 0; i < b.size; ++i )
            if( data[i] != b.data[i] )
                return false;
        return true;
    }
    bool ends( const XMLByte* const data, Count_t count, const detail::bytes& b ) const
    {
        if( count < b.size )
            return false;
        for( Count_t i = 0; i < b.size; ++i )
            if( data[count - b.size + i] != b.data[i] )
                return false;
        return true;
    }
    bool starts( const XMLByte* const data, Count_t count, const detail::bytes& b ) const
    {
        if( count < b.size )
            return false;
        for( Count_t i = 0; i < b.size; ++i )
            if( data[i] != b.data[i] )
                return false;
        return true;
    }
    void shift( XERCES_CPP_NAMESPACE::XMLFormatter* const formatter )
    {
        for( unsigned short level = 0; level < level_ * detail::INDENT; ++level )
            target_.writeChars( space_.data, space_.size, formatter );
    }
    void newline( XERCES_CPP_NAMESPACE::XMLFormatter* const formatter )
    {
        target_.writeChars( new_line_.data, new_line_.size, formatter );
    }
    void pre( const XMLByte* const data, const Count_t count, XERCES_CPP_NAMESPACE::XMLFormatter* const formatter )
    {
        if( cdata_ )
            return;
        if( equals( data, count, open_angle_ ) )
        {
            ++level_;
            if( inline_ )
                newline( formatter );
            inline_ = true;
            shift( formatter );
        }
        else if( ! inline_ && equals( data, count, open_angle_forward_slash_ ) )
            shift( formatter );
    }
    void post( const XMLByte* const data, const Count_t count, XERCES_CPP_NAMESPACE::XMLFormatter* const formatter )
    {
        if( cdata( data, count ) )
            return;
        if( ends( data, count, forward_slash_ ) )
        {
            --level_;
            inline_ = false;
        }
        else if( ! inline_ && ends( data, count, close_angle_ ) )
            newline( formatter );
    }
    bool cdata( const XMLByte* const data, const Count_t count )
    {
        if( starts( data, count, cdata_start_ ) )
            cdata_ = true;
        else if( cdata_ && equals( data, count, cdata_end_ ) )
            cdata_ = false;
        else
            return cdata_;
        return true;
    }
    //@}

private:
    //! @name Member data
    //@{
    XERCES_CPP_NAMESPACE::XMLFormatTarget& target_;
    XERCES_CPP_NAMESPACE::XMLTranscoder* transcoder_;
    detail::bytes open_angle_, close_angle_;
    detail::bytes forward_slash_;
    detail::bytes open_angle_forward_slash_;
    detail::bytes cdata_start_, cdata_end_;
    detail::bytes new_line_, space_;
    int level_;
    bool cdata_;
    bool inline_;
    //@}
};

}

#endif // xeumeuleu_beautifier_hpp
