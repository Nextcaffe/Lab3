#include "Cryptographer.h"

#include <stdexcept>
#include <memory>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>


class DummyCrypto: public ICrypto
{
public:
    Data encode(const Data& data) override {
        return data;
    }

    Data decode(const Data& data) override {
        return data;
    }
    ~DummyCrypto() = default;
};

class XORCrypto: public ICrypto
{
private:
    Data password_;
public:
    XORCrypto(const Data& password) {
        password_ = password;
    }
    Data encode(const Data& data) override {
        Data result = data;
        size_t passwordIdx = 0;
        for (size_t i = 0; i < data.size(); i++, passwordIdx = (passwordIdx + 1) % password_.size()) {
            result[i] = result[i] ^ password_[passwordIdx];
        }
        return result;
    }

    Data decode(const Data& data) override {
        Data result = data;
        size_t passwordIdx = 0;
        for (size_t i = 0; i < data.size(); i++, passwordIdx = (passwordIdx + 1) % password_.size()) {
            result[i] = result[i] ^ password_[passwordIdx];
        }
        return result;
    }
    ~XORCrypto() = default;
};


class CaesarCrypto: public ICrypto
{
private:
    uint8_t password_;
public:
    CaesarCrypto(const Data& password) {
        password_ = 0;
        for (size_t i = 0; i < password.size(); i++) {
            password_ += password[i];
        }
    }
    Data encode(const Data& data) override {
        Data result = data;
        for (size_t i = 0; i < data.size(); i++) {
            result[i] = result[i] + password_; 
        }
        return result;
    }

    Data decode(const Data& data) override {
        Data result = data;
        for (size_t i = 0; i < data.size(); i++) {
            result[i] = result[i] - password_; 
        }
        return result;
    }
    ~CaesarCrypto() = default;
};

class SegmentCrypto: public ICrypto
{
private:
    uint8_t password_;
public:
    SegmentCrypto(const Data& password) {
        password_ = 0;
        for (size_t i = 0; i < password.size(); i++) {
            password_ += password[i];
        }
        password_ = password_ % 12;
    }
    Data encode(const Data& data) override {
        Data result = data;
        for (size_t segment = 0; password_ * segment < data.size(); segment++) {
            size_t length = password_;
            if (segment * password_ + length > data.size()) {
                length = data.size() - segment * password_;
            }
            for (size_t i = 0; i < length/2; i++) {
                uint8_t tmp = result[i + segment * password_];
                result[segment * password_ + i] = result[segment * password_ + (length - i - 1)]; 
                result[segment * password_ + (length - i - 1)] = tmp; 
            }
        }
        return result;
    }

    Data decode(const Data& data) override {
        Data result = data;
        for (size_t segment = 0; password_ * segment < data.size(); segment++) {
            size_t length = password_;
            if (segment * password_ + length > data.size()) {
                length = data.size() - segment * password_;
            }
            for (size_t i = 0; i < length/2; i++) {
                uint8_t tmp = result[i + segment * password_];
                result[segment * password_ + i] = result[segment * password_ + (length - i - 1)]; 
                result[segment * password_ + (length - i - 1)] = tmp; 
            }
        }
        return result;
    }
    ~SegmentCrypto() = default;
};

template <typename Crypto1, typename Cryto2>
class CombinedCrypto: public ICrypto
{
private:
    Crypto1 crypto1_;
    Cryto2 crypto2_;

public:
    CombinedCrypto(const Data& password) 
        : crypto1_(password)
        , crypto2_(password)
    {}
    Data encode(const Data& data) override {
        Data intermediate_data = crypto1_.encode(data);
        Data result = crypto2_.encode(intermediate_data);
        return result;
    }

    Data decode(const Data& data) override {
        Data intermediate_data = crypto2_.decode(data);
        Data result = crypto1_.decode(intermediate_data);
        return result;
    }
    ~CombinedCrypto() = default;
};


std::shared_ptr<ICrypto> makeCrypto(CryptoType type, const Data& password) {
    switch (type) {
    case CryptoType::Dummy:
        return std::make_shared<DummyCrypto>();
    case CryptoType::XOR:
        return std::make_shared<XORCrypto>(password);
    case CryptoType::Caesar:
        return std::make_shared<CaesarCrypto>(password);
    case CryptoType::Segment:
        return std::make_shared<SegmentCrypto>(password);
    case CryptoType::XOR_Segment:
        return std::make_shared<CombinedCrypto <XORCrypto, SegmentCrypto>>(password);
    case CryptoType::Caesarm_Segment:
        return std::make_shared<CombinedCrypto <CaesarCrypto, SegmentCrypto>>(password);
    }
    throw std::runtime_error("Unknown crypto type");
}

CryptoType parseCryptoType(const std::string& type) {
    if (type == "dummy") {
        return CryptoType::Dummy;
    } else if (type == "xor") {
        return CryptoType::XOR;
    } else if (type == "caesar") {
        return CryptoType::Caesar;
    } else if (type == "segment") {
        return CryptoType::Segment;
    } else if (type == "xor+segment") {
        return CryptoType::XOR_Segment;
    } else if (type == "caesar+segment") {
        return CryptoType::Caesarm_Segment;
    }
    throw std::runtime_error("Unknown crypto type: " + type);
}