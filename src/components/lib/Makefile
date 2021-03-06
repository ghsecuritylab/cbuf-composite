include Makefile.src Makefile.comp

LIB_OBJS=heap.o cobj_format.o
LIBS=$(LIB_OBJS:%.o=%.a)
MANDITORY=c_stub.o cos_asm_upcall.o cos_asm_ainv.o cos_component.o
MAND=$(MANDITORY_LIB)
SIMPLE_STACKS=c_stub.o cos_asm_upcall_simple_stacks.o cos_asm_ainv.o cos_component.o
SIMPLE_STKLIB=simple_stklib.o

.PHONY: all
all: $(LIBS) $(MAND) $(SIMPLE_STKLIB)

# we have to compile these without dietlibc so that there are not
# symbol conflicts and this is why we have the %.a here and don't
# output a .a file.
%.a:%.c
	$(info |     [CC]   Creating library file $@ from $^)
	@$(CC) $(CFLAGS) $(CINC) -o $(@:%.a=%.o) -c $<
	@$(AR) cr lib$@ $(@:%.a=%.o)

$(MAND): $(MANDITORY)
	@$(LD) -r -o $@ $^


$(SIMPLE_STKLIB): $(SIMPLE_STACKS)
	@$(LD) -r -o $@ $^

%.o:%.S
	$(info |     [AS]   Compiling assembly file $^ into $@)
	@$(AS) $(ASFLAGS) $(CINC) -c -o $@ $^

%.o:%.c
	$(info |     [CC]   Compiling C file $^ into $@)
	@$(CC) $(CFLAGS) $(CINC) -o $@ -c $^

clean:
	$(info |     [RM]   Cleaning up directory)
	@rm -f a.out *.o *.a *.d *~

distclean:
	make -C musl-1.1.11 distclean
	make -C lwip/cos clean
	make -C lua/cos clean
	make -C ps clean
	make -C posix clean
	make -C libccv clean
	make -C libopencv clean
	make -C libcxx clean
# keep the following commands in one line. make executes each line
# with a new shell.
	cd ck; ./configure; cd ..
	make -C ck distclean

musl: 
	cd musl-1.1.11; ./configure --disable-shared; cd ..
	make -C musl-1.1.11
	make -C musl-1.1.11 install

init: clean distclean musl all
	make -C lua/cos
# keep the following commands in one line. Same as above.
	cd ck; ./configure; cd ..
	make -C ck
	make -C lwip/cos
	make -C posix
	make -C ps
	make -C libccv cos_libccv.a
	make -C libcxx
	make -C libopencv

lwipclean:
	make -C lwip/cos clean
lwip: lwipclean
	make -C lwip/cos
