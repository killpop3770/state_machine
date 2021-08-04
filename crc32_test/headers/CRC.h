//
// Created by 41 on 05.07.2021.
//

#ifndef CRC32_TEST_CRC_H
#define CRC32_TEST_CRC_H

class CRC {
public:
    //crc32_table() - function to generate array for tabular calculations.
    //ATTENTION: This function should call, but only ONCE, before crc32().
    static void crc32_table();

    //crc32() - main function for cyclic redundancy check algorithm(CRC32).
    static unsigned long crc32(size_t len, char *pBuf);

private:
    static uint32_t crc_table[256];
};

#endif //CRC32_TEST_CRC_H
