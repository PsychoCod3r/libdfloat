#!/usr/bin/make
#
# Usage:
# make (to build libdfloat
# make clean (to remove temporary files)
# make test (to build test file)
#
# Makefile currently includes support for
# gcc as well as untested support for the
# LLVM and Open Watcom compilers.
#
# Modify environment variables for your
# system.

# Default is gcc running on *NIX
# Comment out if not using this setup
TEST_FILE := test.c
COMPILE := gcc
LINK := gcc
ARCHIVE := ar
DELETE := rm

#Uncomment for Open Watcom on Windows
#COMPILE := wcl386
#LINK := wlink
#ARCHIVE := wlib
#DELETE := del

# Uncomment for LLVM running on *NIX
#COMPILE := clang
#LINK := llvm-ld
#ARCHIVE := llvm-ld
#DELETE := rm

# Add any additional compiler options here.
CMP_OPT :=

#MK_OBJ is the option for compiling without linking
MK_OBJ :=
MK_OBJ += $(if $(findstring gcc, $(COMPILE)),-c,)
MK_OBJ += $(if $(findstring wcl, $(COMPILE)),-c,)
MK_OBJ += $(if $(findstring clang, $(COMPILE)),-c,)

# LNK_OPT contains the options for the linker
LNK_OPT :=
LNK_OPT += $(if $(findstring gcc, $(LINK)),-L . -ldfloat,)
LNK_OPT += $(if $(findstring wlink, $(LINK)),LIBPATH . LIBRARY dfloat.lib,)
LNK_OPT += $(if $(findstring llvm-ld, $(LINK)),-L . -ldfloat,)

#LIBRARY is the filename for the library to be built
LIBRARY :=
LIBRARY += $(if $(findstring ar, $(ARCHIVE)),libdfloat.a,)
LIBRARY += $(if $(findstring wlib, $(ARCHIVE)),dfloat.lib,)
LIBRARY += $(if $(findstring llvm-ld, $(ARCHIVE)),libdfloat.a,)

# ARC_CMD accounts for a + before each object filename
# in Open Watcom
ARC_CMD := $(if $(findstring wlib, $(ARCHIVE)),+,)

# Options for the archiving utility
ARC_OPT :=
ARC_OPT += $(if $(findstring ar, $(ARCHIVE)),-rsv,)
ARC_OPT += $(if $(findstring wlib, $(ARCHIVE)),-b -n,)
ARC_OPT += $(if $(findstring llvm-ld, $(ARCHIVE)),-link-as-library -o,)

# The next section accounts for different file extensions
# for the object files.

MAIN_OBJ :=
MAIN_OBJ += $(if $(findstring gcc, $(COMPILE)),dfloat.o,)
MAIN_OBJ += $(if $(findstring wcl, $(COMPILE)),dfloat.obj,)
MAIN_OBJ += $(if $(findstring clang, $(COMPILE)),dfloat.o,)

FREE_OBJ :=
FREE_OBJ += $(if $(findstring gcc, $(COMPILE)),dfloat_free.o,)
FREE_OBJ += $(if $(findstring wcl, $(COMPILE)),dfloat_free.obj,)
FREE_OBJ += $(if $(findstring clang, $(COMPILE)),dfloat_free.o,)

# Object file that the test file gets compiled into
TEST_OBJ :=
TEST_OBJ += $(if $(findstring gcc, $(COMPILE)),test.o,)
TEST_OBJ += $(if $(findstring wcl, $(COMPILE)),test.obj,)
TEST_OBJ += $(if $(findstring clang, $(COMPILE)),test.o,)

# Portion of link command to go before the object file when
# compiling the test program
LNK_CMD :=
LNK_CMD += $(if $(findstring gcc, $(LINK)),-o test,)
LNK_CMD += $(if $(findstring wlink, $(LINK)),FILE,)
LNK_CMD += $(if $(findstring llvm-ld, $(LINK)),-o test,)

.PHONY: clean test all

all: $(LIBRARY)
	@echo "Build complete"

# ARCHIVING PHASE:

$(LIBRARY): $(MAIN_OBJ) $(FREE_OBJ)
	$(ARCHIVE) $(ARC_OPT) $(LIBRARY) $(ARC_CMD)$(MAIN_OBJ) $(ARC_CMD)$(FREE_OBJ)

# COMPILATION PHASE:

$(MAIN_OBJ): dfloat.c dfloat.h
	$(COMPILE) $(CMP_OPT) $(MK_OBJ) dfloat.c

$(FREE_OBJ): dfloat_free.c dfloat.h
	$(COMPILE) $(CMP_OPT) $(MK_OBJ) dfloat_free.c

# POST-BUILD PHASE:

clean:
	$(DELETE) $(MAIN_OBJ) $(FREE_OBJ)

# Test file not included in repository
test:
	$(COMPILE) $(CMP_OPT) $(MK_OBJ) $(TEST_FILE)
	$(LINK) $(LNK_CMD) $(TEST_OBJ) $(LNK_OPT)
	@echo "Build complete"
