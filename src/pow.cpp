// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pow.h"
#include "chain.h"
#include "chainparams.h"
#include "main.h"
#include "primitives/block.h"
#include "uint256.h"
#include "util.h"
#include "spork.h"
#include <math.h>

unsigned int static DarkGravityWave3(const CBlockIndex* pindexLast) {

   int64_t nPastBlocks = 24;
   const CBlockIndex *pindex = pindexLast;
   uint256 bnPastTargetAvg;
   for (unsigned int nCountBlocks = 1; nCountBlocks <= nPastBlocks; nCountBlocks++) {
       uint256 bnTarget = uint256().SetCompact(pindex->nBits);
       if (nCountBlocks == 1) {
           bnPastTargetAvg = bnTarget;
       } else {
           bnPastTargetAvg = (bnPastTargetAvg * nCountBlocks + bnTarget) / (nCountBlocks + 1);
       }

       if(nCountBlocks != nPastBlocks) {
           assert(pindex->pprev);
           pindex = pindex->pprev;
       }
   }

   uint256 bnNew(bnPastTargetAvg);
   int64_t nActualTimespan = pindexLast->GetBlockTime() - pindex->GetBlockTime();
   int64_t nTargetTimespan = nPastBlocks * 150;
   if (nActualTimespan < nTargetTimespan/1.5)
       nActualTimespan = nTargetTimespan/1.5;
   if (nActualTimespan > nTargetTimespan*1.5)
       nActualTimespan = nTargetTimespan*1.5;

   bnNew *= nActualTimespan;
   bnNew /= nTargetTimespan;

   if (bnNew > Params().powLimit()) {
       bnNew = Params().powLimit();
   }

   return bnNew.GetCompact();
}

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast)
{
   if (pindexLast->nHeight > forkend)
   {
       return DarkGravityWave3(pindexLast);
   }
   else
   {
       return Params().powLimit().GetCompact();
   }
}

unsigned int NexxtD(const CBlockIndex* pindexPrev, const CBlockHeader* pblock)
{
   if (IsSporkActive(SPORK_12_NEXXT) && pindexPrev->nHeight > forkend)
   {
       return NexxtDG(pindexPrev, pblock);
   }
   else
   {
       return GetNextWorkRequired(pindexPrev);
   }
}

unsigned int NexxtDG(const CBlockIndex* pindexLast, const CBlockHeader *pblock)
{
   int64_t nPastBlocks = 24;
   const CBlockIndex *pindex = pindexLast;
   uint256 bnPastTargetAvg;
   for (unsigned int nCountBlocks = 1; nCountBlocks <= nPastBlocks; nCountBlocks++) {
       uint256 bnTarget = uint256().SetCompact(pindex->nBits);
       if (nCountBlocks == 1) {
           bnPastTargetAvg = bnTarget;
       } else {
           bnPastTargetAvg = (bnPastTargetAvg * nCountBlocks + bnTarget) / (nCountBlocks + 1);
       }

       if(nCountBlocks != nPastBlocks) {
           assert(pindex->pprev);
           pindex = pindex->pprev;
       }
   }

   uint256 bnNew(bnPastTargetAvg);
   int64_t nActualTimespan = pindexLast->GetBlockTime() - pindex->GetBlockTime();
   int64_t nTargetTimespan = nPastBlocks * Nexxt(pindexLast, pblock);

   bnNew *= nActualTimespan;
   bnNew /= nTargetTimespan;

   if (bnNew > Params().powLimit()) {
       bnNew = Params().powLimit();
   }

   return bnNew.GetCompact();
}

int64_t Nexxt(const CBlockIndex* pindexPrev, const CBlockHeader* pblock)
{
       if      (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (60 * 60) + 0)) {
           return 1; }

       else if (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (55 * 60) + 0)) {
           return 2; }

       else if (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (50 * 60) + 0)) {
           return 4; }

       else if (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (45 * 60) + 0)) {
           return 6; }

       else if (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (40 * 60) + 0)) {
           return 8; }

       else if (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (35 * 60) + 0)) {
           return 12; }

       else if (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (30 * 60) + 0)) {
           return 18; }

       else if (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (25 * 60) + 0)) {
           return 27; }

       else if (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (20 * 60) + 0)) {
           return 41; }

       else if (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (15 * 60) + 0)) {
           return 62; }

       else if (pblock->GetBlockTime() > (pindexPrev->GetBlockTime() + (10 * 60) + 0)) {
           return 106; }

       else {
           return 150; }
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits)
{
   bool fNegative;
   bool fOverflow;
   uint256 bnTarget;

   if (Params().SkipProofOfWorkCheck())
       return true;

   bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

   // Check range
   if (fNegative || bnTarget == 0 || fOverflow || bnTarget > Params().powLimit())
       return error("CheckProofOfWork() : nBits below minimum work");

   // Check proof of work matches claimed amount
   if (hash > bnTarget)
       return error("CheckProofOfWork() : hash doesn't match nBits");

   return true;
}

uint256 GetBlockProof(const CBlockIndex& block)
{
   uint256 bnTarget;
   bool fNegative;
   bool fOverflow;
   bnTarget.SetCompact(block.nBits, &fNegative, &fOverflow);
   if (fNegative || fOverflow || bnTarget == 0)
       return 0;
   // We need to compute 2**256 / (bnTarget+1), but we can't represent 2**256
   // as it's too large for a uint256. However, as 2**256 is at least as large
   // as bnTarget+1, it is equal to ((2**256 - bnTarget - 1) / (bnTarget+1)) + 1,
   // or ~bnTarget / (nTarget+1) + 1.
   return (~bnTarget / (bnTarget + 1)) + 1;
}
