// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2005 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#include "xeumeuleu_pch.h"
#include "translate.h"

using namespace xml;
using namespace XERCES_CPP_NAMESPACE;

// -----------------------------------------------------------------------------
// Name: translate constructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
translate::translate( const std::string& str )
    : pCh_    ( XMLString::transcode( str.c_str() ) )
    , isOwner_( true )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: translate constructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
translate::translate( const XMLCh* const pCh )
    : pCh_    ( pCh )
    , isOwner_( false )
{
    // NOTHING
}

// -----------------------------------------------------------------------------
// Name: translate destructor
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
translate::~translate()
{
    if( isOwner_ )
        XMLString::release( const_cast< XMLCh** >( &pCh_ ) ); // $$$$ MAT 2006-01-04: not the cleanest class on earth...
}

// -----------------------------------------------------------------------------
// Name: translate::operator const XMLCh* const
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
translate::operator const XMLCh* const() const
{
    return pCh_;
}

// -----------------------------------------------------------------------------
// Name: translate::operator std::string
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
translate::operator std::string() const
{
    if( ! pCh_ )
        return std::string();
    char* pStr = XMLString::transcode( pCh_ );
    if( ! pStr )
        return std::string();
    const std::string str( pStr );
    XMLString::release( &pStr );
    return str;
}

// -----------------------------------------------------------------------------
// Name: translate::operator==
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
bool translate::operator==( const XMLCh* const pCh ) const
{
    return XMLString::equals( pCh, pCh_ );
}

// -----------------------------------------------------------------------------
// Name: translate::operator==
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
bool translate::operator==( const std::string& str ) const
{
    return translate( str ) == pCh_;
}

// -----------------------------------------------------------------------------
// Name: xml::operator==
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
bool xml::operator==( const XMLCh* const pCh, const translate& tr )
{
    return tr.operator ==( pCh );
}

// -----------------------------------------------------------------------------
// Name: xml::operator==
// Created: MAT 2006-01-04
// -----------------------------------------------------------------------------
bool xml::operator==( const std::string& str, const translate& tr )
{
    return tr.operator ==( str );
}

// -----------------------------------------------------------------------------
// Name: xml::operator<<
// Created: MAT 2006-03-26
// -----------------------------------------------------------------------------
std::ostream& xml::operator<<( std::ostream& stream, const translate& tr )
{
    return stream << tr.operator std::string();
}
