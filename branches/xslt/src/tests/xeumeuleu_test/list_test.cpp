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
#include "xeumeuleu/xml.h"

using namespace mockpp;

namespace
{
    class my_class
    {
    public:
        void my_method( xml::xistream& ) {}
        void my_const_method( xml::xistream& ) const {}
    };

    class my_type
    {
    };

    class my_class_ext_1
    {
    public:
        void my_method( xml::xistream& , my_type& ) {}
        void my_const_method( xml::xistream& , my_type& ) const {}
    };

    class my_class_ext_const_1
    {
    public:
        void my_method( xml::xistream& , const my_type& ) {}
        void my_const_method( xml::xistream& , const my_type& ) const {}
    };

    class my_class_ext_2
    {
    public:
        void my_method( xml::xistream& , my_type& , my_type& ) {}
        void my_const_method( xml::xistream& , my_type& , my_type& ) const {}
    };

    class my_class_ext_const_2
    {
    public:
        void my_method( xml::xistream& , const my_type&, my_type& ) {}
        void my_const_method( xml::xistream& , const my_type&, my_type& ) const {}
    };

    class my_class_ext_const_const_2
    {
    public:
        void my_method_const( xml::xistream& , const my_type&, const my_type& ) {}
        void my_const_method_const( xml::xistream& , const my_type&, const my_type& ) const {}
    };

    void warning_check()
    {
        xml::xistream& xis = *(xml::xistream*)0;
        {
            my_class my_instance;
            xis >> xml::list( "node", my_instance, &my_class::my_method );
        }
        {
            my_class my_instance;
            xis >> xml::list( "node", my_instance, &my_class::my_const_method );
        }
        {
            const my_class my_instance = my_class();
            xis >> xml::list( "node", my_instance, &my_class::my_const_method );
        }

        my_type param;
        my_type& param_ref = param;
        const my_type& param_const_ref = param;
        {
            my_class_ext_1 my_instance;
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_method, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_const_method, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_method, param_ref );
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_const_method, param_ref );
        }
        {
            const my_class_ext_1 my_instance = my_class_ext_1();
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_const_method, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_1::my_const_method, param_ref );
        }
        {
            my_class_ext_const_1 my_instance;
            xis >> xml::list( "node", my_instance, &my_class_ext_const_1::my_method, param_const_ref );
            xis >> xml::list( "node", my_instance, &my_class_ext_const_1::my_const_method, param_const_ref );
        }
        {
            const my_class_ext_const_1 my_instance = my_class_ext_const_1();
            xis >> xml::list( "node", my_instance, &my_class_ext_const_1::my_const_method, param_const_ref );
        }
        {
            my_class_ext_2 my_instance;
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_method, param, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_const_method, param, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_method, param_ref, param_ref );
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_const_method, param_ref, param_ref );
       }
       {
            const my_class_ext_2 my_instance = my_class_ext_2();
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_const_method, param, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_2::my_const_method, param_ref, param_ref );
       }
       {
            my_class_ext_const_2 my_instance;
            xis >> xml::list( "node", my_instance, &my_class_ext_const_2::my_method, param_const_ref, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_const_2::my_const_method, param_const_ref, param_ref );
       }
       {
            const my_class_ext_const_2 my_instance = my_class_ext_const_2();
            xis >> xml::list( "node", my_instance, &my_class_ext_const_2::my_const_method, param_const_ref, param );
            xis >> xml::list( "node", my_instance, &my_class_ext_const_2::my_const_method, param_const_ref, param_ref );
       }
       {
            my_class_ext_const_const_2 my_instance;
            xis >> xml::list( "node", my_instance, &my_class_ext_const_const_2::my_method_const, param_const_ref, param_const_ref );
            xis >> xml::list( "node", my_instance, &my_class_ext_const_const_2::my_const_method_const, param_const_ref, param_const_ref );
       }
       {
            const my_class_ext_const_const_2 my_instance = my_class_ext_const_const_2();
            xis >> xml::list( "node", my_instance, &my_class_ext_const_const_2::my_const_method_const, param_const_ref, param_const_ref );
        }
    }
}

namespace
{
    class mock_custom_class : public mockpp::ChainableMockObject
    {
    public:
        mock_custom_class()
            : mockpp::ChainableMockObject( "mock_custom_class", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( xml::xistream& xis )
        {
            std::string content;
            xis >> content;
            process_mocker.forward( content );
        }
        mockpp::ChainableMockMethod< void, std::string > process_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_list_from_element_calls_a_custom_method )
{
    mock_custom_class mock_custom;
    mock_custom.process_mocker.expects( once() ).with( eq< std::string >( "content number one" ) );
    mock_custom.process_mocker.expects( once() ).with( eq< std::string >( "content number two" ) );
    xml::xistringstream xis( "<element>"
                               "<sub-node>content number one</sub-node>"
                               "<sub-node>content number two</sub-node>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::list( "sub-node", mock_custom, &mock_custom_class::process )
        >> xml::end();
    mock_custom.verify();
}

namespace
{
    class mock_custom_class_with_parameters : public mockpp::ChainableMockObject
    {
    public:
        mock_custom_class_with_parameters()
            : mockpp::ChainableMockObject( "mock_custom_class_with_parameters", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( xml::xistream& xis, int p1, const float p2 )
        {
            std::string content;
            xis >> content;
            process_mocker.forward( content, p1, p2 );
        }
        mockpp::ChainableMockMethod< void, std::string, int, float > process_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method_with_parameters
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_list_from_element_calls_a_custom_method_with_parameters )
{
    mock_custom_class_with_parameters mock_custom;
    int p1 = 12;
    const float p2 = 12.42f;
    mock_custom.process_mocker.expects( mockpp::once() ).with( eq< std::string >( "content" ), eq( p1 ), eq( p2 ) );
    xml::xistringstream xis( "<element>"
                               "<sub-node>content</sub-node>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::list( "sub-node", mock_custom, &mock_custom_class_with_parameters::process, p1, p2 )
        >> xml::end();
    mock_custom.verify();
}

namespace
{
    class an_interface
    {
    };

    class mock_custom_class_with_polymorphic_parameter : public mockpp::ChainableMockObject
    {
    public:
        mock_custom_class_with_polymorphic_parameter()
            : mockpp::ChainableMockObject( "mock_custom_class_with_polymorphic_parameter", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( xml::xistream& xis, an_interface& p1 )
        {
            std::string content;
            xis >> content;
            process_mocker.forward( content, &p1 );
        }
        mockpp::ChainableMockMethod< void, std::string, an_interface* > process_mocker;
    };

    class a_class : public an_interface
    {
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method_with_polymorphic_parameter
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_list_from_element_calls_a_custom_method_with_polymorphic_parameter )
{
    mock_custom_class_with_polymorphic_parameter mock_custom;
    a_class my_instance;
    mock_custom.process_mocker.expects( mockpp::once() ).with( eq< std::string >( "content" ), eq< an_interface* >( &my_instance ) );
    xml::xistringstream xis( "<element>"
                               "<sub-node>content</sub-node>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::list( "sub-node", mock_custom, &mock_custom_class_with_polymorphic_parameter::process, my_instance )
        >> xml::end();
    mock_custom.verify();
}

namespace
{
    class custom_class
    {
    public:
        void process( xml::xistream& xis )
        {
            xis >> xml::end();
        }
    };
}

// -----------------------------------------------------------------------------
// Name: move_up_from_sub_node_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( move_up_from_sub_node_throws_an_exception )
{
    custom_class custom;
    xml::xistringstream xis( "<element>"
                               "<sub-node>content number one</sub-node>"
                             "</element>" );
    BOOST_CHECK_THROW( xis >> xml::start( "element" ) >> xml::list( "sub-node", custom, &custom_class::process ), xml::exception );
}

namespace
{
    class mock_custom_class_name_list_with_parameters : public mockpp::ChainableMockObject
    {
    public:
        mock_custom_class_name_list_with_parameters()
            : mockpp::ChainableMockObject( "mock_custom_class_name_list_with_parameters", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( const std::string& name, xml::xistream& xis, int p1 )
        {
            std::string content;
            xis >> content;
            process_mocker.forward( name, content, p1 );
        }
        mockpp::ChainableMockMethod< void, std::string, std::string, int > process_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: read_name_list_with_parameters
// Created: ZEBRE 2006-08-30
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_name_list_with_parameters )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node1>content number one</sub-node1>"
                               "<sub-node2>content number two</sub-node2>"
                             "</element>" );
    int p1 = 12;
    mock_custom_class_name_list_with_parameters mock_custom;
    mock_custom.process_mocker.expects( mockpp::once() ).with( eq< std::string >( "sub-node1" ), eq< std::string >( "content number one" ), eq( p1 ) );
    mock_custom.process_mocker.expects( mockpp::once() ).with( eq< std::string >( "sub-node2" ), eq< std::string >( "content number two" ), eq( p1 ) );
    xis >> xml::start( "element" )
            >> xml::list( mock_custom, &mock_custom_class_name_list_with_parameters::process, p1 )
        >> xml::end();
    mock_custom.verify();
}

namespace
{
    class mock_custom_class_name_list : public mockpp::ChainableMockObject
    {
    public:
        mock_custom_class_name_list()
            : mockpp::ChainableMockObject( "mock_custom_class_name_list", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( const std::string& name, xml::xistream& xis )
        {
            std::string content;
            xis >> content;
            process_mocker.forward( name, content );
        }
        mockpp::ChainableMockMethod< void, std::string, std::string > process_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: read_name_list_is_not_called_with_content
// Created: ZEBRE 2006-08-30
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( read_name_list_is_not_called_with_content )
{
    xml::xistringstream xis( "<element>"
                               "content not to be read"
                               "<sub-node>content</sub-node>"
                             "</element>" );
    mock_custom_class_name_list mock_custom;
    mock_custom.process_mocker.expects( mockpp::once() ).with( eq< std::string >( "sub-node" ), eq< std::string >( "content" ) );
    xis >> xml::start( "element" )
            >> xml::list( mock_custom, &mock_custom_class_name_list::process )
        >> xml::end();
    mock_custom.verify();
}

namespace
{
    class a_class_virtually_inheriting_from_another : virtual public an_interface
    {
    public:
        void process( xml::xistream& /*xis*/ )
        {
            // NOTHING
        }
    };
}

// -----------------------------------------------------------------------------
// Name: msvc_does_not_issue_packing_related_warning_C4355_or_C4121_when_using_virtual_inheritance
// Created: MAT 2007-06-28
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( msvc_does_not_issue_packing_related_warning_C4355_or_C4121_when_using_virtual_inheritance )
{
    xml::xistringstream xis( "<element/>" );
    a_class_virtually_inheriting_from_another my_instance;
    xis >> xml::list( "element", my_instance, &a_class_virtually_inheriting_from_another::process );
}
