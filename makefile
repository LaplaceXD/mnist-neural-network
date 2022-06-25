# Usage:
# make				# compile ALL binaries
# make clean_dir	# remove ALL output directories
# make clean		# remove ALL binaries

.PHONY = all

CC = gcc				# compiler
CFLAGS = -Wall -Werror -Os
LIB_DIR = lib
OUTPUT_DIR = output
OUT_NAME = mnist		# binary filename
MAIN = main

OUT_NAME := $(strip ${OUT_NAME})
OUTPUT_DUPES := $(wildcard ${OUTPUT_DIR}*)
OUTPUT_COUNT := $(words ${OUTPUT_DUPES})
ifneq (${OUTPUT_COUNT}, 0)
	OUTPUT_DIR := "${OUTPUT_DIR}(${OUTPUT_COUNT})"
endif

LIB_SRCS := $(wildcard ${LIB_DIR}/*.c)
LIB_BINS := $(LIB_SRCS:lib/%.c=%)
OUTPUT := $(LIB_BINS:%=${OUTPUT_DIR}/%.o) ${OUTPUT_DIR}/main.o

all: make_output_dir compile merge clean_up

make_output_dir:
	@echo "Creating output directory..."
	@mkdir ${OUTPUT_DIR}

compile:
	@echo "Creating objects..."
	@$(foreach BIN, ${LIB_BINS}, ${CC} ${CFLAGS} -c ${LIB_DIR}/${BIN}.c -o ${OUTPUT_DIR}/${BIN}.o;)
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

clean_dir:
	@echo "Removing output directories..."
	@$(foreach DUPE, ${OUTPUT_DUPES}, rm -rf "${DUPE}";)

clean:
	@echo "Removing ${OUT_NAME}.exe..."
	@rm -rf ${OUT_NAME}.exe