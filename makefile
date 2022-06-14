# Usage:
# make			# compile all binary
# make clean	# remove ALL binaries and object

.PHONY = all

CC = gcc				# compiler
LIB_DIR = lib
OUTPUT_DIR = output
OUT_NAME = mnist		# binary filename
MAIN = main

LIB_SRCS := $(wildcard ${LIB_DIR}/*.c)
LIB_BINS := $(LIB_SRCS:lib/%.c=%)
OUTPUT := $(LIB_BINS:%=${OUTPUT_DIR}/%.o) ${OUTPUT_DIR}/main.o

all: make_output_dir compile merge

make_output_dir:
ifeq ("$(wildcard ${OUTPUT_DIR})", "")
	@echo "Creating output directory..."
	@mkdir output
endif

compile:
	@echo "Creating objects..."
	@$(foreach BIN, ${LIB_BINS}, ${CC} ${LIB_DIR}/${BIN}.c -o ${OUTPUT_DIR}/${BIN}.o -c;)
	@echo "Creating main..."
	@${CC} ${MAIN}.c -o ${OUTPUT_DIR}/${MAIN}.o -c

merge:
	@echo "Creating output..."
	@${CC} -o ${OUT_NAME} ${OUTPUT}

clean:
	@echo "Deleting output..."
	@rm -rf ${OUTPUT_DIR}
	@echo "Deleting output file..."
	@rm -rf $(strip ${OUT_NAME}).exe