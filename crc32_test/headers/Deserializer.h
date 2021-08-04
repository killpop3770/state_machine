//
// Created by 41 on 05.07.2021.
//

#ifndef CRC32_TEST_DESERIALIZER_H
#define CRC32_TEST_DESERIALIZER_H

#include "CRC.h"
#include "Archive.h"

class Deserializer : public CRC, public Archive<Deserializer> {
public:

//    auto operator&(auto &t) {
//        return deserialize(t);
//    }

//    template<typename T>
//    Deserializer operator<<(T &t) {
//        return *this;
//    }

    template<class T>
    Deserializer& operator&(T& t) {
        if (not m_failed) {
            bool ok = deserialize(&t) > 0;
            m_failed |= not ok;
        }
        return *this;
    }

    explicit Deserializer(char *pBuf, uint16_t size);

    [[nodiscard]] uint16_t size() const;

    [[nodiscard]] bool checkingBufSize(size_t xSize) const;

    size_t deserialize(uint8_t *ptr);

    size_t deserialize(uint16_t *ptr);

    size_t deserialize(uint32_t *ptr);

    size_t deserialize(bool *ptr);

    size_t deserialize(char *pStr, size_t n);

    void reset() override;

protected:
    template<class T>
    bool apply(T &&t) {
        return deserialize(&t) > 0;
    }

private:
    char *buf;
    const char *ptrForSize;
    uint16_t sizeOfBuf;
};

#endif //CRC32_TEST_DESERIALIZER_H
