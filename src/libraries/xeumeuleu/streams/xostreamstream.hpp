/*
 *   Copyright (c) 2009, Mathieu Champlon
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

#ifndef xeumeuleu_xostreamstream_hpp
#define xeumeuleu_xostreamstream_hpp

#include <xeumeuleu/streams/xostream.hpp>
#include <xeumeuleu/streams/encoding.hpp>
#include <xeumeuleu/bridges/xerces/document.hpp>
#include <xeumeuleu/bridges/xerces/output.hpp>
#include <algorithm>
#include <ostream>

#ifdef _MSC_VER
#   pragma warning( push )
#   pragma warning( disable: 4355 )
#endif

namespace xml
{
// =============================================================================
/** @class  xostreamstream
    @brief  Xml stream to adapt a standard output stream
*/
// Created: MCO 2009-11-12
// =============================================================================
class xostreamstream : private document, private flushable, public xostream
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit xostreamstream( std::basic_ostream< char >& stream, const encoding& encoding = encoding() )
        : xostream( output_ )
        , output_  ( *document_, *document_, *this )
        , stream_  ( stream )
        , encoding_( encoding )
        , flushed_ ( false )
    {}
    virtual ~xostreamstream()
    {
        try
        {
            if( ! flushed_ )
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
        std::string data;
        fill( data, encoding_ );
        std::copy( data.begin(), data.end(), std::ostreambuf_iterator< char >( stream_ ) );
        flushed_ = true;
    }
    //@}

private:
    //! @name Member data
    //@{
    output output_;
    std::basic_ostream< char >& stream_;
    const std::string encoding_;
    bool flushed_;
    //@}
};

}

#ifdef _MSC_VER
#   pragma warning( pop )
#endif

#endif // xeumeuleu_xostreamstream_hpp
