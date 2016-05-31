#!/bin/sh
# to run: $ . file.sh
file="./test_spiral_external.sh"

if [ -r $file ]
then
   echo ""
   echo "> spiral external pattern"

   time ../reveal -in ../resource/TEST/external/external_Green_8.png -b 8 -c Green -out ../resource/TEST/output/spiral_external/external_Green_8_png.txt -p external_spiral
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/ammonium_chloride.txt ../resource/TEST/output/spiral_external/external_Green_8_png.txt | wc

   time ../reveal -in ../resource/TEST/external/external_Red_1.png -b 1 -c Red -out ../resource/TEST/output/spiral_external/external_Red_1_png.txt -p external_spiral
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/ammonium_chloride.txt ../resource/TEST/output/spiral_external/external_Red_1_png.txt | wc

   #cd ..
   #time ./reveal -in resource/TEST/external/external_Blue_3.png -b 3 -c Blue -out resource/TEST/output/spiral_external/external_Blue_3_png.txt -p external_spiral
   #echo "> diff"
   #sdiff -B -b -s resource/TEST/txt/3-19disc.txt resource/TEST/output/spiral_external/external_Blue_3_png.txt | wc
else
   echo "-- error"
fi
