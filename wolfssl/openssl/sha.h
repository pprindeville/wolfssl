/* sha.h
 *
 * Copyright (C) 2006-2021 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */

/* sha.h for openssl */


#ifndef WOLFSSL_SHA_H_
#define WOLFSSL_SHA_H_

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/types.h>

#ifdef WOLFSSL_PREFIX
#include "prefix_sha.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif


typedef struct WOLFSSL_SHA_CTX {
    /* big enough to hold wolfcrypt Sha, but check on init */
#if defined(STM32_HASH)
    void* holder[(112 + WC_ASYNC_DEV_SIZE + sizeof(STM32_HASH_Context)) / sizeof(void*)];
#else
    void* holder[(112 + WC_ASYNC_DEV_SIZE) / sizeof(void*)];
#endif
    #ifdef WOLF_CRYPTO_CB
    void* cryptocb_holder[(sizeof(int) + sizeof(void*) + 4) / sizeof(void*)];
    #endif
} WOLFSSL_SHA_CTX;

WOLFSSL_API int wolfSSL_SHA_Init(WOLFSSL_SHA_CTX*);
WOLFSSL_API int wolfSSL_SHA_Update(WOLFSSL_SHA_CTX*, const void*, unsigned long);
WOLFSSL_API int wolfSSL_SHA_Final(unsigned char*, WOLFSSL_SHA_CTX*);
WOLFSSL_API int wolfSSL_SHA_Transform(WOLFSSL_SHA_CTX*, 
                                          const unsigned char *data);
/* SHA1 points to above, shouldn't use SHA0 ever */
WOLFSSL_API int wolfSSL_SHA1_Init(WOLFSSL_SHA_CTX*);
WOLFSSL_API int wolfSSL_SHA1_Update(WOLFSSL_SHA_CTX*, const void*, unsigned long);
WOLFSSL_API int wolfSSL_SHA1_Final(unsigned char*, WOLFSSL_SHA_CTX*);
WOLFSSL_API int wolfSSL_SHA1_Transform(WOLFSSL_SHA_CTX*, 
                                          const unsigned char *data);
enum {
    SHA_DIGEST_LENGTH = 20
};


typedef WOLFSSL_SHA_CTX SHA_CTX;

#define SHA_Init wolfSSL_SHA_Init
#define SHA_Update wolfSSL_SHA_Update
#define SHA_Final wolfSSL_SHA_Final
#define SHA_Transform wolfSSL_SHA_Transform

#if defined(NO_OLD_SHA_NAMES) && !defined(HAVE_SELFTEST) && \
    (!defined(HAVE_FIPS) || \
    (defined(HAVE_FIPS_VERSION) && HAVE_FIPS_VERSION > 2))
    /* SHA is only available in non-fips mode or fips version > 2 mode 
     * because of SHA enum in FIPS build. */
    #define SHA wolfSSL_SHA1
#endif

#define SHA1_Init wolfSSL_SHA1_Init
#define SHA1_Update wolfSSL_SHA1_Update
#define SHA1_Final wolfSSL_SHA1_Final
#define SHA1_Transform wolfSSL_SHA1_Transform

#ifdef WOLFSSL_SHA224

/* Using ALIGN16 because when AES-NI is enabled digest and buffer in Sha256
 * struct are 16 byte aligned. Any dereference to those elements after casting
 * to Sha224, is expected to also be 16 byte aligned addresses.  */
typedef struct WOLFSSL_SHA224_CTX {
    /* big enough to hold wolfcrypt Sha224, but check on init */
    ALIGN16 void* holder[(272 + WC_ASYNC_DEV_SIZE) / sizeof(void*)];
} WOLFSSL_SHA224_CTX;

WOLFSSL_API int wolfSSL_SHA224_Init(WOLFSSL_SHA224_CTX*);
WOLFSSL_API int wolfSSL_SHA224_Update(WOLFSSL_SHA224_CTX*, const void*,
	                                 unsigned long);
WOLFSSL_API int wolfSSL_SHA224_Final(unsigned char*, WOLFSSL_SHA224_CTX*);

enum {
    SHA224_DIGEST_LENGTH = 28
};


typedef WOLFSSL_SHA224_CTX SHA224_CTX;

#define SHA224_Init   wolfSSL_SHA224_Init
#define SHA224_Update wolfSSL_SHA224_Update
#define SHA224_Final  wolfSSL_SHA224_Final
#if defined(NO_OLD_SHA_NAMES) && !defined(HAVE_SELFTEST) && \
    (!defined(HAVE_FIPS) || \
    (defined(HAVE_FIPS_VERSION) && HAVE_FIPS_VERSION > 2))
    /* SHA224 is only available in non-fips mode or fips version > 2 mode 
     * because of SHA224 enum in FIPS build. */
    #define SHA224 wolfSSL_SHA224
#endif

#endif /* WOLFSSL_SHA224 */


/* Using ALIGN16 because when AES-NI is enabled digest and buffer in Sha256
 * struct are 16 byte aligned. Any dereference to those elements after casting
 * to Sha256, is expected to also be 16 byte aligned addresses.  */
typedef struct WOLFSSL_SHA256_CTX {
    /* big enough to hold wolfcrypt Sha256, but check on init */
    ALIGN16 void* holder[(272 + WC_ASYNC_DEV_SIZE) / sizeof(void*)];
} WOLFSSL_SHA256_CTX;

WOLFSSL_API int wolfSSL_SHA256_Init(WOLFSSL_SHA256_CTX*);
WOLFSSL_API int wolfSSL_SHA256_Update(WOLFSSL_SHA256_CTX*, const void*,
                                 unsigned long);
WOLFSSL_API int wolfSSL_SHA256_Final(unsigned char*, WOLFSSL_SHA256_CTX*);
WOLFSSL_API int wolfSSL_SHA256_Transform(WOLFSSL_SHA256_CTX*, 
                                                const unsigned char *data);
enum {
    SHA256_DIGEST_LENGTH = 32
};


typedef WOLFSSL_SHA256_CTX SHA256_CTX;

#define SHA256_Init   wolfSSL_SHA256_Init
#define SHA256_Update wolfSSL_SHA256_Update
#define SHA256_Final  wolfSSL_SHA256_Final
#define SHA256_Transform wolfSSL_SHA256_Transform

#if defined(NO_OLD_SHA_NAMES) && !defined(HAVE_FIPS) && !defined(HAVE_SELFTEST)
    /* SHA256 is only available in non-fips mode because of SHA256 enum in FIPS
     * build. */
    #define SHA256 wolfSSL_SHA256
#endif


#ifdef WOLFSSL_SHA384

typedef struct WOLFSSL_SHA384_CTX {
    /* big enough to hold wolfCrypt Sha384, but check on init */
    void* holder[(268 + WC_ASYNC_DEV_SIZE) / sizeof(void*)];
} WOLFSSL_SHA384_CTX;

WOLFSSL_API int wolfSSL_SHA384_Init(WOLFSSL_SHA384_CTX*);
WOLFSSL_API int wolfSSL_SHA384_Update(WOLFSSL_SHA384_CTX*, const void*,
	                                 unsigned long);
WOLFSSL_API int wolfSSL_SHA384_Final(unsigned char*, WOLFSSL_SHA384_CTX*);

enum {
    SHA384_DIGEST_LENGTH = 48
};


typedef WOLFSSL_SHA384_CTX SHA384_CTX;

#define SHA384_Init   wolfSSL_SHA384_Init
#define SHA384_Update wolfSSL_SHA384_Update
#define SHA384_Final  wolfSSL_SHA384_Final
#if defined(NO_OLD_SHA_NAMES) && !defined(HAVE_FIPS) && !defined(HAVE_SELFTEST)
    /* SHA384 is only available in non-fips mode because of SHA384 enum in FIPS
     * build. */
    #define SHA384 wolfSSL_SHA384
#endif
#endif /* WOLFSSL_SHA384 */

#ifdef WOLFSSL_SHA512

typedef struct WOLFSSL_SHA512_CTX {
    /* big enough to hold wolfCrypt Sha384, but check on init */
    void* holder[(288 + WC_ASYNC_DEV_SIZE) / sizeof(void*)];
} WOLFSSL_SHA512_CTX;

WOLFSSL_API int wolfSSL_SHA512_Init(WOLFSSL_SHA512_CTX*);
WOLFSSL_API int wolfSSL_SHA512_Update(WOLFSSL_SHA512_CTX*, const void*,
                                     unsigned long);
WOLFSSL_API int wolfSSL_SHA512_Final(unsigned char*, WOLFSSL_SHA512_CTX*);
WOLFSSL_API int wolfSSL_SHA512_Transform(WOLFSSL_SHA512_CTX*, 
                                        const unsigned char*);
enum {
    SHA512_DIGEST_LENGTH = 64
};


typedef WOLFSSL_SHA512_CTX SHA512_CTX;

#define SHA512_Init   wolfSSL_SHA512_Init
#define SHA512_Update wolfSSL_SHA512_Update
#define SHA512_Final  wolfSSL_SHA512_Final
#define SHA512_Transform wolfSSL_SHA512_Transform
#if defined(NO_OLD_SHA_NAMES) && !defined(HAVE_FIPS) && !defined(HAVE_SELFTEST)
    /* SHA512 is only available in non-fips mode because of SHA512 enum in FIPS
     * build. */
    #define SHA512 wolfSSL_SHA512
#endif

#if !defined(WOLFSSL_NOSHA512_224)
typedef struct WOLFSSL_SHA512_CTX WOLFSSL_SHA512_224_CTX;
typedef WOLFSSL_SHA512_224_CTX SHA512_224_CTX;

WOLFSSL_API int wolfSSL_SHA512_224_Init(WOLFSSL_SHA512_CTX*);
WOLFSSL_API int wolfSSL_SHA512_224_Update(WOLFSSL_SHA512_CTX*, const void*,
                                     unsigned long);
WOLFSSL_API int wolfSSL_SHA512_224_Final(unsigned char*, WOLFSSL_SHA512_CTX*);
WOLFSSL_API int wolfSSL_SHA512_224_Transform(WOLFSSL_SHA512_CTX*, 
                                        const unsigned char*);


#define SHA512_224_Init   wolfSSL_SHA512_224_Init
#define SHA512_224_Update wolfSSL_SHA512_224_Update
#define SHA512_224_Final  wolfSSL_SHA512_224_Final
#define SHA512_224_Transform wolfSSL_SHA512_224_Transform

#if defined(NO_OLD_SHA_NAMES) && !defined(HAVE_FIPS) && !defined(HAVE_SELFTEST)
    #define SHA512_224 wolfSSL_SHA512_224
#endif
#endif /* !WOLFSSL_NOSHA512_224 */

#if !defined(WOLFSSL_NOSHA512_256)
typedef struct WOLFSSL_SHA512_CTX WOLFSSL_SHA512_256_CTX;
typedef WOLFSSL_SHA512_256_CTX SHA512_256_CTX;

WOLFSSL_API int wolfSSL_SHA512_256_Init(WOLFSSL_SHA512_CTX*);
WOLFSSL_API int wolfSSL_SHA512_256_Update(WOLFSSL_SHA512_CTX*, const void*,
                                     unsigned long);
WOLFSSL_API int wolfSSL_SHA512_256_Final(unsigned char*, WOLFSSL_SHA512_CTX*);
WOLFSSL_API int wolfSSL_SHA512_256_Transform(WOLFSSL_SHA512_CTX*, 
                                        const unsigned char*);

#define SHA512_256_Init   wolfSSL_SHA512_256_Init
#define SHA512_256_Update wolfSSL_SHA512_256_Update
#define SHA512_256_Final  wolfSSL_SHA512_256_Final
#define SHA512_256_Transform wolfSSL_SHA512_256_Transform

#if defined(NO_OLD_SHA_NAMES) && !defined(HAVE_FIPS) && !defined(HAVE_SELFTEST)
    #define SHA512_256 wolfSSL_SHA512_256
#endif
#endif /* !WOLFSSL_NOSHA512_256 */


#endif /* WOLFSSL_SHA512 */




#ifdef __cplusplus
    }  /* extern "C" */
#endif


#endif /* WOLFSSL_SHA_H_ */

