#ifndef BITCOIN_INVALID_OUTPOINTS_JSON_H
#define BITCOIN_INVALID_OUTPOINTS_JSON_H
#include <string>


std::string LoadInvalidOutPoints()
{
    std::string str = "[\n"
                      "  {\n"
                      "    \"txid\": \"000\",\n"
                      "    \"n\": 0\n"
                      "  },\n"
                      "  {\n"
                      "    \"txid\": \"000\",\n"
                      "    \"n\": 0\n"
                      "  }\n"
                      "]";




    return str;
}

#endif //BITCOIN_INVALID_OUTPOINTS_JSON_H
