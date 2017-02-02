// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0x45;
        pchMessageStart[3] = 0x50;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04e3b77ed19efdc11ed11208b7785b79b20e81a759cc65f6e45919dadb960d4575dba105cbd121a43472976550cfc798562d3fc4a6f7641b93f817e1a15ae7adba");
        vchSyncCheckpointPubKey = ParseHex("04a3059fa6ff60fb459ad2b3703e294f55fa858dc57d35e89efdad5bb959f311fc4fb2604881c0a1aa5fc47bf459d4a373a061ebddeba8255a99af748fe698ca08");
        nDefaultPort = 17777;
        nRPCPort = 17778;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        const char* pszTimestamp = "05/08/2016 00:00 Step by step";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1470355200, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1470355200;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 5046295;

        hashGenesisBlock = uint256("0x4066aa83c029cad21d5c932fd0443e118afab6e914eec16d04d511d6512a79ca");
        if (true && (genesis.GetHash() != hashGenesisBlock))
        {
            cout << "genesis: MAIN:"<<endl;
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetPoWHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "genesis: \n" << genesis.ToString() << endl;
            cout << "genesis.GetPoWHash(): " << genesis.GetPoWHash().ToString() << endl;
            cout << "genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "genesis.nTime: " << genesis.nTime << endl;
            cout << "genesis.nNonce: " << genesis.nNonce << endl;
        }


        assert(hashGenesisBlock == uint256("0x4066aa83c029cad21d5c932fd0443e118afab6e914eec16d04d511d6512a79ca"));
        assert(genesis.hashMerkleRoot == uint256("0x0702c16b56cc2c512663ce6e0629f41ffc21b3cbaa8e735f62403b21edeccd7b"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(63);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(95);
        base58Prefixes[SECRET_KEY] =     list_of(163);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        bnProofOfStakeLimit = CBigNum(~uint256(32));
        
        nPoWReward = 0 * COIN;
        nLaunchTime = genesis.nTime;
        nCoinbaseMaturity = 120;
        nStakeMinConfirmations = 120;
        nStakeMinAge = 8 * 60 * 60; // 8 Hrs
        nModifierInterval = 10 * 60; // time to elapse before new modifier is computed
        nStakeCoinYearReward = 1 * CENT; // 1% per year
        nFirstPoSBlock = 160;
        nTargetSpacing =  60;
        nTargetTimespan = 20 * 60;
        nMinDelay = 2;
        nMaxMoney = 1500000000 * COIN;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x73;
        pchMessageStart[1] = 0x74;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0x70;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04e14e1a52538e9f38311b2f518fe530440b7de50e292b5ddd0eadb89db8d515fc9855ef3fcb419111057073a7ae5b51290089b962d8bfbf293e319683b1cb9cee");
        vchSyncCheckpointPubKey = ParseHex("04a4f10ca4156d8026990aed1fb70fd9511d73e341878e4d2f944fe9d9bb3dd262f3a62bdc7031157d19d9477b28d0d672ffdb54af232dbf0504707631f1768d94");
        nDefaultPort = 18777;
        nRPCPort = 18778;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 5791712;
        hashGenesisBlock = uint256("0x5817eb18c9765788d18cc47aaa34c8f93d8f6d8a1a4e52371b5f95087c087d20");
        if (true && (genesis.GetHash() != hashGenesisBlock))
        {
            cout << "genesis: TEST:"<<endl;
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetPoWHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "genesis: \n" << genesis.ToString() << endl;
            cout << "genesis.GetPoWHash(): " << genesis.GetPoWHash().ToString() << endl;
            cout << "genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "genesis.nTime: " << genesis.nTime << endl;
            cout << "genesis.nNonce: " << genesis.nNonce << endl;
        }

        assert(hashGenesisBlock == uint256("0x5817eb18c9765788d18cc47aaa34c8f93d8f6d8a1a4e52371b5f95087c087d20"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(125);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(157);
        base58Prefixes[SECRET_KEY]     = list_of(225);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        bnProofOfStakeLimit = CBigNum(~uint256(20));

        nCoinbaseMaturity = 10;
        nStakeMinConfirmations = 10;
        nStakeMinAge = 8 * 60 * 60; // 8 Hrs
        nModifierInterval = 10 * 60; // time to elapse before new modifier is computed
        nStakeCoinYearReward = 1 * CENT; // 1% per year
        nMinDelay = 2;
        nMaxMoney = 2000000000 * COIN;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xe2;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0xc4;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1470000000;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 617537;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 47777;
        strDataDir = "regtest";

        hashGenesisBlock = uint256("0xcc37164ad5e4bb75b6c61b893d2831beb02f080cb813aba94e7bab84981c7086");
        if (true && (genesis.GetHash() != hashGenesisBlock))
        {
            cout << "genesis: REGTEST:"<<endl;
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetPoWHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "genesis: \n" << genesis.ToString() << endl;
            cout << "genesis.GetPoWHash(): " << genesis.GetPoWHash().ToString() << endl;
            cout << "genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "genesis.nTime: " << genesis.nTime << endl;
            cout << "genesis.nNonce: " << genesis.nNonce << endl;
        }
        assert(hashGenesisBlock == uint256("0xcc37164ad5e4bb75b6c61b893d2831beb02f080cb813aba94e7bab84981c7086"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
