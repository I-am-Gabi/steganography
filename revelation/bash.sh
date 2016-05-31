#!/bin/sh
# to run: $ . file.sh
file="./bash.sh"

if [ -r $file ]
then
   echo "-- KGMS --"
   cmake .
   make
   cd bin
   # echo "export PATH=$PATH:." >> ~/.bashrc
   # source ~/.bashrc
else
   echo "-- erro --"
fi
