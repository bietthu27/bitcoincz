// Copyright (c) 2014-2016 The Dash developers
// Copyright (c) 2019 The BCZ Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SPORK_H
#define SPORK_H

#include "base58.h"
#include "key.h"
#include "main.h"
#include "net.h"
#include "sync.h"
#include "util.h"

#include "obfuscation.h"
#include "protocol.h"

using namespace std;
using namespace boost;

#define SPORK_START 10001
#define SPORK_END 10020

#define SPORK_2_SWIFTTX 10002
#define SPORK_3_SWIFTTX_BLOCK_FILTERING 10003
#define SPORK_5_MAX_VALUE 10005
#define SPORK_6_POW_STOP 10006
#define SPORK_7_POS_START 10007
#define SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT 10008
#define SPORK_9_ALERT_TIME 10009
#define SPORK_10_ALERT_BLOCK 10010
#define SPORK_11_F_PAY 10011
#define SPORK_12_NEXXT 10012
#define SPORK_13_MN_F_PAYMENTS 10013
#define SPORK_14_FEE_CHECK 10014
#define SPORK_15_MN_MODE_X 10015
#define SPORK_16_ZEROCOIN_MAINTENANCE_MODE 10016
#define SPORK_17_ZEROCOIN_STAKE 10017
#define SPORK_18_RECONSIDER_BLOCKS 10018
#define SPORK_19_LYRA_ALGO 10019
#define SPORK_20_ZEROCOIN_START 10020


#define SPORK_2_SWIFTTX_DEFAULT 978307200                         //2001-1-1
#define SPORK_3_SWIFTTX_BLOCK_FILTERING_DEFAULT 1424217600        //2015-2-18
#define SPORK_5_MAX_VALUE_DEFAULT 1000                            //1000 BCZ
#define SPORK_6_POW_STOP_DEFAULT 4070908800                       //BLOCK
#define SPORK_7_POS_START_DEFAULT 4070908800                      //BLOCK
#define SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT_DEFAULT 4070908800 //OFF
#define SPORK_9_ALERT_TIME_DEFAULT 4070908800                     //OFF
#define SPORK_10_ALERT_BLOCK_DEFAULT 4070908800                   //OFF
#define SPORK_11_F_PAY_DEFAULT 4070908800                         //OFF
#define SPORK_12_NEXXT_DEFAULT 4070908800                         //OFF
#define SPORK_13_MN_F_PAYMENTS_DEFAULT 4070908800                 //OFF
#define SPORK_14_FEE_CHECK_DEFAULT 4070908800                     //OFF
#define SPORK_15_MN_MODE_X_DEFAULT 1000                           //COIN
#define SPORK_16_ZEROCOIN_MAINTENANCE_MODE_DEFAULT 0              //ON
#define SPORK_17_ZEROCOIN_STAKE_DEFAULT 4070908800                //OFF
#define SPORK_18_RECONSIDER_BLOCKS_DEFAULT 0                      //BLOCKS
#define SPORK_19_LYRA_ALGO_DEFAULT 4070908800                     //BLOCKS
#define SPORK_20_ZEROCOIN_START_DEFAULT 4070908800                //BLOCKS


class CSporkMessage;
class CSporkManager;

extern std::map<uint256, CSporkMessage> mapSporks;
extern std::map<int, CSporkMessage> mapSporksActive;
extern CSporkManager sporkManager;

void LoadSporksFromDB();
void ProcessSpork(CNode* pfrom, std::string& strCommand, CDataStream& vRecv);
int64_t GetSporkValue(int nSporkID);
bool IsSporkActive(int nSporkID);
void ReprocessBlocks(int nBlocks);

//
// Spork Class
// Keeps track of all of the network spork settings
//

class CSporkMessage
{
public:
    std::vector<unsigned char> vchSig;
    int nSporkID;
    int64_t nValue;
    int64_t nTimeSigned;

    uint256 GetHash()
    {
        CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
        ss << nSporkID;
        ss << nValue;
        ss << nTimeSigned;
        return ss.GetHash();
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion)
    {
        READWRITE(nSporkID);
        READWRITE(nValue);
        READWRITE(nTimeSigned);
        READWRITE(vchSig);
    }
};


class CSporkManager
{
private:
    std::vector<unsigned char> vchSig;
    std::string strMasterPrivKey;

public:
    CSporkManager()
    {
    }

    std::string GetSporkNameByID(int id);
    int GetSporkIDByName(std::string strName);
    void ExecuteSpork(int nSporkID, int nValue);
    bool UpdateSpork(int nSporkID, int64_t nValue);
    bool SetPrivKey(std::string strPrivKey);
    bool CheckSignature(CSporkMessage& spork, bool fCheckSigner = false);
    bool Sign(CSporkMessage& spork);
    void Relay(CSporkMessage& msg);
};

#endif
