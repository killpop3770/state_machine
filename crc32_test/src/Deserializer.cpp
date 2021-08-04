//
// Created by 41 on 05.07.2021.
//

#include <cstring>
#include <cstdint>
#include "../headers/CRC.h"
#include "../headers/Deserializer.h"

Deserializer::Deserializer(char *pBuf, const uint16_t size)
        : buf(pBuf), ptrForSize(pBuf), sizeOfBuf(size)
        , Archive()
{
}

[[nodiscard]] uint16_t Deserializer::size() const {
    return buf - ptrForSize;
}

[[nodiscard]] bool Deserializer::checkingBufSize(size_t xSize) const {
    return xSize + size() > sizeOfBuf;
}

size_t Deserializer::deserialize(uint8_t *ptr) {
    size_t size = sizeof(*ptr);
    if(checkingBufSize(size)) return 0;
    *ptr = (uint8_t) *buf++;
    return size;
}

size_t Deserializer::deserialize(uint16_t *ptr) {
    size_t size = sizeof(*ptr);
    if(checkingBufSize(size)) return 0;
    uint16_t a = (uint8_t) *buf++;
    *ptr = ((uint8_t) *buf++ << 8) | a;
    return size;
}

size_t Deserializer::deserialize(uint32_t *ptr) {
    size_t size = sizeof(*ptr);
    if(checkingBufSize(size)) return 0;
    uint32_t a = (unsigned char) *buf++;
    a = ((uint8_t) *buf++ << 8) | a;
    a = ((uint8_t) *buf++ << 16) | a;
    *ptr = (uint8_t) *buf++ << 24 | a;
    return size;
}

size_t Deserializer::deserialize(bool *ptr) {
    size_t size = sizeof(*ptr);
    if(checkingBufSize(size)) return 0;
    *ptr = (bool) *buf++;
    return size;
}

size_t Deserializer::deserialize(char *pStr, size_t n) {
    //Writing length of byte-string
    uint16_t givenLen;
    this->deserialize(&givenLen);
    if(checkingBufSize(givenLen)) return 0;
    if(n == 0) return 0; //can not to count length of data

    //Writing data in NVRAM
    for (int i = 0; i < givenLen; i++)
        *pStr++ = *buf++;
    return givenLen;
}

void Deserializer::reset() {
    Archive::reset();
    // TODO Implement me
        buf = (char *)ptrForSize;
}
