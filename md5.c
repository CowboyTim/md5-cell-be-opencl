

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>


/* typedef a 32 bit type */
typedef unsigned long int UINT4;

UINT4 h0;
UINT4 h1;
UINT4 h2;
UINT4 h3;

inline void endian_swap (UINT4 *x) {
    *x =   (*x >> 24)               |
	      ((*x << 8 ) & 0x00FF0000) | 
          ((*x >> 8 ) & 0x0000FF00) | 
           (*x << 24);
}

void MD5Print(unsigned char *inString){
    UINT4 hh0 = h0, hh1 = h1, hh2 = h2, hh3 = h3;
    endian_swap(&hh0);
    endian_swap(&hh1);
    endian_swap(&hh2);
    endian_swap(&hh3);
    fprintf(stderr, "%08x%08x%08x%08x", (unsigned int)hh0, (unsigned int)hh1, (unsigned int)hh2, (unsigned int)hh3);
    fprintf(stderr, " \"%s\"\n\n", inString);
}

typedef struct {
    unsigned char wanted[4];
    unsigned char inString[17];
    unsigned int  len;
    unsigned int  nriter;
} blah;


int main(){

    cl_uint        nr_devices;
    cl_device_id   device;
    clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ACCELERATOR, 1, &device, &nr_devices);

    cl_int err = 0;
    cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if (ctx == NULL)
        fprintf(stderr, "Error creating context: %d\n", err);


    int source = 0;
    char fn[] = "md5_kernel_ACCELERATOR_CellBE_processor.ocl";
    char fn_src[] = "md5_kernel.cl";
    char * buffer;
    FILE *pFile;
    pFile = fopen(fn, "rb");
    if (pFile==NULL) {
        source = 1;
        pFile = fopen(fn_src, "rb");
        if (pFile==NULL) {
            fprintf(stderr, "Error opening file %s error: %s\n", fn_src, strerror(errno)); 
            exit(1);
        }
    }
    fseek(pFile , 0 , SEEK_END);
    long lSize = ftell(pFile);
    rewind(pFile);
    buffer = (unsigned char*)malloc(sizeof(unsigned char)*lSize);
    size_t result = fread(buffer,1,lSize,pFile);
    fclose(pFile);

    cl_program clp;
    if(source){
        const char *b = buffer;
        clp = clCreateProgramWithSource(ctx, 1, &b, &result, &err);
        if (clp == NULL || err != CL_SUCCESS)
            fprintf(stderr, "Error creating program: %d\n", err);

        cl_int r = clBuildProgram(clp, 1, &device, NULL, NULL, NULL);
        if( r != CL_SUCCESS )
            fprintf(stderr, "Error building program: %d\n", r);

        size_t clp_iptr_sizes[1];
        cl_int clp_i_r = clGetProgramInfo(clp, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), &clp_iptr_sizes, NULL);
        if(clp_i_r != CL_SUCCESS)
            fprintf(stderr, "Error program info sizes: %d\n", clp_i_r);
        fprintf(stderr, "Size: %d\n", (unsigned int)clp_iptr_sizes[0]);
        void * clp_iptr[1];
        clp_iptr[0] = (void *)malloc(sizeof(unsigned char)*clp_iptr_sizes[0]);
        clp_i_r = clGetProgramInfo(clp, CL_PROGRAM_BINARIES, sizeof(unsigned char)*clp_iptr_sizes[0], &clp_iptr, NULL);
        if(clp_i_r != CL_SUCCESS)
            fprintf(stderr, "Error program info sizes: %d\n", clp_i_r);
        fprintf(stderr, "Writing size: %d\n", (unsigned int)clp_iptr_sizes[0]);
        FILE *pFileC = fopen(fn, "wb");
        if (pFileC==NULL) {
            fprintf(stderr, "Error opening %s for writing: %s\n", fn, strerror(errno)); 
            exit (1);
        }
        fwrite(clp_iptr[0],clp_iptr_sizes[0]*sizeof(unsigned char),1,pFileC);
        fclose(pFileC);
        free(clp_iptr[0]);

    } else {
        void * clb;
        clb = buffer;
        clp = clCreateProgramWithBinary(ctx, 1, &device, &result, clb, NULL, &err);
        if (clp == NULL || err != CL_SUCCESS)
            fprintf(stderr, "Error creating binary program: %d\n", err);

        cl_int r = clBuildProgram(clp, 1, &device, NULL, NULL, NULL);
        if( r != CL_SUCCESS )
            fprintf(stderr, "Error building program: %d\n", r);

    }
    free(buffer);

    cl_kernel clk = clCreateKernel(clp, "MD5Check", &err);
    if( clk == NULL )
        fprintf(stderr, "Error creating kernel: %d\n", err);


    blah * arg;
    arg = (blah *)malloc(sizeof(blah));
    strcpy(&arg->inString, "xxxxxxxxxxxxxxxa\0");
    arg->len = strlen(arg->inString);
    arg->nriter = 5;

    /* this is 'xxxxxxxxxxxxxxxx' */
    char digest_wanted[] = "45ed9cc2f92b77cd8b2f5bd59ff635f8";
    UINT4 digest_wanted_hex1;
    UINT4 digest_wanted_hex2;
    UINT4 digest_wanted_hex3;
    UINT4 digest_wanted_hex4;

    sscanf ((const char *)digest_wanted, "%08x%08x%08x%08x",
          (unsigned int *)&digest_wanted_hex1,
          (unsigned int *)&digest_wanted_hex2,
          (unsigned int *)&digest_wanted_hex3,
          (unsigned int *)&digest_wanted_hex4);
    endian_swap(&digest_wanted_hex1);
    endian_swap(&digest_wanted_hex2);
    endian_swap(&digest_wanted_hex3);
    endian_swap(&digest_wanted_hex4);

    arg->wanted[0] = digest_wanted_hex1;
    arg->wanted[1] = digest_wanted_hex2;
    arg->wanted[2] = digest_wanted_hex3;
    arg->wanted[3] = digest_wanted_hex4;

    cl_mem clb = clCreateBuffer(ctx, CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR, sizeof(blah), arg, &err);
    if( clb == NULL )
        fprintf(stderr, "Error creating buffer: %d\n", err);

    cl_int oka = clSetKernelArg(clk, 0, sizeof(cl_mem), &clb);
    if( oka != CL_SUCCESS )
        fprintf(stderr, "Error setting kernel ARGS: %d\n", oka);

    cl_command_queue clc = clCreateCommandQueue(ctx, device, 0, &err);
    if( clc == NULL )
        fprintf(stderr, "Error creating command queue: %d\n", err);

    fprintf(stderr, "Enqueuing kernel\n");
	size_t global_dimensions[] = {6,1};
    cl_int ok = clEnqueueNDRangeKernel(clc, clk, 2, NULL, (const size_t *)&global_dimensions, NULL, 0, NULL, NULL);
    if( ok != CL_SUCCESS )
        fprintf(stderr, "Error enqueuing kernel: %d\n", ok);

    /*
    fprintf(stderr, "Waiting for readBuffer\n");
    cl_int ok2 = clEnqueueReadBuffer(clc, clb, CL_TRUE, 0, 13, rbuf, 0, NULL, NULL);
    if( ok2 != CL_SUCCESS )
        fprintf(stderr, "Error enqueuing readbuffer: %d\n", ok2);

    fprintf(stderr, "DONE: %s\n", rbuf);
    */

    free(arg);

    return 0;
}
