#!/bin/sh
# to run: $ . file.sh
file="./test_parser.sh"

if [ -r $file ]
then
   cd ../..
   ./reveal -in resource/TEST/direct/file_error.png -b 12 -c Red,Green,Blue -out resource/TEST/output/direct/version01.txt -p direct
   cat resource/output/log.txt

   ./reveal -in resource/TEST/direct/version01.png -b 12 -c Red,Green,Blue -out resource/TEST/output/direct/version01.txt -p direct
   cat resource/output/log.txt

   ./reveal -in resource/TEST/direct/version01.png -b 1 -c Reder -out resource/TEST/output/direct/version01.txt -p direct
   cat resource/output/log.txt

   ./reveal -in resource/TEST/direct/version01.png -b -1 -c Red,Green,Blue -out resource/TEST/output/direct/version01.txt -p direction
   cat resource/output/log.txt

   ./reveal -Fin jpg -in resource/TEST/direct/version01.png -b 1 -c Red,Green,Blue -out resource/TEST/output/direct/version01.txt -p direct
   cat resource/output/log.txt

   echo "\n"

   ./reveal -in resource/NOVALID/ERROR_jpg.png -b 1 -c Red,Green,Blue -out resource/TEST/output/direct/version01.txt -p direct
   cat resource/output/log.txt

   ./reveal
   cat resource/output/log.txt

else
   echo "-- error"
fi