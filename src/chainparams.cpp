// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2019 The BCZ Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "spork.h"
#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;


/**
 * Main network
 */

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
        (     0, uint256("0x00000fca55bd94508769f48d6d17c4aa3f9ae40b072036a3691752f1b70ef2dd"))
        (     1, uint256("0x00000d401c34c59f6c7eb1120f7686493099dc37758c839facda1277a8f69b7d"))
        (    27, uint256("0x0000027392926c9e3deedcb818b8cf372f0a264ed4349627e6ac10b2e6ccd349"))
        (   632, uint256("0x00000ff68dfdd471089ef2cb1b63d2c830f5bc7b4b2a9f4397b9c6601001455b"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1556228348, // * UNIX timestamp of last checkpoint block
    10000,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    500        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool notused) const
{
    assert(this);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec("25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                            "31438167899885040445364023527381951378636564391212010397122822120720357");
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);
    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = { 'b' };
        pchMessageStart[1] = { 'c' };
        pchMessageStart[2] = { 'z' };
        pchMessageStart[3] = { '0' };
        vAlertPubKey = ParseHex("048378e08a534895875d23874348f0e126f55911837bc920c559fd2f835ec4dd209b95582039de00b322347f5b38b11d2fe078349d0347884f420d4e11bf3a4c4c");
        nMaxCheckblocks = 576;
        nMaxClockdrift = 24 * 60 * 60;
        nStakeMinAge = 60 * 60;
        nStakeTargetSpacing = 150;
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetTimespan = 150;
        nTargetSpacing = 150;
        nMaturity = 100;
        nMaxMoneyOut = 21000000 * COIN;
        npowLimit = ~uint256(0) >> 20;
        const char* pszTimestamp = "BCZ BORN";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0x1e0fffff << CBigNum(4).getvch() << std::vector < unsigned char >((const unsigned char *) pszTimestamp, (const unsigned char *) pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0;
        txNew.vout[0].scriptPubKey = CScript();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 2;
        genesis.nTime = 1554888888;
        genesis.nBits = 0x1e0fffff;
        genesis.nNonce = 249257;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000fca55bd94508769f48d6d17c4aa3f9ae40b072036a3691752f1b70ef2dd"));
        assert(genesis.hashMerkleRoot == uint256("0x0adff40a2ade8baf5c2c311748928ff4d4d727d2042b1f685fe8ca1f70a1021b"));
        vSeeds.push_back(CDNSSeedData("51.83.98.8", "51.83.98.8"));
        vSeeds.push_back(CDNSSeedData("51.83.98.12", "51.83.98.12"));
        vSeeds.push_back(CDNSSeedData("51.83.98.13", "51.83.98.13"));
        vSeeds.push_back(CDNSSeedData("51.83.98.21", "51.83.98.21"));
        vSeeds.push_back(CDNSSeedData("51.83.78.28", "51.83.78.28"));
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 20);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 210);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
        nPoolMaxTransactions = 3;
        strSporkKey = "04964af71decbf046031d1bf6a13b747a433bc14dc97c6f7f0b5b33d26eea81dc2a8df57d50b07251975857592989f730d0e7153ca3bc65ebc29e0b21cb57683b5";
        strObfuscationPoolDummyAddress = "B52EagiPxecjS9zwyebbCZz3x3QuYBNezo";
        /** Zerocoin */

        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
