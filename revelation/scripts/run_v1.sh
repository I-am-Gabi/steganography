#!/bin/sh
# to run: $ . file.sh
file="./run_v1.sh"

if [ -r $file ]
then
   cd ../../dissimulation
   chmod 777 build.sh
   ./build.sh
   ./dissimulate -in RGB_test.png -c Red,Green,Blue -b 2 -out ../revelation/resource/TEST/direct/version01 -msg ../revelation/resource/TEST/txt/agrange.txt > file_log.txt
   cd ../revelation
   ./build.sh
   ./reveal -in resource/TEST/direct/version01.png -b 2 -c Red,Green,Blue -out resource/TEST/output/direct/version01.txt -p direct
   # if we wrote the message in the console
   # echo "version 1.0 project steganography" > resource/TEST/txt/version01.txt
   echo "diff "
   sdiff -B -b -s resource/TEST/txt/agrange.txt resource/TEST/output/direct/version01.txt | wc
else
   echo "-- error"
fi