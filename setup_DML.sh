#!/bin/bash
git config --global --add safe.directory /home/user
git submodule update --init --recursive

mkdir -p third_party/DML/build
mkdir -p third_party/DML/dml_install

cd third_party/DML/build
#cmake -DDML_BUILD_EXAMPLES=OFF -DDML_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=../dml_install ..
cmake -DDML_BUILD_EXAMPLES=ON -DDML_BUILD_TESTS=ON -DCMAKE_INSTALL_PREFIX=../dml_install ..
cmake --build . --target install
