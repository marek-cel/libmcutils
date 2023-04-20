call clean.bat

mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=%LIMBCUTILS_DIR%
cmake --build . --config Release