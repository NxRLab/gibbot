# microchip's compiler
CC:=xc16-gcc
# microchip's archiver
AR:=xc16-ar
# microchip's hex converter
HX:=xc16-bin2hex
# target PIC
PROC:=33EP512MC806
# linker script
SCRIPT:=p$(PROC).gld
# microchip's install dir
MC_DIR:=/opt/microchip/mplabx

# programmer 
JAVA:=$(MC_DIR)/sys/java/jre1.7.0_67/bin/java
JAR:=$(MC_DIR)/mplab_ipe/ipecmd.jar
PK3:=$(JAVA) -jar $(JAR) -P$(PROC) -M -TPPK3 -OL

# library source and ouput directories
LIB_INCLUDE:=./include
LIB_DIR:=./lib
LIB_SRC_DIR:=./src ./src/boards
LIB_GIB:=$(LIB_DIR)/libgibbot.a

# hex directory
HX_DIR:=./hex

# ctags flags
TAGS_SRC_FLAGS:=--extra=+f --c-kinds=+x
TAGS_MCP_FLAGS:=--extra=+f --c-kinds=+px

# various compiler flags
PICFLAGS:=-mcpu=$(PROC) -msmart-io=1 -msfr-warn=off -mno-eds-warn -legacy-libc
CFLAGS:=-O1 -Wall -I $(LIB_INCLUDE) $(PICFLAGS)
LDFLAGS:=-Wl,--script=$(SCRIPT),--heap=2048
LDLIBS:=-L$(LIB_DIR) -lgibbot -ldsp-elf -lq
ARFLAGS:= crs
OUTPUT_OPTION=-MMD -MF $(LIB_DIR)/$(@F).d -o $@

# library files
LIB_SRC:=$(wildcard $(addsuffix /*.c, $(LIB_SRC_DIR)))
LIB_OBJ:=$(LIB_SRC:.c=.o)
LIB_DEP:=$(wildcard $(LIB_DIR)/*.o.d)

# hex dep files -- recursive (i.e., delayed) expansion is important here
HX_DEP=$(wildcard $(HX_DIR)/*.hex.d)

# rule to program device based on .hex file
%: $(HX_DIR)/%.hex
	$(PK3) -F$<
	$(RM) log.* MPLABXLog.xml*

# write dependency makefile for new build target, if valid directory
ABS_DIR:=$(wildcard $(abspath $(DIR)))
TARGET:=$(notdir $(ABS_DIR))
SRC:=$(wildcard $(ABS_DIR)/*.c)
ifneq ($(SRC),)
TARGET_HEX:=$(HX_DIR)/$(TARGET).hex
TARGET_ELF:=$(TARGET_HEX:.hex=.elf)
TARGET_LST:=$(TARGET_HEX:.hex=.lst)
CFLAGS+=-I $(DIR)
LDFLAGS+=-Wl,-Map=$(TARGET_LST)
MKFL:=$(TARGET_HEX).d
TRGTL:=$(TARGET_HEX): $(SRC) lib $(LIB_GIB)
CMPL:=$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET_ELF) $(SRC) $(LDLIBS)
HXL:=$(HX) $(TARGET_ELF)
RML:=$(RM) $(TARGET_ELF)
$(file > $(MKFL),$(TRGTL))
$(file >> $(MKFL),	$(CMPL))
$(file >> $(MKFL),	$(HXL))
$(file >> $(MKFL),	$(RML))
else
TARGET:=;
endif

# targets
program: $(TARGET)

all: lib docs tags

lib: $(LIB_GIB)

$(LIB_GIB): $(LIB_GIB)($(LIB_OBJ))

.INTERMEDIATE: $(LIB_OBJ)

.PHONY: docs
docs:
	doxygen docs/Doxyfile

.PHONY : tags
tags:
	ctags $(TAGS_SRC_FLAGS) $(LIB_SRC)
	ctags $(TAGS_SRC_FLAGS) -a -R $(LIB_INCLUDE)
	ctags $(TAGS_MCP_FLAGS) -a $(MC_DIR)/../xc16/v1.24/support/dsPIC33E/h/p$(PROC).h
	ctags $(TAGS_MCP_FLAGS) -a $(MC_DIR)/../xc16/v1.24/include/lega-c/*.h
	ctags $(TAGS_MCP_FLAGS) -a $(MC_DIR)/../xc16/v1.24/support/generic/h/*.h

.PHONY : ./src/utils.c

.PHONY : clean
clean:
	$(RM) $(LIB_GIB) $(HX_DIR)/*.hex $(HX_DIR)/*.lst 

.PHONY : distclean
distclean: clean
	$(RM) $(LIB_DEP) $(HX_DEP) tags
	$(RM) -r docs/html

# read dep files to recompile targets that depend on files not usually scanned
# for changes by make; continue processing if dep file does not exist.
-include $(LIB_DEP)
-include $(HX_DEP)
