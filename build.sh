cmake .. -DCMAKE_INSTALL_PREFIX="${PWD}/../install" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make -j9
make install
