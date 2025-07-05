#!/bin/bash

cmake -B build
cd build
make clean
make install
cd ..
echo "Installation completed"