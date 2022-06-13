# Usage:
# make			# compile all binary
# make clean	# remove ALL binaries and object

.PHONY = all

CC = gcc				# compiler
OUTPUT_DIR = output
OUT_NAME = mnist		# binary filename
MAIN = main

LIBS := $(wildcard lib/*)
LIBS_BINS := $(LIBS:lib/%=%)
OUTPUT := $(LIBS_BINS:%=${OUTPUT_DIR}/%.o) ${OUTPUT_DIR}/main.o

all: make_output_dir compile_lib merge_lib

make_output_dir:
ifeq ("$(wildcard ${OUTPUT_DIR})", "")
	@echo "Creating output directory..."
	mkdir output
endif

compile_lib:
	@echo "Creating objects..."
	@$(foreach LIB, ${LIBS_BINS}, ${CC} lib/${LIB}/${LIB}.c -o ${OUTPUT_DIR}/${LIB}.o -c;)
	@echo "Creating main..."
	@${CC} ${MAIN}.c -o ${OUTPUT_DIR}/${MAIN}.o -c

merge_lib:
	@echo "Creating output..."
	@${CC} -o ${OUT_NAME} ${OUTPUT}

clean:
	@echo "Deleting output..."
	@rm -rf ${OUTPUT_DIR}
	@echo "Deleting output file..."
	@rm -rf $(strip ${OUT_NAME}).exe