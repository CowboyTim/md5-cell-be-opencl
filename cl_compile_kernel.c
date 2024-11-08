#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CL_TARGET_OPENCL_VERSION 300
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>

char* common_read_file(const char *path, long *length_out) {
    char *buffer;
    FILE *f;
    long length;

    f = fopen(path, "r");
    assert(NULL != f);
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if (fread(buffer, 1, length, f) < (size_t)length) {
        return NULL;
    }
    fclose(f);
    if (NULL != length_out) {
        *length_out = length;
    }
    return buffer;
}

int main(int argc, char **argv) {
    FILE *f;
    char *binary;
    char *source;
    cl_context context;
    cl_device_id device;
    cl_platform_id platform;
    cl_program program;
    cl_int errorcode_ret;
    cl_int CL_err = CL_SUCCESS;
    cl_uint numPlatforms = 0;
    size_t binary_size;
    char *source_path;
    char *output_path;
    long lengths[1];
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <output>\n", argv[0]);
        return EXIT_FAILURE;
    }
    source_path = argv[1];
    output_path = argv[2];

    source = common_read_file(source_path, &lengths[0]);

    CL_err = clGetPlatformIDs(1, &platform, &numPlatforms);
    if (CL_err != CL_SUCCESS) {
        fprintf(stderr, "Error getting platform: %d\n", CL_err);
        return EXIT_FAILURE;
    }
    CL_err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    if (CL_err != CL_SUCCESS) {
        fprintf(stderr, "Error getting device: %d\n", CL_err);
        return EXIT_FAILURE;
    }
    context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    program = clCreateProgramWithSource(context, 1, (const char **)&source, (const size_t *)&lengths, &errorcode_ret);
    if (errorcode_ret != CL_SUCCESS) {
        fprintf(stderr, "Error creating program: %d\n", errorcode_ret);
        return EXIT_FAILURE;
    }
    CL_err = clBuildProgram(program, 1, &device, "", NULL, NULL);
    if (CL_err != CL_SUCCESS) {
        if (CL_err == CL_BUILD_PROGRAM_FAILURE) {
            size_t length;
            clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &length);
            char *log = malloc(length);
            clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, length, log, NULL);
            fprintf(stderr, "%s\n", log);
            free(log);
        }
        fprintf(stderr, "Error building program: %d\n", CL_err);
        return EXIT_FAILURE;
    }
    CL_err = clGetProgramInfo(program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), &binary_size, NULL);
    if (CL_err != CL_SUCCESS) {
        fprintf(stderr, "Error getting program info: %d\n", CL_err);
        return EXIT_FAILURE;
    }
    binary = malloc(binary_size);
    clGetProgramInfo(program, CL_PROGRAM_BINARIES, binary_size, &binary, NULL);
    f = fopen(output_path, "w");
    fwrite(binary, binary_size, 1, f);
    fclose(f);

    clReleaseProgram(program);
    clReleaseContext(context);
    return EXIT_SUCCESS;
}
