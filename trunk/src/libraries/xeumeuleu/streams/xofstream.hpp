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

#ifndef xeumeuleu_xofstream_hpp
#define xeumeuleu_xofstream_hpp

#include <xeumeuleu/streams/xostream.hpp>
#include <xeumeuleu/streams/encoding.hpp>
#include <xeumeuleu/bridges/xerces/document.hpp>
#include <xeumeuleu/bridges/xerces/output.hpp>

#ifdef _MSC_VER
#   pragma warning( push )
#   pragma warning( disable: 4355 )
#endif

namespace xml
{
// =============================================================================
/** @class  xofstream
    @brief  Xml file output stream
    @par    Using example
    @code
    xml::xofstream xos( "filename" );
    xml::xofstream xos( "filename", xml::encoding( "UTF-8" ) );
    @endcode
*/
// Created: MAT 2006-01-04
// =============================================================================
class xofstream : private document, private flushable, public xostream
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit xofstream( const std::string& filename, const encoding& encoding = encoding() )
        : xostream( output_ )
        , output_  ( *document_, *document_, *this )
        , filename_( filename )
        , encoding_( encoding )
        , flushed_ ( false )
    {}
    virtual ~xofstream()
    {
        try
        {
            if(
#ifndef __CYGWIN__
                ! std::uncaught_exception() &&
#endif // $$$$ MAT : not sure if it's cygwin or gcc 3.4.4 but uncaught_exception always returns true
                ! flushed_ )
                flush();
        }
        catch( ... )
        {}
    }
    //@}

private:
    //! @name Operations
    //@{
    virtual void flush()
    {
        fill( filename_, encoding_ );
        flushed_ = true;
    }
    //@}

private:
    //! @name Member data
    //@{
    output output_;
    const std::string filename_;
    const std::string encoding_;
    bool flushed_;
    //@}
};

}

#ifdef _MSC_VER
#   pragma warning( pop )
#endif

#endif // xeumeuleu_xofstream_hpp
