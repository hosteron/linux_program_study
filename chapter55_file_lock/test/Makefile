TARGET=$(notdir $(shell pwd))
SRC=$(shell ls *.c)
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon
t_flock:t_flock.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
i_fcntl_locking:i_fcntl_locking.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
fcntl_flock:fcntl_flock.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
fcntl_flock_content:fcntl_flock_content.c
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@

clean:
	rm -f $(TARGET) *.o t_flock i_fcntl_locking fcntl_flock fcntl_flock_content
