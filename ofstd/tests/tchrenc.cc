/*
 *
 *  Copyright (C) 2011, OFFIS e.V.
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *    OFFIS e.V.
 *    R&D Division Health
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *
 *  Module:  ofstd
 *
 *  Author:  Joerg Riesmeier
 *
 *  Purpose: test program for OFCharacterEncoding
 *
 *  Last Update:      $Author: joergr $
 *  Update Date:      $Date: 2011-10-21 09:15:03 $
 *  CVS/RCS Revision: $Revision: 1.1 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#define OFTEST_OFSTD_ONLY
#include "dcmtk/ofstd/oftest.h"
#include "dcmtk/ofstd/ofchrenc.h"


OFTEST(ofstd_OFCharacterEncoding_1)
{
    // the returned string should never be empty
    OFCHECK(!OFCharacterEncoding::getLibraryVersionString().empty());
    // check whether libiconv support is available
    if (OFCharacterEncoding::isLibraryAvailable())
    {
        OFCharacterEncoding charEnc;
        OFString resultStr;
        // first, do some basic validity checks
        OFCHECK(!charEnc.getLocaleEncoding().empty());
        OFCHECK(charEnc.selectEncoding("ASCII", "UTF-8").good());
        OFCHECK(charEnc.convertString("Simple Text", resultStr).good());
        OFCHECK_EQUAL(resultStr, "Simple Text");
        OFCHECK(charEnc.selectEncoding("ASCII", "DCMTK").bad());
        OFCHECK(charEnc.selectEncoding("DCMTK", "ASCII").bad());
        OFCHECK(charEnc.selectEncoding("", "ASCII").good());
        OFCHECK(charEnc.selectEncoding("ASCII", "").good());
        OFCHECK(charEnc.selectEncoding("ASCII", charEnc.getLocaleEncoding()).good());
        charEnc.setTransliterationMode(OFTrue);
        charEnc.setDiscardIllegalSequenceMode(OFTrue);
        charEnc.clear();
        OFCHECK_EQUAL(charEnc.getTransliterationMode(), OFFalse);
        OFCHECK_EQUAL(charEnc.getDiscardIllegalSequenceMode(), OFFalse);
        OFCHECK(charEnc.convertString("Simple Text", resultStr).bad());
    }
}

OFTEST(ofstd_OFCharacterEncoding_2)
{
    if (OFCharacterEncoding::isLibraryAvailable())
    {
        OFCharacterEncoding charEnc;
        OFString resultStr1, resultStr2;
        // then do some real conversions
        OFCHECK(charEnc.selectEncoding("ISO-8859-1", "UTF-8").good());
        OFCHECK(charEnc.convertString("J\366rg", resultStr1).good());
        OFCHECK_EQUAL(resultStr1, "J\303\266rg");
        OFCHECK_EQUAL(resultStr1.length(), 5);
        OFCHECK(charEnc.convertString("J\351r\364me", resultStr2).good());
        OFCHECK_EQUAL(resultStr2, "J\303\251r\303\264me");
        OFCHECK_EQUAL(resultStr2.length(), 8);
        // and convert back to the original encoding
        OFString resultStr3, resultStr4;
        OFCHECK(charEnc.selectEncoding("UTF-8", "ISO-8859-1").good());
        OFCHECK(charEnc.convertString(resultStr1, resultStr3).good());
        OFCHECK_EQUAL(resultStr3, "J\366rg");
        OFCHECK(charEnc.convertString(resultStr2, resultStr4).good());
        OFCHECK_EQUAL(resultStr4, "J\351r\364me");
    }
}

OFTEST(ofstd_OFCharacterEncoding_3)
{
    if (OFCharacterEncoding::isLibraryAvailable())
    {
        // create a huge string with valid ISO 8859-1 characters (code #32 to #255)
        char hugeStr[4096];
        for (size_t i = 0; i < sizeof(hugeStr); i++)
            hugeStr[i] = 32 + (i % 224);
        // then convert it to UTF-8 (and check whether the internal buffering works)
        OFCharacterEncoding charEnc;
        OFString resultStr;
        OFCHECK(charEnc.selectEncoding("ISO-8859-1", "UTF-8").good());
        OFCHECK(charEnc.convertString(OFString(hugeStr, sizeof(hugeStr)), resultStr).good());
        OFCHECK_EQUAL(resultStr.length(), 6400);
    }
}

OFTEST(ofstd_OFCharacterEncoding_4)
{
    if (OFCharacterEncoding::isLibraryAvailable())
    {
        OFCharacterEncoding charEnc;
        OFString resultStr;
        // enable transliteration mode
        charEnc.setTransliterationMode(OFTrue);
        OFCHECK(charEnc.selectEncoding("ISO-8859-1", "ASCII").good());
        OFCHECK(charEnc.convertString("J\366rg", resultStr).good());
        OFCHECK_EQUAL(resultStr, "J\"org");
        // disable transliteration mode
        charEnc.setTransliterationMode(OFFalse);
        OFCHECK(charEnc.convertString("J\366rg", resultStr).bad());
    }
}

OFTEST(ofstd_OFCharacterEncoding_5)
{
    if (OFCharacterEncoding::isLibraryAvailable())
    {
        OFCharacterEncoding charEnc;
        OFString resultStr;
        // enable discard illegal sequence mode
        charEnc.setDiscardIllegalSequenceMode(OFTrue);
        OFCHECK(charEnc.selectEncoding("ISO-8859-1", "ASCII").good());
        OFCHECK(charEnc.convertString("J\366rg", resultStr).good());
        OFCHECK_EQUAL(resultStr, "Jrg");
        // disable discard illegal sequence mode
        charEnc.setDiscardIllegalSequenceMode(OFFalse);
        OFCHECK(charEnc.convertString("J\366rg", resultStr).bad());
    }
}


/*
 *
 * CVS/RCS Log:
 * $Log: tchrenc.cc,v $
 * Revision 1.1  2011-10-21 09:15:03  joergr
 * Added class for managing and converting between different character encodings
 * based on the libiconv toolkit.
 *
 *
 *
 */