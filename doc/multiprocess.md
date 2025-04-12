# Multiprocess Fujicoin

_This document describes usage of the multiprocess feature. For design information, see the [design/multiprocess.md](design/multiprocess.md) file._

## Build Option

On Unix systems, the `-DWITH_MULTIPROCESS=ON` build option can be passed to build the supplemental `fujicoin-node` and `fujicoin-gui` multiprocess executables.

## Debugging

The `-debug=ipc` command line option can be used to see requests and responses between processes.

## Installation

The multiprocess feature requires [Cap'n Proto](https://capnproto.org/) and [libmultiprocess](https://github.com/fujicoin-core/libmultiprocess) as dependencies. A simple way to get started using it without installing these dependencies manually is to use the [depends system](../depends) with the `MULTIPROCESS=1` [dependency option](../depends#dependency-options) passed to make:

```
cd <FUJICOIN_SOURCE_DIRECTORY>
make -C depends NO_QT=1 MULTIPROCESS=1
# Set host platform to output of gcc -dumpmachine or clang -dumpmachine or check the depends/ directory for the generated subdirectory name
HOST_PLATFORM="x86_64-pc-linux-gnu"
cmake -B build --toolchain=depends/$HOST_PLATFORM/toolchain.cmake
cmake --build build
build/bin/fujicoin-node -regtest -printtoconsole -debug=ipc
FUJICOIND=$(pwd)/build/bin/fujicoin-node build/test/functional/test_runner.py
```

The `cmake` build will pick up settings and library locations from the depends directory, so there is no need to pass `-DWITH_MULTIPROCESS=ON` as a separate flag when using the depends system (it's controlled by the `MULTIPROCESS=1` option).

Alternately, you can install [Cap'n Proto](https://capnproto.org/) and [libmultiprocess](https://github.com/fujicoin-core/libmultiprocess) packages on your system, and just run `cmake -B build -DWITH_MULTIPROCESS=ON` without using the depends system. The `cmake` build will be able to locate the installed packages via [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/). See [Installation](https://github.com/fujicoin-core/libmultiprocess/blob/master/doc/install.md) section of the libmultiprocess readme for install steps. See [build-unix.md](build-unix.md) and [build-osx.md](build-osx.md) for information about installing dependencies in general.

## Usage

`fujicoin-node` is a drop-in replacement for `fujicoind`, and `fujicoin-gui` is a drop-in replacement for `fujicoin-qt`, and there are no differences in use or external behavior between the new and old executables. But internally after [#10102](https://github.com/fujicoin/fujicoin/pull/10102), `fujicoin-gui` will spawn a `fujicoin-node` process to run P2P and RPC code, communicating with it across a socket pair, and `fujicoin-node` will spawn `fujicoin-wallet` to run wallet code, also communicating over a socket pair. This will let node, wallet, and GUI code run in separate address spaces for better isolation, and allow future improvements like being able to start and stop components independently on different machines and environments.
[#19460](https://github.com/fujicoin/fujicoin/pull/19460) also adds a new `fujicoin-node` `-ipcbind` option and a `fujicoind-wallet` `-ipcconnect` option to allow new wallet processes to connect to an existing node process.
And [#19461](https://github.com/fujicoin/fujicoin/pull/19461) adds a new `fujicoin-gui` `-ipcconnect` option to allow new GUI processes to connect to an existing node process.
