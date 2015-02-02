//
//  main.c
//  CRC Table
//
//  Created by Plubell,Dan on 1/9/15.
//  Copyright (c) 2015 Plubell,Dan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned short crctab[256];/* The CRC lookup table */

#define GENERATE_POLYNOMIAL 0x1021/* The CCITT polynomial */

static unsigned short crchware ( unsigned short data,unsigned short poly,unsigned short accum)
{
    int i;
    data <<= 8;
    for (i=8; i>0; i--)
    {
        if ((data ^ accum) & 0x8000){ /* if msb of (data XOR accum) is TRUE*/
            accum = (accum << 1) ^ poly; /* shift and subtract poly */
            
        }
        else
            accum <<= 1; /* otherwise, transparent shift */
        data <<= 1; /* move up next bit for XOR */ }
    return accum;
}
void crcupdate ( unsigned short data, unsigned short *accum ) {
    *accum = (*accum << 8) ^ crctab[(*accum >> 8) ^ data];

}
void mk_crctbl ( void ) {
    unsigned short i;
    for (i=0; i<256; ++i) {
        /* Fill the table with CRCs of values .... */
        crctab[i] = crchware ( i, GENERATE_POLYNOMIAL, 0 );
        printf("tableEntry: %d\n",crctab[i]);
    }
}

static void testcrc(void){
    unsigned short crc = 0;
    char *message= "Check this message!";
    
    mk_crctbl();
    
    for(int i = 0; i < strlen(message);i++){
        crcupdate(message[i],&crc);
    }
    printf ("Message=<%s>, CRC=%04x\n",message,crc);
    
}
int main(int argc, const char * argv[]) {
    testcrc();
    return 0;
}
