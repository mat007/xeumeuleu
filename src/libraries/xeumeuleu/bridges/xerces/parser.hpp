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

#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/translate.hpp>
#include <xeumeuleu/bridges/xerces/detail/error_handler.hpp>
#include <xeumeuleu/bridges/xerces/detail/xerces_ptr.hpp>
#include <sstream>

namespace xml
{
    class external_grammar;
    class internal_grammar;
    class memory_grammar;
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
    explicit parser( XERCES_CPP_NAMESPACE::DOMLSParser& parser )
        : parser_( parser )
    {
        set( XERCES_CPP_NAMESPACE::XMLUni::fgXercesUserAdoptsDOMDocument, true );
        set( XERCES_CPP_NAMESPACE::XMLUni::fgDOMNamespaces, true );
        set( XERCES_CPP_NAMESPACE::XMLUni::fgDOMDatatypeNormalization, true );
        set( XERCES_CPP_NAMESPACE::XMLUni::fgXercesSchema, true );
        parser_.getDomConfig()->setParameter( XERCES_CPP_NAMESPACE::XMLUni::fgDOMErrorHandler, &handler_ );
    }
    ~parser()
    {
        parser_.getDomConfig()->setParameter( XERCES_CPP_NAMESPACE::XMLUni::fgDOMErrorHandler, static_cast< void* >( 0 ) );
    }
    //@}

    //! @name Operations
    //@{
    XERCES_CPP_NAMESPACE::DOMDocument& parse( XERCES_CPP_NAMESPACE::InputSource& source )
    {
        XERCES_CPP_NAMESPACE::Wrapper4InputSource input( &source, false );
        xerces_ptr< XERCES_CPP_NAMESPACE::DOMDocument > document( parser_.parse( &input ) );
        handler_.check();
        return document.release();
    }

    void configure( const external_grammar& /*grammar*/, const std::string& uri )
    {
        configure();
        parser_.loadGrammar( translate( uri ), XERCES_CPP_NAMESPACE::Grammar::SchemaGrammarType, true );
        handler_.check( "failed to load grammar '" + uri + "'" );
    }
    void configure( const internal_grammar& /*grammar*/ )
    {
        set( XERCES_CPP_NAMESPACE::XMLUni::fgDOMValidateIfSchema, true );
    }
    void configure( const memory_grammar& /*grammar*/, const std::string& schema )
    {
        configure();
        XERCES_CPP_NAMESPACE::MemBufInputSource source( reinterpret_cast< const XMLByte* >( schema.c_str() ), schema.size(), make_id().c_str() );
        XERCES_CPP_NAMESPACE::Wrapper4InputSource input( &source, false );
        parser_.loadGrammar( &input, XERCES_CPP_NAMESPACE::Grammar::SchemaGrammarType, true );
        handler_.check( "failed to load memory grammar" );
    }
    void configure( const null_grammar& /*grammar*/ )
    {
        set( XERCES_CPP_NAMESPACE::XMLUni::fgDOMValidate, false );
        set( XERCES_CPP_NAMESPACE::XMLUni::fgXercesLoadSchema, false );
        set( XERCES_CPP_NAMESPACE::XMLUni::fgXercesLoadExternalDTD, false );
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    parser( const parser& );            //!< Copy constructor
    parser& operator=( const parser& ); //!< Assignment operator
    //@}

    //! @name Helpers
    //@{
    void set( const XMLCh feature[], bool value )
    {
        parser_.getDomConfig()->setParameter( feature, value );
    }
    void configure()
    {
        // $$$$ MAT 2006-03-27: use XERCES_CPP_NAMESPACE::XMLUni::fgXercesSchemaExternalNoNameSpaceSchemaLocation ?
        set( XERCES_CPP_NAMESPACE::XMLUni::fgDOMValidate, true );
        set( XERCES_CPP_NAMESPACE::XMLUni::fgXercesHandleMultipleImports, true );
        set( XERCES_CPP_NAMESPACE::XMLUni::fgXercesUseCachedGrammarInParse, true );
    }
    std::string make_id()
    {
        static int i = 0;
        std::stringstream s;
        s << "memory grammar " << i++;
        return s.str();
    }
    //@}

private:
    //! @name Member data
    //@{
    XERCES_CPP_NAMESPACE::DOMLSParser& parser_;
    error_handler handler_;
    //@}
};

}

#endif // xeumeuleu_parser_hpp
