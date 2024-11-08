#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>


/* typedef a 32 bit type */
typedef unsigned long int UINT4;

inline void endian_swap (UINT4 *x) {
    *x =   (*x >> 24)               |
          ((*x << 8 ) & 0x00FF0000) | 
          ((*x >> 8 ) & 0x0000FF00) | 
           (*x << 24);
}

void MD5Print(unsigned char *inString, UINT4 h0, UINT4 h1, UINT4 h2, UINT4 h3){
    UINT4 hh0 = h0, hh1 = h1, hh2 = h2, hh3 = h3;
    /*
    endian_swap(&hh0);
    endian_swap(&hh1);
    endian_swap(&hh2);
    endian_swap(&hh3);
    */
    fprintf(stderr, "%08x%08x%08x%08x", (unsigned int)hh0, (unsigned int)hh1, (unsigned int)hh2, (unsigned int)hh3);
    fprintf(stderr, " \"%s\"\n\n", inString);
}

typedef struct {
    unsigned int  wanted[4];
    unsigned char inString[17];
    unsigned int  len;
    unsigned int  nriter;
} blah;

int main(int argc, char *argv[]){
    cl_platform_id platform;
    cl_int CL_err = CL_SUCCESS;
    cl_uint        nr_platforms = 0;
    cl_device_id   device;
    cl_event       event;
    CL_err = clGetPlatformIDs(1, &platform, &nr_platforms);
    if (CL_err != CL_SUCCESS) {
        fprintf(stderr, "Error getting platform: %d\n", CL_err);
        return EXIT_FAILURE;
    }
    CL_err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    if (CL_err != CL_SUCCESS) {
        fprintf(stderr, "Error getting device: %d\n", CL_err);
        return EXIT_FAILURE;
    }
    cl_context ctx = clCreateContext(NULL, 1, &device, NULL, NULL, &CL_err);
    if (ctx == NULL){
        fprintf(stderr, "Error creating context: %d\n", CL_err);
        return EXIT_FAILURE;
    }
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <cl kernel .ocl> [<source>]\n", argv[0]);
        return EXIT_FAILURE;
    }
    int source = 0;
    char *fn = argv[1];
    char *fn_src = argv[2];
    char *buffer = NULL;
    FILE *pFile  = NULL;
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
    buffer = (char*)malloc(sizeof(unsigned char)*lSize);
    size_t result = fread(buffer,1,lSize,pFile);
    fclose(pFile);

    cl_program clp;
    if(source){
        fprintf(stderr, "Using source\n");
        const char *b = buffer;
        clp = clCreateProgramWithSource(ctx, 1, &b, &result, &CL_err);
        if (clp == NULL || CL_err != CL_SUCCESS){
            fprintf(stderr, "Error creating program: %d\n", CL_err);
            return EXIT_FAILURE;
        }

        cl_int r = clBuildProgram(clp, 1, &device, NULL, NULL, NULL);
        if( r != CL_SUCCESS ){
            fprintf(stderr, "Error building program: %d\n", r);
            return EXIT_FAILURE;
        }

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
        fprintf(stderr, "Using binary program\n");
        clp = clCreateProgramWithBinary(ctx, 1, &device, &result, (const unsigned char **)&buffer, NULL, &CL_err);
        if (clp == NULL || CL_err != CL_SUCCESS){
            if (CL_err == CL_INVALID_BINARY) {
                fprintf(stderr, "Invalid binary\n");
                return EXIT_FAILURE;
            }
            fprintf(stderr, "Error creating binary program: %d\n", CL_err);
            return EXIT_FAILURE;
        }

        cl_int r = clBuildProgram(clp, 1, &device, NULL, NULL, NULL);
        if( r != CL_SUCCESS ){
            fprintf(stderr, "Error building program: %d\n", r);
            return EXIT_FAILURE;
        }
    }
    free(buffer);

    cl_kernel clk = clCreateKernel(clp, "MD5Check", &CL_err);
    if( clk == NULL ){
        fprintf(stderr, "Error creating kernel: %d\n", CL_err);
        return EXIT_FAILURE;
    }


    blah *arg = NULL;
    arg = (blah *)malloc(sizeof(blah));

    /* this is 'xxxxxxxxxxxxxxxx' */
    char start_string[]  = "xxxxxxxxxxxxxxxx\0";
    char digest_wanted[] = "45ed9cc2f92b77cd8b2f5bd59ff635f8\0";

    memcpy(arg->inString, start_string, sizeof(arg->inString));
    arg->len = strlen((char *)arg->inString);
    arg->nriter = 5;

    sscanf(digest_wanted, "%08x%08x%08x%08x",
          (unsigned int *)&arg->wanted[0],
          (unsigned int *)&arg->wanted[1],
          (unsigned int *)&arg->wanted[2],
          (unsigned int *)&arg->wanted[3]);
    fprintf(stderr, "START: %s\n",   arg[0].inString);
    fprintf(stderr, "START: %d\n",   arg[0].len);
    fprintf(stderr, "START: %d\n",   arg[0].nriter);
    fprintf(stderr, "START: %08x\n", arg[0].wanted[0]);
    fprintf(stderr, "START: %08x\n", arg[0].wanted[1]);
    fprintf(stderr, "START: %08x\n", arg[0].wanted[2]);
    fprintf(stderr, "START: %08x\n", arg[0].wanted[3]);

    cl_mem clb = clCreateBuffer(ctx, CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR, sizeof(blah), arg, &CL_err);
    if( clb == NULL ){
        fprintf(stderr, "Error creating buffer: %d\n", CL_err);
        return EXIT_FAILURE;
    }

    cl_int oka = clSetKernelArg(clk, 0, sizeof(cl_mem), &clb);
    if( oka != CL_SUCCESS ){
        fprintf(stderr, "Error setting kernel ARGS: %d\n", oka);
        return EXIT_FAILURE;
    }

    cl_command_queue clc = clCreateCommandQueue(ctx, device, 0, &CL_err);
    if( clc == NULL ){
        fprintf(stderr, "Error creating command queue: %d\n", CL_err);
        return EXIT_FAILURE;
    }

    fprintf(stderr, "Enqueuing kernel\n");
    size_t global_dimensions[] = {6,1};
    cl_int ok = clEnqueueNDRangeKernel(clc, clk, 2, NULL, (const size_t *)&global_dimensions, NULL, 0, NULL, NULL);
    if( ok != CL_SUCCESS ){
        fprintf(stderr, "Error enqueuing kernel: %d\n", ok);
        return EXIT_FAILURE;
    }
    fprintf(stderr, "Waiting for kernel finish\n");
    clFinish(clc);

    fprintf(stderr, "Waiting for readBuffer\n");
    blah ret[1];
    cl_int ok2 = clEnqueueReadBuffer(clc, clb, CL_TRUE, 0, sizeof(blah), (unsigned char *)&ret, 0, &event, NULL);
    if( ok2 != CL_SUCCESS ){
        fprintf(stderr, "Error enqueuing readbuffer: %d\n", ok2);
        return EXIT_FAILURE;
    }
    fprintf(stderr, "DONE: %s\n",   ret[0].inString);
    fprintf(stderr, "DONE: %d\n",   ret[0].len);
    fprintf(stderr, "DONE: %d\n",   ret[0].nriter);
    fprintf(stderr, "DONE: %08x\n", ret[0].wanted[0]);
    fprintf(stderr, "DONE: %08x\n", ret[0].wanted[1]);
    fprintf(stderr, "DONE: %08x\n", ret[0].wanted[2]);
    fprintf(stderr, "DONE: %08x\n", ret[0].wanted[3]);

    clReleaseMemObject(clb);
    clReleaseKernel(clk);
    clReleaseProgram(clp);
    clReleaseCommandQueue(clc);
    clReleaseContext(ctx);
    free(arg);
    return 0;
}
