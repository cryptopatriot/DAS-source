// Copyright (c) 2014-2016 The Das Core developers

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef MASTERNODE_SYNC_H
#define MASTERNODE_SYNC_H

#define MASTERNODE_SYNC_INITIAL           0
#define MASTERNODE_SYNC_SPORKS            1
#define MASTERNODE_SYNC_LIST              2
#define MASTERNODE_SYNC_MNW               3
#define MASTERNODE_SYNC_GOVERNANCE        4
#define MASTERNODE_SYNC_GOVOBJ            10
#define MASTERNODE_SYNC_GOVERNANCE_FIN    11
#define MASTERNODE_SYNC_FAILED            998
#define MASTERNODE_SYNC_FINISHED          999

#define MASTERNODE_SYNC_TIMEOUT           30 // our blocks are 2.5 minutes so 30 seconds should be fine

class CMasternodeSync;
extern CMasternodeSync masternodeSync;

//
// CMasternodeSync : Sync masternode assets in stages
//

class CMasternodeSync
{
public:
    std::map<uint256, int> mapSeenSyncMNB;
    std::map<uint256, int> mapSeenSyncMNW;
    std::map<uint256, int> mapSeenSyncBudget;

    int64_t lastMasternodeList;
    int64_t lastMasternodeWinner;
    int64_t lastBudgetItem;
    int64_t lastFailure;
    int nCountFailures;

    // sum of all counts
    int sumMasternodeList;
    int sumMasternodeWinner;
    int sumBudgetItemProp;
    int sumBudgetItemFin;
    // peers that reported counts
    int countMasternodeList;
    int countMasternodeWinner;
    int countBudgetItemProp;
    int countBudgetItemFin;

    // Count peers we've requested the list from
    int RequestedMasternodeAssets;
    int RequestedMasternodeAttempt;

    // Time when current masternode asset sync started
    int64_t nAssetSyncStarted;

    // Keep track of current block index
    const CBlockIndex *pCurrentBlockIndex;

    CMasternodeSync();

    void AddedMasternodeList(uint256 hash);
    void AddedMasternodeWinner(uint256 hash);
    void AddedBudgetItem(uint256 hash);
    void GetNextAsset();
    std::string GetAssetName();
    std::string GetSyncStatus();
    void ProcessMessage(CNode* pfrom, std::string& strCommand, CDataStream& vRecv);
    bool IsBudgetFinEmpty();
    bool IsBudgetPropEmpty();

    void Reset();
    void Process();
    bool IsSynced();
    bool IsBlockchainSynced();
    void ClearFulfilledRequest();

    void UpdatedBlockTip(const CBlockIndex *pindex);
};

#endif
