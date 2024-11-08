all:  runner

runner: cl_compile_kernel runner.o md5_kernel.ocl
	$(CC) $(LDFLAGS) runner.o -o runner -lOpenCL

%.ocl: %.cl
	./cl_compile_kernel $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

cl_compile_kernel:
	$(CC) $(CFLAGS) $(LDFLAGS) -o cl_compile_kernel cl_compile_kernel.c -lOpenCL

clean:
	@rm -f runner runner.o cl_compile_kernel

CC      = gcc
CFLAGS  = -I. -g -O3 -Wall -Wextra
LDFLAGS =
