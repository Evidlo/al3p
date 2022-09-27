#ifndef AL3P_H_
#define AL3P_H_

#include "jabplc.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define mask(n) ((1u<<n) - 1)

#define errcheck(func, error) {\
    if (error != JABPLC_SUCCESS) {\
        fprintf(stderr, "%s : Failed : Unable to pack due to error code %u\n", func, error);\
        exit(1);\
    }\
}

typedef enum {
    AL3P_SUCCESS,
} al3p_error_t;

typedef struct {
    // split member
    bool sm;
    // protocol character
    uint8_t pchar;
    // length field present
    bool lfp;
    // control character
    uint8_t cchar;
    // sequence number
    uint16_t seq;
    // split packet sequence number
    uint8_t ssq;
    // total field
    uint8_t tot;
    // length field
    uint32_t lf;
    // payload
    uint8_t* pl[];
} thin_t;

uint32_t len_thin(thin_t packet);

al3p_error_t pack_thin(uint8_t* buff, uint32_t size, thin_t packet);



#endif // BITCRAM_H_
