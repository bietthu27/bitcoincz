
#ifndef BITCOIN_MASTERNODE_UTIL_H
#define BITCOIN_MASTERNODE_UTIL_H

#include "wallet.h"

std::string makeGenkey();

void writeConfFile(std::string _line);

std::string getConfParam(std::string _arg);

CBitcoinAddress GetAccountAddressForMasternode( std::string  strAccount, bool bForceNew=false);

void writeMasternodeConfFile(std::string  _alias, std::string  _ipport,std::string  mnprivkey,std::string  _output,std::string  _index);

void writeMasternodeConfInfo(std::string  mnGenkey, std::string  strIpPort);

std::vector<std::pair<std::string ,std::string >> checkMasternodeOutputs();

void cleanConf();

void RemoveMasternodeConfigs();

#endif // BITCOIN_MASTERNODE_UTIL_H
