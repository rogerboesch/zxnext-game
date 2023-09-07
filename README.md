# The ZX Spectrum Next Game with no Name

I work on a ZX Spectrum Next Game for the following reasons:

- The ZX Spectrum was my first computer
- I love retro (game) programming
- I like to document the path to a finished game and make it easier for others to start

Because C/C++ is my daily (main) programming language I have decided to go the C route.
Maybe some parts have to be implemented in Z80 Assembler, but I will decide that on the way.

*Note: The informations and script are related to macOS but will work probably also as is undre Linux.*


## Build the source

Building the source is as easy as type-in

```bash
make
```


Of course this is only true if you have already installed the Z88DK crosscompiler toolchain.
If not, you have to do this before (for Windows):

- Download Windows version of Z88DK
- Install make (Not necc. but highly recommended)S
- Install CSpect *(and also set path environment variable to CSpect folder)*
- Before start always execute batch file ```%USERPROFILE%\z88dk\z88dk_prompt.bat``` from the Z88DK folder to set path and config files
 
I use for the game a modified version of Stefan Bylunds SpriteLib.
You find the original README file in the spritelib folder and also on his Github repo at: https://github.com/stefanbylund/zxnext_sprite


## Some useful informations

### Z88DK

- https://github.com/z88dk/z88dk/wiki/installation
- https://github.com/z88dk/z88dk/wiki/Platform---Sinclair-ZX-Spectrum-Next


### ZX Spectrum Next

#### Create a ZX Spectrum dot command
zcc +zxn program.c -clib=classic -lndos -create-app -subtype=dot -o program

- For DOT commands it's recommended to use the ROM printer which can be enabled with the option -pragma-redirect:fputc_cons=fputc_cons_rom_rst
- File operations are available via <stdio.h> and <fcntl.h> by linking with the -lesxdos library.


#### Classic library

**Tilemap mode**

z88dk supports the Next tilemap screen mode. When using this screen mode the entire display is taken over and the following tilemap addresses are used: Tile definitions = $4c00, tilemap = $6c00. On startup, the palette is redefined to support the screen colour defined in <conio.h>.
When the tilemap is configured with attributes (i.e mode 64, 66) then changing the ink colour, for example using textcolor() will result in the character being printed in that colour.
Note: The font isn't automatically copied when switching to tilemap modes - you will need to do this programatically using console_ioctl() with the argument IOCTL_GENCON_SET_FONT32.
When using the IOCTL_GENCON_SET_FONT32 and IOCTL_GENCON_SET_UDGS ioctl values, the 8x8 characters are copied to the tile definitions in monochrome using colour indices of 0 for background and CLIB_TILES_PALETTE_SET_INDEX (default value 1) as set pixels.
The console driver supports your application changing the addresses for the tile definitions and tilemaps.


**Graphics**

The classic graphics operations are supported in all available screen modes. In tilemap mode you must call zxn_create_tilemap_graphics() from <arch/zxn.h> to setup the lores graphics set prior to plotting anything.


**Pragmas to control classic library**

https://github.com/z88dk/z88dk/wiki/Classic--Pragmas


**Math library**

https://github.com/z88dk/z88dk/wiki/Classic--Maths-Libraries


#### New library

**CRT**

https://github.com/z88dk/z88dk/wiki/CRT
The crt is the startup code that runs before calling main(). It is responsible for setting the memory map, instantiating device drivers on stdin/stdout/stderr, initializing the bss and data sections and calling any initialization code prior to calling main(). On return from main() it is responsible for closing open files, resetting the stack and preparing to return to the host.

**Pragma overrides**

Pragmas embedded in the C source can override the crt configuration. Pragmas can be located in any C source file in your project but it's best to keep them confined either to your main.c or to a dedicated file in projects that use makefiles and consist of many source files.

**Header files**

- https://github.com/z88dk/z88dk/wiki/Header-Files


**Library**

- **CRT0** holds the name of the crt file used by the classic C library. This is ignored when the new C library is used.
- OPTIONS lists the default compile line options. These can be overridden and augmented by the following CLIBs.
- **CLIB** lists options that are added to the compile when "-clib=???" appears on the compile line. For compiles using the new C library, **"-clib=new"**, "-clib=sdcc_ix" or "-clib=sdcc_iy" are used. The first one sets up a compile using sccz80 while the latter two set up compiles using sdcc with the distinction being which index register the C library uses.

For available CRT numbers see lst of files in:

**$PATH/z88dk/libsrc/_DEVELOPMENT/target/zxn/startup/zxn_crt_xxx.asm.m4**


### Other Resources

**C Programming**

- [ZX Spectrum Development with Z88DK](https://github.com/z88dk/z88dk/blob/master/doc/ZXSpectrumZSDCCnewlib_01_GettingStarted.md) 

**Assembler Programming**

- [Good summary for Assembler programming for the the ZX](https://github.com/varmfskii/zxnext_code/blob/master/zx_next_notes/zxnext_notes.pdf)
- [Assembler programming for the the ZX](http://chuntey.arjunnair.in/)
- [Assembler programming for the the ZX and ZX Next](https://www.chibiakumas.com/z80/ZXSpectrum.php)
- [Game programming for the ZX Spectrum](https://spectrumcomputing.co.uk/index.php?cat=96&id=2001501)
