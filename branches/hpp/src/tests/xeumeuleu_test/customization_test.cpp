/*
 *   Copyright (c) 2009, Mathieu Champlon
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

using namespace mockpp;

namespace
{
    class user_type
    {
    public:
        friend xml::xistream& operator>>( xml::xistream& xis, user_type& )
        {
            return xis;
        }
        friend xml::xostream& operator<<( xml::xostream& xos, const user_type& )
        {
            return xos;
        }
    };
}

// -----------------------------------------------------------------------------
// Name: user_type_with_unserialization_friend_function_can_be_read_from_stream
// Created: MCO 2009-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( user_type_with_unserialization_friend_function_can_be_read_from_stream )
{
    xml::xistringstream xis( "<root/>" );
    user_type t;
    xis >> t;
}

// -----------------------------------------------------------------------------
// Name: user_type_with_serialization_friend_function_can_be_written_to_stream
// Created: MCO 2009-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( user_type_with_serialization_friend_function_can_be_written_to_stream )
{
    xml::xostringstream xos;
    xos << user_type();
}

namespace
{
    class user_derived_type : public user_type
    {
    };
}

// -----------------------------------------------------------------------------
// Name: user_type_derived_from_user_type_with_unserialization_friend_function_can_be_read_from_stream
// Created: MCO 2009-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( user_type_derived_from_user_type_with_unserialization_friend_function_can_be_read_from_stream )
{
    xml::xistringstream xis( "<root/>" );
    user_derived_type t;
    xis >> t;
}

// -----------------------------------------------------------------------------
// Name: user_type_derived_from_user_type_with_serialization_friend_function_can_be_written_to_stream
// Created: MCO 2009-03-20
// -----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( user_type_derived_from_user_type_with_serialization_friend_function_can_be_written_to_stream )
{
    xml::xostringstream xos;
    xos << user_derived_type();
}
