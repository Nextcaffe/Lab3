#include "Cryptographer.h"

#include <stdexcept>
#include <memory>
#include <cstdint>
#include <vector>

class DummyCrypto: public ICrypto
{
public:
    Data encode(const Data& data) override {
        return data;
    }

    Data decode(const Data& data) override {
        return data;
    }
};

class XORCrypto: public ICrypto
{
private:
    Data password_;
public:
    XORCrypto(const Data& password)
        : password_(password)
    {}
    Data encode(const Data& data) override {
        Data result = data;
        size_t passwordIdx = 0;
        for (size_t i = 0; i < data.size(); i++, passwordIdx = (passwordIdx + 1) % password_.size()) {
            result[i] ^= password_[passwordIdx];
        }
        return result;
    }

    Data decode(const Data& data) override {
        return encode(data);
    }
};

std::shared_ptr<ICrypto> makeCrypto(CryptoType type, const Data& password) {
    switch (type) {
    case CryptoType::Dummy:
        return std::make_shared<DummyCrypto>();
    case CryptoType::XOR:
        return std::make_shared<XORCrypto>(password);
    }
    throw std::runtime_error("Unknown crypto type");
}

CryptoType parseCryptoType(const std::string& type) {
    if (type == "dummy") {
        return CryptoType::Dummy;
    } else if (type == "xor") {
        return CryptoType::XOR;
    }
    throw std::runtime_error("Unknown crypto type: " + type);
}