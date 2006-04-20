/*
 *
 *  Copyright (C) 1994-2002, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Kuratorium OFFIS e.V.
 *    Healthcare Information and Communication Systems
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module:  dcmdata
 *
 *  Author:  Andreas Barth
 *
 *  Purpose: Interface of class DcmCharString
 *
 *  Last Update:      Author: amithaperera 
 *  Update Date:      Date: 2004/01/14 04:01:09 
 *  Source File:      Source: /cvsroot/vxl/vxl/v3p/dcmtk/dcmdata/include/dcchrstr.h,v 
 *  CVS/RCS Revision: Revision: 1.1 
 *  Status:           State: Exp 
 *
 *  CVS/RCS Log at end of file
 *
 */


#ifndef DCCHRSTR_H
#define DCCHRSTR_H

#include "osconfig.h"    /* make sure OS specific configuration is included first */

//
// This implementation does not support 16 bit character sets. Since 8 bit
// character sets are supported by the class DcmByteString the class
// DcmCharString is derived from DcmByteString without any extensions.
//
// If the extension for 16 bit character sets will be implemented this class
// must be derived directly from DcmElement. This class is designed to support
// the value representations (LO, LT, PN, SH, ST, UT). They are a problem because
// their value width (1, 2, .. Bytes) is specified by the element
// SpecificCharacterSet (0008, 0005) and an implementation must support
// different value widths that cannot be derived from the value representation.
//

#include "dcbytstr.h"


/** base class for DICOM elements with value representation LO, LT, PN, SH, ST, UT
 */
class DcmCharString
  : public DcmByteString
{

  public:

    /** constructor.
     *  Create new element from given tag and length.
     *  @param tag DICOM tag for the new element
     *  @param len value length for the new element
     */
    DcmCharString(const DcmTag &tag,
                  const Uint32 len);

    /** copy constructor
     *  @param old element to be copied
     */
    DcmCharString(const DcmCharString &old);

    /** destructor
     */
    virtual ~DcmCharString();

    /** assignment operator
     *  @param obj element to be assigned/copied
     *  @return reference to this object
     */
    DcmCharString &operator=(const DcmCharString &obj);
};


#endif // DCCHRSTR_H


/*
 * CVS/RCS Log:
 * Log: dcchrstr.h,v 
 * Revision 1.1  2004/01/14 04:01:09  amithaperera
 * Add better DICOM support by wrapping DCMTK, and add a stripped down
 * version of DCMTK to v3p. Add more DICOM test cases.
 *
 * Revision 1.8  2002/12/06 12:49:08  joergr
 * Enhanced "print()" function by re-working the implementation and replacing
 * the boolean "showFullData" parameter by a more general integer flag.
 * Added doc++ documentation.
 * Made source code formatting more consistent with other modules/files.
 *
 * Revision 1.7  2001/06/01 15:48:33  meichel
 * Updated copyright header
 *
 * Revision 1.6  2000/03/08 16:26:11  meichel
 * Updated copyright header.
 *
 * Revision 1.5  1999/03/31 09:24:30  meichel
 * Updated copyright header in module dcmdata
 *
 *
 */
