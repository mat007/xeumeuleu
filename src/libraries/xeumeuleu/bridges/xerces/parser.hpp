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

#ifndef xeumeuleu_parser_hpp
#define xeumeuleu_parser_hpp

#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/translate.hpp>
#include <xeumeuleu/bridges/xerces/detail/error_handler.hpp>
#include <xeumeuleu/bridges/xerces/detail/xerces_ptr.hpp>

namespace xml
{
    class external_grammar;
    class internal_grammar;
    class null_grammar;

// =============================================================================
/** @class  parser
    @brief  Parser wrapper
*/
// Created: MCO 2007-01-16
// =============================================================================
class parser
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit parser( XERCES_CPP_NAMESPACE::DOMBuilder& builder )
        : builder_( builder )
    {
        builder_.setFeature( XERCES_CPP_NAMESPACE::XMLUni::fgXercesUserAdoptsDOMDocument, true );
        builder_.setFeature( XERCES_CPP_NAMESPACE::XMLUni::fgDOMNamespaces, true );
        builder_.setFeature( XERCES_CPP_NAMESPACE::XMLUni::fgDOMDatatypeNormalization, true );
        builder_.setFeature( XERCES_CPP_NAMESPACE::XMLUni::fgXercesSchema, true );
    }
    virtual ~parser()
    {}
    //@}

    //! @name Operations
    //@{
    XERCES_CPP_NAMESPACE::DOMDocument& parse( XERCES_CPP_NAMESPACE::InputSource& source )
    {
        error_handler handler;
        builder_.setErrorHandler( &handler );
        XERCES_CPP_NAMESPACE::Wrapper4InputSource input( &source, false );
        xerces_ptr< XERCES_CPP_NAMESPACE::DOMDocument > document( builder_.parse( input ) );
        handler.check();
        return document.release();
    }

    void configure( const external_grammar& /*grammar*/, const std::string& uri )
    {
        builder_.setFeature( XERCES_CPP_NAMESPACE::XMLUni::fgDOMValidation, true );
        builder_.setFeature( XERCES_CPP_NAMESPACE::XMLUni::fgXercesUseCachedGrammarInParse, true );
        // $$$$ MAT 2006-03-27: use builder_.setProperty( XERCES_CPP_NAMESPACE::XMLUni::fgXercesSchemaExternalNoNameSpaceSchemaLocation, ... ) ?
        if( ! builder_.loadGrammar( translate( uri ), XERCES_CPP_NAMESPACE::Grammar::SchemaGrammarType, true ) )
            throw xml::exception( "Failed to load grammar '" + uri + "'" );
    }
    void configure( const internal_grammar& /*grammar*/ )
    {
        builder_.setFeature( XERCES_CPP_NAMESPACE::XMLUni::fgDOMValidateIfSchema, true );
    }
    void configure( const null_grammar& /*grammar*/ )
    {
        builder_.setFeature( XERCES_CPP_NAMESPACE::XMLUni::fgDOMValidation, false );
        builder_.setFeature( XERCES_CPP_NAMESPACE::XMLUni::fgXercesLoadExternalDTD, false );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    parser( const parser& );            //!< Copy constructor
    parser& operator=( const parser& ); //!< Assignment operator
    //@}

private:
    //! @name Member data
    //@{
    XERCES_CPP_NAMESPACE::DOMBuilder& builder_;
    //@}
};

}

#endif // xeumeuleu_parser_hpp
