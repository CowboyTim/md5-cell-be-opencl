
__kernel void
sommeer(__global       float * v1,
        __global       float * v2)
{
    size_t tid = get_global_id(0);
    v1[tid] = v1[tid] + v2[tid];
}


#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable
__constant char hw[] = "Hello World\n";
__kernel void hello(__global char * out)
{
    size_t tid = get_global_id(0);
    out[tid] = hw[tid];
}

typedef struct {
    unsigned char * wanted;
    unsigned char * inString;
    unsigned int    len;
    unsigned int    nriter;
} blah;


typedef unsigned long int UINT4;

/* F, G and H are basic MD5 functions: selection, majority, parity */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4 */
/* Rotation is separate from addition to prevent recomputation */
#define FF(a, b, c, d, x, s, ac) \
  {(a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) \
  {(a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) \
  {(a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) \
  {(a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
   (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }



/* Basic MD5 step. Transform buf based on in.
 */
void Transform (UINT4 * in, UINT4 *h0, UINT4 *h1, UINT4 *h2, UINT4 *h3)
{
  UINT4 a = *h0, b = *h1, c = *h2, d = *h3;

  /* Round 1 */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
  FF (a, b, c, d, in[0], S11, 3614090360);	/* 1 */
  FF (d, a, b, c, in[1], S12, 3905402710);	/* 2 */
  FF (c, d, a, b, in[2], S13, 606105819);	/* 3 */
  FF (b, c, d, a, in[3], S14, 3250441966);	/* 4 */
  FF (a, b, c, d, in[4], S11, 4118548399);	/* 5 */
  FF (d, a, b, c, in[5], S12, 1200080426);	/* 6 */
  FF (c, d, a, b, in[6], S13, 2821735955);	/* 7 */
  FF (b, c, d, a, in[7], S14, 4249261313);	/* 8 */
  FF (a, b, c, d, in[8], S11, 1770035416);	/* 9 */
  FF (d, a, b, c, in[9], S12, 2336552879);	/* 10 */
  FF (c, d, a, b, in[10], S13, 4294925233);	/* 11 */
  FF (b, c, d, a, in[11], S14, 2304563134);	/* 12 */
  FF (a, b, c, d, in[12], S11, 1804603682);	/* 13 */
  FF (d, a, b, c, in[13], S12, 4254626195);	/* 14 */
  FF (c, d, a, b, in[14], S13, 2792965006);	/* 15 */
  FF (b, c, d, a, in[15], S14, 1236535329);	/* 16 */

  /* Round 2 */
#define S21 5
#define S22 9
#define S23 14
#define S24 20
  GG (a, b, c, d, in[1], S21, 4129170786);	/* 17 */
  GG (d, a, b, c, in[6], S22, 3225465664);	/* 18 */
  GG (c, d, a, b, in[11], S23, 643717713);	/* 19 */
  GG (b, c, d, a, in[0], S24, 3921069994);	/* 20 */
  GG (a, b, c, d, in[5], S21, 3593408605);	/* 21 */
  GG (d, a, b, c, in[10], S22, 38016083);	/* 22 */
  GG (c, d, a, b, in[15], S23, 3634488961);	/* 23 */
  GG (b, c, d, a, in[4], S24, 3889429448);	/* 24 */
  GG (a, b, c, d, in[9], S21, 568446438);	/* 25 */
  GG (d, a, b, c, in[14], S22, 3275163606);	/* 26 */
  GG (c, d, a, b, in[3], S23, 4107603335);	/* 27 */
  GG (b, c, d, a, in[8], S24, 1163531501);	/* 28 */
  GG (a, b, c, d, in[13], S21, 2850285829);	/* 29 */
  GG (d, a, b, c, in[2], S22, 4243563512);	/* 30 */
  GG (c, d, a, b, in[7], S23, 1735328473);	/* 31 */
  GG (b, c, d, a, in[12], S24, 2368359562);	/* 32 */

  /* Round 3 */
#define S31 4
#define S32 11
#define S33 16
#define S34 23
  HH (a, b, c, d, in[5], S31, 4294588738);	/* 33 */
  HH (d, a, b, c, in[8], S32, 2272392833);	/* 34 */
  HH (c, d, a, b, in[11], S33, 1839030562);	/* 35 */
  HH (b, c, d, a, in[14], S34, 4259657740);	/* 36 */
  HH (a, b, c, d, in[1], S31, 2763975236);	/* 37 */
  HH (d, a, b, c, in[4], S32, 1272893353);	/* 38 */
  HH (c, d, a, b, in[7], S33, 4139469664);	/* 39 */
  HH (b, c, d, a, in[10], S34, 3200236656);	/* 40 */
  HH (a, b, c, d, in[13], S31, 681279174);	/* 41 */
  HH (d, a, b, c, in[0], S32, 3936430074);	/* 42 */
  HH (c, d, a, b, in[3], S33, 3572445317);	/* 43 */
  HH (b, c, d, a, in[6], S34, 76029189);	/* 44 */
  HH (a, b, c, d, in[9], S31, 3654602809);	/* 45 */
  HH (d, a, b, c, in[12], S32, 3873151461);	/* 46 */
  HH (c, d, a, b, in[15], S33, 530742520);	/* 47 */
  HH (b, c, d, a, in[2], S34, 3299628645);	/* 48 */

  /* Round 4 */
#define S41 6
#define S42 10
#define S43 15
#define S44 21
  II (a, b, c, d, in[0], S41, 4096336452);	/* 49 */
  II (d, a, b, c, in[7], S42, 1126891415);	/* 50 */
  II (c, d, a, b, in[14], S43, 2878612391);	/* 51 */
  II (b, c, d, a, in[5], S44, 4237533241);	/* 52 */
  II (a, b, c, d, in[12], S41, 1700485571);	/* 53 */
  II (d, a, b, c, in[3], S42, 2399980690);	/* 54 */
  II (c, d, a, b, in[10], S43, 4293915773);	/* 55 */
  II (b, c, d, a, in[1], S44, 2240044497);	/* 56 */
  II (a, b, c, d, in[8], S41, 1873313359);	/* 57 */
  II (d, a, b, c, in[15], S42, 4264355552);	/* 58 */
  II (c, d, a, b, in[6], S43, 2734768916);	/* 59 */
  II (b, c, d, a, in[13], S44, 1309151649);	/* 60 */
  II (a, b, c, d, in[4], S41, 4149444226);	/* 61 */
  II (d, a, b, c, in[11], S42, 3174756917);	/* 62 */
  II (c, d, a, b, in[2], S43, 718787259);	/* 63 */
  II (b, c, d, a, in[9], S44, 3951481745);	/* 64 */

  *h0 += a;
  *h1 += b;
  *h2 += c;
  *h3 += d;
}

void MD5Calc(unsigned char *inBuf, UINT4 inLen, UINT4 *h0, UINT4 *h1, UINT4 *h2, UINT4 *h3)
{

  /* Load magic initialization constants.
   */
  *h0 = (UINT4) 0x67452301;
  *h1 = (UINT4) 0xefcdab89;
  *h2 = (UINT4) 0x98badcfe;
  *h3 = (UINT4) 0x10325476;

  UINT4 in[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,(inLen << 3),0};

  unsigned int i, ii;

  /* append length scratch_in bits and transform */
  for (i = 0, ii = 0; i < 4; i++, ii += 4)
    in[i] = ((UINT4) inBuf[ii + 3] << 24) |
            ((UINT4) inBuf[ii + 2] << 16) |
            ((UINT4) inBuf[ii + 1] << 8 ) | 
             (UINT4) inBuf[ii];
  in[4] = 0x80;

  Transform(in, h0, h1, h2, h3);
}


__kernel void MD5Check(__global blah *a)
{
    UINT4 i = 0;
    UINT4 h0;
    UINT4 h1;
    UINT4 h2;
    UINT4 h3;

    for(i = 0; i < a->nriter; i++){
        MD5Calc(a->inString, a->len, &h0, &h1, &h2, &h3);
        if (h0 == a->wanted[0] &&
            h1 == a->wanted[1] &&
            h2 == a->wanted[2] && 
            h3 == a->wanted[3]) {
            a->wanted[0] = h0;
            a->wanted[1] = h1;
            a->wanted[2] = h2;
            a->wanted[3] = h3;
            return;
        }
    } 
    a->wanted[0] = 0;
    a->wanted[1] = 0;
    a->wanted[2] = 0;
    a->wanted[3] = 0;
    return;
}
