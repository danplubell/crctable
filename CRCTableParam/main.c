#include <stdio.h>
#include <stdlib.h> 
#include "crcmodel.h"
/******************************************************************************/
/* TABLE PARAMETERS */ /* ================ */ /* The following parameters entirely determine the table to be generated. You */ /*shouldneedtomodifyonlythedefinitionsinthissectionbeforerunning */
/* this program. */
/*
 /* TB_FILE is the name of the output file. */
/* TB_WIDTH is the table width in bytes (either 2 or 4). */
/* TB_POLY is the "polynomial", which must be TB_WIDTH bytes wide. */
/* TB_REVER indicates whether the table is to be reversed (reflected). */
/*
 /* Example: /*
 /* #define TB_FILE
 /* #define TB_WIDTH
 /* #define TB_POLY
 /* #define TB_REVER
 */
*/ */ */
"crctable.out" */ 2 */ 0x8005L */ TRUE */
#defineTB_FILE "crctable.out" #defineTB_WIDTH 4 #defineTB_POLY 0x04C11DB7L #defineTB_REVER TRUE
/******************************************************************************/ /* Miscellaneous definitions. */
#define LOCAL static
FILE *outfile;
#define WR(X) fprintf(outfile,(X)) #define WP(X,Y) fprintf(outfile,(X),(Y))
http://www.zlib.net/crc_v3.txt
30/34
*/
*/
￼1/4/2015 www.zlib.net/crc_v3.txt
/******************************************************************************/
LOCAL void chk_err P_((char *));
LOCAL void chk_err (mess) /*Ifmessisnon-empty,writeitoutandabort.Otherwise,checktheerror */ /* status of outfile and abort if an error has occurred. */ char *mess;
{
    if(mess[0]!=0 ){printf("%s\n",mess);exit(EXIT_FAILURE);}
    if(ferror(outfile)){perror("chk_err"); exit(EXIT_FAILURE);} }
/******************************************************************************/
LOCAL void chkparam P_((void)); LOCAL void chkparam ()
{
    if ((TB_WIDTH != 2) && (TB_WIDTH != 4)) chk_err("chkparam: Width parameter is illegal.");
    if ((TB_WIDTH == 2) && (TB_POLY & 0xFFFF0000L)) chk_err("chkparam: Poly parameter is too wide.");
    if ((TB_REVER != FALSE) && (TB_REVER != TRUE)) chk_err("chkparam: Reverse parameter is not boolean.");
} /******************************************************************************/
LOCAL void gentable P_((void)); LOCAL void gentable ()
{
    WR("/*****************************************************************/\n");
    WR("/*
       WR("/* CRC LOOKUP TABLE
          WR("/* ================
             WR("/* The following CRC lookup table was generated automagically WR("/* by the Rocksoft^tm Model CRC Algorithm Table Generation WR("/* Program V1.0 using the following model parameters:
                                                                                    WR("/*
                                                                                    WP("/* Width :%1lubytes.
                                                                                    (ulong) TB_WIDTH);
                                                                                    if (TB_WIDTH == 2)
                                                                                    WP("/* Poly : 0x%04lX
                                                                                    (ulong) TB_POLY); else
                                                                                    WP("/* Poly : 0x%08lXL (ulong) TB_POLY);
                                                                                    */\n"); */\n"); */\n"); */\n"); */\n"); */\n"); */\n");
       */\n", */\n",
       */\n",
       if (TB_REVER)
       WR("/* Reverse : TRUE.
          else
          WR("/* Reverse : FALSE.
             WR("/*
                WR("/*FormoreinformationontheRocksoft^tmModelCRCAlgorithm,
                   WR("/* see the document titled \"A Painless Guide to CRC Error
                      WR("/* Detection Algorithms\" by Ross Williams WR("/*(ross@guest.adelaide.edu.au.).Thisdocumentislikelytobe
                                                                          WR("/* in the FTP archive \"ftp.adelaide.edu.au/pub/rocksoft\".
                                                                          WR("/* WR("/*****************************************************************/\n"); WR("\n");
                         switch (TB_WIDTH)
                         http://www.zlib.net/crc_v3.txt
                         31/34
                         */\n");
                         */\n");
                         */\n"); */\n");
                      */\n"); */\n");
                   */\n"); */\n"); */\n");
                1/4/2015 www.zlib.net/crc_v3.txt
    {
    case 2: WR("unsigned short crctable[256] =\n{\n"); break; case4:WR("unsignedlong crctable[256]=\n{\n");break; default: chk_err("gentable: TB_WIDTH is invalid.");
    } chk_err("");
    {
        int i;
        cm_t cm;
        char *form
        int perline=(TB_WIDTH==2)?8:4;
        cm.cm_width = TB_WIDTH*8; cm.cm_poly =TB_POLY; cm.cm_refin = TB_REVER;
        for (i=0; i<256; i++) {
            WR(" ");
            WP(form,(ulong) cm_tab(&cm,i));
            if (i != 255) WR(",");
            if (((i+1) % perline) == 0) WR("\n"); chk_err("");
        }
        WR("};\n");
        WR("\n"); WR("/*****************************************************************/\n"); WR("/* End of CRC Lookup Table */\n"); WR("/*****************************************************************/\n"); WR("");
        chk_err("");
    } }
    /******************************************************************************/
                main () {
                    printf("\n");
                    printf("Rocksoft^tm Model CRC Algorithm Table Generation Program V1.0\n"); printf("-------------------------------------------------------------\n"); printf("Output file is \"%s\".\n",TB_FILE);
                    chkparam();
                    outfile = fopen(TB_FILE,"w"); chk_err("");
                    gentable();
                    if (fclose(outfile) != 0)
                        chk_err("main: Couldn't close output file."); printf("\nSUCCESS: The table has been successfully written.\n");
                }
    /******************************************************************************/ /* End of crctable.c */ /******************************************************************************/
