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

#include "xeumeuleu_test_pch.h"
#include <xeumeuleu/xml.hpp>
#include <turtle/mock.hpp>
#include <boost/bind.hpp>

namespace
{
    bool compare_content( xml::xistream& xis, const std::string& expected )
    {
        std::string actual;
        xis >> actual;
        return actual == expected;
    }

    MOCK_CLASS( mock_custom_class )
    {
        MOCK_METHOD_EXT( process, 2, void( const std::string&, xml::xistream& ), process )
    };
}

// -----------------------------------------------------------------------------
// Name: read_attributes_from_element_calls_a_custom_method
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_attributes_from_element_calls_a_custom_method )
{
    mock_custom_class mock_custom;
    MOCK_EXPECT( mock_custom, process ).once().with( "first", boost::bind( &compare_content, _1, "attribute content 1" ) );
    MOCK_EXPECT( mock_custom, process ).once().with( "second", boost::bind( &compare_content, _1, "attribute content 2" ) );
    xml::xistringstream xis( "<element first='attribute content 1' second='attribute content 2'/>" );
    xis >> xml::start( "element" )
            >> xml::attributes( mock_custom, &mock_custom_class::process );
}

// -----------------------------------------------------------------------------
// Name: read_attributes_from_element_without_attribute_does_not_call_the_custom_method
// Created: MAT 2007-08-01
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_attributes_from_element_without_attribute_does_not_call_the_custom_method )
{
    mock_custom_class mock_custom;
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::attributes( mock_custom, &mock_custom_class::process );
}

// -----------------------------------------------------------------------------
// Name: adding_the_same_attribute_twice_reads_only_one_attribute_back
// Created: MCO 2010-04-15
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( adding_the_same_attribute_twice_reads_only_one_attribute_back )
{
    xml::xobufferstream xos;
    xos << xml::start( "root" )
            << xml::attribute( "attribute", "the first value" )
            << xml::attribute( "attribute", "the second value" );
    mock_custom_class mock_custom;
    MOCK_EXPECT( mock_custom, process ).once().with( "attribute", boost::bind( &compare_content, _1, "the second value" ) );
    xos >> xml::start( "root" )
            >> xml::attributes( mock_custom, &mock_custom_class::process );
}

namespace
{
    MOCK_FUNCTOR( void() ) process;
    void my_name_function( const std::string&, const std::string&, xml::xistream& )
    {
        process();
    }
}

// -----------------------------------------------------------------------------
// Name: attributes_accepts_function_as_functor
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( attributes_accepts_function_as_functor )
{
    xml::xistringstream xis( "<element attribute='my_attribute'/>" );
    xis >> xml::start( "element" );
    MOCK_RESET( process, _ );
    MOCK_EXPECT( process, _ ).once();
    xis >> xml::attributes( &my_name_function );
}

namespace
{
    class my_functor_class
    {
    public:
        void operator()( const std::string&, const std::string&, xml::xistream& ) const
        {
            process();
        }
    };
}

// -----------------------------------------------------------------------------
// Name: attributes_accepts_functor_and_makes_an_internal_copy
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( attributes_accepts_functor_and_makes_an_internal_copy )
{
    xml::xistringstream xis( "<element attribute='my_attribute'/>" );
    xis >> xml::start( "element" );
    MOCK_RESET( process, _ );
    MOCK_EXPECT( process, _ ).once();
    xis >> xml::attributes( my_functor_class() );
}

namespace
{
    class my_non_copyable_functor_class
    {
    public:
        my_non_copyable_functor_class() {}

        void operator()( const std::string&, const std::string&, xml::xistream& ) const
        {
            process();
        }
    private:
        my_non_copyable_functor_class( const my_non_copyable_functor_class& );
        my_non_copyable_functor_class& operator=( const my_non_copyable_functor_class& );
    };
}

// -----------------------------------------------------------------------------
// Name: attributes_accepts_functor_as_reference
// Created: MAT 2008-11-14
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( attributes_accepts_functor_as_reference )
{
    xml::xistringstream xis( "<element attribute='my_attribute'/>" );
    xis >> xml::start( "element" );
    MOCK_RESET( process, _ );
    MOCK_EXPECT( process, _ ).once();
    my_non_copyable_functor_class functor;
    xis >> xml::attributes< my_non_copyable_functor_class& >( functor );
}

namespace
{
    MOCK_CLASS( my_bindable_class )
    {
        void my_method_1( xml::xistream& )
        {
            process();
        }
        void const_my_method_1( xml::xistream& ) const
        {
            process();
        }
        void my_method_2( const std::string&, xml::xistream& )
        {
            process();
        }
        void const_my_method_2( const std::string&, xml::xistream& ) const
        {
            process();
        }
        MOCK_METHOD_EXT( process, 0, void(), process )
    };
}

// -----------------------------------------------------------------------------
// Name: attributes_accepts_boost_bind_as_functor
// Created: MAT 2008-02-29
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( attributes_accepts_boost_bind_as_functor )
{
    xml::xistringstream xis( "<element attribute='my_attribute'/>" );
    xis >> xml::start( "element" );
    {
        my_bindable_class my_instance;
        MOCK_EXPECT( my_instance, process ).once();
        xis >> xml::attributes( boost::bind( &my_bindable_class::my_method_2, boost::ref( my_instance ), _2, _3 ) );
        mock::verify();
    }
    {
        my_bindable_class my_instance;
        MOCK_EXPECT( my_instance, process ).once();
        xis >> xml::attributes( boost::bind( &my_bindable_class::const_my_method_2, boost::ref( my_instance ), _2, _3 ) );
    }
}
