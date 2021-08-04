#include <iostream>
#include <cstring>
#include "../headers/Config.h"

using namespace std;

////////////////////////////////////////////////
////    int x = 258;          // 10111101100  //
////    int a = (x &0xFF);    // 11101100     //
////    int b = (x >> 8);     // 101          //
////    int c = (b << 8);     // 11111010     //
////    int d = a | c;        // 10100000000  //
////////////////////////////////////////////////

//class CRC {
//public:
//    //crc32_table() - function to generate array for tabular calculations.
//    //ATTENTION: This function should call, but only ONCE, before crc32().
//    static void crc32_table() {
//        uint32_t crc;
//        int i, j;
//
//        for (i = 0; i < 256; i++) {
//            crc = i;
//            for (j = 0; j < 8; j++) crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1; //0xEDB88320UL - polynome
//            crc_table[i] = crc;
//        }
//    }
//
//    //crc32() - main function for cyclic redundancy check algorithm(CRC32).
//    static unsigned long crc32(size_t len, char *pBuf) {
//        uint32_t crc = 0xFFFFFFFFUL;
//
//        while (len--) crc = crc_table[(crc ^ *pBuf++) & 0xFF] ^ (crc >> 8);
//
//        return (crc ^ 0xFFFFFFFFUL);
//    }
//
//private:
//    static uint32_t crc_table[256];
//};
//
//uint32_t CRC::crc_table[256] = {};
//
//class Deserializer : public CRC {
//public:
//    explicit Deserializer(char *pBuf, const uint16_t size)
//            : buf(pBuf), ptrForSize(pBuf), sizeOfBuf(size)
//    {
//    }
//
//    [[nodiscard]] auto size() const {
//        return buf - ptrForSize;
//    }
//
//    [[nodiscard]] bool checkingBufSize(size_t xSize) const {
//        return xSize + size() > sizeOfBuf;
//    }
//
//    size_t deserialize(uint8_t *ptr) {
//        size_t size = sizeof(*ptr);
//        if(checkingBufSize(size)) return 0;
//        *ptr = (uint8_t) *buf++;
//        return size;
//    }
//
//    size_t deserialize(uint16_t *ptr) {
//        size_t size = sizeof(*ptr);
//        if(checkingBufSize(size)) return 0;
//        uint16_t a = (uint8_t) *buf++;
//        *ptr = ((uint8_t) *buf++ << 8) | a;
//        return size;
//    }
//
//    size_t deserialize(uint32_t *ptr) {
//        size_t size = sizeof(*ptr);
//        if(checkingBufSize(size)) return 0;
//        uint32_t a = (unsigned char) *buf++;
//        a = ((uint8_t) *buf++ << 8) | a;
//        a = ((uint8_t) *buf++ << 16) | a;
//        *ptr = (uint8_t) *buf++ << 24 | a;
//        return size;
//    }
//
//    size_t deserialize(bool *ptr) {
//        size_t size = sizeof(*ptr);
//        if(checkingBufSize(size)) return 0;
//        *ptr = (bool) buf++;
//        return size;
//    }
//
//    size_t deserialize(char *ptr) {
//        size_t size = sizeof(*ptr);
//        if(checkingBufSize(size)) return 0;
//        //Read 2 bytes from buf -> read next char array:
//        uint16_t len0 = 0;
//        uint16_t *len = &len0;
//        return deserialize(ptr, *len);
//    }
//
//    size_t deserialize(char *pStr, size_t n) {
//        //Writing length of byte-string
//        uint16_t givenLen;
//        this->deserialize(&givenLen);
//        if(checkingBufSize(givenLen)) return 0;
//        if(n == 0) return 0; //can not to count length of data
//
//        //Writing data in NVRAM
//        for (int i = 0; i < givenLen; i++)
//            *buf++ = *pStr++;
//        return givenLen;
//    }
//
////    void reset(){
////        buf = ptrForSize;
////    }
//
//private:
//    char *buf;
//    const char *ptrForSize;
//    const uint16_t sizeOfBuf;
//};
//
//class Serializer : public CRC {
//public:
//
//    explicit Serializer(char *pBuf, const uint16_t size)
//            : buf(pBuf), ptrForSize(pBuf), sizeOfBuf(size)
//    {
//    }
//
//    [[nodiscard]] uint16_t size() const {
//        return buf - ptrForSize;
//    }
//
//    [[nodiscard]] bool checkingBufSize(size_t xSize) const {
//        return xSize + size() > sizeOfBuf;
//    }
//
//    size_t serialize(uint8_t x) {
//        size_t size = sizeof(x);
//        if(checkingBufSize(size)) return 0;
//        *buf++ = (char) x;
//        return size;
//    }
//
//    size_t serialize(uint16_t x) {
//        size_t size = sizeof(x);
//        if(checkingBufSize(size)) return 0;
//        *buf++ = (char) (x & 0xFF);
//        *buf++ = (char) (x >> 8);
//        return size;
//    }
//
//    size_t serialize(uint32_t x) {
//        size_t size = sizeof(x);
//        if(checkingBufSize(size)) return 0;
//        *buf++ = (char) (x & 0xFF);
//        *buf++ = (char) ((x >> 8) & 0xFF);
//        *buf++ = (char) ((x >> 16) & 0xFF);
//        *buf++ = (char) (x >> 24 & 0xFF);
//        return size;
//    }
//
//    size_t serialize(bool x) {
//        size_t size = sizeof(x);
//        if(checkingBufSize(size)) return 0;
//        *buf++ = (char) x;
//        return size;
//    }
//
//    size_t serialize(const char *pStr) {
//        size_t len = strlen(pStr);
//        if(checkingBufSize(len)) return 0;
//        assert(len <= UINT16_MAX);
//        return serialize(pStr, len);
//    }
//
//    size_t serialize(const char *pStr, size_t n) {
//        //Writing length of byte-string
//        assert(n <= UINT16_MAX);
//        this->serialize((uint16_t) n);
//
//        //Writing data in NVRAM
//        for (int i = 0; i < n; i++)
//            *buf++ = *pStr++;
//        return n;
//    }
//
//    void reset(){
//        buf = ptrForSize;
//    }
//
//private:
//    char *buf;
//    char *ptrForSize;
//    const uint16_t sizeOfBuf;
//};
//
//struct Config {
//    uint8_t x{};
//    uint16_t y{};
//    uint32_t z{};
//    bool k{};
//    char m[6] = "hello";
//};
//
//void serialize_Config(Serializer &_ser, const Config &_config) {
//    _ser.serialize(_config.x);
//    _ser.serialize(_config.y);
//    _ser.serialize(_config.z);
//    _ser.serialize(_config.k);
//    _ser.serialize(_config.m);
//}
//
//void deserialize_Config(Deserializer &_des, Config *_pConfig) {
//    _des.deserialize(&_pConfig->x);
//    _des.deserialize(&_pConfig->y);
//    _des.deserialize(&_pConfig->z);
//    _des.deserialize(&_pConfig->k);
//    _des.deserialize(_pConfig->m);
//}
//
//const uint16_t len = 256;
//static char myNVRAM[len];   //ROM
//
//void writeConfig(const Config &cfg) {
//
//    //Local buffer
//    char buf[len];
//
//    //Serialize in buffer
//    Serializer ser0(buf, len);
//    serialize_Config(ser0, cfg);
//
//    //CRC
//    CRC::crc32_table();
//    unsigned long crcHash = CRC::crc32(ser0.size(), buf);
//
//    //Serialize in memory
//    Serializer ser1(myNVRAM, len);
//    ser1.serialize(buf, ser0.size());
//
//    //Additional serialize for crc-hash
//    ser1.serialize((uint32_t) crcHash);
//}
//
//bool readConfig(Config *pCfg) {
//
//    uint16_t sizeOfData;  //size of serialized data
//    uint32_t crcHash0; //crc-hash from serialized data
//
//    //Size of serialized data
//    Deserializer des0(myNVRAM, len); //Des in once
//    des0.deserialize(&sizeOfData);
//
//    //Deserialize crc-hash1 from memory
//    Deserializer des1((myNVRAM + des0.size() + sizeOfData), len);
//    des1.deserialize(&crcHash0);
//
//    //CRC
//    unsigned long crcHash1 = CRC::crc32(sizeOfData, myNVRAM + des0.size());
//
//    //Deserialize only after hash-sum
//    if (crcHash0 == crcHash1) {
//        cout << crcHash0 << " == " << crcHash1 << endl;
//        deserialize_Config(des0, pCfg);
//        return true;
//    } else {
//        cout << crcHash0 << " != " << crcHash1 << endl;
//        return false;
//    }
//}

//auto test(Archive& ar) {
//    uint32_t x = 10;
//    return ar & x;
//}

auto test2(Serializer& ar) {
    uint32_t x = 10;
    return ar & x;
}

int main() {
    Config config{131, 54120, 4000000000, true};
    Config config1{};

    writeConfig(config);
    cout << boolalpha << readConfig(&config1) << endl;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    extern char buf0[len]; // buffer
    KeyBoardConfig keyBCfg{12, 140}; // data struct
    KeyBoardConfig keyBCfg0{};

    Serializer ser(myNVRAM, len); // serializer for data

    volatile bool ok;
//    ok = (bool)test(ser);
    ser.reset();
    ok = (bool)test2(ser);
    ok = not ok;
#if 0
    ConfigSectionDescriptor<KeyBoardConfig>::pack(std::forward<Serializer>(ser), std::forward<KeyBoardConfig>(keyBCfg));

    Deserializer des(myNVRAM, len);
    ConfigSectionDescriptor<KeyBoardConfig>::pack(std::forward<Deserializer>(des), std::forward<KeyBoardConfig>(keyBCfg0));

//    des.deserialize(&keyBCfg0.keyRate);
//    des.deserialize(&keyBCfg0.shutDownTimeOut);

    printf("%d\n", keyBCfg0.keyRate);
    printf("%d\n", keyBCfg0.shutDownTimeOut);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    if (config.x != config1.x)
        cout << "Negative at x position: " << static_cast<int>(config.x) << " != " << static_cast<int>(config1.x)
             << endl;
    else
        cout << "Positive at x position: " << static_cast<int>(config.x) << " == " << static_cast<int>(config1.x)
             << endl;

    if (config.y != config1.y)
        cout << "Negative at y position: " << config.y << " != " << config1.y << endl;
    else
        cout << "Positive at y position: " << static_cast<long>(config.y) << " == " << static_cast<long>(config1.y)
             << endl;

    if (config.z != config1.z)
        cout << "Negative at z position: " << config.z << " != " << config1.z << endl;
    else
        cout << "Positive at z position: " << static_cast<long long>(config.z) << " == "
             << static_cast<long long>(config1.z) << endl;

    if (config.k != config1.k)
        cout << "Negative at k position: " << boolalpha << config.k << " != " << config1.k << endl;
    else
        cout << "Positive at k position: " << boolalpha << (config.k) << " == " << (config1.k) << endl;

    if (strcmp(config.m, config1.m) != 0)
        cout << "Negative at m position: " << config.m << " != " << config1.m << endl;
    else
        cout << "Positive at m position: " << config.m << " == " << config1.m << endl;
#endif
}