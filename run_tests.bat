set PATH=%PATH%;%LIBXML2_DIR%\bin;%GTEST_DIR%\bin

cd bin
call tests.exe --gtest_filter=* --gtest_break_on_failure

