#!/bin/sh
# to run: $ . file.sh
file="./run_v3.sh"

if [ -r $file ]
then
   cd ../../dissimulation
   chmod 777 build.sh
   ./build.sh
   ./dissimulate -in test.png -c Red,Green,Blue -b 4 -out ../revelation/resource/TEST/direct/version05 -msg specs.pdf -compress > file_log.txt

   cd ../revelation
   ./build.sh
   ./reveal -in resource/TEST/direct/version05.png -c Red,Green,Blue -b 4 -p direct -out resource/output.pdf -compress
   #echo "diff "
   #diff -B -b -s resource/TEST/txt/big_text.txt resource/output/msg_decompress.txt | wc
else
   echo "-- error"
fi