/*
 **********************************************************************
 ** md5.h -- Header file for implementation of MD5                   **
 ** RSA Data Security, Inc. MD5 Message Digest Algorithm             **
 ** Created: 2/17/90 RLR                                             **
 ** Revised: 12/27/90 SRD,AJ,BSK,JT Reference C version              **
 ** Revised (for MD5): RLR 4/27/91                                   **
 **   -- G modified to have y&~z instead of y&z                      **
 **   -- FF, GG, HH modified to add in last register done            **
 **   -- Access pattern: round 2 works mod 5, round 3 works mod 3    **
 **   -- distinct additive constant for each step                    **
 **   -- round 4 added, working mod 7                                **
 **********************************************************************
 */

/*
 **********************************************************************
 ** Copyright (C) 1990, RSA Data Security, Inc. All rights reserved. **
 **                                                                  **
 ** License to copy and use this software is granted provided that   **
 ** it is identified as the "RSA Data Security, Inc. MD5 Message     **
 ** Digest Algorithm" in all material mentioning or referencing this **
 ** software or this function.                                       **
 **                                                                  **
 ** License is also granted to make and use derivative works         **
 ** provided that such works are identified as "derived from the RSA **
 ** Data Security, Inc. MD5 Message Digest Algorithm" in all         **
 ** material mentioning or referencing the derived work.             **
 **                                                                  **
 ** RSA Data Security, Inc. makes no representations concerning      **
 ** either the merchantability of this software or the suitability   **
 ** of this software for any particular purpose.  It is provided "as **
 ** is" without express or implied warranty of any kind.             **
 **                                                                  **
 ** These notices must be retained in any copies of any part of this **
 ** documentation and/or software.                                   **
 **********************************************************************
 */

#include <spu_intrinsics.h>

/* typedef a 32 bit type */
typedef unsigned  int UINT4;
typedef vector unsigned int VUINT4;

char inString[] = "xxxxxxxxxxxxxxxo";


/* Load magic initialization constants.
*/
VUINT4 aC = {0x67452301,0x67452301,0x67452301,0x67452301};
VUINT4 bC = {0xefcdab89,0xefcdab89,0xefcdab89,0xefcdab89};
VUINT4 cC = {0x98badcfe,0x98badcfe,0x98badcfe,0x98badcfe};
VUINT4 dC = {0x10325476,0x10325476,0x10325476,0x10325476};


VUINT4 aa;
VUINT4 bb;
VUINT4 cc;
VUINT4 dd;
VUINT4 bitLen;

VUINT4 digest_w_h0;
VUINT4 digest_w_h1;
VUINT4 digest_w_h2;
VUINT4 digest_w_h3;


VUINT4 in0 = {0,0,0,0};
VUINT4 in1 = {0,0,0,0};
VUINT4 in2 = {0,0,0,0};
VUINT4 in3 = {0,0,0,0};
VUINT4 in4 = {0x80,0x80,0x80,0x80};

/* forward declaration */
#define k0  3614090360
#define k1  3905402710
#define k2   606105819
#define k3  3250441966
#define k4  4118548399
#define k5  1200080426
#define k6  2821735955
#define k7  4249261313
#define k8  1770035416
#define k9  2336552879
#define k10 4294925233
#define k11 2304563134
#define k12 1804603682
#define k13 4254626195
#define k14 2792965006
#define k15 1236535329
#define k16 4129170786
#define k17 3225465664
#define k18  643717713
#define k19 3921069994
#define k20 3593408605
#define k21   38016083
#define k22 3634488961
#define k23 3889429448
#define k24  568446438
#define k25 3275163606
#define k26 4107603335
#define k27 1163531501
#define k28 2850285829
#define k29 4243563512
#define k30 1735328473
#define k31 2368359562
#define k32 4294588738
#define k33 2272392833
#define k34 1839030562
#define k35 4259657740
#define k36 2763975236
#define k37 1272893353
#define k38 4139469664
#define k39 3200236656
#define k40  681279174
#define k41 3936430074
#define k42 3572445317
#define k43   76029189
#define k44 3654602809
#define k45 3873151461
#define k46  530742520
#define k47 3299628645
#define k48 4096336452
#define k49 1126891415
#define k50 2878612391
#define k51 4237533241
#define k52 1700485571
#define k53 2399980690
#define k54 4293915773
#define k55 2240044497
#define k56 1873313359
#define k57 4264355552
#define k58 2734768916
#define k59 1309151649
#define k60 4149444226
#define k61 3174756917
#define k62  718787259
#define k63 3951481745


VUINT4 __attribute__ ((aligned(16))) k[64] = {
  {k0 ,k0 ,k0 ,k0 },
  {k1 ,k1 ,k1 ,k1 },
  {k2 ,k2 ,k2 ,k2 },
  {k3 ,k3 ,k3 ,k3 },
  {k4 ,k4 ,k4 ,k4 },
  {k5 ,k5 ,k5 ,k5 },
  {k6 ,k6 ,k6 ,k6 },
  {k7 ,k7 ,k7 ,k7 },
  {k8 ,k8 ,k8 ,k8 },
  {k9 ,k9 ,k9 ,k9 },
  {k10,k10,k10,k10},
  {k11,k11,k11,k11},
  {k12,k12,k12,k12},
  {k13,k13,k13,k13},
  {k14,k14,k14,k14},
  {k15,k15,k15,k15},
  {k16,k16,k16,k16},
  {k17,k17,k17,k17},
  {k18,k18,k18,k18},
  {k19,k19,k19,k19},
  {k20,k20,k20,k20},
  {k21,k21,k21,k21},
  {k22,k22,k22,k22},
  {k23,k23,k23,k23},
  {k24,k24,k24,k24},
  {k25,k25,k25,k25},
  {k26,k26,k26,k26},
  {k27,k27,k27,k27},
  {k28,k28,k28,k28},
  {k29,k29,k29,k29},
  {k30,k30,k30,k30},
  {k31,k31,k31,k31},
  {k32,k32,k32,k32},
  {k33,k33,k33,k33},
  {k34,k34,k34,k34},
  {k35,k35,k35,k35},
  {k36,k36,k36,k36},
  {k37,k37,k37,k37},
  {k38,k38,k38,k38},
  {k39,k39,k39,k39},
  {k40,k40,k40,k40},
  {k41,k41,k41,k41},
  {k42,k42,k42,k42},
  {k43,k43,k43,k43},
  {k44,k44,k44,k44},
  {k45,k45,k45,k45},
  {k46,k46,k46,k46},
  {k47,k47,k47,k47},
  {k48,k48,k48,k48},
  {k49,k49,k49,k49},
  {k50,k50,k50,k50},
  {k51,k51,k51,k51},
  {k52,k52,k52,k52},
  {k53,k53,k53,k53},
  {k54,k54,k54,k54},
  {k55,k55,k55,k55},
  {k56,k56,k56,k56},
  {k57,k57,k57,k57},
  {k58,k58,k58,k58},
  {k59,k59,k59,k59},
  {k60,k60,k60,k60},
  {k61,k61,k61,k61},
  {k62,k62,k62,k62},
  {k63,k63,k63,k63}
};

/* F, G and H are basic MD5 functions: selection, majority, parity */
#define F(x, y, z) (spu_or(spu_and(x, y), spu_andc(z, x)))
#define G(x, y, z) (spu_or(spu_and(x, z), spu_andc(y, z)))
#define H(x, y, z) (spu_xor(spu_xor(x, y),z))
#define I(x, y, z) (spu_xor(y, spu_orc(x, z)))
//#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
//#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
//#define H(x, y, z) ((x) ^ (y) ^ (z))
//#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits */
//#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define ROTATE_LEFT(x, n) (spu_rl(x, n))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4 */
/* Rotation is separate from addition to prevent recomputation */
#define FF(a, b, c, d, x, s, ac) \
  { (a) = spu_add(ROTATE_LEFT ((spu_add((a), spu_add(F ((b), (c), (d)), spu_add((x), (ac))))), (s)),(b)); \
  }
#define GG(a, b, c, d, x, s, ac) \
  { (a) = spu_add(ROTATE_LEFT ((spu_add((a), spu_add(G ((b), (c), (d)), spu_add((x), (ac))))), (s)),(b)); \
  }
#define HH(a, b, c, d, x, s, ac) \
  { (a) = spu_add(ROTATE_LEFT ((spu_add((a), spu_add(H ((b), (c), (d)), spu_add((x), (ac))))), (s)),(b)); \
  }
#define II(a, b, c, d, x, s, ac) \
  { (a) = spu_add(ROTATE_LEFT ((spu_add((a), spu_add(I ((b), (c), (d)),spu_add((x), (ac))))), (s)),(b)); \
  }
#define FF_NOX(a, b, c, d, s, ac) \
  { (a) = spu_add(ROTATE_LEFT ((spu_add((a), spu_add(F ((b), (c), (d)), (ac)))), (s)),(b)); \
  }
#define GG_NOX(a, b, c, d, s, ac) \
  { (a) = spu_add(ROTATE_LEFT ((spu_add((a), spu_add(G ((b), (c), (d)), (ac)))), (s)),(b)); \
  }
#define HH_NOX(a, b, c, d, s, ac) \
  { (a) = spu_add(ROTATE_LEFT ((spu_add((a), spu_add(H ((b), (c), (d)), (ac)))), (s)),(b)); \
  }
#define II_NOX(a, b, c, d, s, ac) \
  { (a) = spu_add(ROTATE_LEFT ((spu_add((a), spu_add(I ((b), (c), (d)),(ac)))), (s)),(b)); \
  }

/*
#define FF(a, b, c, d, x, s, ac) \
  {s0 = F ((b), (c), (d)); \
   s1 = s0 + (x); \
   s2 = s1 + (a); \
   s3 = s2 + spu_splats((UINT4)(ac)); \
   s4 = ROTATE_LEFT ((s3), (s)); \
   (a) = s4 +  (b); \
  }
#define GG(a, b, c, d, x, s, ac) \
  {(a) += G ((b), (c), (d)) + (x) + spu_splats((UINT4)(ac)); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) \
  {(a) += H ((b), (c), (d)) + (x) + spu_splats((UINT4)(ac)); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) \
  {(a) += I ((b), (c), (d)) + (x) + spu_splats((UINT4)(ac)); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }*/

//inline void MD5Calc ()
//{
//  VUINT4 in0 = {0,0,0,0}, in1 = {0,0,0,0}, in2 = {0,0,0,0}, in3 = {0,0,0,0};
//    
//  spu_insert((((UINT4)inString[ 3] << 24) | ((UINT4)inString[ 2] << 16) | ((UINT4)inString[ 1] << 8) | (UINT4)inString[ 0]), in0, 0);
//  spu_insert((((UINT4)inString[ 7] << 24) | ((UINT4)inString[ 6] << 16) | ((UINT4)inString[ 5] << 8) | (UINT4)inString[ 4]), in1, 0);
//  spu_insert((((UINT4)inString[11] << 24) | ((UINT4)inString[10] << 16) | ((UINT4)inString[ 9] << 8) | (UINT4)inString[ 8]), in2, 0);
//  spu_insert((((UINT4)inString[15] << 24) | ((UINT4)inString[14] << 16) | ((UINT4)inString[13] << 8) | (UINT4)inString[12]), in3, 0);
//
//  VUINT4 in4 = {0x80,0x80,0x80,0x80};
//
///*  a = aC;
//  b = bC;
//  c = cC;
//  d = dC;*/
// VUINT4 a = (VUINT4){0x67452301,0x67452301,0x67452301,0x67452301};
// VUINT4 b = (VUINT4){0xefcdab89,0xefcdab89,0xefcdab89,0xefcdab89};
// VUINT4 c = (VUINT4){0x98badcfe,0x98badcfe,0x98badcfe,0x98badcfe};
// VUINT4 d = (VUINT4){0x10325476,0x10325476,0x10325476,0x10325476};
//
//  /* Round 1 */
//#define S11 (UINT4)7
//#define S12 (UINT4)12
//#define S13 (UINT4)17
//#define S14 (UINT4)22
//  //FF     (a, b, c, d, in0,    S11, 3614090360);	/* 1 */
//  a = spu_add(b, ROTATE_LEFT(spu_add(in0, spu_splats(3614090359)), S11)); /* -1 !!! */
//
//  FF     (d, a, b, c, in1,    S12, 3905402710);	/*  2 */
//  FF     (c, d, a, b, in2,    S13,  606105819);	/*  3 */
//  FF     (b, c, d, a, in3,    S14, 3250441966);	/*  4 */
//  FF     (a, b, c, d, in4,    S11, 4118548399);	/*  5 */
//  FF_NOX (d, a, b, c,         S12, 1200080426);	/*  6 */
//  FF_NOX (c, d, a, b,         S13, 2821735955);	/*  7 */
//  FF_NOX (b, c, d, a,         S14, 4249261313);	/*  8 */
//  FF_NOX (a, b, c, d,         S11, 1770035416);	/*  9 */
//  FF_NOX (d, a, b, c,         S12, 2336552879);	/* 10 */
//  FF_NOX (c, d, a, b,         S13, 4294925233);	/* 11 */
//  FF_NOX (b, c, d, a,         S14, 2304563134);	/* 12 */
//  FF_NOX (a, b, c, d,         S11, 1804603682);	/* 13 */
//  FF_NOX (d, a, b, c,         S12, 4254626195);	/* 14 */
//  FF     (c, d, a, b, bitLen, S13, 2792965006);	/* 15 */
//  FF_NOX (b, c, d, a,         S14, 1236535329);	/* 16 */
//
//
//  /* Round 2 */
//#define S21 5
//#define S22 9
//#define S23 14
//#define S24 20
//  GG     (a, b, c, d, in1,    S21, 4129170786);	/* 17 */
//  GG_NOX (d, a, b, c,         S22, 3225465664);	/* 18 */
//  GG_NOX (c, d, a, b,         S23,  643717713);	/* 19 */
//  GG     (b, c, d, a, in0,    S24, 3921069994);	/* 20 */
//  GG_NOX (a, b, c, d,         S21, 3593408605);	/* 21 */
//  GG_NOX (d, a, b, c,         S22,   38016083);	/* 22 */
//  GG_NOX (c, d, a, b,         S23, 3634488961);	/* 23 */
//  GG     (b, c, d, a, in4,    S24, 3889429448);	/* 24 */
//  GG_NOX (a, b, c, d,         S21,  568446438);	/* 25 */
//  GG     (d, a, b, c, bitLen, S22, 3275163606);	/* 26 */
//  GG     (c, d, a, b, in3,    S23, 4107603335);	/* 27 */
//  GG_NOX (b, c, d, a,         S24, 1163531501);	/* 28 */
//  GG_NOX (a, b, c, d,         S21, 2850285829);	/* 29 */
//  GG     (d, a, b, c, in2,    S22, 4243563512);	/* 30 */
//  GG_NOX (c, d, a, b,         S23, 1735328473);	/* 31 */
//  GG_NOX (b, c, d, a,         S24, 2368359562);	/* 32 */
//
//  /* Round 3 */
//#define S31 4
//#define S32 11
//#define S33 16
//#define S34 23
//  HH_NOX (a, b, c, d,         S31, 4294588738);	/* 33 */
//  HH_NOX (d, a, b, c,         S32, 2272392833);	/* 34 */
//  HH_NOX (c, d, a, b,         S33, 1839030562);	/* 35 */
//  HH     (b, c, d, a, bitLen, S34, 4259657740);	/* 36 */
//  HH     (a, b, c, d, in1,    S31, 2763975236);	/* 37 */
//  HH     (d, a, b, c, in4,    S32, 1272893353);	/* 38 */
//  HH_NOX (c, d, a, b,         S33, 4139469664);	/* 39 */
//  HH_NOX (b, c, d, a,         S34, 3200236656);	/* 40 */
//  HH_NOX (a, b, c, d,         S31,  681279174);	/* 41 */
//  HH     (d, a, b, c, in0,    S32, 3936430074);	/* 42 */
//  HH     (c, d, a, b, in3,    S33, 3572445317);	/* 43 */
//  HH_NOX (b, c, d, a,         S34,   76029189);	/* 44 */
//  HH_NOX (a, b, c, d,         S31, 3654602809);	/* 45 */
//  HH_NOX (d, a, b, c,         S32, 3873151461);	/* 46 */
//  HH_NOX (c, d, a, b,         S33,  530742520);	/* 47 */
//  HH     (b, c, d, a, in2,    S34, 3299628645);	/* 48 */
//
//  /* Round 4 */
//#define S41 6
//#define S42 10
//#define S43 15
//#define S44 21
//  II     (a, b, c, d, in0,    S41, 4096336452);	/* 49 */
//  II_NOX (d, a, b, c,         S42, 1126891415);	/* 50 */
//  II     (c, d, a, b, bitLen, S43, 2878612391);	/* 51 */
//  II_NOX (b, c, d, a,         S44, 4237533241);	/* 52 */
//  II_NOX (a, b, c, d,         S41, 1700485571);	/* 53 */
//  II     (d, a, b, c, in3,    S42, 2399980690);	/* 54 */
//  II_NOX (c, d, a, b,         S43, 4293915773);	/* 55 */
//  II     (b, c, d, a, in1,    S44, 2240044497);	/* 56 */
//  II_NOX (a, b, c, d,         S41, 1873313359);	/* 57 */
//  II_NOX (d, a, b, c,         S42, 4264355552);	/* 58 */
//  II_NOX (c, d, a, b,         S43, 2734768916);	/* 59 */
//  II_NOX (b, c, d, a,         S44, 1309151649);	/* 60 */
//  II     (a, b, c, d, in4,    S41, 4149444226);	/* 61 */
//  II_NOX (d, a, b, c,         S42, 3174756917);	/* 62 */
//  II     (c, d, a, b, in2,    S43,  718787259);	/* 63 */
//  II_NOX (b, c, d, a,         S44, 3951481745);	/* 64 */
//
//  a = spu_add(a, aC);
//  b = spu_add(b, bC);
//  c = spu_add(c, cC);
//  d = spu_add(d, dC);
//
//}

inline void endian_swap (UINT4 *x)
{
  *x =  (*x >> 24)               |
	   ((*x << 8 ) & 0x00FF0000) | 
       ((*x >> 8 ) & 0x0000FF00) | 
        (*x << 24);
}

void MD5Print( unsigned char *inString){
    int i;
    UINT4 hh0, hh1, hh2, hh3;
    for(i = 0; i < 4; i++){
        hh0 = spu_extract(aa, i);
        hh1 = spu_extract(bb, i);
        hh2 = spu_extract(cc, i);
        hh3 = spu_extract(dd, i);

        endian_swap (&hh0);
        endian_swap (&hh1);
        endian_swap (&hh2);
        endian_swap (&hh3);
        printf ("v:%d, %08x%08x%08x%08x", i, hh0, hh1, hh2, hh3);
        printf (" \"%s\"\n", inString);
    }
}

inline int new_MD5Calc(UINT4 counter){
UINT4 i=0;
    do {

 //VUINT4 a;
 //VUINT4 b;
 //VUINT4 c;
 //VUINT4 d;
 VUINT4 in0 = {0,0,0,0}, in1 = {0,0,0,0}, in2 = {0,0,0,0}, in3 = {0,0,0,0};
 VUINT4 in4 = {0x80,0x80,0x80,0x80};
 VUINT4 a   = {0x67452301,0x67452301,0x67452301,0x67452301};
 VUINT4 b   = {0xefcdab89,0xefcdab89,0xefcdab89,0xefcdab89};
 VUINT4 c   = {0x98badcfe,0x98badcfe,0x98badcfe,0x98badcfe};
 VUINT4 d   = {0x10325476,0x10325476,0x10325476,0x10325476};

    
  //if(i==0){
      in0 = spu_insert((((UINT4)inString[ 3] << 24) |
                        ((UINT4)inString[ 2] << 16) |
                        ((UINT4)inString[ 1] << 8 ) |
                         (UINT4)inString[ 0]         ), in0, 0);

      in1 = spu_insert((((UINT4)inString[ 7] << 24) | ((UINT4)inString[ 6] << 16) | ((UINT4)inString[ 5] << 8) | (UINT4)inString[ 4]), in1, 0);
      in2 = spu_insert((((UINT4)inString[11] << 24) | ((UINT4)inString[10] << 16) | ((UINT4)inString[ 9] << 8) | (UINT4)inString[ 8]), in2, 0);
   //}
  in3 = spu_insert((((UINT4)inString[15] << 24) | ((UINT4)inString[14] << 16) | ((UINT4)inString[13] << 8) | (UINT4)inString[12]), in3, 0);

     //MD5Calc();
/*  a = aC;
  b = bC;
  c = cC;
  d = dC;*/

/* VUINT4 a = aC;
 VUINT4 b = bC;
 VUINT4 c = cC;
 VUINT4 d = dC;*/


  /* Round 1 */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
  //FF     (a, b, c, d, in0,    S11, 3614090360);	/* 1 */
  //if(i==0){
      a = spu_add(b, ROTATE_LEFT(spu_add(in0, k[0]), S11));

      FF     (d, a, b, c, in1,    S12, k[1 ]);	/*  2 */
      FF     (c, d, a, b, in2,    S13, k[2 ]);	/*  3 */
  //}
  FF     (b, c, d, a, in3,    S14, k[3 ]);	/*  4 */
  FF     (a, b, c, d, in4,    S11, k[4 ]);	/*  5 */
  FF_NOX (d, a, b, c,         S12, k[5 ]);	/*  6 */
  FF_NOX (c, d, a, b,         S13, k[6 ]);	/*  7 */
  FF_NOX (b, c, d, a,         S14, k[7 ]);	/*  8 */
  FF_NOX (a, b, c, d,         S11, k[8 ]);	/*  9 */
  FF_NOX (d, a, b, c,         S12, k[9 ]);	/* 10 */
  FF_NOX (c, d, a, b,         S13, k[10]);	/* 11 */
  FF_NOX (b, c, d, a,         S14, k[11]);	/* 12 */
  FF_NOX (a, b, c, d,         S11, k[12]);	/* 13 */
  FF_NOX (d, a, b, c,         S12, k[13]);	/* 14 */
  FF     (c, d, a, b, bitLen, S13, k[14]);	/* 15 */
  FF_NOX (b, c, d, a,         S14, k[15]);	/* 16 */


  /* Round 2 */
#define S21 5
#define S22 9
#define S23 14
#define S24 20
  GG     (a, b, c, d, in1,    S21, k[16]);	/* 17 */
  GG_NOX (d, a, b, c,         S22, k[17]);	/* 18 */
  GG_NOX (c, d, a, b,         S23, k[18]);	/* 19 */
  GG     (b, c, d, a, in0,    S24, k[19]);	/* 20 */
  GG_NOX (a, b, c, d,         S21, k[20]);	/* 21 */
  GG_NOX (d, a, b, c,         S22, k[21]);	/* 22 */
  GG_NOX (c, d, a, b,         S23, k[22]);	/* 23 */
  GG     (b, c, d, a, in4,    S24, k[23]);	/* 24 */
  GG_NOX (a, b, c, d,         S21, k[24]);	/* 25 */
  GG     (d, a, b, c, bitLen, S22, k[25]);	/* 26 */
  GG     (c, d, a, b, in3,    S23, k[26]);	/* 27 */
  GG_NOX (b, c, d, a,         S24, k[27]);	/* 28 */
  GG_NOX (a, b, c, d,         S21, k[28]);	/* 29 */
  GG     (d, a, b, c, in2,    S22, k[29]);	/* 30 */
  GG_NOX (c, d, a, b,         S23, k[30]);	/* 31 */
  GG_NOX (b, c, d, a,         S24, k[31]);	/* 32 */

  /* Round 3 */
#define S31 4
#define S32 11
#define S33 16
#define S34 23
  HH_NOX (a, b, c, d,         S31, k[32]);	/* 33 */
  HH_NOX (d, a, b, c,         S32, k[33]);	/* 34 */
  HH_NOX (c, d, a, b,         S33, k[34]);	/* 35 */
  HH     (b, c, d, a, bitLen, S34, k[35]);	/* 36 */
  HH     (a, b, c, d, in1,    S31, k[36]);	/* 37 */
  HH     (d, a, b, c, in4,    S32, k[37]);	/* 38 */
  HH_NOX (c, d, a, b,         S33, k[38]);	/* 39 */
  HH_NOX (b, c, d, a,         S34, k[39]);	/* 40 */
  HH_NOX (a, b, c, d,         S31, k[40]);	/* 41 */
  HH     (d, a, b, c, in0,    S32, k[41]);	/* 42 */
  HH     (c, d, a, b, in3,    S33, k[42]);	/* 43 */
  HH_NOX (b, c, d, a,         S34, k[43]);	/* 44 */
  HH_NOX (a, b, c, d,         S31, k[44]);	/* 45 */
  HH_NOX (d, a, b, c,         S32, k[45]);	/* 46 */
  HH_NOX (c, d, a, b,         S33, k[46]);	/* 47 */
  HH     (b, c, d, a, in2,    S34, k[47]);	/* 48 */

  /* Round 4 */
#define S41 6
#define S42 10
#define S43 15
#define S44 21
  II     (a, b, c, d, in0,    S41, k[48]);	/* 49 */
  II_NOX (d, a, b, c,         S42, k[49]);	/* 50 */
  II     (c, d, a, b, bitLen, S43, k[50]);	/* 51 */
  II_NOX (b, c, d, a,         S44, k[51]);	/* 52 */
  II_NOX (a, b, c, d,         S41, k[52]);	/* 53 */
  II     (d, a, b, c, in3,    S42, k[53]);	/* 54 */
  II_NOX (c, d, a, b,         S43, k[54]);	/* 55 */
  II     (b, c, d, a, in1,    S44, k[55]);	/* 56 */
  II_NOX (a, b, c, d,         S41, k[56]);	/* 57 */
  II_NOX (d, a, b, c,         S42, k[57]);	/* 58 */
  II_NOX (c, d, a, b,         S43, k[58]);	/* 59 */
  II_NOX (b, c, d, a,         S44, k[59]);	/* 60 */
  II     (a, b, c, d, in4,    S41, k[60]);	/* 61 */
  II_NOX (d, a, b, c,         S42, k[61]);	/* 62 */
  II     (c, d, a, b, in2,    S43, k[62]);	/* 63 */
  II_NOX (b, c, d, a,         S44, k[63]);	/* 64 */

  //a = spu_add(a, aC);
  //b = spu_add(b, bC);
  //c = spu_add(c, cC);
  //d = spu_add(d, dC);


    //ok = !(a == digest_w_h0 && b == digest_w_h1 && c == digest_w_h2 && d == digest_w_h3);
    //for(j = 0; j < 4; j++){
    //
        VUINT4 t = spu_xor(
                     spu_xor(spu_xor(a, digest_w_h0), 
                             spu_xor(b, digest_w_h1)),
                     spu_xor(spu_xor(c, digest_w_h2), 
                             spu_xor(d, digest_w_h3))) ;
        if(spu_extract(t,0)==0 ||
           spu_extract(t,1)==0 ||
           spu_extract(t,2)==0 ||
           spu_extract(t,3)==0){
            aa=a;bb=b;cc=c;dd=d;
            return i;
        }
    inString[0] = inString[1];
    ++i;
  }
  while(__builtin_expect((i < counter), 1));
return i;
}

/*inline void endian_swap(unsigned long long x)
{
    x = (x>>56) | 
        ((x<<40) & 0x00FF000000000000) |
        ((x<<24) & 0x0000FF0000000000) |
        ((x<<8)  & 0x000000FF00000000) |
        ((x>>8)  & 0x00000000FF000000) |
        ((x>>24) & 0x0000000000FF0000) |
        ((x>>40) & 0x000000000000FF00) |
        (x<<56);
}*/

/*
 **********************************************************************
 ** End of md5.c                                                     **
 ******************************* (cut) ********************************
 */

/*
 **********************************************************************
 ** md5driver.c -- sample routines to test                           **
 ** RSA Data Security, Inc. MD5 message digest algorithm.            **
 ** Created: 2/16/90 RLR                                             **
 ** Updated: 1/91 SRD                                                **
 **********************************************************************
 */

/*
 **********************************************************************
 ** Copyright (C) 1990, RSA Data Security, Inc. All rights reserved. **
 **                                                                  **
 ** RSA Data Security, Inc. makes no representations concerning      **
 ** either the merchantability of this software or the suitability   **
 ** of this software for any particular purpose.  It is provided "as **
 ** is" without express or implied warranty of any kind.             **
 **                                                                  **
 ** These notices must be retained in any copies of any part of this **
 ** documentation and/or software.                                   **
 **********************************************************************
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>
//#include <math.h>


int main (int argc, char *argv[])
{
  /* this is 'xxxxxxxxxxxxxxxx' */
  char digest_wanted[] = "45ed9cc2f92b77cd8b2f5bd59ff635f8";
  UINT4 digest_wanted_hex1;
  UINT4 digest_wanted_hex2;
  UINT4 digest_wanted_hex3;
  UINT4 digest_wanted_hex4;

  sscanf ((const char *)digest_wanted, "%08x%08x%08x%08x",
          &digest_wanted_hex1,
		  &digest_wanted_hex2, 
          &digest_wanted_hex3, 
          &digest_wanted_hex4);
  endian_swap (&digest_wanted_hex1);
  endian_swap (&digest_wanted_hex2);
  endian_swap (&digest_wanted_hex3);
  endian_swap (&digest_wanted_hex4);

  digest_w_h0 = spu_sub(spu_splats(digest_wanted_hex1), (VUINT4)spu_splats(0x67452301));
  digest_w_h1 = spu_sub(spu_splats(digest_wanted_hex2), (VUINT4)spu_splats(0xefcdab89));
  digest_w_h2 = spu_sub(spu_splats(digest_wanted_hex3), (VUINT4)spu_splats(0x98badcfe));
  digest_w_h3 = spu_sub(spu_splats(digest_wanted_hex4), (VUINT4)spu_splats(0x10325476));

/*
  from wiki, doesn't work..
  UINT4 ka[64];
  int k;
  for(k=0; k < 64; k++){
        ka[k] = floor(abs(sin(k+1)) * pow(2,32));
        printf("i:%d,%08x\n", k, ka[k]);
  }*/
/*
  VUINT4 digest_w_h0 = spu_splats(digest_wanted_hex1);
  VUINT4 digest_w_h1 = spu_splats(digest_wanted_hex2);
  VUINT4 digest_w_h2 = spu_splats(digest_wanted_hex3);
  VUINT4 digest_w_h3 = spu_splats(digest_wanted_hex4);*/

  //digest_wanted_hex1 -= 0x67452301;
  //digest_wanted_hex2 -= 0xefcdab89;
  //digest_wanted_hex3 -= 0x98badcfe;
  //digest_wanted_hex4 -= 0x10325476;

  UINT4 counter = 5000000;
  UINT4 step    = 5000000;
  double et;
  double st;
  UINT4 i=0, j=0;

int ok = 1;

  bitLen = spu_splats(strlen(inString) << 3);

  struct timeval startTime, endTime;
  struct timezone tzp;

  gettimeofday (&startTime, &tzp);

      //VUINT4 in0 = spu_splats(((UINT4)inString[ 3] << 24) | ((UINT4)inString[ 2] << 16) | ((UINT4)inString[ 1] << 8) | (UINT4)inString[ 0]);
      //VUINT4 in1 = spu_splats(((UINT4)inString[ 7] << 24) | ((UINT4)inString[ 6] << 16) | ((UINT4)inString[ 5] << 8) | (UINT4)inString[ 4]);
      //VUINT4 in2 = spu_splats(((UINT4)inString[11] << 24) | ((UINT4)inString[10] << 16) | ((UINT4)inString[ 9] << 8) | (UINT4)inString[ 8]);
      //VUINT4 in3 = spu_splats(((UINT4)inString[15] << 24) | ((UINT4)inString[14] << 16) | ((UINT4)inString[13] << 8) | (UINT4)inString[12]);

/*


UINT4 kc[64];
kc[0 ]= 3614090360;
kc[1 ]= 3905402710;
kc[2 ]=  606105819;
kc[3 ]= 3250441966;
kc[4 ]= 4118548399;
kc[5 ]= 1200080426;
kc[6 ]= 2821735955;
kc[7 ]= 4249261313;
kc[8 ]= 1770035416;
kc[9 ]= 2336552879;
kc[10]= 4294925233;
kc[11]= 2304563134;
kc[12]= 1804603682;
kc[13]= 4254626195;
kc[14]= 2792965006;
kc[15]= 1236535329;
kc[16]= 4129170786;
kc[17]= 3225465664;
kc[18]=  643717713;
kc[19]= 3921069994;
kc[20]= 3593408605;
kc[21]=   38016083;
kc[22]= 3634488961;
kc[23]= 3889429448;
kc[24]=  568446438;
kc[25]= 3275163606;
kc[26]= 4107603335;
kc[27]= 1163531501;
kc[28]= 2850285829;
kc[29]= 4243563512;
kc[30]= 1735328473;
kc[31]= 2368359562;
kc[32]= 4294588738;
kc[33]= 2272392833;
kc[34]= 1839030562;
kc[35]= 4259657740;
kc[36]= 2763975236;
kc[37]= 1272893353;
kc[38]= 4139469664;
kc[39]= 3200236656;
kc[40]=  681279174;
kc[41]= 3936430074;
kc[42]= 3572445317;
kc[43]=   76029189;
kc[44]= 3654602809;
kc[45]= 3873151461;
kc[46]=  530742520;
kc[47]= 3299628645;
kc[48]= 4096336452;
kc[49]= 1126891415;
kc[50]= 2878612391;
kc[51]= 4237533241;
kc[52]= 1700485571;
kc[53]= 2399980690;
kc[54]= 4293915773;
kc[55]= 2240044497;
kc[56]= 1873313359;
kc[57]= 4264355552;
kc[58]= 2734768916;
kc[59]= 1309151649;
kc[60]= 4149444226;
kc[61]= 3174756917;
kc[62]=  718787259;
kc[63]= 3951481745;

kc[0] -= 1;

UINT4 ka;
for(ka=0; ka<64; ka++){
 k[ka] = spu_splats(kc[ka]);
 
}*/


    i = new_MD5Calc(counter);

      
    /*for(j = 0; j < 4; j++){
        UINT4 hh0 = spu_extract(t, j);

        printf ("v0:%d, %08x\n", j, hh0);
    }
        if(
          (spu_extract(a, 0) == digest_wanted_hex1 &&
           spu_extract(b, 0) == digest_wanted_hex2 &&
           spu_extract(c, 0) == digest_wanted_hex3 &&
           spu_extract(d, 0) == digest_wanted_hex4)||
          (spu_extract(a, 1) == digest_wanted_hex1 &&
           spu_extract(b, 1) == digest_wanted_hex2 &&
           spu_extract(c, 1) == digest_wanted_hex3 &&
           spu_extract(d, 1) == digest_wanted_hex4)||
          (spu_extract(a, 2) == digest_wanted_hex1 &&
           spu_extract(b, 2) == digest_wanted_hex2 &&
           spu_extract(c, 2) == digest_wanted_hex3 &&
           spu_extract(d, 2) == digest_wanted_hex4)||
          (spu_extract(a, 3) == digest_wanted_hex1 &&
           spu_extract(b, 3) == digest_wanted_hex2 &&
           spu_extract(c, 3) == digest_wanted_hex3 &&
           spu_extract(d, 3) == digest_wanted_hex4)){

            aa = a; bb = b; cc = d; dd = d;
            ok = 0;
        }
        if(
          (spu_extract(a, 0) == digest_wanted_hex1 &&
           spu_extract(b, 0) == digest_wanted_hex2 &&
           spu_extract(c, 0) == digest_wanted_hex3 &&
           spu_extract(d, 0) == digest_wanted_hex4)){
            aa = a; bb = b; cc = d; dd = d;
            ok = 0;

        } else {
            if
              (spu_extract(a, 1) == digest_wanted_hex1 &&
               spu_extract(b, 1) == digest_wanted_hex2 &&
               spu_extract(c, 1) == digest_wanted_hex3 &&
               spu_extract(d, 1) == digest_wanted_hex4) {
            aa = a; bb = b; cc = d; dd = d;
            ok = 0;
            } else {
              if(spu_extract(a, 2) == digest_wanted_hex1 &&
               spu_extract(b, 2) == digest_wanted_hex2 &&
               spu_extract(c, 2) == digest_wanted_hex3 &&
               spu_extract(d, 2) == digest_wanted_hex4){
            aa = a; bb = b; cc = d; dd = d;
            ok = 0;
                } else {
                if
                  (spu_extract(a, 3) == digest_wanted_hex1 &&
                   spu_extract(b, 3) == digest_wanted_hex2 &&
                   spu_extract(c, 3) == digest_wanted_hex3 &&
                   spu_extract(d, 3) == digest_wanted_hex4){
            aa = a; bb = b; cc = d; dd = d;
            ok = 0;
                }
            }
            }
            }

        if(
          (spu_extract(a, 0) == 0 &&
           spu_extract(b, 0) == 0 &&
           spu_extract(c, 0) == 0 &&
           spu_extract(d, 0) == 0)||
          (spu_extract(a, 1) == 0 &&
           spu_extract(b, 1) == 0 &&
           spu_extract(c, 1) == 0 &&
           spu_extract(d, 1) == 0)||
          (spu_extract(a, 2) == 0 &&
           spu_extract(b, 2) == 0 &&
           spu_extract(c, 2) == 0 &&
           spu_extract(d, 2) == 0)||
          (spu_extract(a, 3) == 0 &&
           spu_extract(b, 3) == 0 &&
           spu_extract(c, 3) == 0 &&
           spu_extract(d, 3) == 0)){

            aa = a; bb = b; cc = d; dd = d;
            ok = 0;
        }*/
    //}

/*    if (__builtin_expect((a == digest_w_h0), 0)) {
        if (__builtin_expect((b == digest_w_h1), 0)) {
            if (__builtin_expect((c == digest_w_h2), 0)) {
                if (__builtin_expect((d == digest_w_h3), 0)) {
                    ok = 0;
            //ok = (a == digest_w_h0 && b == digest_w_h1 && c == digest_w_h2 && d == digest_w_h3);
        //aa = a; bb = b; cc = d; dd = d;
        //break;
                }
            }
        }

    }*/
      
    //if ((i+1) % step == 0){
       gettimeofday (&endTime, &tzp);
       et = ((double)endTime.tv_sec + (double)endTime.tv_usec/1000000);
       et -= ((double)startTime.tv_sec + (double)startTime.tv_usec/1000000);
        printf("nrcalcs: %d, ok:%d, calcs per second: %f\n", i, i, ((double)step)/et);
    //}
    aa = spu_add(aa, 0x67452301);
    bb = spu_add(bb, 0xefcdab89);
    cc = spu_add(cc, 0x98badcfe);
    dd = spu_add(dd, 0x10325476);

  MD5Print(inString);

}
