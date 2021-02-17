/*
 * systemTypes.h
 *
 *  Created on: Feb 25, 2020
 *      Author: yaphan.ng
 */

#ifndef SYSTEMTYPES_H_
#define SYSTEMTYPES_H_

//
//  8 bit long
//
typedef signed char         INT8;
typedef unsigned char       UINT8;

//
// 16 bit long
//
typedef signed short        INT16;
typedef unsigned short      UINT16;

//
// 32 bit long
//
typedef signed int          INT32;
typedef unsigned int        UINT32;
typedef unsigned int*       PUINT32;

//
// 64 bit long
//
typedef signed long long    INT64;
typedef unsigned long long  UINT64;

//
// Alternate integer typedefs w/underscores
//
typedef INT8                INT_8;
typedef UINT8               UINT_8;
typedef INT16               INT_16;
typedef UINT16              UINT_16;
typedef INT32               INT_32;
typedef UINT32              UINT_32;
typedef INT64               INT_64;
typedef UINT64              UINT_64;

#ifndef TRUE
    #define TRUE    1
#endif

#ifndef FALSE
    #define FALSE   0
#endif

// Single bit shift left
#define M(x) (1U << x)

//
//  Define macro to declare code extern "C" for c++
//
//
#ifndef __externC
    #ifdef __cplusplus
        #define __externC extern "C"
    #else
        #define __externC extern
    #endif
#endif

#endif /* SYSTEMTYPES_H_ */
