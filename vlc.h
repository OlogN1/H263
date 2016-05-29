#ifndef CODEC_VLC_H
#define CODEC_VLC_H

/************************************************************************
 *
 *  vlc.h, VLC tables for tmn (TMN encoder) 
 *
 *  Copyright (C) 1997  University of BC, Canada
 *
 *  Contacts: 
 *  Michael Gallant                   <mikeg@ee.ubc.ca>
 *  Guy Cote                          <guyc@ee.ubc.ca>
 *  Berna Erol                        <bernae@ee.ubc.ca>
 *
 *  UBC Image Processing Laboratory   http://www.ee.ubc.ca/image
 *  2356 Main Mall                    tel.: +1 604 822 4051
 *  Vancouver BC Canada V6T1Z4        fax.: +1 604 822 5949
 *
 *  Copyright (C) 1995, 1996  Telenor R&D, Norway
 *  
 *  Contacts: 
 *  Robert Danielsen                  <Robert.Danielsen@nta.no>
 *
 *  Telenor Research and Development  http://www.nta.no/brukere/DVC/
 *  P.O.Box 83                        tel.:   +47 63 84 84 00
 *  N-2007 Kjeller, Norway            fax.:   +47 63 81 00 76
 *
 ************************************************************************/

/*
 * Disclaimer of Warranty
 *
 * These software programs are available to the user without any
 * license fee or royalty on an "as is" basis. The University of
 * British Columbia disclaims any and all warranties, whether
 * express, implied, or statuary, including any implied warranties
 * or merchantability or of fitness for a particular purpose.  In no
 * event shall the copyright-holder be liable for any incidental,
 * punitive, or consequential damages of any kind whatsoever arising
 * from the use of these programs.
 *
 * This disclaimer of warranty extends to the user of these programs
 * and user's customers, employees, agents, transferees, successors,
 * and assigns.
 *
 * The University of British Columbia does not represent or warrant
 * that the programs furnished hereunder are free of infringement of
 * any third-party patents.
 *
 * Commercial implementations of H.263, including shareware, are
 * subject to royalty fees to patent holders.  Many of these patents
 * are general enough such that they are unavoidable regardless of
 * implementation design.
 *
*/


/************************************************************************
 *        
 *  Author:	Robert.Danielsen@nta.no
 *  Date:	06.05.96
 *
 *  Comment:	struct idea from MPEG-2 Simulation Software Group.
 *        
 ************************************************************************/

/* type definitions for variable length code table entries */

typedef struct
{
  unsigned int code; /* right justified */
  int len;
} VLCtable;

typedef struct {
  int val, len;
} VLCtab;



/* CBPY. Straightforward indexing */

static const VLCtable cbpy_tab[16] =
{
  {3,4}, {5,5}, {4,5}, {9,4}, {3,5}, {7,4}, {2,6}, {11,4},
  {2,5}, {3,6}, {5,4}, {10,4}, {4,4}, {8,4}, {6,4}, {3,2}
};

/* Motion vectors */

static const VLCtable mvtab[33] =
{
  {1,1}, {1,2}, {1,3}, {1,4}, {3,6}, {5,7}, {4,7}, {3,7},
  {11,9}, {10,9}, {9,9}, {17,10}, {16,10}, {15,10}, {14,10}, {13,10},
  {12,10}, {11,10}, {10,10}, {9,10}, {8,10}, {7,10}, {6,10}, {5,10},
  {4,10}, {7,11}, {6,11}, {5,11}, {4,11}, {3,11}, {2,11}, {3,12},
  {2,12}
};

/* CBPCM (MCBPC) Indexing by cbpc in first two bits, mode in last two.
 CBPC as in table 4/H.263, MACROBLOCK type (mode): 3 = 01, 4 = 10.
 Example: +c = 01 and mode = 4 gives index = 0110 = 6. */

static const VLCtable cbpcm_intra_tab[15] =
{
  {0x01,9}, {0x01,1}, {0x01,4}, {0x00,0},
  {0x00,0}, {0x01,3}, {0x01,6}, {0x00,0},
  {0x00,0}, {0x02,3}, {0x02,6}, {0x00,0},
  {0x00,0}, {0x03,3}, {0x03,6}
};


/* CBPCM inter.
   Addressing: 5 bit ccmmm (cc = CBPC, mmm = mode (1-5 binary)) */
/* 230897 added codes for new INTER4C_Q MACROBLOCK type */
static const VLCtable cbpcm_inter_tab[32] =
{
  {1,1}, {3,3}, {2,3}, {3,5}, {4,6}, {2,11}, {0,0}, {0,0},
  {3,4}, {7,7}, {5,7}, {4,8}, {4,9}, {12,13}, {0,0}, {0,0},
  {2,4}, {6,7}, {4,7}, {3,8}, {3,9}, {14,13}, {0,0}, {0,0},
  {5,6}, {5,9}, {5,8}, {3,7}, {2,9}, {15,13}, {0,0}, {0,0}
};


/* DCT coefficients. Four tables, two for last = 0, two for last = 1.
   the sign bit must be added afterwards. */

#define ESCAPE                          3

/* first part of coeffs for last = 0. Indexed by [run][level-1] */

static const VLCtable coeff_tab0[2][12] =
{
  /* run = 0 */
  {
    {0x02, 2}, {0x0f, 4}, {0x15, 6}, {0x17, 7},
    {0x1f, 8}, {0x25, 9}, {0x24, 9}, {0x21,10},
    {0x20,10}, {0x07,11}, {0x06,11}, {0x20,11}
  },
  /* run = 1 */
  {
    {0x06, 3}, {0x14, 6}, {0x1e, 8}, {0x0f,10},
    {0x21,11}, {0x50,12}, {0x00, 0}, {0x00, 0},
    {0x00, 0}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  }
};

/* rest of coeffs for last = 0. indexing by [run-2][level-1] */

static const VLCtable coeff_tab1[25][4] =
{
  /* run = 2 */
  {
    {0x0e, 4}, {0x1d, 8}, {0x0e,10}, {0x51,12}
  },
  /* run = 3 */
  {
    {0x0d, 5}, {0x23, 9}, {0x0d,10}, {0x00, 0}
  },
  /* run = 4-26 */
  {
    {0x0c, 5}, {0x22, 9}, {0x52,12}, {0x00, 0}
  },
  {
    {0x0b, 5}, {0x0c,10}, {0x53,12}, {0x00, 0}
  },
  {
    {0x13, 6}, {0x0b,10}, {0x54,12}, {0x00, 0}
  },
  {
    {0x12, 6}, {0x0a,10}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x11, 6}, {0x09,10}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x10, 6}, {0x08,10}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x16, 7}, {0x55,12}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x15, 7}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x14, 7}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x1c, 8}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x1b, 8}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x21, 9}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x20, 9}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x1f, 9}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x1e, 9}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x1d, 9}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x1c, 9}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x1b, 9}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x1a, 9}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x22,11}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x23,11}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x56,12}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x57,12}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  }
};

/* first coeffs of last = 1. indexing by [run][level-1] */

static const VLCtable coeff_tab2[2][3] =
{
  /* run = 0 */
  {
    {0x07, 4}, {0x19, 9}, {0x05,11}
  },
  /* run = 1 */
  {
    {0x0f, 6}, {0x04,11}, {0x00, 0}
  }
};

/* rest of coeffs for last = 1. indexing by [run-2] */

static const VLCtable coeff_tab3[40] =
{
  {0x0e, 6}, {0x0d, 6}, {0x0c, 6},
  {0x13, 7}, {0x12, 7}, {0x11, 7}, {0x10, 7},
  {0x1a, 8}, {0x19, 8}, {0x18, 8}, {0x17, 8},
  {0x16, 8}, {0x15, 8}, {0x14, 8}, {0x13, 8},
  {0x18, 9}, {0x17, 9}, {0x16, 9}, {0x15, 9},    
  {0x14, 9}, {0x13, 9}, {0x12, 9}, {0x11, 9},    
  {0x07,10}, {0x06,10}, {0x05,10}, {0x04,10},    
  {0x24,11}, {0x25,11}, {0x26,11}, {0x27,11},    
  {0x58,12}, {0x59,12}, {0x5a,12}, {0x5b,12},    
  {0x5c,12}, {0x5d,12}, {0x5e,12}, {0x5f,12},
  {0x00, 0}               
};


/* DCT coefficients for INTRA TCOEFF in advanced intra coding mode. 
   Four tables, two for last = 0, two for last = 1.
   the sign bit must be added afterwards. */

/* first part of INTRA_TCOEFF with last = 0 */
/* indexed by [run][level-1] */
static const VLCtable intra_coeff_tab0[2][25] =
{
  /* run = 0 */
  {
    {0x02,2}, {0x06,3}, {0x0e,4}, {0x0c,5},
    {0x0d,5}, {0x10,6}, {0x11,6}, {0x12,6},
    {0x16,7}, {0x1b,8}, {0x20,9}, {0x21,9},
    {0x1a,9}, {0x1b,9}, {0x1c,9}, {0x1d,9},
    {0x1e,9}, {0x1f,9}, {0x23,11}, {0x22,11},
    {0x57,12}, {0x56,12}, {0x55,12}, {0x54,12},
    {0x53,12}


  },
  /* run = 1 */
  {
    {0x0f, 4}, {0x14, 6}, {0x14, 7}, {0x1e,8},
    {0x0f,10}, {0x21,11}, {0x50, 12}, {0x00, 0},
    {0x00, 0}, {0x00, 0}, {0x00, 0}, {0x00, 0},
    {0x00, 0}, {0x00, 0}, {0x00, 0}, {0x00, 0},
    {0x00, 0}, {0x00, 0}, {0x00, 0}, {0x00, 0},
    {0x00, 0}, {0x00, 0}, {0x00, 0}, {0x00, 0},
    {0x00, 0}
  }
};

/* rest of intra coeffs for last = 0. indexing by [run-2][level-1] */
static const VLCtable intra_coeff_tab1[12][4] =
{
  /* run = 2 */
  {
    {0x0b, 5}, {0x15, 7}, {0x0e,10}, {0x09,10}
  },
  /* run = 3 */
  {
    {0x15, 6}, {0x1d, 8}, {0x0d,10}, {0x51, 12}
  },
  /* run = 4-13 */
  {
    {0x13, 6}, {0x23, 9}, {0x07,11}, {0x00, 0}
  },
  {
    {0x17, 7}, {0x22,9}, {0x52,12}, {0x00, 0}
  },
  {
    {0x1c, 8}, {0x0c,10}, {0x00,0}, {0x00, 0}
  },
  {
    {0x1f, 8}, {0x0b,10}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x25, 9}, {0x0a,10}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x24, 9}, {0x06,11}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x21, 10}, {0x00,0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x20, 10}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x08, 10}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },
  {
    {0x20, 11}, {0x00, 0}, {0x00, 0}, {0x00, 0}
  },

};

/* first intra coeffs of last = 1. indexing by [run][level-1] */

static const VLCtable intra_coeff_tab2[2][10] =
{
  /* run = 0 */

  {
  {0x07, 4}, {0x0c, 6}, {0x10,7}, {0x13,8},
  {0x11, 9}, {0x12, 9}, {0x04,10}, {0x27,11},
  {0x26, 11}, {0x5f, 12}
  },
  /* run = 1 */
  {
  {0x0f, 6}, {0x13,9}, {0x05, 10}, {0x25, 11},
  {0x00, 0}, {0x00, 0}, {0x00,0}, {0x00,0},
  {0x00, 0}, {0x00, 0}
  }

};

/* rest of intra coeffs for last = 1. indexing by [run-2][level-1] */

static const VLCtable intra_coeff_tab3[22][3] =
{
  /* run = 2 */
  {
    {0x0e, 6}, {0x14, 9}, {0x24,11}
  },
  /* run = 3 */
  {
    {0x0d, 6}, {0x06, 10}, {0x5e,12}
  },
  /* run = 4-23 */
  {
    {0x11, 7}, {0x07, 10}, {0x00, 0}
  },
  {
    {0x13, 7}, {0x5d,12}, {0x00, 0}
  },
  {
    {0x12, 7}, {0x5c,12}, {0x00, 0}
  },
  {
    {0x14, 8}, {0x5b,12}, {0x00, 0}
  },
  {
    {0x15, 8}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x1a, 8}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x19, 8}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x18, 8}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x17, 8}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x16, 8}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x19, 9}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x15, 9}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x16, 9}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x18, 9}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x17, 9}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x04, 11}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x05, 11}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x58, 12}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x59, 12}, {0x00,0}, {0x00, 0}
  },              
  {
    {0x5a, 12}, {0x00,0}, {0x00, 0}
  },
};

/* inverse DCT table for inter in alternative inter VLC mode */

const VLCtab DCT3Dtab0[] = {
{4225,7}, {4209,7}, {4193,7}, {4177,7}, {193,7}, {177,7}, 
{161,7}, {4,7}, {4161,6}, {4161,6}, {4145,6}, {4145,6}, 
{4129,6}, {4129,6}, {4113,6}, {4113,6}, {145,6}, {145,6}, 
{129,6}, {129,6}, {113,6}, {113,6}, {97,6}, {97,6}, 
{18,6}, {18,6}, {3,6}, {3,6}, {81,5}, {81,5}, 
{81,5}, {81,5}, {65,5}, {65,5}, {65,5}, {65,5}, 
{49,5}, {49,5}, {49,5}, {49,5}, {4097,4}, {4097,4}, 
{4097,4}, {4097,4}, {4097,4}, {4097,4}, {4097,4}, {4097,4}, 
{1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, 
{1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, 
{1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, 
{1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, 
{1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, 
{1,2}, {1,2}, {17,3}, {17,3}, {17,3}, {17,3}, 
{17,3}, {17,3}, {17,3}, {17,3}, {17,3}, {17,3}, 
{17,3}, {17,3}, {17,3}, {17,3}, {17,3}, {17,3}, 
{33,4}, {33,4}, {33,4}, {33,4}, {33,4}, {33,4}, 
{33,4}, {33,4}, {2,4}, {2,4},{2,4},{2,4},
{2,4}, {2,4},{2,4},{2,4},
};


const VLCtab DCT3Dtab1[] = {
{9,10}, {8,10}, {4481,9}, {4481,9}, {4465,9}, {4465,9}, 
{4449,9}, {4449,9}, {4433,9}, {4433,9}, {4417,9}, {4417,9}, 
{4401,9}, {4401,9}, {4385,9}, {4385,9}, {4369,9}, {4369,9}, 
{4098,9}, {4098,9}, {353,9}, {353,9}, {337,9}, {337,9}, 
{321,9}, {321,9}, {305,9}, {305,9}, {289,9}, {289,9}, 
{273,9}, {273,9}, {257,9}, {257,9}, {241,9}, {241,9}, 
{66,9}, {66,9}, {50,9}, {50,9}, {7,9}, {7,9}, 
{6,9}, {6,9}, {4353,8}, {4353,8}, {4353,8}, {4353,8}, 
{4337,8}, {4337,8}, {4337,8}, {4337,8}, {4321,8}, {4321,8}, 
{4321,8}, {4321,8}, {4305,8}, {4305,8}, {4305,8}, {4305,8}, 
{4289,8}, {4289,8}, {4289,8}, {4289,8}, {4273,8}, {4273,8}, 
{4273,8}, {4273,8}, {4257,8}, {4257,8}, {4257,8}, {4257,8}, 
{4241,8}, {4241,8}, {4241,8}, {4241,8}, {225,8}, {225,8}, 
{225,8}, {225,8}, {209,8}, {209,8}, {209,8}, {209,8}, 
{34,8}, {34,8}, {34,8}, {34,8}, {19,8}, {19,8}, 
{19,8}, {19,8}, {5,8}, {5,8}, {5,8}, {5,8}, 
};


const VLCtab DCT3Dtab2[] = {
{4114,11}, {4114,11}, {4099,11}, {4099,11}, {11,11}, {11,11}, 
{10,11}, {10,11}, {4545,10}, {4545,10}, {4545,10}, {4545,10}, 
{4529,10}, {4529,10}, {4529,10}, {4529,10}, {4513,10}, {4513,10}, 
{4513,10}, {4513,10}, {4497,10}, {4497,10}, {4497,10}, {4497,10}, 
{146,10}, {146,10}, {146,10}, {146,10}, {130,10}, {130,10}, 
{130,10}, {130,10}, {114,10}, {114,10}, {114,10}, {114,10}, 
{98,10}, {98,10}, {98,10}, {98,10}, {82,10}, {82,10}, 
{82,10}, {82,10}, {51,10}, {51,10}, {51,10}, {51,10}, 
{35,10}, {35,10}, {35,10}, {35,10}, {20,10}, {20,10}, 
{20,10}, {20,10}, {12,11}, {12,11}, {21,11}, {21,11}, 
{369,11}, {369,11}, {385,11}, {385,11}, {4561,11}, {4561,11}, 
{4577,11}, {4577,11}, {4593,11}, {4593,11}, {4609,11}, {4609,11}, 
{22,12}, {36,12}, {67,12}, {83,12}, {99,12}, {162,12}, 
{401,12}, {417,12}, {4625,12}, {4641,12}, {4657,12}, {4673,12}, 
{4689,12}, {4705,12}, {4721,12}, {4737,12}, {7167,7}, 
{7167,7}, {7167,7}, {7167,7}, {7167,7}, {7167,7}, {7167,7}, 
{7167,7}, {7167,7}, {7167,7}, {7167,7}, {7167,7}, {7167,7}, 
{7167,7}, {7167,7}, {7167,7}, {7167,7}, {7167,7}, {7167,7}, 
{7167,7}, {7167,7}, {7167,7}, {7167,7}, {7167,7}, {7167,7}, 
{7167,7}, {7167,7}, {7167,7}, {7167,7}, {7167,7}, {7167,7}, 
{7167,7}, };

#endif

