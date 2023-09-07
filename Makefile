# ---------------------------------------------------------
# Roger Boesch, (C)2020
#
# Makefile for example game for Sinclair ZX Spectrum Next.
# Uses spritelib from Stefan Bylund
# ---------------------------------------------------------

# Shell command used
RMDIR := rmdir /s /q
MKDIR := mkdir

# Folders
SPRITELIB_SRC := spritelib
SPRITELIB_LIB := lib/sccz80
BINARY := bin
LIBRARY := lib
LIB_TARGET := sccz80
LIBDIR_SCCZ80 := lib\sccz80
LIBDIR_SDCC_IX := lib\sdcc_ix
LIBDIR_SDCC_IY := lib\sdcc_iy

# Compiler settings
CFLAGS := +zxn -subtype=nex -vn -O3 -startup=0 -clib=new -m $(DEBUG)

# Emulator settings
EMULATOR := CSpect.exe
EMULATOR_FLAGS := -fullscreen -basickeys -sound -w2 -60 -vsync -zxnext -mmc=./

# Game source
GAME_SRCS := game.c game_engine.c sprites.c

all: game

game:
	zcc $(CFLAGS) $(GAME_SRCS) -o $(BINARY)/game -create-app

build: game
	$(EMULATOR) $(EMULATOR_FLAGS) bin/game.nex

run:
	$(EMULATOR) $(EMULATOR_FLAGS) bin/game.nex

clean:
	$(RMDIR) $(BINARY)
	$(MKDIR) $(BINARY)
