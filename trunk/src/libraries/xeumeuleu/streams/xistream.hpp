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
#include <xeumeuleu/streams/detail/output_base.hpp>
#include <xeumeuleu/streams/detail/temporary_input.hpp>
#include <xeumeuleu/streams/detail/optional_input.hpp>
#include <string>
#include <memory>

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
        : input_( &input )
    {}
    virtual ~xistream()
    {}
    //@}

    //! @name Operations
    //@{
    void start( const std::string& tag )
    {
        std::auto_ptr< std::string > ns = ns_;
        input_->start( ns.get(), tag );
    }
    void end()
    {
        ns_.reset();
        input_->end();
    }

    friend xistream& operator>>( xistream& xis, std::string& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, bool& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, short& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, int& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, long& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, long long& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, float& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, double& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, long double& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, unsigned short& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, unsigned int& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, unsigned long& value ) { xis.input_->read().to( value ); return xis; }
    friend xistream& operator>>( xistream& xis, unsigned long long& value ) { xis.input_->read().to( value ); return xis; }

    std::auto_ptr< input_base > branch( bool clone ) const
    {
        return input_->branch( clone );
    }

    void copy( output_base& destination ) const
    {
        destination.copy( *input_ );
    }

    void error( const std::string& message ) const
    {
        throw xml::exception( context() + message );
    }
    //@}

    //! @name Accessors
    //@{
    bool has_child( const std::string& name ) const
    {
        return input_->has_child( 0, name );
    }
    bool has_child( const std::string& ns, const std::string& name ) const
    {
        return input_->has_child( &ns, name );
    }
    bool has_attribute( const std::string& name ) const
    {
        return input_->has_attribute( 0, name );
    }
    bool has_attribute( const std::string& ns, const std::string& name ) const
    {
        return input_->has_attribute( &ns, name );
    }
    bool has_content() const
    {
        return input_->has_content();
    }
    bool is_optional() const
    {
        return input_ == optional_.get();
    }

    template< typename T > T value() const;
    std::string value( const char* fallback ) const
    {
        return value( std::string( fallback ) );
    }
    template< typename T > T value( const T& fallback ) const;

    template< typename T > T content( const std::string& name ) const;
    std::string content( const std::string& name, const char* fallback ) const
    {
        return content( name, std::string( fallback ) );
    }
    template< typename T > T content( const std::string& name, const T& fallback ) const;

    template< typename T > void attribute_by_ref( const std::string& name, T& value ) const
    {
        std::auto_ptr< std::string > ns = ns_;
        std::auto_ptr< input_base > input = input_->attribute( ns.get(), name );
        if( input.get() )
        {
            xistream xis( *input );
            xis >> value;
        }
    }

    template< typename T > T attribute( const std::string& name ) const;
    std::string attribute( const std::string& name, const char* fallback ) const
    {
        return attribute( name, std::string( fallback ) );
    }
    template< typename T > T attribute( const std::string& name, const T& fallback ) const;

    void nodes( const visitor& v ) const
    {
        std::auto_ptr< std::string > ns = ns_;
        input_->nodes( ns.get(), v );
    }
    void attributes( const visitor& v ) const
    {
        std::auto_ptr< std::string > ns = ns_;
        input_->attributes( ns.get(), v );
    }

    void prefix( const std::string& ns, std::string& prefix ) const
    {
        input_->prefix( ns, prefix );
    }

    std::string context() const
    {
        return input_->context();
    }
    //@}

    //! @name Modifiers
    //@{
    void optional()
    {
        if( input_ != temporary_.get() && input_ != optional_.get() )
        {
            temporary_.reset( new temporary_input( *input_, *this ) );
            optional_.reset( new optional_input( *input_, *temporary_, *this ) );
            input_ = optional_.get();
        }
    }
    void ns( const std::string& name )
    {
        ns_.reset( new std::string( name ) );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    xistream( const xistream& );            //!< Copy constructor
    xistream& operator=( const xistream& ); //!< Assignment operator
    //@}

    //! @name Operations
    //@{
    virtual input_base& reset( input_base& input )
    {
        input_ = &input;
        return *input_;
    }
    //@}

private:
    //! @name Member data
    //@{
    input_base* input_;
    std::auto_ptr< temporary_input > temporary_;
    std::auto_ptr< optional_input > optional_;
    mutable std::auto_ptr< std::string > ns_;
    //@}
};

}

#include <xeumeuleu/streams/xostream.hpp>
#include <xeumeuleu/streams/xisubstream.hpp>
#include <xeumeuleu/manipulators/attribute.hpp>

namespace xml
{
    template< typename T > T xistream::value() const
    {
        T value;
        xml::xisubstream xiss( *this );
        xiss >> value;
        return value;
    }
    template< typename T > T xistream::value( const T& fallback ) const
    {
        T value = fallback;
        xml::xisubstream xiss( *this );
        xiss.optional();
        xiss >> value;
        return value;
    }
    template< typename T > T xistream::attribute( const std::string& name ) const
    {
        T value;
        xml::xisubstream xiss( *this );
        xiss >> xml::attribute( name, value );
        return value;
    }
    template< typename T > T xistream::attribute( const std::string& name, const T& fallback ) const
    {
        T value = fallback;
        xml::xisubstream xiss( *this );
        xiss.optional();
        xiss >> xml::attribute( name, value );
        return value;
    }
    template< typename T > T xistream::content( const std::string& name ) const
    {
        T value;
        xml::xisubstream xiss( *this );
        xiss.start( name );
        xiss >> value;
        return value;
    }
    template< typename T > T xistream::content( const std::string& name, const T& fallback ) const
    {
        T value = fallback;
        xml::xisubstream xiss( *this );
        xiss.optional();
        xiss.start( name );
        xiss.optional();
        xiss >> value;
        return value;
    }
    inline xistream& operator>>( xistream& xis, xostream& xos )
    {
        xos << xis;
        return xis;
    }
}

#endif // xeumeuleu_xistream_hpp
