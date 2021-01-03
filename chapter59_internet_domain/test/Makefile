TARGET=$(notdir $(shell pwd))
SRC=$(shell ls *.c)
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon
i6d_ucase_cl:i6d_ucase_cl.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
i6d_ucase_sv:i6d_ucase_sv.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
is_seqnum_sv:is_seqnum_sv.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
is_seqnum_cl:is_seqnum_cl.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
clean:
	rm -f $(TARGET) *.o i6d_ucase_cl i6d_ucase_sv is_seqnum_sv is_seqnum_cl
