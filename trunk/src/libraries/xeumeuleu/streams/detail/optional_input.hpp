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

#ifndef xeumeuleu_optional_input_hpp
#define xeumeuleu_optional_input_hpp

#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/streams/detail/input_proxy.hpp>
#include <xeumeuleu/streams/detail/input_context.hpp>
#include <xeumeuleu/streams/detail/null_input.hpp>

namespace xml
{
// =============================================================================
/** @class  optional_input
    @brief  Input state to handle optional manipulation
*/
// Created: MAT 2006-03-20
// =============================================================================
class optional_input : public input_proxy
{
public:
    //! @name Constructors/Destructor
    //@{
    optional_input( input_base& input, input_context& context )
        : input_proxy( input )
        , input_  ( input )
        , context_( context )
        , null_   ( input_, context_ )
    {}
    virtual ~optional_input()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string& tag )
    {
        if( input_.has_child( tag ) )
            context_.reset( input_ ).start( tag );
        else
            context_.reset( null_ ).start( tag );
    }
    virtual void end()
    {
        context_.reset( input_ );
        throw xml::exception( "Invalid 'end' after an 'optional'" );
    }

    virtual void read( std::string& value ) const { read_content( value ); }
    virtual void read( bool& value ) const { read_content( value ); }
    virtual void read( short& value ) const { read_content( value ); }
    virtual void read( int& value ) const { read_content( value ); }
    virtual void read( long& value ) const { read_content( value ); }
    virtual void read( long long& value ) const { read_content( value ); }
    virtual void read( float& value ) const { read_content( value ); }
    virtual void read( double& value ) const { read_content( value ); }
    virtual void read( long double& value ) const { read_content( value ); }
    virtual void read( unsigned short& value ) const { read_content( value ); }
    virtual void read( unsigned int& value ) const { read_content( value ); }
    virtual void read( unsigned long& value ) const { read_content( value ); }
    virtual void read( unsigned long long& value ) const { read_content( value ); }
    //@}

    //! @name Accessors
    //@{
    virtual void attribute( const std::string& name, std::string& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, bool& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, short& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, int& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, long& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, long long& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, float& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, double& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, long double& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned short& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned int& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned long& value ) const { read_attribute( name, value ); }
    virtual void attribute( const std::string& name, unsigned long long& value ) const { read_attribute( name, value ); }

    virtual void nodes( const visitor& v ) const
    {
        context_.reset( input_ ).nodes( v );
    }
    virtual void attributes( const visitor& v ) const
    {
        context_.reset( input_ ).attributes( v );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    optional_input( const optional_input& );            //!< Copy constructor
    optional_input& operator=( const optional_input& ); //!< Assignment operator
    //@}

    //! @name Helpers
    //@{
    template< typename T > void read_content( T& value ) const
    {
        if( input_.has_content() )
            context_.reset( input_ ).read( value );
        else
            context_.reset( input_ );
    }
    template< typename T > void read_attribute( const std::string& name, T& value ) const
    {
        if( input_.has_attribute( name ) )
            context_.reset( input_ ).attribute( name, value );
        else
            context_.reset( input_ );
    }
    //@}

private:
    //! @name Member data
    //@{
    input_base& input_;
    input_context& context_;
    null_input null_;
    //@}
};

}

#endif // xeumeuleu_optional_input_hpp
