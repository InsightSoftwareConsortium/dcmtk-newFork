/*
 *
 *  Copyright (C) 1994-2024, OFFIS e.V.
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
 *  Module:  dcmdata
 *
 *  Author:  Gerd Ehlers
 *
 *  Purpose: Handling of transfer syntaxes
 *
 */

#ifndef DCXFER_H
#define DCXFER_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/dcmdata/dctypes.h"
#include "dcmtk/dcmdata/dcvr.h"

// include this file in doxygen documentation

/** @file dcxfer.h
 *  @brief definition and handling of transfer syntaxes
 */

/** enumeration of all DICOM transfer syntaxes known to the toolkit
 */
typedef enum {
    /// unknown transfer syntax or dataset created in-memory
    EXS_Unknown = -1,
    /// Implicit VR Little Endian
    EXS_LittleEndianImplicit = 0,
    /// Implicit VR Big Endian (pseudo transfer syntax that does not really exist)
    EXS_BigEndianImplicit = 1,
    /// Explicit VR Little Endian
    EXS_LittleEndianExplicit = 2,
    /// Explicit VR Big Endian
    EXS_BigEndianExplicit = 3,
    /// JPEG Baseline (lossy)
    EXS_JPEGProcess1 = 4,
    /// JPEG Extended Sequential (lossy, 8/12 bit)
    EXS_JPEGProcess2_4 = 5,
    /// JPEG Extended Sequential (lossy, 8/12 bit), arithmetic coding
    EXS_JPEGProcess3_5 = 6,
    /// JPEG Spectral Selection, Non-Hierarchical (lossy, 8/12 bit)
    EXS_JPEGProcess6_8 = 7,
    /// JPEG Spectral Selection, Non-Hierarchical (lossy, 8/12 bit), arithmetic coding
    EXS_JPEGProcess7_9 = 8,
    /// JPEG Full Progression, Non-Hierarchical (lossy, 8/12 bit)
    EXS_JPEGProcess10_12 = 9,
    /// JPEG Full Progression, Non-Hierarchical (lossy, 8/12 bit), arithmetic coding
    EXS_JPEGProcess11_13 = 10,
    /// JPEG Lossless with any selection value
    EXS_JPEGProcess14 = 11,
    /// JPEG Lossless with any selection value, arithmetic coding
    EXS_JPEGProcess15 = 12,
    /// JPEG Extended Sequential, Hierarchical (lossy, 8/12 bit)
    EXS_JPEGProcess16_18 = 13,
    /// JPEG Extended Sequential, Hierarchical (lossy, 8/12 bit), arithmetic coding
    EXS_JPEGProcess17_19 = 14,
    /// JPEG Spectral Selection, Hierarchical (lossy, 8/12 bit)
    EXS_JPEGProcess20_22 = 15,
    /// JPEG Spectral Selection, Hierarchical (lossy, 8/12 bit), arithmetic coding
    EXS_JPEGProcess21_23 = 16,
    /// JPEG Full Progression, Hierarchical (lossy, 8/12 bit)
    EXS_JPEGProcess24_26 = 17,
    /// JPEG Full Progression, Hierarchical (lossy, 8/12 bit), arithmetic coding
    EXS_JPEGProcess25_27 = 18,
    /// JPEG Lossless, Hierarchical
    EXS_JPEGProcess28 = 19,
    /// JPEG Lossless, Hierarchical, arithmetic coding
    EXS_JPEGProcess29 = 20,
    /// JPEG Lossless, Selection Value 1
    EXS_JPEGProcess14SV1 = 21,
    /// Run Length Encoding (lossless)
    EXS_RLELossless = 22,
    /// Deflated Explicit VR Little Endian
    EXS_DeflatedLittleEndianExplicit = 23,
    /// JPEG-LS (lossless)
    EXS_JPEGLSLossless = 24,
    /// JPEG-LS (lossless or near-lossless mode)
    EXS_JPEGLSLossy = 25,
    /// JPEG 2000 (lossless)
    EXS_JPEG2000LosslessOnly = 26,
    /// JPEG 2000 (lossless or lossy)
    EXS_JPEG2000 = 27,
    /// JPEG 2000 part 2 multi-component extensions (lossless)
    EXS_JPEG2000MulticomponentLosslessOnly = 28,
    /// JPEG 2000 part 2 multi-component extensions (lossless or lossy)
    EXS_JPEG2000Multicomponent = 29,
    /// JPIP Referenced
    EXS_JPIPReferenced = 30,
    /// JPIP Referenced Deflate
    EXS_JPIPReferencedDeflate = 31,
    /// MPEG2 Main Profile at Main Level
    EXS_MPEG2MainProfileAtMainLevel = 32,
    /// Fragmentable MPEG2 Main Profile / Main Level
    EXS_FragmentableMPEG2MainProfileMainLevel = 33,
    /// MPEG2 Main Profile at High Level
    EXS_MPEG2MainProfileAtHighLevel = 34,
    /// Fragmentable MPEG2 Main Profile / High Level
    EXS_FragmentableMPEG2MainProfileHighLevel = 35,
    /// MPEG4 High Profile / Level 4.1
    EXS_MPEG4HighProfileLevel4_1 = 36,
    /// Fragmentable MPEG4 High Profile / Level 4.1
    EXS_FragmentableMPEG4HighProfileLevel4_1 = 37,
    /// MPEG4 BD-compatible High Profile / Level 4.1
    EXS_MPEG4BDcompatibleHighProfileLevel4_1 = 38,
    /// Fragmentable MPEG4 BD-compatible High Profile / Level 4.1
    EXS_FragmentableMPEG4BDcompatibleHighProfileLevel4_1 = 39,
    /// MPEG4 High Profile / Level 4.2 For 2D Video
    EXS_MPEG4HighProfileLevel4_2_For2DVideo = 40,
    /// Fragmentable MPEG4 High Profile / Level 4.2 For 2D Video
    EXS_FragmentableMPEG4HighProfileLevel4_2_For2DVideo = 41,
    /// MPEG4 High Profile / Level 4.2 For 3D Video
    EXS_MPEG4HighProfileLevel4_2_For3DVideo = 42,
    /// Fragmentable MPEG4 Stereo High Profile / Level 4.2
    EXS_FragmentableMPEG4HighProfileLevel4_2_For3DVideo = 43,
    /// MPEG4 Stereo High Profile / Level 4.2
    EXS_MPEG4StereoHighProfileLevel4_2 = 44,
    /// Fragmentable HEVC/H.265 Main Profile / Level 5.1
    EXS_FragmentableMPEG4StereoHighProfileLevel4_2 = 45,
    /// HEVC/H.265 Main Profile / Level 5.1
    EXS_HEVCMainProfileLevel5_1 = 46,
    /// HEVC/H.265 Main 10 Profile / Level 5.1
    EXS_HEVCMain10ProfileLevel5_1 = 47,
    /// High-Throughput JPEG 2000 Image Compression (Lossless Only)
    EXS_HighThroughputJPEG2000LosslessOnly = 48,
    /// High-Throughput JPEG 2000 with RPCL Options Image Compression (Lossless Only)
    EXS_HighThroughputJPEG2000withRPCLOptionsLosslessOnly = 49,
    /// High-Throughput JPEG 2000 Image Compression
    EXS_HighThroughputJPEG2000 = 50,
    /// JPIP HTJ2K Referenced
    EXS_JPIPHTJ2KReferenced = 51,
    /// JPIP HTJ2K Referenced Deflate
    EXS_JPIPHTJ2KReferencedDeflate = 52,
    /// Private GE Little Endian Implicit with big endian pixel data
    EXS_PrivateGE_LEI_WithBigEndianPixelData = 53
} E_TransferSyntax;

/** enumeration of byte orders
 */
typedef enum {
    /// unknown
    EBO_unknown = 0,

    /// little endian
    EBO_LittleEndian = 1,

    /// big endian
    EBO_BigEndian = 2
} E_ByteOrder;

/** enumeration of VR encoding options
 */
typedef enum {
    /// implicit VR encoding
    EVT_Implicit = 0,

    /// explicit VR encoding
    EVT_Explicit = 1
} E_VRType;

/** enumeration of pixel data encapsulation options
 */
typedef enum {
    /// pixel data not encapsulated
    EJE_NotEncapsulated = 0,

    /// pixel data encapsulated
    EJE_Encapsulated = 1
} E_JPEGEncapsulated;

/** enumeration of stream compression techniques
 */
typedef enum
{
    /// no stream compression
    ESC_none = 0
    /// unsupported stream compression
  , ESC_unsupported = 1
#ifdef WITH_ZLIB
    /// zlib stream compression.
    /// This enum value only available if DCMTK is compiled with ZLIB support enabled.
  , ESC_zlib = 2
#endif
} E_StreamCompression;


/** a class that allows for a lookup of Transfer Syntax properties and readable descriptions
 */
class DCMTK_DCMDATA_EXPORT DcmXfer
{
public:
    /** constructor
     *  @param xfer transfer syntax enum
     */
    DcmXfer(E_TransferSyntax xfer);

    /** constructor
     *  @param xferName_xferID transfer syntax name as string
     */
    DcmXfer(const char *xferName_xferID);

    /// copy constructor
    DcmXfer(const DcmXfer &newXfer);

    /// destructor
    ~DcmXfer();

    /// assignment operator for transfer syntax enum
    DcmXfer & operator=(const E_TransferSyntax xfer);

    /// copy assignment operator
    DcmXfer & operator=(const DcmXfer &newXfer);

    /** comparison operator
     *  @param xfer transfer syntax enum to compare with
     *  @return true if equal, false if not equal
     */
    OFBool operator==(const E_TransferSyntax xfer) const
    {
        return xferSyn == xfer;
    }

    /** comparison operator
     *  @param xfer transfer syntax to compare with
     *  @return true if equal, false if not equal
     */
    OFBool operator==(const DcmXfer &xfer) const
    {
        return xferSyn == xfer.getXfer();
    }

    /** comparison operator
     *  @param xfer transfer syntax enum to compare with
     *  @return true if not equal, false if equal
     */
    OFBool operator!=(const E_TransferSyntax xfer) const
    {
        return xferSyn != xfer;
    }

    /** comparison operator
     *  @param xfer transfer syntax to compare with
     *  @return true if not equal, false if equal
     */
    OFBool operator!=(const DcmXfer &xfer) const
    {
        return xferSyn != xfer.getXfer();
    }

    /// return transfer syntax enum for this transfer syntax
    inline E_TransferSyntax getXfer() const
    {
        return xferSyn;
    }

    /// return byte order for this transfer syntax
    inline E_ByteOrder getByteOrder() const
    {
        return byteOrder;
    }

    /// return byte order for this transfer syntax
    inline E_ByteOrder getPixelDataByteOrder() const
    {
        return pixelDataByteOrder;
    }

    /// return name string for this transfer syntax
    inline const char* getXferName() const
    {
        return xferName;
    }

    /// return keyword string for this transfer syntax
    const char* getXferKeyword() const;

    /// return UID string for this transfer syntax
    inline const char* getXferID() const
    {
        return xferID;
    }

    /// return true if transfer syntax is little endian, false otherwise
    inline OFBool isLittleEndian() const
    {
        return byteOrder == EBO_LittleEndian;
    }

    /// return true if transfer syntax is big endian, false otherwise
    inline OFBool isBigEndian() const
    {
        return byteOrder == EBO_BigEndian;
    }

    /// return true if transfer syntax is implicit VR, false otherwise
    inline OFBool isImplicitVR() const
    {
        return vrType == EVT_Implicit;
    }

    /// return true if transfer syntax is explicit VR, false otherwise
    inline OFBool isExplicitVR() const
    {
        return vrType == EVT_Explicit;
    }

    /// return true if transfer syntax is encapsulated, false otherwise
    inline OFBool isEncapsulated() const
    {
        return encapsulated == EJE_Encapsulated;
    }

    /// return true if transfer syntax is native (non-encapsulated), false otherwise
    inline OFBool isNotEncapsulated() const
    {
        return encapsulated == EJE_NotEncapsulated;
    }

    /** return 8-bit JPEG process ID for this transfer syntax.
     *  Lossy JPEG transfer syntaxes support two alternative JPEG encoding processes - 8 and 12 bits.
     *  When called for a non-JPEG transfer syntax, returns 0.
     *  @return 8-bit JPEG process ID
     */
    inline Uint32 getJPEGProcess8Bit() const
    {
        return JPEGProcess8;
    }

    /** return 12-bit JPEG process ID for this transfer syntax.
     *  Lossy JPEG transfer syntaxes support two alternative JPEG encoding processes - 8 and 12 bits.
     *  When called for a non-JPEG transfer syntax, returns 0.
     *  @return 12-bit JPEG process ID
     */
    inline Uint32 getJPEGProcess12Bit() const
    {
        return JPEGProcess12;
    }

    /** check whether transfer syntax uses a lossy compression
     *  @return true if transfer syntax uses a lossy compression, false otherwise
     */
    inline OFBool isLossy() const
    {
        return lossy;
    }

    /** check whether transfer syntax uses a lossless compression or no compression
     *  @return true if transfer syntax uses a lossless compression or no compression,
     *    false otherwise
     */
    inline OFBool isLossless() const
    {
        return !lossy;
    }

    /** check whether transfer syntax is retired
     *  @return true if transfer syntax is retired, false otherwise
     */
    inline OFBool isRetired() const
    {
        return retired;
    }

    /** get stream compression type for this transfer syntax
     *  @return stream compression type for this transfer syntax
     */
    inline E_StreamCompression getStreamCompression() const
    {
        return streamCompression;
    }

    /** check whether transfer syntax uses (0028,7FE0) Pixel Data Provider URL
     *  to reference pixel data
     *  @return true if transfer syntax uses URL reference to pixel data
     */
    inline OFBool isReferenced() const
    {
        return referenced;
    }

    /** check whether transfer syntax allows the encapsulated pixel stream of
     *  encoded pixel data to be split into one or more fragments
     *  @return true if transfer syntax supports fragmentable pixel data
     */
    inline OFBool isFragmentable() const
    {
        return fragmentable;
    }

    /** return the number of bytes needed to describe the tag, length, VR
     *  and any reserved fields for this transfer syntax when encoding the
     *  specified VR.
     *  @param evr value representation to be encoded in this transfer syntax
     *  @return number of bytes needed
     */
    Uint32 sizeofTagHeader(DcmEVR evr) const;

private:
    /// transfer syntax UID
    const char          *xferID;

    /// transfer syntax name
    const char          *xferName;

    /// transfer syntax enum
    E_TransferSyntax    xferSyn;

    /// transfer syntax byte order
    E_ByteOrder         byteOrder;

    /// transfer syntax byte order for pixel data
    E_ByteOrder         pixelDataByteOrder;

    /// transfer syntax VR encoding (implicit/explicit)
    E_VRType            vrType;

    /// transfer syntax encapsulated or native
    E_JPEGEncapsulated  encapsulated;

    /// 8-bit lossy JPEG process ID for this transfer syntax, 0 if not applicable
    Uint32              JPEGProcess8;

    /// 12-bit lossy JPEG process ID for this transfer syntax, 0 if not applicable
    Uint32              JPEGProcess12;

    /// flag indicating whether this transfer syntax uses a lossy compression
    OFBool              lossy;

    /// flag indicating whether this transfer syntax has been retired from DICOM
    OFBool              retired;

    /// transfer syntax stream compression type
    E_StreamCompression streamCompression;

    /// flag indicating whether this transfer syntax uses a pixel data URL reference
    OFBool              referenced;

    /// flag indicating whether this transfer syntax supports fragmentable pixel data
    OFBool              fragmentable;

};

/** global constant describing the byte order on the machine the application
 *  is currently executing on. This is runtime and not compile time information
 *  because of "fat" binaries that can be executed on multiple CPU types (e.g. NeXTStep)
 */
extern DCMTK_DCMDATA_EXPORT const E_ByteOrder gLocalByteOrder;

#endif // DCXFER_H
