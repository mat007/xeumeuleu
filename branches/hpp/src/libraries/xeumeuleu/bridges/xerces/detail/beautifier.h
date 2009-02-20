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

#ifndef xeumeuleu_beautifier_h
#define xeumeuleu_beautifier_h

#include <xeumeuleu/bridges/xerces/detail/xerces.h>
#include <xeumeuleu/bridges/xerces/detail/translate.h>

namespace xml
{
namespace detail
{
    const XMLCh NEW_LINE[] = { XERCES_CPP_NAMESPACE::chLF, XERCES_CPP_NAMESPACE::chNull };
    const XMLCh SPACE[] = { XERCES_CPP_NAMESPACE::chSpace, XERCES_CPP_NAMESPACE::chNull };
}
// =============================================================================
/** @class  beautifier
    @brief  Xerces target wrapper

    Intercepts written data to remove double new lines (xerces pretty print 'bug')
*/
// Created: MAT 2006-01-05
// =============================================================================
class beautifier : public XERCES_CPP_NAMESPACE::XMLFormatTarget
{
public:
    //! @name Constructors/Destructor
    //@{
    beautifier( XERCES_CPP_NAMESPACE::XMLFormatTarget& target, const XMLCh* new_line )
        : target_          ( target )
        , new_line_        ( translate( new_line == XERCES_CPP_NAMESPACE::chNull ? detail::NEW_LINE : new_line ) )
        , space_           ( translate( detail::SPACE ) )
        , discard_new_line_( false )
        , discard_spaces_  ( false )
        , shift_           ( 0 )
    {}
    virtual ~beautifier()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void writeChars( const XMLByte* const data, const unsigned int count, XERCES_CPP_NAMESPACE::XMLFormatter* const formatter )
    {
        if( is_new_line( data, count ) )
        {
            if( ! discard_new_line_ && ! discard_spaces_ )
                target_.writeChars( data, count, formatter );
            discard_new_line_ = ! discard_new_line_;
            discard_spaces_ = true;
            shift_ = 0;
        }
        else if( discard_spaces_ && is_space( data, count ) )
            ++shift_;
        else
        {
            shift( formatter );
            target_.writeChars( data, count, formatter );
            discard_new_line_ = false;
        }
    }

    virtual void flush()
    {
        target_.flush();
    }
    //@}

private:
    //! @name Helpers
    //@{
    bool is_new_line( const XMLByte* const data, const unsigned int count ) const
    {
        return count == new_line_.size() &&
               0 == strncmp( reinterpret_cast< const char* const >( data ), new_line_.c_str(), count );
    }
    bool is_space( const XMLByte* const data, const unsigned int count ) const
    {
        return count == space_.size() &&
               0 == strncmp( reinterpret_cast< const char* const >( data ), space_.c_str(), count );
    }

    void shift( XERCES_CPP_NAMESPACE::XMLFormatter* const formatter )
    {
        while( shift_-- > 0 )
            target_.writeChars( reinterpret_cast< const XMLByte* const >( space_.c_str() ), 1, formatter ); // $$$$ MCO 2007-03-16: 
        shift_ = 0;
        discard_spaces_ = false;
    }
    //@}

private:
    //! @name Member data
    //@{
    XERCES_CPP_NAMESPACE::XMLFormatTarget& target_;
    const std::string new_line_;
    const std::string space_;
    bool discard_new_line_;
    bool discard_spaces_;
    unsigned short shift_;
    //@}
};

}

#endif // xeumeuleu_beautifier_h
