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

#ifndef xeumeuleu_xistream_hpp
#define xeumeuleu_xistream_hpp

#include <xeumeuleu/streams/detail/input_context.hpp>
#include <xeumeuleu/streams/detail/input_base.hpp>
#include <xeumeuleu/streams/detail/optional_input.hpp>
#include <string>
#include <memory>

#ifdef _MSC_VER
#   pragma warning( push )
#   pragma warning( disable: 4355 )
#endif

namespace xml
{
    class xostream;

// =============================================================================
/** @class  xistream
    @brief  Xml input stream
*/
// Created: MAT 2006-01-04
// =============================================================================
class xistream : protected input_context
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit xistream( input_base& input )
        : base_    ( input )
        , input_   ( &input )
        , optional_( input, *this )
    {}
    virtual ~xistream()
    {}
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag )
    {
        input_->start( tag );
    }
    void end()
    {
        input_->end();
    }

    void read( std::string& value ) const { input_->read( value ); }
    void read( bool& value ) const { input_->read( value ); }
    void read( short& value ) const { input_->read( value ); }
    void read( int& value ) const { input_->read( value ); }
    void read( long& value ) const { input_->read( value ); }
    void read( long long& value ) const { input_->read( value ); }
    void read( float& value ) const { input_->read( value ); }
    void read( double& value ) const { input_->read( value ); }
    void read( long double& value ) const { input_->read( value ); }
    void read( unsigned short& value ) const { input_->read( value ); }
    void read( unsigned int& value ) const { input_->read( value ); }
    void read( unsigned long& value ) const { input_->read( value ); }
    void read( unsigned long long& value ) const { input_->read( value ); }
    void read( xostream& xos ) const;

    xistream& operator>>( std::string& value ) { input_->read( value ); return *this; }
    xistream& operator>>( bool& value ) { input_->read( value ); return *this; }
    xistream& operator>>( short& value ) { input_->read( value ); return *this; }
    xistream& operator>>( int& value ) { input_->read( value ); return *this; }
    xistream& operator>>( long& value ) { input_->read( value ); return *this; }
    xistream& operator>>( long long& value ) { input_->read( value ); return *this; }
    xistream& operator>>( float& value ) { input_->read( value ); return *this; }
    xistream& operator>>( double& value ) { input_->read( value ); return *this; }
    xistream& operator>>( long double& value ) { input_->read( value ); return *this; }
    xistream& operator>>( unsigned short& value ) { input_->read( value ); return *this; }
    xistream& operator>>( unsigned int& value ) { input_->read( value ); return *this; }
    xistream& operator>>( unsigned long& value ) { input_->read( value ); return *this; }
    xistream& operator>>( unsigned long long& value ) { input_->read( value ); return *this; }
    xistream& operator>>( xostream& xos );

    std::auto_ptr< input_base > branch( bool clone ) const
    {
        return input_->branch( clone );
    }

    void copy( output& destination ) const
    {
        input_->copy( destination );
    }

    void error( const std::string& message ) const
    {
        input_->error( message );
    }
    //@}

    //! @name Accessors
    //@{
    bool has_child( const std::string& name ) const
    {
        return input_->has_child( name );
    }
    bool has_attribute( const std::string& name ) const
    {
        return input_->has_attribute( name );
    }
    bool has_content() const
    {
        return input_->has_content();
    }

    template< typename T > void attribute( const std::string& name, T& value ) const
    {
        input_->attribute( name, value );
    }

    void nodes( const visitor& v ) const
    {
        input_->nodes( v );
    }
    void attributes( const visitor& v ) const
    {
        input_->attributes( v );
    }
    //@}

    //! @name Modifiers
    //@{
    void optional()
    {
        if( input_ == &base_ )
            input_ = &optional_;
    }
    //@}

private:
    //! @name Operations
    //@{
    virtual input_base& reset( input_base& input )
    {
        input_ = &input;
        return *input_;
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    xistream( const xistream& );            //!< Copy constructor
    xistream& operator=( const xistream& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    const input_base& base_;
    input_base* input_;
    optional_input optional_;
    //@}
};

#ifdef _MSC_VER
#   pragma warning( pop )
#endif

}

#include <xeumeuleu/streams/xostream.hpp>

namespace xml
{
    inline void xistream::read( xostream& xos ) const
    {
        xos.write( *this );
    }
    inline xistream& xistream::operator>>( xostream& xos )
    {
        xos.write( *this );
        return *this;
    }
}

#endif // xeumeuleu_xistream_hpp
