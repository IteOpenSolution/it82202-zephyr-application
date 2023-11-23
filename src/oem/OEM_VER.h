/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _ITE_OEM_VER_H_
#define _ITE_OEM_VER_H_

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/
extern const unsigned char SIGN_MUFG[];
extern const unsigned char SIGN_DATE[];
extern const unsigned char SIGN_MODL[];
extern const unsigned char SIGN_GUST[];
extern const unsigned char SIGN_PCBV[];
extern const unsigned char SIGN_ECVR[];
extern const unsigned char ECVER[];

/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Reload_EC_Ver(void);

#endif /* _ITE_OEM_VER_H_ */