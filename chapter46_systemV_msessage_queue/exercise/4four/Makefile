TARGET=$(notdir $(shell pwd))
SRC=svmsg_file_server.c
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib -I./
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon
svmsg_file_server:$(SRC)
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
svmsg_file_client:svmsg_file_client.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
clean:
	rm -f svmsg_file_server *.o svmsg_file_client
