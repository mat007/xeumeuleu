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

#ifndef xeumeuleu_grammar_hpp
#define xeumeuleu_grammar_hpp

#include <xeumeuleu/bridges/xerces/parser.hpp>
#include <string>

namespace xml
{
// =============================================================================
/** @class  grammar
    @brief  Grammar declaration
*/
// Created: MAT 2006-03-24
// =============================================================================
class grammar
{
public:
    //! @name Constructors/Destructor
    //@{
             grammar() {}
    virtual ~grammar() {}
    //@}

    //! @name Operations
    //@{
    virtual void configure( parser& parser ) const = 0;
    //@}
};

// =============================================================================
/** @class  external_grammar
    @brief  Grammar implementation to set an external schema for validation
*/
// Created: MAT 2006-03-24
// =============================================================================
class external_grammar : public grammar
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit external_grammar( const std::string& uri )
        : uri_( uri )
    {}
    virtual ~external_grammar()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void configure( parser& parser ) const
    {
        parser.configure( *this, uri_ );
    }
    //@}

private:
    //! @name Member data
    //@{
    std::string uri_;
    //@}
};

// =============================================================================
/** @class  internal_grammar
    @brief  Grammar implementation to set internal schema validation
*/
// Created: ZEBRE 2006-08-30
// =============================================================================
class internal_grammar : public grammar
{
public:
    //! @name Constructors/Destructor
    //@{
    internal_grammar()
    {}
    virtual ~internal_grammar()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void configure( parser& parser ) const
    {
        parser.configure( *this );
    }
    //@}
};

// =============================================================================
/** @class  memory_grammar
    @brief  Grammar implementation to set an in-memory schema for validation
*/
// Created: MAT 2010-11-12
// =============================================================================
class memory_grammar : public grammar
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit memory_grammar( const std::string& schema )
        : schema_( schema )
    {}
    virtual ~memory_grammar()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void configure( parser& parser ) const
    {
        parser.configure( *this, schema_ );
    }
    //@}

private:
    //! @name Member data
    //@{
    std::string schema_;
    //@}
};

// =============================================================================
/** @class  null_grammar
    @brief  Grammar implementation to disable validation
*/
// Created: MCO 2007-01-16
// =============================================================================
class null_grammar : public grammar
{
public:
    //! @name Constructors/Destructor
    //@{
    null_grammar()
    {}
    virtual ~null_grammar()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void configure( parser& parser ) const
    {
        parser.configure( *this );
    }
    //@}
};

namespace detail
{
// =============================================================================
/** @class  grammars
    @brief  Grammar implementation to combine grammars
*/
// Created: MAT 2010-11-19
// =============================================================================
class grammars : public grammar
{
public:
    grammars( const grammar& lhs, const grammar& rhs )
        : lhs_( &lhs )
        , rhs_( &rhs )
    {}
    virtual void configure( parser& parser ) const
    {
        lhs_->configure( parser );
        rhs_->configure( parser );
    }
private:
    const grammar* lhs_;
    const grammar* rhs_;
};
}

inline detail::grammars operator+( const grammar& lhs, const grammar& rhs )
{
    return detail::grammars( lhs, rhs );
}

}

#endif // xeumeuleu_grammar_hpp
