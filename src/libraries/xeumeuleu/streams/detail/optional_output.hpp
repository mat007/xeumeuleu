/*
 *   Copyright (c) 2017, Mathieu Champlon
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

#ifndef xeumeuleu_optional_output_hpp
#define xeumeuleu_optional_output_hpp

#include <xeumeuleu/streams/detail/output_base.hpp>
#include <xeumeuleu/streams/detail/output_context.hpp>
#include <xeumeuleu/bridges/xerces/input.hpp>
#include <xeumeuleu/bridges/xerces/output.hpp>

namespace xml
{
namespace detail
{
    class delayed_data
    {
    public:
        virtual ~delayed_data()
        {}

        virtual void commit( output_base& output ) const = 0;

        virtual bool end() const = 0;
    };
}

// =============================================================================
/** @class  optional_output
    @brief  Output base
*/
// Created: MAT 2017-03-15
// =============================================================================
class optional_output : public output_base
{
public:
    //! @name Constructors/Destructor
    //@{
    optional_output( output_base& output, output_context& context )
        : parent_  ( 0 )
        , output_  ( output )
        , context_ ( context )
        , optional_( true )
    {}
    optional_output( optional_output& parent, output_base& output, output_context& context )
        : parent_  ( &parent )
        , output_  ( output )
        , context_ ( context )
        , optional_( false )
    {}
    virtual ~optional_output()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string* ns, const std::string& tag );
    virtual void end()
    {
        bool end = false;
        while( !delayed_.empty() && !end )
        {
            end = delayed_.back()->end();
            delayed_.pop_back();
        }
        if( !end )
            output_.end();
        if( delayed_.empty() )
            context_.reset( output_ );
    }

    virtual void write( const std::string& value )
    {
        commit().write( value );
    }
    virtual void write( bool value )
    {
        commit().write( value );
    }
    virtual void write( int value )
    {
        commit().write( value );
    }
    virtual void write( long value )
    {
        commit().write( value );
    }
    virtual void write( long long value )
    {
        commit().write( value );
    }
    virtual void write( float value )
    {
        commit().write( value );
    }
    virtual void write( double value )
    {
        commit().write( value );
    }
    virtual void write( long double value )
    {
        commit().write( value );
    }
    virtual void write( unsigned int value )
    {
        commit().write( value );
    }
    virtual void write( unsigned long value )
    {
        commit().write( value );
    }
    virtual void write( unsigned long long value )
    {
        commit().write( value );
    }

    virtual void cdata( const std::string& value )
    {
        commit().cdata( value );
    }
    virtual void instruction( const std::string& target, const std::string& data )
    {
        commit().instruction( target, data );
    }
    virtual void prefix( const std::string& ns, const std::string& prefix )
    {
        commit().prefix( ns, prefix );
    }

    virtual std::unique_ptr< output_base > attribute( const std::string* ns, const std::string& name );

    virtual void copy( const input_base& input )
    {
        commit().copy( input );
    }

    virtual std::unique_ptr< output_base > branch() const
    {
        if( optional_ )
            throw xml::exception( "invalid branch after optional" );
        return output_.branch();
    }

    void optional()
    {
        optional_ = true;
    }
    //@}

private:
    //! @name Operations
    //@{
    output_base& commit()
    {
        if( commit_ )
            return *commit_;
        std::unique_ptr< output_base > output;
        if( parent_ )
            output = parent_->commit().branch();
        for( auto it = delayed_.begin(); it != delayed_.end(); ++it )
            (*it)->commit( output ? *output : output_ );
        delayed_.clear();
        if( output )
            return context_.reset( std::move( output ) );
        commit_ = output_.branch();
        return context_.reset( output_ );
    }
    //@}

private:
    //! @name Member data
    //@{
    optional_output* parent_;
    output_base& output_;
    output_context& context_;
    std::unique_ptr< output_base > commit_;
    std::vector< std::unique_ptr< detail::delayed_data > > delayed_;
    bool optional_;
    //@}
};

}

#include <xeumeuleu/bridges/xerces/document.hpp>

namespace xml
{
namespace detail
{
    class delayed_start : public delayed_data
    {
    public:
        delayed_start( const std::string* ns, const std::string& tag )
            : ns_ ( ns ? new std::string( *ns ) : 0 )
            , tag_( tag )
        {}

    private:
        virtual void commit( output_base& output ) const
        {
            output.start( ns_.get(), tag_ );
        }

        virtual bool end() const
        {
            return true;
        }

    private:
        std::unique_ptr< std::string > ns_;
        std::string tag_;
    };

    class delayed_attribute : public delayed_data, private document
    {
    public:
        delayed_attribute()
            : output_( *document_, *document_ )
            , input_ ( *document_ )
        {
            output_.start( 0, "root" );
            input_.start( 0, "root" );
        }

        std::unique_ptr< output_base > attribute( const std::string* ns, const std::string& name )
        {
            return output_.attribute( ns, name );
        }

    private:
        virtual void commit( output_base& output ) const
        {
            output.copy( input_ );
        }

        virtual bool end() const
        {
            return false;
        }

    private:
        output output_;
        input input_;
    };
}

    inline void optional_output::start( const std::string* ns, const std::string& tag )
    {
        if( optional_ )
        {
            optional_ = false;
            delayed_.push_back( std::unique_ptr< detail::delayed_start >( new detail::delayed_start( ns, tag ) ) );
        }
        else
            commit().start( ns, tag );
    }

    inline std::unique_ptr< output_base > optional_output::attribute( const std::string* ns, const std::string& name )
    {
        if( optional_ && !delayed_.empty() )
        {
            optional_ = false;
            std::unique_ptr< detail::delayed_attribute > data( new detail::delayed_attribute() );
            auto output = data->attribute( ns, name );
            delayed_.push_back( std::move( data ) );
            return std::move( output );
        }
        return commit().attribute( ns, name );
    }
}

#endif // xeumeuleu_optional_output_hpp
