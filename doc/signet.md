Contents
========
This document describes how to set up your own Signet network.

Launch Signet
=============

fujicoin.conf settings
----------------------
Set `fujicoin.conf` in the data folder(`~/.fujicoin`) referring to the example below.

    [main]
    #rpcuser=
    #rpcpassword=
    #rpcauth=user:ffb389c0.......0dd878972
    rpcallowip=127.0.0.1
    server=1
    
    [signet]
    #rpcuser=
    #rpcpassword=
    #rpcauth=user:ffb389c0.......0dd878972
    rpcallowip=127.0.0.1
    server=1
    daemon=1
    #addnode=
    #signetchallenge=512102f8........4f2a51ae

Start fujicoind with signet: `./fujicoind -signet`

Create a signetchallenge for your own network
---------------------------------------------
Use something like the [BIP39 tool](https://iancoleman.io/bip39/) to obtain the legacy address, private key, and public key pair.
Create signetcharrenge from this public key.
You will need to import the private key into your wallet later.

    For example:
    ADDR=Wzjjb6AuENq846LV1EzSqVh4jrB22q26fC
    PRIVKEY=Wuok1Ko8p72C6yMdXtbVRPyyJbKSmuKwobjrW76tLn86MahFHCpw
    PUBKEY=03c0fad339e8a0641732400023180dd884f68075a51b1a05e4825501c3282ab606

    ・signetchallenge = 5121 + PUBKEY + 51ae
    CHALLENGE=512103c0fad339e8a0641732400023180dd884f68075a51b1a05e4825501c3282ab60651ae

Mining environment settings
---------------------------
Start fujicoind.

    ./fujicoind -signet -daemon -signetchallenge=$CHALLENGE
    CLI="./fujicoin-cli -signet"
    $CLI createwallet "signet"

Create and import the private key descriptor.

    ・Format of descriptor: multi(1, <priv_key>)#<checksum>
    descriptor: multi(1, Wuok1Ko8p72C6yMdXtbVRPyyJbKSmuKwobjrW76tLn86MahFHCpw)
    $CLI getdescriptorinfo "multi(1,Wuok1Ko8p72C6yMdXtbVRPyyJbKSmuKwobjrW76tLn86MahFHCpw)" | grep checksum
    "checksum": "7uwn2a0x",
    $CLI importdescriptors '[{"desc":"multi(1,Wuok1Ko8p72C6yMdXtbVRPyyJbKSmuKwobjrW76tLn86MahFHCpw)#7uwn2a0x","timestamp":"now","active":false,"internal":false}]'

Mining
======

Please clone the fujicoin source code to the folder where you installed the fujicoin binaries and prepare miner and test_framework.

    git clone https://github.com/fujicoin/fujicoin.git
    cp -r fujicoin/test/functional/test_framework .
    cp fujicoin/contrib/signet/miner .

To mine the first block in your custom chain, you can run:

    cd to_fujicoind_folder
    CLI="./fujicoin-cli -signet"
    MINER="./miner"
    GRIND="./fujicoin-util grind"
    ADDRESS="X93kbwJctRMXzVXRX6MUxUeteYGbLFz5MR"  # Note: Use legacy address

To mining block number 1, execute the following command. 
This will mine a block with the current timestamp. 
If you want to backdate the chain, you can give a different timestamp to --set-block-time. 
A UnixTime 12 hours ago is recommended.

    $MINER --cli="$CLI" generate --grind-cmd="$GRIND" --address="$ADDRESS" --nbits=1f0fffff --set-block-time=-1


Using the --ongoing parameter will then cause the signet miner to create blocks indefinitely. 
It will pick the time between blocks so that difficulty is adjusted to match the provided --nbits value. 
Setting nbits to 1f0fffff will create blocks every minute.

    $MINER --cli="$CLI" generate --grind-cmd="$GRIND" --address="$ADDR" --nbits=1f0fffff --ongoing

