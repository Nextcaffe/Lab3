#ifndef CRYPTOGRAPHER_H
#define CRYPTOGRAPHER_H

#include <cstdint>
#include <vector>
#include <memory>

using Data = std::vector<uint8_t>;

enum class CryptoType {Dummy, XOR, Caesar, Segment, XOR_Segment, Caesarm_Segment};

class ICrypto {
public:
    virtual Data encode(const Data& data) = 0;
    virtual Data decode(const Data& data) = 0;
    virtual ~ICrypto() = default;
};

std::shared_ptr<ICrypto> makeCrypto(CryptoType type, const Data& password);
CryptoType parseCryptoType(const std::string& type);

#endif // CRYPTOGRAPHER_H