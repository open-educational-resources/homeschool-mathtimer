# Homeschool Math Timer

A simple math timer program to let kids do lots of math problems in a certain amount of time.  Large colorful graphics and multiple levels of difficulty make this a fun way to pass the time.

![Alt text](/screenshots/playscreen.png?raw=true "Play Screen")
![Alt text](/screenshots/win-screen.png?raw=true "You Win")
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
`sudo make install`

