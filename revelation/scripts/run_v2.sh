#!/bin/sh
# to run: $ . file.sh
file="./run_v2.sh"

if [ -r $file ]
then
   cd ../../dissimulation
   chmod 777 build.sh
   ./build.sh
   #./dissimulate -in RGB_test.png -c Red -b 4 -out ../revelation/resource/TEST/direct/version01 -msg "abcdefghijklmnopqrstuvxz" -compress > file_log.txt

   #./dissimulate -in RGB_test.png -c Red -b 4 -out ../revelation/resource/TEST/direct/version02 -msg "ababababababab" -compress > file_log.txt

   #./dissimulate -in RGB_test.png -c Red -b 4 -out ../revelation/resource/TEST/direct/version03 -msg "aaaaaaaaaaaaaaaaa" -compress > file_log.txt

   #./dissimulate -in RGB_test.png -c Red -b 8 -out ../revelation/resource/TEST/direct/version04 -msg "ééééèèèèàààààççççç" -compress > file_log.txt

   ./dissimulate -in RGB_test.png -c Red,Green,Blue -b 1 -out ../revelation/resource/TEST/direct/version05 -msg ../revelation/resource/TEST/txt/big_text.txt -compress more > file_log.txt

   cd ../revelation
   ./build.sh
#   ./reveal -in resource/TEST/direct/version01.png -b 3 -c Red -p direct -compress
#   echo "diff "
#   echo "abcdefghijklmnopqrstuvxz" > resource/TEST/txt/version01.txt
#   sdiff -B -b -s resource/TEST/txt/version01.txt resource/output/msg_decompress.txt | wc

#   ./reveal -in resource/TEST/direct/version02.png -b 3 -c Red -p direct -compress
#   echo "diff "
#   echo "abab" > resource/TEST/txt/version02.txt
#   sdiff -B -b -s resource/TEST/txt/version02.txt resource/output/msg_decompress.txt | wc

#   ./reveal -in resource/TEST/direct/version03.png -b 4 -c Red -p direct -compress
#   echo "diff "
#   echo "aaaa" > resource/TEST/txt/version03.txt
#   sdiff -B -b -s resource/TEST/txt/version03.txt resource/output/msg_decompress.txt | wc

#   ./reveal -in resource/TEST/direct/version04.png -b 8 -c Red -p direct -compress
#   echo "diff "
#   echo "ééééèèèèàààààççççç" > resource/TEST/txt/version04.txt
#   sdiff -B -b -s resource/TEST/txt/version04.txt resource/output/msg_decompress.txt | wc

   ./reveal -in resource/TEST/direct/version05.png -c Red,Green,Blue -b 1 -p direct -compress more
   echo "diff "
   sdiff -B -b -s resource/TEST/txt/big_text.txt resource/output/msg_decompress.txt | wc
else
   echo "-- error"
fi