# math-timer
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
