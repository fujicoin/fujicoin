# Copyright (c) 2023-present The Fujicoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

function(generate_setup_nsi)
  set(abs_top_srcdir ${PROJECT_SOURCE_DIR})
  set(abs_top_builddir ${PROJECT_BINARY_DIR})
  set(CLIENT_URL ${PROJECT_HOMEPAGE_URL})
  set(CLIENT_TARNAME "fujicoin")
  set(FUJICOIN_GUI_NAME "fujicoin-qt")
  set(FUJICOIN_DAEMON_NAME "fujicoind")
  set(FUJICOIN_CLI_NAME "fujicoin-cli")
  set(FUJICOIN_TX_NAME "fujicoin-tx")
  set(FUJICOIN_WALLET_TOOL_NAME "fujicoin-wallet")
  set(FUJICOIN_TEST_NAME "test_fujicoin")
  set(EXEEXT ${CMAKE_EXECUTABLE_SUFFIX})
  configure_file(${PROJECT_SOURCE_DIR}/share/setup.nsi.in ${PROJECT_BINARY_DIR}/fujicoin-win64-setup.nsi USE_SOURCE_PERMISSIONS @ONLY)
endfunction()
