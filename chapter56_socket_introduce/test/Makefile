TARGET=$(notdir $(shell pwd))
SRC=$(shell ls *.c)
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon
sock_udp_s:sock_udp_s.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
sock_udp_c:sock_udp_c.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
sock_udp_c1:sock_udp_c1.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
clean:
	rm -f $(TARGET) *.o sock_udp_s sock_udp_c sock_udp_c1
