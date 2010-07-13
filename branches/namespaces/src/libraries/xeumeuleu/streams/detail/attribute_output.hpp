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

#ifndef xeumeuleu_attribute_output_hpp
#define xeumeuleu_attribute_output_hpp

#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/streams/detail/output_base.hpp>
#include <string>

namespace xml
{
// =============================================================================
/** @class  output_base
    @brief  Attribute output implementation
*/
// Created: MAT 2009-11-27
// =============================================================================
class attribute_output : public output_base
{
public:
    //! @name Constructors/Destructor
    //@{
    attribute_output( output_base& output, const std::string& attribute )
        : output_   ( output )
        , attribute_( attribute )
    {}
    virtual ~attribute_output()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string& /*tag*/ )
    {
        throw xml::exception( "Invalid 'start' while writing attribute" );
    }
    virtual void start( const std::string& /*ns*/, const std::string& /*tag*/ )
    {
        throw xml::exception( "Invalid 'start' while writing attribute" );
    }
    virtual void end()
    {
        throw xml::exception( "Invalid 'end' while writing attribute" );
    }

    virtual void write( const std::string& value ) { output_.attribute( attribute_, value ); }
    virtual void write( bool value ) { output_.attribute( attribute_, value ); }
    virtual void write( int value ) { output_.attribute( attribute_, value ); }
    virtual void write( long value ) { output_.attribute( attribute_, value ); }
    virtual void write( long long value ) { output_.attribute( attribute_, value ); }
    virtual void write( float value ) { output_.attribute( attribute_, value ); }
    virtual void write( double value ) { output_.attribute( attribute_, value ); }
    virtual void write( long double value ) { output_.attribute( attribute_, value ); }
    virtual void write( unsigned int value ) { output_.attribute( attribute_, value ); }
    virtual void write( unsigned long value ) { output_.attribute( attribute_, value ); }
    virtual void write( unsigned long long value ) { output_.attribute( attribute_, value ); }

    virtual void cdata( const std::string& /*value*/ )
    {
        throw xml::exception( "Invalid 'cdata' while writing attribute" );
    }
    virtual void instruction( const std::string& /*target*/, const std::string& /*data*/ )
    {
        throw xml::exception( "Invalid 'instruction' while writing attribute" );
    }

    virtual void attribute( const std::string& /*name*/, const std::string& /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }
    virtual void attribute( const std::string& /*name*/, bool /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }
    virtual void attribute( const std::string& /*name*/, int /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }
    virtual void attribute( const std::string& /*name*/, long /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }
    virtual void attribute( const std::string& /*name*/, long long /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }
    virtual void attribute( const std::string& /*name*/, float /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }
    virtual void attribute( const std::string& /*name*/, double /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }
    virtual void attribute( const std::string& /*name*/, long double /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }
    virtual void attribute( const std::string& /*name*/, unsigned int /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }
    virtual void attribute( const std::string& /*name*/, unsigned long /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }
    virtual void attribute( const std::string& /*name*/, unsigned long long /*value*/ )
    {
        throw xml::exception( "Invalid 'attribute' while writing attribute" );
    }

    virtual void copy( const input_base& /*input*/ )
    {
        throw xml::exception( "Invalid 'copy' while writing attribute" );
    }

    virtual std::auto_ptr< output_base > branch() const
    {
        throw xml::exception( "Invalid 'branch' while writing attribute" );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    attribute_output( const attribute_output& );            //!< Copy constructor
    attribute_output& operator=( const attribute_output& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    output_base& output_;
    const std::string& attribute_;
    //@}
};

}

#endif // xeumeuleu_attribute_output_hpp
