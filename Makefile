# ---------------------------------------------------------
# Roger Boesch, (C)2020
#
# Makefile for example game for Sinclair ZX Spectrum Next.
# Uses spritelib from Stefan Bylund
# ---------------------------------------------------------

# Shell command used
RM := rm -rf
MKDIR := mkdir -p
CURRENT_DIR := $(shell pwd)

# Folders
SPRITELIB_SRC := spritelib
SPRITELIB_LIB := lib/sccz80
BINARY := bin
LIBDIR_SCCZ80 := lib/sccz80
LIBDIR_SDCC_IX := lib/sdcc_ix
LIBDIR_SDCC_IY := lib/sdcc_iy

# Compiler settings
CFLAGS := +zxn -subtype=nex -vn -O3 -startup=0 -clib=new -m $(DEBUG) -L$(SPRITELIB_LIB) -lzxnext_sprite -I$(SPRITELIB_SRC)

# Emulator settings
EMULATOR := /Applications/ZEsarUX.app/Contents/MacOS/zesarux
EMULATOR_FLAGS := --machine tbblue --enable-mmc --enable-divmmc-ports --mmc-file ../Resources/tbblue.mmc --quickexit

# Game source
GAME_SRCS := game_engine.c \
	game.c

# Spritelib source
SPRITELIB_SRCS := $(SPRITELIB_SRC)/set_sprite_layers_system.c \
	$(SPRITELIB_SRC)/get_sprite_system_state.c \
	$(SPRITELIB_SRC)/set_sprite_display_palette.c \
	$(SPRITELIB_SRC)/set_sprite_rw_palette.c \
	$(SPRITELIB_SRC)/set_sprite_palette.c \
	$(SPRITELIB_SRC)/reset_sprite_palette.c \
	$(SPRITELIB_SRC)/set_sprite_slot.c \
	$(SPRITELIB_SRC)/set_sprite_pattern.c \
	$(SPRITELIB_SRC)/set_sprite_attributes.c \
	$(SPRITELIB_SRC)/set_sprite_attributes_ext.c \
	$(SPRITELIB_SRC)/load_sprite_patterns.c \
	$(SPRITELIB_SRC)/load_sprite_palette.c

all: spritelib_sccz80 all_game

all_game:
	$(MKDIR) $(BINARY)
	zcc $(CFLAGS) $(GAME_SRCS) -o $(BINARY)/game -create-app

spritelib_sccz80:
	$(MKDIR) $(LIBDIR_SCCZ80)
	zcc +zxn -vn -O3 -x -clib=new $(DEBUG) -Iinclude $(SPRITELIB_SRCS) -o $(LIBDIR_SCCZ80)/zxnext_sprite

run: all_game
	$(EMULATOR) $(CURRENT_DIR)/bin/game.nex $(EMULATOR_FLAGS)

clean:
	$(RM) lib bin zcc_opt.def
