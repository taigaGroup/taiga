#!/bin/bash

cd ../../../build
make
cd -
rm -rf out.txt
root -l -q testCamera.C &> out.txt
wait
subl out.txt
