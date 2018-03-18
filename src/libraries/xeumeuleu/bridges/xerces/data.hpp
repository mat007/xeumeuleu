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
#include <cstdio>
#ifdef __GNUC__
#include <cxxabi.h>
#include <cstdlib>
#endif
#include <limits>
#include <typeinfo>

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
        : node_( 0 )
    {}
    explicit data( const XERCES_CPP_NAMESPACE::DOMNode& node )
        : node_( &node )
    {}
    //@}

    //! @name Operations
    //@{
    void to( std::string& v ) const { XEUMEULEU_TRY if( node_ ) v = translate( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( bool& v ) const { XEUMEULEU_TRY if( node_ ) v = to_bool( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( short& v ) const { XEUMEULEU_TRY if( node_ ) v = to_signed< short >( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( int& v ) const { XEUMEULEU_TRY if( node_ ) v = to_signed< int >( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( long& v ) const { XEUMEULEU_TRY if( node_ ) v = to_signed< long >( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( long long& v ) const { XEUMEULEU_TRY if( node_ ) v = to_signed< long long >( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( float& v ) const { XEUMEULEU_TRY if( node_ ) v = to_float< float > ( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( double& v ) const { XEUMEULEU_TRY if( node_ ) v = to_float< double >( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( long double& v ) const { XEUMEULEU_TRY if( node_ ) v = to_float< long double >( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( unsigned short& v ) const { XEUMEULEU_TRY if( node_ ) v = to_unsigned< unsigned short >( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( unsigned int& v ) const { XEUMEULEU_TRY if( node_ ) v = to_unsigned< unsigned int >( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( unsigned long& v ) const { XEUMEULEU_TRY if( node_ ) v = to_unsigned< unsigned long >( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
    void to( unsigned long long& v ) const { XEUMEULEU_TRY if( node_ ) v = to_unsigned< unsigned long long >( get_data() ); XEUMEULEU_CATCH_WITH_CONTEXT }
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
    template< typename T > T to_signed( const XMLCh* from ) const
    {
        return convert< T >( trim( translate( from ) ) );
    }
    template< typename T > T to_unsigned( const XMLCh* from ) const
    {
        const std::string data = trim( translate( from ) );
        if( data.empty() || data[0] == '-' )
            throw exception( context() + "value of " + location() + " is not a " + name( typeid( T ) ) + ": " + data );
        return convert< T >( data );
    }
    template< typename T > T to_float( const XMLCh* from ) const
    {
        const std::string data = trim( translate( from ) );
        if( data == "INF" )
            return std::numeric_limits< T >::infinity();
        if( data == "-INF" )
            return - std::numeric_limits< T >::infinity();
        if( data == "NaN" )
            return - std::numeric_limits< T >::quiet_NaN();
        return convert< T >( data );
    }
    template< typename T > T convert( const std::string& data ) const
    {
        std::stringstream stream( data );
        T value;
        stream >> value;
        if( stream && stream.eof() )
            return value;
        throw exception( context() + "value of " + location() + " is not a " + name( typeid( T ) ) + ": " + data );
    }
    bool to_bool( const XMLCh* from ) const
    {
        const std::string data = trim( translate( from ) );
        if( data == "true" || data == "1" )
            return true;
        if( data == "false" || data == "0" )
            return false;
        throw exception( context() + "value of " + location() + " is not a boolean: " + trim( translate( from ) ) );
    }

    std::string context() const
    {
        return xml::context( *node_->getParentNode() );
    }
    std::string location() const
    {
        return xml::location( *node_->getParentNode() );
    }
    //@}

private:
    //! @name Member data
    //@{
    const XERCES_CPP_NAMESPACE::DOMNode* node_;
    //@}
};

}

#endif // xeumeuleu_data_hpp
