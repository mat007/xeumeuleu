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

#include "buffer.h"

using namespace xsl;

// -----------------------------------------------------------------------------
// Name: buffer constructor
// Created: MCO 2007-10-02
// -----------------------------------------------------------------------------
buffer::buffer( output& output, std::auto_ptr< buffer > next )
    : output_( output )
    , owned_ ( true )
    , next_  ( next )
    , level_ ( 0 )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: buffer constructor
// Created: MCO 2007-10-02
// -----------------------------------------------------------------------------
buffer::buffer( output& output )
    : output_( output )
    , owned_ ( false )
    , level_ ( 0 )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: buffer destructor
// Created: MCO 2007-10-02
// -----------------------------------------------------------------------------
buffer::~buffer()
{
    if( owned_ )
        delete &output_;
}

// -----------------------------------------------------------------------------
// Name: buffer::parameter
// Created: MCO 2007-10-02
// -----------------------------------------------------------------------------
void buffer::parameter( const std::string& key, const std::string& expression )
{
    output_.parameter( key, expression );
}

// -----------------------------------------------------------------------------
// Name: buffer::apply
// Created: MCO 2007-10-02
// -----------------------------------------------------------------------------
buffer* buffer::apply( const xml::start& start )
{
    output_.apply( start );
    ++level_;
    return this;
}

// -----------------------------------------------------------------------------
// Name: buffer::apply
// Created: MCO 2007-10-02
// -----------------------------------------------------------------------------
buffer* buffer::apply( const xml::end_manipulator& end )
{
    output_.apply( end );
    --level_;
    return transform();
}

// -----------------------------------------------------------------------------
// Name: buffer::transform
// Created: MCO 2007-10-02
// -----------------------------------------------------------------------------
buffer* buffer::transform()
{
    if( level_ == 0 )
    {
        output_.transform();
        if( next_.get() )
            return chain();
    }
    return this;
}

// -----------------------------------------------------------------------------
// Name: buffer::chain
// Created: MCO 2007-10-02
// -----------------------------------------------------------------------------
buffer* buffer::chain()
{
    buffer* next = next_->apply( output_ );
    if( next != next_.get() )
        return next;
    return next_.release();
}