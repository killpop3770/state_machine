//
// Created by 41 on 05.07.2021.
//
#include <cstring>
#include <cstdint>
#include "../headers/CRC.h"

    static uint32_t crc_table[256];

    //crc32_table() - function to generate array for tabular calculations.
    //ATTENTION: This function should call, but only ONCE, before crc32().
     void CRC::crc32_table() {
        uint32_t crc;
        int i, j;

        for (i = 0; i < 256; i++) {
            crc = i;
            for (j = 0; j < 8; j++) crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1; //0xEDB88320UL - polynome
            crc_table[i] = crc;
        }
    }

    //crc32() - main function for cyclic redundancy check algorithm(CRC32).
    unsigned long CRC::crc32(size_t len, char *pBuf) {
        uint32_t crc = 0xFFFFFFFFUL;

        while (len--) crc = crc_table[(crc ^ *pBuf++) & 0xFF] ^ (crc >> 8);

        return (crc ^ 0xFFFFFFFFUL);
    }

    uint32_t CRC::crc_table[256] = {};