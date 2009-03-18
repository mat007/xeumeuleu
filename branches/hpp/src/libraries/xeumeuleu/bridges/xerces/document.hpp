/*
 *   Copyright (c) 2008, Mathieu Champlon
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

#ifndef xeumeuleu_document_hpp
#define xeumeuleu_document_hpp

#include <xeumeuleu/streams/grammar.hpp>
#include <xeumeuleu/streams/encoding.hpp>
#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/bridges/xerces/parser.hpp>
#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/xerces_ptr.hpp>
#include <xeumeuleu/bridges/xerces/detail/chained_exception.hpp>
#include <xeumeuleu/bridges/xerces/detail/error_hppandler.hpp>
#include <xeumeuleu/bridges/xerces/detail/beautifier.hpp>
#include <xeumeuleu/bridges/xerces/detail/translate.hpp>
#include <xeumeuleu/bridges/xerces/detail/locator.hpp>
#include <xeumeuleu/bridges/xerces/detail/builder.hpp>
#include <fstream>

#define TRY try {
#define CATCH } \
    catch( const XERCES_CPP_NAMESPACE::OutOfMemoryException& ) { throw xml::exception( "Out of memory" ); } \
    catch( const XERCES_CPP_NAMESPACE::XMLException& e ) { throw chained_exception( e ); } \
    catch( const XERCES_CPP_NAMESPACE::DOMException& e ) { throw chained_exception( e ); }

namespace xml
{
// =============================================================================
/** @class  document
    @brief  Document base class
*/
// Created: MAT 2008-02-25
// =============================================================================
class document
{
protected:
    //! @name Constructors/Destructor
    //@{
    document()
        : document_( build() )
    {}
    document( const std::string& filename, const encoding* encoding, const grammar& grammar )
        : document_( build( filename, encoding, grammar ) )
    {}
    document( const char* data, std::size_t size, const encoding* encoding, const grammar& grammar )
        : document_( build( data, size, encoding, grammar ) )
    {}
    virtual ~document()
    {
        clean( document_.get() );
    }
    //@}

    //! @name Operations
    //@{
    void fill( const std::string& filename, const std::string& encoding ) const
    {
        if( ! document_->hasChildNodes() )
            return;
        XERCES_CPP_NAMESPACE::LocalFileFormatTarget target( filename.c_str() );
        write( target, encoding );
    }
    void fill( std::string& data, const std::string& encoding ) const
    {
        if( ! document_->hasChildNodes() )
            return;
        XERCES_CPP_NAMESPACE::MemBufFormatTarget target;
        write( target, encoding );
        data = reinterpret_cast< const char* >( target.getRawBuffer() );
    }
    //@}

private:
    //! @name Helpers
    //@{
    void write( XERCES_CPP_NAMESPACE::XMLFormatTarget& destination, const std::string& encoding ) const
    {
        XERCES_CPP_NAMESPACE::DOMImplementation* impl = XERCES_CPP_NAMESPACE::DOMImplementationRegistry::getDOMImplementation( translate( "LS" ) );
        if( ! impl )
            throw xml::exception( "Internal error in 'document::write' : DOMImplementation 'LS' not found" );
        xerces_ptr< XERCES_CPP_NAMESPACE::DOMWriter > writer( *dynamic_cast< XERCES_CPP_NAMESPACE::DOMImplementationLS* >( impl )->createDOMWriter() );
        error_hppandler handler;
        writer->setErrorHandler( &handler );
        writer->setEncoding( translate( encoding ) );
        writer->setFeature( XERCES_CPP_NAMESPACE::XMLUni::fgDOMWRTFormatPrettyPrint, true );
        writer->setFeature( XERCES_CPP_NAMESPACE::XMLUni:: fgDOMWRTBOM, true );
        beautifier target( destination, writer->getNewLine() );
        writer->writeNode( &target, *document_ );
    }

    struct Initializer
    {
        Initializer()
        {
            XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();
        }
        ~Initializer()
        {
            XERCES_CPP_NAMESPACE::XMLPlatformUtils::Terminate();
        }
    };
    void initialize() const
    {
        static const Initializer initializer;
    }
    XERCES_CPP_NAMESPACE::DOMDocument& build() const
    {
        TRY
            initialize();
            XERCES_CPP_NAMESPACE::DOMImplementation* impl = XERCES_CPP_NAMESPACE::DOMImplementationRegistry::getDOMImplementation( translate( "LS" ) );
            if( ! impl )
                throw xml::exception( "Internal error in 'document::build' : DOMImplementation 'LS' not found" );
            return *impl->createDocument();
        CATCH
    }
    XERCES_CPP_NAMESPACE::DOMDocument& parse( XERCES_CPP_NAMESPACE::InputSource& source, const encoding* encoding, const grammar& grammar ) const
    {
        builder builder( translate( source.getSystemId() ) );
        parser parser( builder );
        grammar.configure( parser );
        if( encoding )
            source.setEncoding( translate( *encoding ) );
        return parser.parse( source );
    }
    XERCES_CPP_NAMESPACE::DOMDocument& build( const std::string& filename, const encoding* encoding, const grammar& grammar ) const
    {
        TRY
            initialize();
            if( ! std::ifstream( filename.c_str() ) )
                throw xml::exception( "Unable to open file '" + filename + "'" );
            XERCES_CPP_NAMESPACE::LocalFileInputSource source( static_cast< const XMLCh* const >( translate( filename ) ) );
            return parse( source, encoding, grammar );
        CATCH
    }
    XERCES_CPP_NAMESPACE::DOMDocument& build( const char* data, std::size_t size, const encoding* encoding, const grammar& grammar ) const
    {
        TRY
            initialize();
            XERCES_CPP_NAMESPACE::MemBufInputSource source( reinterpret_cast< const XMLByte* >( data ), size, "string_input", false );
            return parse( source, encoding, grammar );
        CATCH
    }
    void clean( XERCES_CPP_NAMESPACE::DOMNode* node ) const
    {
        while( node )
        {
            delete reinterpret_cast< locator* >( node->getUserData( translate( "locator" ) ) );
            clean( node->getFirstChild() );
            node = node->getNextSibling();
        }
    }
    //@}

private:
    //! @name Copy/Assignment
    //@{
    document( const document& );            //!< Copy constructor
    document& operator=( const document& ); //!< Assignment operator
    //@}

protected:
    //! @name Member data
    //@{
    xerces_ptr< XERCES_CPP_NAMESPACE::DOMDocument > document_;
    //@}
};

}

#undef TRY
#undef CATCH

#endif // xeumeuleu_document_hpp
