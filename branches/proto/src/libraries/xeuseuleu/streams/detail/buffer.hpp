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

#ifndef xeuseuleu_buffer_hpp
#define xeuseuleu_buffer_hpp

#include <xeuseuleu/streams/detail/output.hpp>
#include <memory>

namespace xsl
{
// =============================================================================
/** @class  buffer
    @brief  Buffer implementation
*/
// Created: MCO 2007-10-02
// =============================================================================
class buffer
{
public:
    //! @name Constructors/Destructor
    //@{
    buffer( std::auto_ptr< output > output, std::auto_ptr< buffer > next )
        : output_( *output.release() )
        , owned_ ( true )
        , next_  ( next )
        , level_ ( 0 )
    {}
    explicit buffer( output& output )
        : output_( output )
        , owned_ ( false )
        , level_ ( 0 )
    {}
    ~buffer()
    {
        if( owned_ )
            delete &output_;
    }
    //@}

    //! @name Operations
    //@{
    void parameter( const std::string& key, const std::string& expression )
    {
        output_.parameter( key, expression );
    }

    buffer* apply( const xml::start_manipulator& m )
    {
        output_.apply( m );
        ++level_;
        return this;
    }
    buffer* apply( const xml::end_manipulator& m )
    {
        output_.apply( m );
        --level_;
        return transform();
    }

    template< typename T > buffer* apply( const T& value )
    {
        output_.apply( value );
        return transform();
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    buffer( const buffer& );            //!< Copy constructor
    buffer& operator=( const buffer& ); //!< Assignment operator
    //@}

    //! @name Helpers
    //@{
    buffer* transform()
    {
        if( level_ == 0 )
        {
            output_.transform();
            if( next_.get() )
                return chain();
        }
        return this;
    }
    buffer* chain()
    {
        buffer* next = next_->apply( output_ );
        if( next != next_.get() )
            return next;
        return next_.release();
    }
    //@}

private:
    //! @name Member data
    //@{
    output& output_;
    bool owned_; // $$$$ MAT : not so great...
    std::auto_ptr< buffer > next_;
    unsigned int level_;
    //@}
};

}

#endif // xeuseuleu_buffer_hpp
