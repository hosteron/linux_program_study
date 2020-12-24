TARGET=$(notdir $(shell pwd))
SRC=$(shell ls *.c)
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon
us_xfr_sv:us_xfr_sv.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@ 
us_xfr_cl:us_xfr_cl.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@ 
ud_ucase_sv:ud_ucase_sv.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@ 
ud_ucase_cl:ud_ucase_cl.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@ 
clean:
	rm -f $(TARGET) *.o us_xfr_sv us_xfr_cl ud_ucase_sv ud_ucase_cl
