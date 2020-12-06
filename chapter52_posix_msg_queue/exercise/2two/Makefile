TARGET=$(notdir $(shell pwd))
SRC=$(shell ls *.c)
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib -g
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon -lrt
mq_seqnum_server:mq_seqnum_server.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
mq_seqnum_client:mq_seqnum_client.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@


clean:
	rm -f $(TARGET) *.o mq_seqnum_server mq_seqnum_client
