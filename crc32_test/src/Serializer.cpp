//
// Created by 41 on 05.07.2021.
//

#include <cstring>
#include <cstdint>
#include <cassert>
#include <iostream>
#include "../headers/CRC.h"
#include "../headers/Serializer.h"

    Serializer::Serializer(char *pBuf, const uint16_t size)
            : buf(pBuf), ptrForSize(pBuf), sizeOfBuf(size)
    {
    }

    [[nodiscard]] uint16_t Serializer::size() const {
        return buf - ptrForSize;
    }

    [[nodiscard]] bool Serializer::checkingBufSize(size_t xSize) const {
        return xSize + size() > sizeOfBuf;
    }

    size_t Serializer::serialize(uint8_t x) {
        size_t size = sizeof(x);
        if(checkingBufSize(size)) return 0;
        *buf++ = (char) x;
        return size;
    }

    size_t Serializer::serialize(uint16_t x) {
        size_t size = sizeof(x);
        if(checkingBufSize(size)) return 0;
        *buf++ = (char) (x & 0xFF);
        *buf++ = (char) (x >> 8);
        return size;
    }

    size_t Serializer::serialize(uint32_t x) {
        size_t size = sizeof(x);
        if(checkingBufSize(size)) return 0;
        *buf++ = (char) (x & 0xFF);
        *buf++ = (char) ((x >> 8) & 0xFF);
        *buf++ = (char) ((x >> 16) & 0xFF);
        *buf++ = (char) (x >> 24 & 0xFF);
        return size;
    }

    size_t Serializer::serialize(bool x) {
        size_t size = sizeof(x);
        if(checkingBufSize(size)) return 0;
        *buf++ = (char) x;
        return size;
    }

    size_t Serializer::serialize(const char *pStr) {
        size_t len = strlen(pStr);
        if(checkingBufSize(len)) return 0;
        assert(len <= UINT16_MAX);
        return serialize(pStr, len);
    }

    size_t Serializer::serialize(const char *pStr, size_t n) {
        //Writing length of byte-string
        assert(n <= UINT16_MAX);
        this->serialize((uint16_t) n);

        //Writing data in NVRAM
        for (int i = 0; i < n; i++)
            *buf++ = *pStr++;
        return n;
    }

    void Serializer::reset() {
        Archive::reset();
        buf = (char *)ptrForSize;
    }