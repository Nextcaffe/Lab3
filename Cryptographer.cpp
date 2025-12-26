#include "Cryptographer.h"

#include <stdexcept>
#include <memory>
#include <cstdint>
#include <string>
#include <vector>
#include <cmath>

std::string uint8_to_hex(uint8_t x) {
    Data2 hex = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    std::string new_x;
    new_x = hex[x/16] + hex[x%16];
    return new_x;
}

Data2 vector_uint8_to_hex(const Data1& data) {
    Data2 new_data;
    for (size_t i = 0; i < data.size(); i++) {
        new_data.push_back(uint8_to_hex(data[i]));
    }
    return new_data;
}

uint8_t hex_to_uint8(std::string x) {
    uint8_t new_x = 0;
    for (int i = 0; i < 2; i++) {
        uint8_t tmp = x[i];
        if (tmp >= 'A') {
            tmp -= 'A';
            tmp += 10;
        } else {
            tmp -= '0';
        }
        new_x += pow(16, (1-i)) * tmp;
    }
    return new_x;
}

Data1 hex_to_vector_uint8(const Data2& data) {
    Data1 new_data;
    for (size_t i = 0; i < data.size(); i++) {
        new_data.push_back(hex_to_uint8(data[i]));
    }
    return new_data;
}


class DummyCrypto: public ICrypto
{
public:
    Data2 encode(const Data1& data) override {
        Data2 new_data = vector_uint8_to_hex(data);
        return new_data;
    }

    Data1 decode(const Data2& data) override {
        Data1 new_data = hex_to_vector_uint8(data);
        return new_data;
    }
};

class XORCrypto: public ICrypto
{
private:
    Data1 password_;
public:
    XORCrypto(const Data1& password) {
        password_ = password;
    }
    Data2 encode(const Data1& data) override {
        Data1 result = data;
        size_t passwordIdx = 0;
        for (size_t i = 0; i < data.size(); i++, passwordIdx = (passwordIdx + 1) % password_.size()) {
            result[i] = result[i] ^ password_[passwordIdx];
        }
        Data2 new_result = vector_uint8_to_hex(result);
        return new_result;
    }

    Data1 decode(const Data2& data) override {
        Data1 new_data = hex_to_vector_uint8(data);
        Data1 result = new_data;
        size_t passwordIdx = 0;
        for (size_t i = 0; i < data.size(); i++, passwordIdx = (passwordIdx + 1) % password_.size()) {
            result[i] = result[i] ^ password_[passwordIdx];
        }
        return result;
    }
};


class CaesarCrypto: public ICrypto
{
private:
    uint8_t password_;
public:
    CaesarCrypto(const Data1& password) {
        password_ = 0;
        for (size_t i = 0; i < password.size(); i++) {
            password_ += password[i];
        }
    }
    Data2 encode(const Data1& data) override {
        Data1 result = data;
        for (size_t i = 0; i < data.size(); i++) {
            result[i] = data[i] + password_; 
        }
        Data2 new_result = vector_uint8_to_hex(result);
        return new_result;
    }

    Data1 decode(const Data2& data) override {
        Data1 new_data = hex_to_vector_uint8(data);
        Data1 result = new_data;
        for (size_t i = 0; i < data.size(); i++) {
            result[i] = new_data[i] - password_; 
        }
        return result;
    }
};


std::shared_ptr<ICrypto> makeCrypto(CryptoType type, const Data1& password) {
    switch (type) {
    case CryptoType::Dummy:
        return std::make_shared<DummyCrypto>();
    case CryptoType::XOR:
        return std::make_shared<XORCrypto>(password);
    case CryptoType::Caesar:
        return std::make_shared<CaesarCrypto>(password);
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
    }
    throw std::runtime_error("Unknown crypto type: " + type);
}
