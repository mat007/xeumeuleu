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

// -----------------------------------------------------------------------------
// Name: reading_optional_non_existing_element_does_not_throw_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_optional_non_existing_element_does_not_throw_exception )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional;
    BOOST_CHECK_NO_THROW( xis >> xml::start( "non-existing-child" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_optional_non_existing_element_sub_node_does_not_throw_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_optional_non_existing_element_sub_node_does_not_throw_exception )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional
            >> xml::start( "non-existing-child" );
    BOOST_CHECK_NO_THROW( xis >> xml::start( "non-existing-sub-child" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_optional_non_existing_element_content_does_not_throw_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_optional_non_existing_element_content_does_not_throw_exception )
{
    xml::xistringstream xis( "<element/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::optional
            >> xml::start( "non-existing-child" );
    BOOST_CHECK_NO_THROW( xis >> value );
    BOOST_CHECK_EQUAL( 0, value );
}

// -----------------------------------------------------------------------------
// Name: reading_optional_non_existing_element_attribute_does_not_throw_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_optional_non_existing_element_attribute_does_not_throw_exception )
{
    xml::xistringstream xis( "<element/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::optional
            >> xml::start( "non-existing-child" );
    BOOST_CHECK_NO_THROW( xis >> xml::attribute( "attribute", value ) );
    BOOST_CHECK_EQUAL( 0, value );
}

// -----------------------------------------------------------------------------
// Name: moving_out_of_optional_non_existing_element_terminates_the_optional_sub_tree
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( moving_out_of_optional_non_existing_element_terminates_the_optional_sub_tree )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional
            >> xml::start( "non-existing-child" )
            >> xml::end;
    BOOST_CHECK_THROW( xis >> xml::start( "non-existing-child" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: reading_existing_element_inside_optional_non_existing_element_is_still_optional
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_existing_element_inside_optional_non_existing_element_is_still_optional )
{
    xml::xistringstream xis( "<element>"
                               "<existing-child/>"
                             "</element>" );
    xis >> xml::start( "element" )
            >> xml::optional
            >> xml::start( "non-existing-child" )
                >> xml::start( "existing-child" )
                >> xml::end;
    BOOST_CHECK_NO_THROW( xis >> xml::start( "non-existing-sub-child" ) );
}

// -----------------------------------------------------------------------------
// Name: reading_optional_element_inside_optional_non_existing_element
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_optional_element_inside_optional_non_existing_element )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional
            >> xml::start( "non-existing-child" )
                >> xml::optional
                >> xml::start( "non-existing-sub-child" )
                >> xml::end
            >> xml::end;
    BOOST_CHECK_THROW( xis >> xml::start( "non-existing-child" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: setting_optional_before_moving_up_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( setting_optional_before_moving_up_throws_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional;
    BOOST_CHECK_THROW( xis >> xml::end, xml::exception );
}

namespace
{
    class custom_class
    {
    public:
        void process( xml::xistream& )
        {}
    };
}

// -----------------------------------------------------------------------------
// Name: reading_a_list_resets_the_optional_flag
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_a_list_resets_the_optional_flag )
{
    custom_class custom;
    xml::xistringstream xis( "<element/>" );
    xis >> xml::start( "element" )
            >> xml::optional
            >> xml::list( "non-existing-child", custom, &custom_class::process );
    BOOST_CHECK_THROW( xis >> xml::start( "non-existing-child" ), xml::exception );
}

// -----------------------------------------------------------------------------
// Name: reading_an_optional_non_existing_attribute_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_an_optional_non_existing_attribute_does_not_throw_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::optional;
    BOOST_CHECK_NO_THROW( xis >> xml::attribute( "non-existinig-attribute", value ) );
    BOOST_CHECK_EQUAL( 0, value );
}

// -----------------------------------------------------------------------------
// Name: reading_an_optional_non_existing_text_content_does_not_throw_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_an_optional_non_existing_text_content_does_not_throw_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    int value = 0;
    xis >> xml::start( "element" )
            >> xml::optional;
    BOOST_CHECK_NO_THROW( xis >> value );
    BOOST_CHECK_EQUAL( 0, value );
}

// -----------------------------------------------------------------------------
// Name: reading_an_optional_non_existing_content_in_existing_tag_throws_an_exception
// Created: MCO 2006-01-03
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( reading_an_optional_non_existing_content_in_existing_tag_throws_an_exception )
{
    xml::xistringstream xis( "<element/>" );
    std::string value;
    xis >> xml::optional;
    BOOST_CHECK_THROW( xis >> xml::content( "element", value ), std::exception ); // because content = start + read + end
    BOOST_CHECK_EQUAL( "", value );
}
