# Homeschool Math Timer

A simple math timer program to let kids do lots of math problems in a certain amount of time.  Large colorful graphics and multiple levels of difficulty make this a fun way to pass the time.

![Alt text](/screenshots/playscreen.png?raw=true "Play Screen")
![Alt text](/screenshots/win-screen.png?raw=true "You Win")

## Ubuntu/Debian
I have a PPA (personal package archive) with all my homeschool programs
Add it this way (from a terminal), or use your favorite GUI to add a PPA

```
sudo add-apt-repository ppa:israeldahl/homeschool
sudo apt update
sudo apt install homeschool-mathtimer
```
Enjoy!

## Nerd stuff below

You can build this yourself with cmake, and some libraries, mostly FLTK and stdc++/gcc/x11/xpm/pkg-config libraries

You probably have many of these already installed if you compile things often

If you use Arch... please package this as an AUR for people :smile:

### Note:
If you use Fedora most dev packages have the ending -devel
just do a:

`yum search <thing>`

or

`dnf search <thing>`

Build Depends on Debian/Ubuntu

- cmake
- gcc-multilib [amd64]
- g++-multilib [amd64]
- libc6
- libfltk-images1.3
- libfltk1.3
- libfltk1.3-dev
- libfltk1.3-compat-headers
- libgcc1
- libstdc++6
- libx11-dev
- libxpm-dev
- fluid
- pkg-config

This program requires an out of source build, so create a build directory, for example:
`mkdir -p bin`
then enter the directory and configure it with cmake
```
cd bin
cmake ..
```
Then once it configures run make
You can then run

```
make
sudo make install
```
unless you are already root... then you probably didn't need to even read this section.
