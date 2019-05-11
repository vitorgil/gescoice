Set-Variable -Name "install_path"  -Value "C:/projects/coice/install"
Set-Variable -Name "toolchain_bin" -Value "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64i/bin"
Set-Variable -Name "qt_path"       -Value "C:/Qt/5.12.3/mingw73_64"

$env:Path += ";$toolchain_bin"

cmake .. -G "MinGW Makefiles" `
         -DCMAKE_INSTALL_PREFIX="$install_path" `
         -DCMAKE_PREFIX_PATH="$qt_path/lib/cmake/Qt5" `
         -DGTEST_ROOT="C:/googletest-distribution"

mingw32-make -j5 install

# Copy because these are not on the path
Copy-Item "$qt_path/bin/Qt5Widgets.dll" -Destination $install_path/bin/
Copy-Item "$qt_path/bin/Qt5Core.dll"    -Destination $install_path/bin/
Copy-Item "$qt_path/bin/Qt5Gui.dll"     -Destination $install_path/bin/
Copy-Item "$toolchain_bin/libgcc_s_seh-1.dll"  -Destination $install_path/bin/
Copy-Item "$toolchain_bin/libstdc++-6.dll"     -Destination $install_path/bin/
Copy-Item "$toolchain_bin/libwinpthread-1.dll" -Destination $install_path/bin/
