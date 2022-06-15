# Usage:
# make			# compile all binary
# make clean	# remove ALL binaries and object

.PHONY = all

CC = gcc				# compiler
LIB_DIR = lib
OUTPUT_DIR = output
OUT_NAME = mnist		# binary filename
MAIN = main

OUT_NAME := $(strip ${OUT_NAME})
OUTPUT_DUPES := $(wildcard ${OUTPUT_DIR}*)
OUTPUT_COUNT := $(words ${OUTPUT_DUPES})
OUTPUT_DIR := "${OUTPUT_DIR} (${OUTPUT_COUNT})"

LIB_SRCS := $(wildcard ${LIB_DIR}/*.c)
LIB_BINS := $(LIB_SRCS:lib/%.c=%)
OUTPUT := $(LIB_BINS:%=${OUTPUT_DIR}/%.o) ${OUTPUT_DIR}/main.o

all: make_output_dir compile merge clean_up

make_output_dir:
	@echo "Creating output directory..."
	@mkdir ${OUTPUT_DIR}

compile:
	@echo "Creating objects..."
	@$(foreach BIN, ${LIB_BINS}, ${CC} ${LIB_DIR}/${BIN}.c -o ${OUTPUT_DIR}/${BIN}.o -c;)
	@echo "Creating main..."
	@${CC} ${MAIN}.c -o ${OUTPUT_DIR}/${MAIN}.o -c

merge:
	@echo "Creating output..."
	@${CC} -o ${OUT_NAME} ${OUTPUT}

clean_up:
	@echo "Cleaning up..."
	@rm -rf ${OUTPUT_DIR}

run:
	@./${OUT_NAME}.exe	

remove:
	@echo "Removing ${OUT_NAME}.exe..."
	@rm -rf ${OUT_NAME}.exe