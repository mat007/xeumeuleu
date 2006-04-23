// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2005 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#include <string>
#include <iostream>
#include <xercesc/util/XMLString.hpp>

#ifndef _xeumeuleu_translate_h_
#define _xeumeuleu_translate_h_

namespace xml
{

// =============================================================================
/** @class  translate
    @brief  String translation helpers
*/
// Created: MAT 2006-01-04
// =============================================================================
class translate
{
public:
    //! @name Constructors/Destructor
    //@{
    explicit translate( const std::string& str );
    explicit translate( const XMLCh* const pCh );
    ~translate();
    //@}

    //! @name Operators
    //@{
    operator const XMLCh* const() const;
    operator std::string() const;

    bool operator==( const XMLCh* const pCh ) const;
    bool operator==( const std::string& str ) const;
    //@}

private:
    //! @name Copy/Assignement
    //@{
    translate( const translate& );            //!< Copy constructor
    translate& operator=( const translate& ); //!< Assignment operator
    //@}

private:
    //! @name Data members
    //@{
    const XMLCh* const pCh_;
    bool isOwner_;
    //@}
};

bool operator==( const XMLCh* const pCh, const translate& tr );
bool operator==( const std::string& str, const translate& tr );

std::ostream& operator<<( std::ostream& stream, const translate& tr );

}

#endif // _xeumeuleu_translate_h_
