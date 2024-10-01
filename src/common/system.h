// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-present The Fujicoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef FUJICOIN_COMMON_SYSTEM_H
#define FUJICOIN_COMMON_SYSTEM_H

#include <config/fujicoin-config.h> // IWYU pragma: keep

#include <cstdint>
#include <string>

// Application startup time (used for uptime calculation)
int64_t GetStartupTime();

void SetupEnvironment();
[[nodiscard]] bool SetupNetworking();
#ifndef WIN32
std::string ShellEscape(const std::string& arg);
#endif
#if HAVE_SYSTEM
void runCommand(const std::string& strCommand);
#endif

/**
 * Return the number of cores available on the current system.
 * @note This does count virtual cores, such as those provided by HyperThreading.
 */
int GetNumCores();

#endif // FUJICOIN_COMMON_SYSTEM_H
