TARGET=$(notdir $(shell pwd))
SRC=$(shell ls *.c)
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon -lrt
pshm_create:pshm_create.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
pshm_write:pshm_write.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
pshm_read:pshm_read.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
pshm_unlink:pshm_unlink.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
clean:
	rm -f $(TARGET) *.o pshm_create pshm_write pshm_read pshm_unlink
