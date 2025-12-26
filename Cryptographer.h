#ifndef CRYPTOGRAPHER_H
#define CRYPTOGRAPHER_H

#include <cstdint>
#include <vector>
#include <memory>

using Data1 = std::vector<uint8_t>;
using Data2 = std::vector<std::string>;

enum class CryptoType {Dummy, XOR, Caesar};

class ICrypto {
public:
    virtual Data2 encode(const Data1& data) = 0;
    virtual Data1 decode(const Data2& data) = 0;
};

std::shared_ptr<ICrypto> makeCrypto(CryptoType type, const Data1& password);
CryptoType parseCryptoType(const std::string& type);

#endif // CRYPTOGRAPHER_H
