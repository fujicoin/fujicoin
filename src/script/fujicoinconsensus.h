// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2021 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef FUJICOIN_SCRIPT_FUJICOINCONSENSUS_H
#define FUJICOIN_SCRIPT_FUJICOINCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_FUJICOIN_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/fujicoin-config.h>
  #if defined(_WIN32)
    #if defined(HAVE_DLLEXPORT_ATTRIBUTE)
      #define EXPORT_SYMBOL __declspec(dllexport)
    #else
      #define EXPORT_SYMBOL
    #endif
  #elif defined(HAVE_DEFAULT_VISIBILITY_ATTRIBUTE)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBFUJICOINCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define FUJICOINCONSENSUS_API_VER 2

typedef enum fujicoinconsensus_error_t
{
    fujicoinconsensus_ERR_OK = 0,
    fujicoinconsensus_ERR_TX_INDEX,
    fujicoinconsensus_ERR_TX_SIZE_MISMATCH,
    fujicoinconsensus_ERR_TX_DESERIALIZE,
    fujicoinconsensus_ERR_AMOUNT_REQUIRED,
    fujicoinconsensus_ERR_INVALID_FLAGS,
    fujicoinconsensus_ERR_SPENT_OUTPUTS_REQUIRED,
    fujicoinconsensus_ERR_SPENT_OUTPUTS_MISMATCH
} fujicoinconsensus_error;

/** Script verification flags */
enum
{
    fujicoinconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    fujicoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    fujicoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    fujicoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    fujicoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    fujicoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    fujicoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    fujicoinconsensus_SCRIPT_FLAGS_VERIFY_TAPROOT             = (1U << 17), // enable TAPROOT (BIPs 341 & 342)
    fujicoinconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = fujicoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH | fujicoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               fujicoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | fujicoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               fujicoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | fujicoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS |
                                                               fujicoinconsensus_SCRIPT_FLAGS_VERIFY_TAPROOT
};

typedef struct {
    const unsigned char *scriptPubKey;
    unsigned int scriptPubKeySize;
    int64_t value;
} UTXO;

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int fujicoinconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, fujicoinconsensus_error* err);

EXPORT_SYMBOL int fujicoinconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, fujicoinconsensus_error* err);

EXPORT_SYMBOL int fujicoinconsensus_verify_script_with_spent_outputs(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    const UTXO *spentOutputs, unsigned int spentOutputsLen,
                                    unsigned int nIn, unsigned int flags, fujicoinconsensus_error* err);

EXPORT_SYMBOL unsigned int fujicoinconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // FUJICOIN_SCRIPT_FUJICOINCONSENSUS_H
