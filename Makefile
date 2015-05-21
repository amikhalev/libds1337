# Filename: Makefile
# Author: 	Alex Mikhalev
# Date:		May 20, 2015

CC 			:= avr-gcc
AR 			:= avr-ar
CPUFLAGS	:=-mmcu=atmega16 -DF_CPU=1000000UL
CFLAGS		=-Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields ${CPUFLAGS} -I ${SRC_DIR}

SRC_DIR		:= ./src
BUILD_DIR 	:= ./build

SRCS 		:= $(wildcard ${SRC_DIR}/*.c)
OBJS		:= $(subst ${SRC_DIR}/,${BUILD_DIR}/,${SRCS:.c=.o})
OUTPUT_LIB	:= ${BUILD_DIR}/libds1337.a

.PHONY: all

all: ${OUTPUT_LIB}

clean:
	rm ${OBJS} ${OUTPUT_LIB}

${BUILD_DIR}/%.o: ${SRC_DIR}/%.c ${BUILD_DIR}
	${CC} ${CFLAGS} -c -o "$@" "$<"
	
${BUILD_DIR}:
	mkdir ${BUILD_DIR}
	
${OUTPUT_LIB}: ${OBJS}
	${AR} -r "${OUTPUT_LIB}" $(OBJS) $(LIBS)