# A ZX Spectrum Next Game

I work on a ZX Spectrum Next Game for the following reasons:

- The ZX Spectrum was my first computer
- I love retro (game) programming
- I like to document the path to a finished game and make it easier for others to start

Because C/C++ is my daily (main) programming language I have decided to go the C route.
Maybe some parts have to be implemented in Z80 Assembler, but I will decide that on the way.

*Note: The informations and make script are related to Windows but will work with minor changes also on macOS and Linux*

Currently I still work on the basics but I will add later more informations about the game itself

Next steps are:

- [ ] Add text functionality
- [ ] Load sprites from file
- [ ] Add sound
- [ ] Start with the game


## Build the source

Building the source is as easy as type-in

```bash
make
```

If not, then follow this steps:

1. Install the [Z88DK](https://github.com/z88dk/z88dk) crosscompiler toolchain
2. Install CSpect (Sinclair ZX Spectrum Emulator)
2. Set *%PATH%* environment variable to CSpect folder
3. Download the *zxnext_game repository either* as a ZIP archive using the "Clone or download" button at the top of this page or with Git using the following command:

```git clone https://github.com/rogerboesch/zxnext_game.git```

Go to the zxnext_game directory and enter the following command:

```make game```

To build and start it directly after in the emulator type in:

```make build```

If you just want start the program without building at first type in:

```make run```


### Toolchain

On Windows, make is not available by default and you have to install it first.
I use the *Chocolatey* package manager for this and I can just highly recommend it.

### Sprite Library

I use for the game a modified version of Stefan Bylunds SpriteLib.
You find the original README file in the spritelib folder and also on his [Github](https://github.com/stefanbylund/zxnext_sprite) repo.


## More informations

Find here [Info](INFO.md) some more information about Z88DK and ZX Spectrum/Next programming in genefral
