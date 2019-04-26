// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_STAKER_H
#define BITCOIN_STAKER_H

#include <stdint.h>

class CBlock;
class CBlockHeader;
class CBlockIndex;
class CReserveKey;
class CScript;
class CWallet;

struct CBlockTemplate;

/** Run the miner threads */
void StakeBCZ(bool fStake_BCZ, CWallet* pwallet, int nThreads);
/** Generate a new block, without valid proof-of-work */
CBlockTemplate* CreateNewPOSBlock(const CScript& scriptPubKeyIn, CWallet* pwallet);
CBlockTemplate* CreateNewPOSBlockWithKey(CReserveKey& reservekey, CWallet* pwallet);
/** Modify the extranonce in a block */
void IncrementExtraNonce2(CBlock* pblock, CBlockIndex* pindexPrev, unsigned int& nExtraNonce);
void POSMiner(CWallet* pwallet, bool fProofOfStake);

#endif // BITCOIN_STAKER_H
