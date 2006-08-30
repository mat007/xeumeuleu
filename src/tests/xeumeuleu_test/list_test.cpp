// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2005 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

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
    class xistream_constraint : public mockpp::Constraint< xml::xistream >
    {
    public:
        xistream_constraint( const std::string& content )
            : content_( content )
        {}
        virtual bool eval( const xml::xistream& arg ) const
        {
            xml::xistream& xis = const_cast< xml::xistream& >( arg );
            std::string content;
            xis >> content;
            return content_ == content;
        }
        virtual mockpp::String describeTo( mockpp::String &buffer ) const
        {
            mockpp::String fmt = MOCKPP_PCHAR( "xistream content '%1'" );
            fmt << content_;
            buffer += fmt;
            return buffer;
        }
    private:
        const std::string content_;
    };

    class mock_custom_class : public mockpp::ChainableMockObject
    {
    public:
        mock_custom_class()
            : mockpp::ChainableMockObject( "mock_custom_class", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( xml::xistream& xis )
        {
            process_mocker.forward( xis );
        }
        mockpp::ChainableMockMethod< void, xml::xistream > process_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_list_from_element_calls_a_custom_method )
{
    mock_custom_class mock_custom;
    mock_custom.process_mocker.expects( once() ).with( new xistream_constraint( "content number one" ) );
    mock_custom.process_mocker.expects( once() ).with( new xistream_constraint( "content number two" ) );
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
            : mockpp::ChainableMockObject( "mock_custom_class", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( xml::xistream& xis, int& p1, const float& p2 )
        {
            process_mocker.forward( xis, p1, p2 );
        }
        mockpp::ChainableMockMethod< void, xml::xistream, int, float > process_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method_with_parameters
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_list_from_element_calls_a_custom_method_with_parameters )
{
    mock_custom_class_with_parameters mock_custom;
    int p1 = 12;
    const float p2 = 12.42f;
    mock_custom.process_mocker.expects( mockpp::once() ).with( new xistream_constraint( "content" ), eq( p1 ), eq( p2 ) );
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
            : mockpp::ChainableMockObject( "mock_custom_class", 0 )
            , process_mocker             ( "process", this )
        {}
        void process( xml::xistream& xis, an_interface& p1 )
        {
            process_mocker.forward( xis, &p1 );
        }
        mockpp::ChainableMockMethod< void, xml::xistream, an_interface* > process_mocker;
    };

    class a_class : public an_interface
    {
    };
}

// -----------------------------------------------------------------------------
// Name: read_list_from_element_calls_a_custom_method_with_polymorphic_parameter
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_list_from_element_calls_a_custom_method_with_polymorphic_parameter )
{
    mock_custom_class_with_polymorphic_parameter mock_custom;
    a_class my_instance;
    mock_custom.process_mocker.expects( mockpp::once() ).with( new xistream_constraint( "content" ), eq< an_interface* >( &my_instance ) );
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
BOOST_AUTO_UNIT_TEST( move_up_from_sub_node_throws_an_exception )
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
        void process( const std::string& name, xml::xistream& xis, int& p1 )
        {
            process_mocker.forward( name, xis, p1 );
        }
        mockpp::ChainableMockMethod< void, std::string, xml::xistream, int > process_mocker;
    };
}

// -----------------------------------------------------------------------------
// Name: read_name_list_with_parameters
// Created: ZEBRE 2006-08-30
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_name_list_with_parameters )
{
    xml::xistringstream xis( "<element>"
                               "<sub-node1>content number one</sub-node1>"
                               "<sub-node2>content number two</sub-node2>"
                             "</element>" );
    int p1 = 12;
    mock_custom_class_name_list_with_parameters mock_custom;
    mock_custom.process_mocker.expects( mockpp::once() ).with( eq( std::string( "sub-node1" ) ), new xistream_constraint( "content number one" ), eq( p1 ) );
    mock_custom.process_mocker.expects( mockpp::once() ).with( eq( std::string( "sub-node2" ) ), new xistream_constraint( "content number two" ), eq( p1 ) );

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
            process_mocker.forward( name, xis );
        }
        mockpp::ChainableMockMethod< void, std::string, xml::xistream > process_mocker;
    };
}
 
// -----------------------------------------------------------------------------
// Name: read_name_list_is_not_called_with_content
// Created: ZEBRE 2006-08-30
// -----------------------------------------------------------------------------
BOOST_AUTO_UNIT_TEST( read_name_list_is_not_called_with_content )
{
    xml::xistringstream xis( "<element>"
                               "content not to be read"
                               "<sub-node>content</sub-node>"
                             "</element>" );
    mock_custom_class_name_list mock_custom;
    mock_custom.process_mocker.expects( mockpp::once() ).with( eq( std::string( "sub-node" ) ), new xistream_constraint( "content" ) );

    xis >> xml::start( "element" )
            >> xml::list( mock_custom, &mock_custom_class_name_list::process )
        >> xml::end();
    mock_custom.verify();
}
