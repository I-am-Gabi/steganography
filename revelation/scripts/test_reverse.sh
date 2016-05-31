#!/usr/bin/env bash

# to run: $ . file.sh
file="./test_reverse.sh"

if [ -r $file ]
then
   echo ""
   echo "> reverse pattern"

   time ../reveal -in ../resource/TEST/reverse/reverse_Blue_3.png -b 3 -c Blue -out ../resource/TEST/output/reverse/reverse_Blue_3_png.txt -p reverse
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/agrange.txt ../resource/TEST/output/reverse/reverse_Blue_3_png.txt | wc

   time ../reveal -in ../resource/TEST/reverse/reverse_Green_8.png -b 8 -c Green -out ../resource/TEST/output/reverse/reverse_Green_8_png.txt -p reverse
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/ammonium_chloride.txt ../resource/TEST/output/reverse/reverse_Green_8_png.txt | wc

else
   echo "-- error"
fi
