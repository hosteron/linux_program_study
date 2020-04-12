TARGET=$(notdir $(shell pwd))
SRC=$(shell ls *.c)
$(TARGET):$(SRC)
	gcc -o $@ $<
clean:
	rm -f $(TARGET) *.o
