TARGET=$(notdir $(shell pwd))
SRC=$(shell ls *.c)
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon -lrt
pmsg_unlink:pmsg_unlink.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
pmsg_create:pmsg_create.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
pmsg_getattr:pmsg_getattr.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
pmsg_send:pmsg_send.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
pmsg_receive:pmsg_receive.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
pmsg_notify_sig:pmsg_notify_sig.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
pmsg_notify_thread:pmsg_notify_thread.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@


clean:
	rm -f $(TARGET) *.o pmsg_unlink pmsg_create pmsg_getattr pmsg_send pmsg_receive pmsg_notify_sig pmsg_notify_thread
