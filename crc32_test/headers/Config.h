//
// Created by 41 on 05.07.2021.
//

#ifndef CRC32_TEST_CONFIG_H
#define CRC32_TEST_CONFIG_H

#include <iostream>
#include "Serializer.h"
#include "Deserializer.h"

const uint16_t len = 256;
extern char myNVRAM[len];   //ROM
inline const uint32_t magic = 0x636F6E66; //preambula

/// Base
template<typename Type>
struct ConfigSectionDescriptor {
    static constexpr uint8_t code = 0;

    template<class Archive>
    static constexpr auto pack(Archive &&ar, Type &&x) {
        return ar & x;
    }
};

struct KeyBoardConfig {
    uint8_t keyRate;
    uint16_t shutDownTimeOut;
};

/// ConfigSectionDescriptor<KeyBoardConfig> specialization.
template<>
struct ConfigSectionDescriptor<KeyBoardConfig> {
    static constexpr uint8_t code = 1;

    template<class Archive>
    static constexpr auto pack(Archive &&ar, KeyBoardConfig &x) {
        return ar & x.keyRate & x.shutDownTimeOut;
    }
};


struct UserConfig {
    uint32_t pincode;
    uint8_t key[32];
};

/// ConfigSectionDescriptor<UserConfig> specialization.
template<>
struct ConfigSectionDescriptor<UserConfig> {
    static constexpr uint8_t code = 1;

    template<class Archive>
    static constexpr auto pack(Archive &&ar, UserConfig &x) {
        return ar & x.pincode & x.key;
    }
};

struct TestConfig {
    //
};

struct Config {
    uint8_t x{};
    uint16_t y{};
    uint32_t z{};
    bool k{};
    char m[6] = "hello";
};

bool serialize_Config(Serializer &_ser, const Config &_config);

bool deserialize_Config(Deserializer &_des, Config *_pConfig);

void writeConfig(const Config &cfg);

bool readConfig(Config *pCfg);

void harmToBit();

#endif //CRC32_TEST_CONFIG_H
