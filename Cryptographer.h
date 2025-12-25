#ifndef CRYPTOGRAPHER_H
#define CRYPTOGRAPHER_H

#include <cstdint>
#include <vector>
#include <memory>

using Data = std::vector<uint8_t>;

enum class CryptoType {Dummy, XOR};

class ICrypto {
public:
    virtual Data encode(const Data& data) = 0;
    virtual Data decode(const Data& data) = 0;
};

CryptoType parseCryptoType(const std::string& type);
std::shared_ptr<ICrypto> makeCrypto(CryptoType type, const Data& password);


#endif // CRYPTOGRAPHER_H
