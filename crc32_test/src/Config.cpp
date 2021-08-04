//
// Created by 41 on 05.07.2021.
//

#include <cstdint>
#include "../headers/Config.h"

char myNVRAM[len];// ROM

bool serialize_Config(Serializer &_ser, const Config &_config) {
    return (_ser.serialize(_config.x) and
            _ser.serialize(_config.y) and
            _ser.serialize(_config.z) and
            _ser.serialize(_config.k) and
            _ser.serialize(_config.m, sizeof(_config.m)));
}

bool deserialize_Config(Deserializer &_des, Config *_pConfig) {
    return (_des.deserialize(&_pConfig->x) and
            _des.deserialize(&_pConfig->y) and
            _des.deserialize(&_pConfig->z) and
            _des.deserialize(&_pConfig->k) and
            _des.deserialize(_pConfig->m, sizeof(_pConfig->m)));
}

void writeConfig(const Config &cfg) {

    //package <- preambula + length + data + crc

    //Local buffer
    char buf[len];

    //Serialize in buffer
    Serializer ser0(buf, len);
    serialize_Config(ser0, cfg);

    //CRC
    CRC::crc32_table();
    unsigned long crcHash = CRC::crc32(ser0.size(), buf);

    //Serialize in memory
    Serializer ser1(myNVRAM, len);
    ser1.serialize((uint32_t)magic);
    ser1.serialize(buf, ser0.size());

    //Additional serialize for crc-hash
    ser1.serialize((uint32_t)crcHash);
}

bool readConfig(Config *pCfg) {

    uint16_t sizeOfData;  //size of serialized data
    uint32_t crcHash0; //crc-hash from serialized data
    uint32_t magic0; //preambula

    //Size of serialized data
    Deserializer des0(myNVRAM, len);
    des0.deserialize(&magic0);
    des0.deserialize(&sizeOfData);

    //Deserialize crc-hash1 from memory
    Deserializer des1((myNVRAM + des0.size() + sizeOfData), len);
    des1.deserialize(&crcHash0);

    //CRC
    unsigned long crcHash1 = CRC::crc32(sizeOfData, myNVRAM + des0.size());

    //Deserialize only after hash-sum
    if (crcHash0 == crcHash1) {
//        std::cout << "CRC-Hash: " << crcHash0 << " == " << crcHash1 << std::endl;
        deserialize_Config(des0, pCfg);
        return true;
    } else {
//        std::cout << "CRC-Hash: " << crcHash0 << " != " << crcHash1 << std::endl;
        return false;
    }
}

//This function only for test
void harmToBit() {
    myNVRAM[5] = '0';
}