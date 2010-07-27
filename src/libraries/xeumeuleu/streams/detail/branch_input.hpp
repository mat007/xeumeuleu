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

#ifndef xeumeuleu_branch_input_hpp
#define xeumeuleu_branch_input_hpp

#include <xeumeuleu/streams/detail/input_proxy.hpp>

namespace xml
{
// =============================================================================
/** @class  branch_input
    @brief  Input to handle branch manipulation
*/
// Created: MAT 2008-01-07
// =============================================================================
class branch_input : public input_proxy
{
public:
    //! @name Constructors/Destructor
    //@{
    branch_input( input_base& input1, input_base& input2, input_context& context )
        : input_proxy( input1 )
        , input1_ ( input1 )
        , input2_ ( input2 )
        , context_( context )
        , level_  ( 0 )
    {}
    virtual ~branch_input()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string* ns, const std::string& tag )
    {
        input1_.start( ns, tag );
        ++level_;
    }
    virtual void end()
    {
        input1_.end();
        if( --level_ == 0 )
            context_.reset( input2_ );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    branch_input( const branch_input& );            //!< Copy constructor
    branch_input& operator=( const branch_input& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    input_base& input1_;
    input_base& input2_;
    input_context& context_;
    unsigned int level_;
    //@}
};

}

#endif // xeumeuleu_branch_input_hpp
