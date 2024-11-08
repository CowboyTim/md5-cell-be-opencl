all:  md5

md5: cl_compile_kernel md5.o md5_kernel.ocl
	$(CC) $(LDFLAGS) md5.o -o md5 -lOpenCL

%.ocl: %.cl
	./cl_compile_kernel $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

cl_compile_kernel:
	$(CC) $(CFLAGS) $(LDFLAGS) -o cl_compile_kernel cl_compile_kernel.c -lOpenCL

clean:
	@rm -f md5 md5.o cl_compile_kernel

CC      = gcc
CFLAGS  = -I. -g -O3 -Wall -Wextra
LDFLAGS =
