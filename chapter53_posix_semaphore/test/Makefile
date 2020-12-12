TARGET=$(notdir $(shell pwd))
SRC=$(shell ls *.c)
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon -pthread
psem_create:psem_create.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
psem_unlink:psem_unlink.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
psem_wait:psem_wait.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
psem_post:psem_post.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
psem_getvalue:psem_getvalue.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@

clean:
	rm -f $(TARGET) *.o psem_create psem_unlink psem_wait psem_post psem_getvalue
