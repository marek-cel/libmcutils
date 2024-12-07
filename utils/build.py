#!/usr/bin/env python3

import os
import platform
import subprocess
import sys
import clean
import misc

build_dir = "build"


def build(with_tests):
    if with_tests:
        misc.printGreen("Building with tests...")
    else:
        misc.printGreen("Building...")
    os_name = platform.system()
    if os_name == "Linux":
        buildForLinux(with_tests)
    elif os_name == "Windows":
        buildForWindows(with_tests)
    misc.printGreen("Building done.")


def buildForLinux(with_tests):
    cmake_cmd = [
        'cmake', '.',
        '-DCMAKE_BUILD_TYPE=Release',
        '-DCMAKE_INSTALL_PREFIX=/usr/local',
        '-B', build_dir
    ]
    if with_tests:
        cmake_cmd.append('-DBUILD_TESTING=On \
                         -DCMAKE_CXX_FLAGS=-O0 \
                         -fno-elide-constructors \
                         -fno-default-inline \
                         -fprofile-arcs -ftest-coverage')
    else:
        cmake_cmd.append('-DBUILD_TESTING=Off')
    result = subprocess.run(cmake_cmd)
    if result.returncode == 0:
        subprocess.run(
            "cmake --build " + build_dir + " --config Release -j 4 --target all tests-mcutils --",
            shell=True
        )


def buildForWindows(with_tests):
    cmake_cmd = [
        'cmake', '.',
        '-DCMAKE_BUILD_TYPE=Release',
        '-B', build_dir
    ]
    if os.getenv('LIBMCUTILS_DIR') is not None:
        install_dir = os.getenv('LIBMCUTILS_DIR')
        cmake_cmd.append('-DCMAKE_PREFIX_PATH=' + install_dir)
    if with_tests:
        cmake_cmd.append('-DBUILD_TESTING=On \
                         -DCMAKE_CXX_FLAGS=-O0 \
                         -fno-elide-constructors \
                         -fno-default-inline \
                         -fprofile-arcs -ftest-coverage')
    else:
        cmake_cmd.append('-DBUILD_TESTING=Off')
    print(" ".join(cmake_cmd))
    result = subprocess.run(cmake_cmd)
    if result.returncode == 0:
        subprocess.run(
            "cmake --build " + build_dir + " --config Release -j 4",
            shell=True
        )


if __name__ == "__main__":
    clean.removeBuildDirs()
    os.chdir("..")
    with_tests = False
    if "--with-tests" in sys.argv:
        with_tests = True
    build(with_tests)
