CC = gcc
OPTIONS = -o -funsigned-char 
EXE = finalpoker
INCLUDE = objects.h
OBJS = finalpoker.c
.PHONY: all clean run

all: ${OBJS}
	@echo "Building.." 
	${CC} ${INCLUDE}
	${CC} ${OPTIONS} ${INCLUDE} ${OBJS} target_bin 
	
%.o: %.c  # % pattern wildcard matching
	${CC} ${OPTIONS} -c $*.c ${INCLUDES}
list:
	@echo $(shell ls) #
run: ${EXE}
	@echo "Running..."
	./${EXE}
clean:
	@echo "Cleaning up.."
	-rm -rf *.o 
	-rm target_bin
