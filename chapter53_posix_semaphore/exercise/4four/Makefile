TARGET=$(notdir $(shell pwd))
SRC=$(shell ls *.c)
CFLAGS=-I/home/xiangzhou/workdir/linux_program_study/common/lib
LDFLAGS=-L/home/xiangzhou/workdir/linux_program_study/common/lib -lcommon -pthread
$(TARGET):$(SRC)
	gcc $< ${CFLAGS} ${LDFLAGS} -o  $@
clean:
	rm -f $(TARGET) *.o
