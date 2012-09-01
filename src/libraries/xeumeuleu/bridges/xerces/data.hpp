/*
 *   Copyright (c) 2010, Mathieu Champlon
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

#ifndef xeumeuleu_data_hpp
#define xeumeuleu_data_hpp

#include <xeumeuleu/streams/exception.hpp>
#include <xeumeuleu/streams/detail/input_base.hpp>
#include <xeumeuleu/bridges/xerces/detail/xerces.hpp>
#include <xeumeuleu/bridges/xerces/detail/trim.hpp>
#include <xeumeuleu/bridges/xerces/detail/chained_exception.hpp>
#include <xeumeuleu/bridges/xerces/detail/translate.hpp>
#include <xeumeuleu/bridges/xerces/detail/locator.hpp>
#include <typeinfo>
#include <limits>
#ifdef __GNUC__
#include <cxxabi.h>
#include <cstdlib>
#endif

#define XEUMEULEU_TRY try {
#define XEUMEULEU_CATCH } \
            catch( const XERCES_CPP_NAMESPACE::OutOfMemoryException& ) { throw exception( "Out of memory" ); } \
            catch( const XERCES_CPP_NAMESPACE::XMLException& e ) { throw chained_exception( e, context() ); } \
            catch( const XERCES_CPP_NAMESPACE::DOMException& e ) { throw chained_exception( e, context() ); }

namespace xml
{
    class input;

// =============================================================================
/** @class  data
    @brief  Data implementation
*/
// Created: MAT 2010-06-29
// =============================================================================
class data
{
public:
    //! @name Constructors/Destructor
    //@{
    data()
        : parent_( 0 )
        , node_  ( 0 )
    {}
    data( const XERCES_CPP_NAMESPACE::DOMNode& parent, const XERCES_CPP_NAMESPACE::DOMNode& node )
        : parent_( &parent )
        , node_  ( &node )
    {}
    //@}

    //! @name Operations
    //@{
    void to( std::string& v ) const { XEUMEULEU_TRY if( node_ ) v = translate( get_data() ); XEUMEULEU_CATCH }
    void to( bool& v ) const { XEUMEULEU_TRY if( node_ ) v = to_bool( get_data() ); XEUMEULEU_CATCH }
    void to( short& v ) const { XEUMEULEU_TRY if( node_ ) v = convert< short >( get_data() ); XEUMEULEU_CATCH }
    void to( int& v ) const { XEUMEULEU_TRY if( node_ ) v = to_int( get_data() ); XEUMEULEU_CATCH }
    void to( long& v ) const { XEUMEULEU_TRY if( node_ ) v = convert< long >( get_data() ); XEUMEULEU_CATCH }
    void to( long long& v ) const { XEUMEULEU_TRY if( node_ ) v = convert< long long >( get_data() ); XEUMEULEU_CATCH }
    void to( float& v ) const { XEUMEULEU_TRY if( node_ ) v = to_float( get_data() ); XEUMEULEU_CATCH }
    void to( double& v ) const { XEUMEULEU_TRY if( node_ ) v = to_double( get_data() ); XEUMEULEU_CATCH }
    void to( long double& v ) const { XEUMEULEU_TRY if( node_ ) v = convert< long double >( get_data() ); XEUMEULEU_CATCH }
    void to( unsigned short& v ) const { XEUMEULEU_TRY if( node_ ) v = convert< unsigned short >( get_data() ); XEUMEULEU_CATCH }
    void to( unsigned int& v ) const { XEUMEULEU_TRY if( node_ ) v = convert< unsigned int >( get_data() ); XEUMEULEU_CATCH }
    void to( unsigned long& v ) const { XEUMEULEU_TRY if( node_ ) v = convert< unsigned long >( get_data() ); XEUMEULEU_CATCH }
    void to( unsigned long long& v ) const { XEUMEULEU_TRY if( node_ ) v = convert< unsigned long long >( get_data() ); XEUMEULEU_CATCH }
    //@}

private:
    //! @name Helpers
    //@{
    const XMLCh* get_data() const
    {
        return node_->getNodeValue();
    }
    std::string name( const std::type_info& info ) const
    {
        const char* name = info.name();
#ifdef __GNUC__
        int status = 0;
        char* demangled = abi::__cxa_demangle( name, NULL, 0, &status );
        if( ! status && demangled )
        {
            std::string result( demangled );
            free( demangled );
            return result;
        }
#endif
        return name;
    }
    template< typename T > T convert( const XMLCh* from ) const
    {
        const double data = XERCES_CPP_NAMESPACE::XMLDouble( from ).getValue();
        const T result = static_cast< T >( data );
        if( static_cast< double >( result ) != data )
            throw exception( context() + "Value of " + location() + " is not a " + name( typeid( T ) ) );
        return result;
    }
    float to_float( const XMLCh* from ) const
    {
        const XERCES_CPP_NAMESPACE::XMLFloat data( from );
        if( data.isDataOverflowed() )
            throw exception( context() + "Value of " + location() + " overflowed (probably a double instead of a float)" );
        switch( data.getType() )
        {
            case XERCES_CPP_NAMESPACE::XMLDouble::NegINF :
                return - std::numeric_limits< float >::infinity();
            case XERCES_CPP_NAMESPACE::XMLDouble::PosINF :
                return std::numeric_limits< float >::infinity();
            case XERCES_CPP_NAMESPACE::XMLDouble::NaN :
                return std::numeric_limits< float >::quiet_NaN();
            default:
                return static_cast< float >( data.getValue() );
        }
    }
    double to_double( const XMLCh* from ) const
    {
        const XERCES_CPP_NAMESPACE::XMLDouble data( from );
        if( data.isDataOverflowed() )
            throw exception( context() + "Value of " + location() + " overflowed (probably more than a double)" );
        switch( data.getType() )
        {
            case XERCES_CPP_NAMESPACE::XMLDouble::NegINF :
                return - std::numeric_limits< double >::infinity();
            case XERCES_CPP_NAMESPACE::XMLDouble::PosINF :
                return std::numeric_limits< double >::infinity();
            case XERCES_CPP_NAMESPACE::XMLDouble::NaN :
                return std::numeric_limits< double >::quiet_NaN();
            default:
                return data.getValue();
        }
    }
    int to_int( const XMLCh* from ) const
    {
        return XERCES_CPP_NAMESPACE::XMLString::parseInt( from );
    }
    bool to_bool( const XMLCh* from ) const
    {
        const std::string data = trim( translate( from ) );
        if( data == "true" || data == "1" )
            return true;
        if( data == "false" || data == "0" )
            return false;
        throw exception( context() + "Value of " + location() + " is not a boolean" );
    }

    std::string context() const
    {
        const locator* loc = reinterpret_cast< locator* >( parent_->getUserData( translate( "locator" ) ) );
        if( loc )
            return *loc;
        return "";
    }
    std::string location() const
    {
        return "Node '" + translate( node_->getNodeName() ) + "'";
    }
    //@}

private:
    //! @name Member data
    //@{
    const XERCES_CPP_NAMESPACE::DOMNode* parent_;
    const XERCES_CPP_NAMESPACE::DOMNode* node_;
    //@}
};

}

#undef XEUMEULEU_TRY
#undef XEUMEULEU_CATCH

#endif // xeumeuleu_data_hpp
