#!/bin/bash

cd ../../../build
make
cd -
rm -rf out.txt out.root
#root -l -q testRun.C &> out.txt
#wait
#subl out.txt
