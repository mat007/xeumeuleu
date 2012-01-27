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

#ifndef xeumeuleu_input_hpp
#define xeumeuleu_input_hpp

#include <xeumeuleu/streams/xistream.hpp>
#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/streams/detail/visitor.hpp>
#include <xeumeuleu/bridges/xerces/output.hpp>
#include <xeumeuleu/bridges/xerces/data.hpp>
#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/trim.hpp>
#include <xeumeuleu/bridges/xerces/detail/chained_exception.hpp>
#include <xeumeuleu/bridges/xerces/detail/translate.hpp>
#include <xeumeuleu/bridges/xerces/detail/locator.hpp>
#include <limits>

#define XEUMEULEU_TRY try {
#define XEUMEULEU_CATCH } \
            catch( const XERCES_CPP_NAMESPACE::OutOfMemoryException& ) { throw exception( "Out of memory" ); } \
            catch( const XERCES_CPP_NAMESPACE::XMLException& e ) { throw chained_exception( e, context() ); } \
            catch( const XERCES_CPP_NAMESPACE::DOMException& e ) { throw chained_exception( e, context() ); }

namespace xml
{
// =============================================================================
/** @class  input
    @brief  Input implementation
*/
// Created: MAT 2006-01-08
// =============================================================================
class input : public input_base
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit input( const XERCES_CPP_NAMESPACE::DOMNode& root )
        : root_   ( root )
        , current_( &root_ )
    {}
    virtual ~input()
    {}
    //@}

    //! @name Operations
    //@{
    virtual void start( const std::string* ns, const std::string& tag )
    {
        XEUMEULEU_TRY
            const XERCES_CPP_NAMESPACE::DOMNode* child = find_child( ns, tag );
            if( ! child )
                throw exception( context() + location() + " does not have a child named '" + tag + "'"
                    + (!ns || ns->empty() ? "" : (" in namespace '" + *ns + "'")) );
            current_ = child;
        XEUMEULEU_CATCH
    }
    virtual void end()
    {
        XEUMEULEU_TRY
            if( current_ == &root_ )
                throw exception( context() + "Cannot move up from " + location() );
            const XERCES_CPP_NAMESPACE::DOMNode* parent = current_->getParentNode();
            if( ! parent )
                throw exception( context() + location() + " has no parent" );
            current_ = parent;
        XEUMEULEU_CATCH
    }

    virtual data read() const
    {
        const XERCES_CPP_NAMESPACE::DOMNode* child = find_content();
        if( ! child )
            throw exception( context() + location() + " does not have a content" );
        return data( *current_, *child );
    }

    virtual std::auto_ptr< input_base > attribute( const std::string* ns, const std::string& name ) const
    {
        const XERCES_CPP_NAMESPACE::DOMNode* attribute = find_attribute( ns, name );
        if( ! attribute )
            throw exception( context() + location() + " does not have an attribute '" + name + "'"
                + (!ns || ns->empty() ? "" : (" in namespace '" + *ns + "'")) );
        return std::auto_ptr< input_base >( new input( *attribute ) );
    }

    virtual std::auto_ptr< input_base > branch( bool clone ) const;

    virtual void copy( output& destination ) const
    {
        XEUMEULEU_TRY
            destination.copy( *current_ );
        XEUMEULEU_CATCH
    }
    //@}

    //! @name Accessors
    //@{
    virtual bool has_child( const std::string* ns, const std::string& name ) const
    {
        XEUMEULEU_TRY
            return find_child( ns, name ) != 0;
        XEUMEULEU_CATCH
    }
    virtual bool has_attribute( const std::string* ns, const std::string& name ) const
    {
        XEUMEULEU_TRY
            return find_attribute( ns, name ) != 0;
        XEUMEULEU_CATCH
    }
    virtual bool has_content() const
    {
        XEUMEULEU_TRY
            return find_content() != 0;
        XEUMEULEU_CATCH
    }
    virtual bool has_prefix( const std::string& ns ) const
    {
        XEUMEULEU_TRY
            return current_->isDefaultNamespace( translate( ns ) ) ||
                lookupPrefix( *current_, translate( ns ) ) != 0;
        XEUMEULEU_CATCH
    }

    bool accept( const std::string* ns, const XERCES_CPP_NAMESPACE::DOMNode* node ) const
    {
        if( !ns )
            return true;
        if( ns->empty() )
            return ! node->getNamespaceURI();
        return *ns == translate( node->getNamespaceURI() );
    }

    virtual void nodes( const std::string* ns, const visitor& v ) const
    {
        XEUMEULEU_TRY
            XERCES_CPP_NAMESPACE::DOMNode* child = current_->getFirstChild();
            while( child )
            {
                if( child->getNodeType() == XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE
                 && accept( ns, child ) )
                {
                    input i( *child );
                    xistream xis( i );
                    const XMLCh* name = child->getLocalName() ? child->getLocalName() : child->getNodeName();
                    v( translate( child->getNamespaceURI() ), translate( name ), xis );
                }
                child = child->getNextSibling();
            }
        XEUMEULEU_CATCH
    }
    virtual void attributes( const std::string* ns, const visitor& v ) const
    {
        XEUMEULEU_TRY
            const XERCES_CPP_NAMESPACE::DOMNamedNodeMap* attributes = current_->getAttributes();
            if( attributes )
            {
                for( XMLSize_t index = 0; index < attributes->getLength(); ++index )
                {
                    XERCES_CPP_NAMESPACE::DOMNode* attribute = attributes->item( index );
                    if( accept( ns, attribute ) )
                    {
                        input i( *attribute );
                        xistream xis( i );
                        const XMLCh* name = attribute->getLocalName() ? attribute->getLocalName() : attribute->getNodeName();
                        v( translate( attribute->getNamespaceURI() ), translate( name ), xis );
                    }
                }
            }
        XEUMEULEU_CATCH
    }

    virtual void prefix( const std::string& ns, std::string& prefix ) const
    {
        XEUMEULEU_TRY
            if( current_->isDefaultNamespace( translate( ns ) ) )
                prefix.clear();
            else
            {
                const XMLCh* p = lookupPrefix( *current_, translate( ns ) );
                if( ! p )
                    throw exception( context() + location() + " has no prefix for namespace '" + ns + "'" );
                prefix = translate( p );
            }
        XEUMEULEU_CATCH
    }

    virtual std::string context() const
    {
        const locator* loc = reinterpret_cast< locator* >( current_->getUserData( translate( "locator" ) ) );
        if( loc )
            return *loc;
        return "";
    }
    //@}

private:
    //! @name Helpers
    //@{
    void error( const std::string& message ) const
    {
        throw exception( context() + message );
    }

    std::string location() const
    {
        return "Node '" + translate( current_->getNodeName() ) + "'";
    }

    template< typename N >
    const XERCES_CPP_NAMESPACE::DOMNode* find_node( const N* nodes, const std::string* ns, const std::string& name ) const
    {
        if( ! nodes )
            return 0;
        for( XMLSize_t i = 0; i < nodes->getLength(); ++i )
        {
            const XERCES_CPP_NAMESPACE::DOMNode* node = nodes->item( i );
            if( (name == translate( node->getLocalName() ) || name == translate( node->getNodeName() ))
                && accept( ns, node ) )
                return node;
        }
        return 0;
    }
    const XERCES_CPP_NAMESPACE::DOMNode* find_child( const std::string* ns, const std::string& name ) const
    {
        return find_node( current_->getChildNodes(), ns, name );
    }
    const XERCES_CPP_NAMESPACE::DOMNode* find_attribute( const std::string* ns, const std::string& name ) const
    {
        return find_node( current_->getAttributes(), ns, name );
    }
    const XERCES_CPP_NAMESPACE::DOMNode* find_content() const
    {
        const XERCES_CPP_NAMESPACE::DOMNode* child = current_->getFirstChild();
        while( child )
        {
            if( current_->getNodeType() != XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE
             || has_content( *child ) )
                return child;
            child = child->getNextSibling();
        }
        return 0;
    }

    bool has_content( const XERCES_CPP_NAMESPACE::DOMNode& node ) const
    {
        if( node.getNodeType() != XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE
         && node.getNodeType() != XERCES_CPP_NAMESPACE::DOMNode::CDATA_SECTION_NODE )
            return false;
        const XMLCh* const value = node.getNodeValue();
        return ! XERCES_CPP_NAMESPACE::XMLChar1_1::isAllSpaces( value, XERCES_CPP_NAMESPACE::XMLString::stringLen( value ) );
    }

    template< typename N >
    void accept( const N* nodes, const std::string& ns, const visitor& v ) const
    {
        XEUMEULEU_TRY
            if( nodes )
            {
                for( XMLSize_t index = 0; index < nodes->getLength(); ++index )
                {
                    XERCES_CPP_NAMESPACE::DOMNode* node = nodes->item( index );
                    if( ns.empty() || ns == translate( node->getNamespaceURI() ) )
                    {
                        input i( *current_ );
                        xistream xis( i );
                        v( translate( node->getNamespaceURI() ), translate( node->getLocalName() ), xis );
                    }
                }
            }
        XEUMEULEU_CATCH
    }
    //@}

private:
    //! @name Member data
    //@{
    const XERCES_CPP_NAMESPACE::DOMNode& root_;
    const XERCES_CPP_NAMESPACE::DOMNode* current_;
    //@}
};

}

#undef XEUMEULEU_TRY
#undef XEUMEULEU_CATCH

#include <xeumeuleu/bridges/xerces/detail/buffer_input.hpp>

#define XEUMEULEU_TRY try {
#define XEUMEULEU_CATCH } \
            catch( const XERCES_CPP_NAMESPACE::OutOfMemoryException& ) { throw exception( "Out of memory" ); } \
            catch( const XERCES_CPP_NAMESPACE::XMLException& e ) { throw chained_exception( e, context() ); } \
            catch( const XERCES_CPP_NAMESPACE::DOMException& e ) { throw chained_exception( e, context() ); }

namespace xml
{
    inline std::auto_ptr< input_base > input::branch( bool clone ) const
    {
        XEUMEULEU_TRY
            if( clone )
                return std::auto_ptr< input_base >( new buffer_input( *current_ ) );
            return std::auto_ptr< input_base >( new input( *current_ ) );
        XEUMEULEU_CATCH
    }
}

#undef XEUMEULEU_TRY
#undef XEUMEULEU_CATCH

#endif // xeumeuleu_input_hpp
