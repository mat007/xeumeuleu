/*
 *   Copyright (c) 2007, Mathieu Champlon
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

#ifndef xeuseuleu_xbuffertransform_hpp
#define xeuseuleu_xbuffertransform_hpp

#include <string>

namespace xsl
{
    class xtransform;

// =============================================================================
/** @class  xbuffertransform
    @brief  Xsl chained transform
    @par    Using example
    @code
    xsl::xbuffertransform xbt( "transform.xsl" );
    @endcode
*/
// Created: SLI 2007-09-07
// =============================================================================
class xbuffertransform
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit xbuffertransform( const std::string& stylesheet )
        : stylesheet_( stylesheet )
        , stream_    ( 0 )
    {}
    explicit xbuffertransform( std::istream& stylesheet )
        : stream_( &stylesheet )
    {}
    virtual ~xbuffertransform()
    {}
    //@}

    //! @name Operations
    //@{
    void apply( xtransform& xst ) const;
    //@}

private:
    //! @name Copy/Assignment
    //@{
    xbuffertransform( const xbuffertransform& );            //!< Copy constructor
    xbuffertransform& operator=( const xbuffertransform& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const std::string stylesheet_;
    std::istream* stream_;
    //@}
};

}

#include <xeuseuleu/streams/xtransform.hpp>

namespace xsl
{
    inline void xbuffertransform::apply( xtransform& xst ) const
    {
        if( stream_ ) // $$$$ MCO : make two separate implementations
            xst.add( *stream_ );
        else
            xst.add( stylesheet_ );
    }
}

#endif // xeuseuleu_xbuffertransform_hpp
