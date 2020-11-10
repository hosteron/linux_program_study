TARGET=$(notdir $(shell pwd))
#SRC=$(shell ls *.c)
SRC = svmsg_create.c
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon
svmsg_create:$(SRC)
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
svmsg_send:svmsg_send.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
svmsg_receive:svmsg_receive.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
clean:
	rm -f svmsg_create *.o svmsg_send svmsg_receive
