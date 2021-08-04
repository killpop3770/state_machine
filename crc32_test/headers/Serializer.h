//
// Created by 41 on 05.07.2021.
//

#ifndef CRC32_TEST_SERIALIZER_H
#define CRC32_TEST_SERIALIZER_H

#include <utility>
#include "CRC.h"
#include "Archive.h"

class Serializer : public CRC, public Archive<Serializer> {
public:

    template<class T>
    Serializer& operator&(const T& t) {
        if (not m_failed) {
            bool ok = serialize(t) > 0;
            m_failed |= not ok;
        }
        return *this;
    }

    explicit Serializer(char *pBuf, uint16_t size);

    [[nodiscard]] uint16_t size() const;

    [[nodiscard]] bool checkingBufSize(size_t xSize) const;

    size_t serialize(uint8_t x);

    size_t serialize(uint16_t x);

    size_t serialize(uint32_t x);

    size_t serialize(bool k);

    size_t serialize(const char *pStr);

    size_t serialize(const char *pStr, size_t n);

    void reset() override;

    template<class T>
    bool apply(T&& x) {
        return serialize(const_cast<const T&>(x)) > 0;
    }

private:
    char *buf;
    char *ptrForSize;
    const uint16_t sizeOfBuf;
};

#endif //CRC32_TEST_SERIALIZER_H
