$env:Path += ";C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin"

cmake .. -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX="c:/projects/coice/install"
mingw32-make -j5 install