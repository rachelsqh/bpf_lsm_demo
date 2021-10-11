srctree = /usr/src/linux-source-5.10
objtree = srctree
all:
	$(Q)clang -O2 -g -D__KERNEL__ -target bpf -I/usr/include/x86_64-linux-gnu/ -c lsm_kern.c -o lsm_kern.o
	bpftool gen skeleton lsm_kern.o > lsm_kern.h
	$(Q)gcc -o loader loader.c $(srctree)/tools/lib/bpf/libbpf.a /usr/lib/x86_64-linux-gnu/libz.a /usr/lib/x86_64-linux-gnu/libelf.a
clean:
	rm -rf *.o loader
