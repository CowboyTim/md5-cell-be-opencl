all:  md5

md5: md5.o md5_kernel_ACCELERATOR_CellBE_processor.ocl
	$(CC) $(LDFLAGS) md5.o -o md5

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%_ACCELERATOR_CellBE_processor.ocl: %.cl
	opencl_build_program $<

clean:
	@rm -f md5 md5.o md5_kernel_ACCELERATOR_CellBE_processor.ocl

CC      = gcc
CFLAGS  = -I. -g -Os
LDFLAGS = -lOpenCL -lm -lstdc++
