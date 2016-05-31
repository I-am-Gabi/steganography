#!/bin/sh
# to run: $ . file.sh
file="./test_direct.sh"

if [ -r $file ]
then
   echo ""
   echo "> direct pattern"

   time ../reveal -in ../resource/TEST/direct/direct_Gray_3.pgm -b 3 -c Gray -out ../resource/TEST/output/direct/direct_Gray_3_pgm.txt -p direct
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/test_m.txt ../resource/TEST/output/direct/direct_Gray_3_pgm.txt | wc

   time ../reveal -in ../resource/TEST/direct/direct_Green_1.png -b 1 -c Green -out ../resource/TEST/output/direct/direct_green_1_png.txt -p direct
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/ammonium_chloride.txt ../resource/TEST/output/direct/direct_green_1_png.txt | wc

   time ../reveal -in ../resource/TEST/direct/direct_Red_3.bmp -b 3 -c Red -out ../resource/TEST/output/direct/direct_Red_3_bmp.txt -p direct
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/test_m.txt ../resource/TEST/output/direct/direct_Red_3_bmp.txt | wc

   time ../reveal -in ../resource/TEST/direct/direct_Red_3.png -b 3 -c Red -out ../resource/TEST/output/direct/direct_Red_3_png.txt -p direct
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/test_m.txt ../resource/TEST/output/direct/direct_Red_3_png.txt | wc

   time ../reveal -in ../resource/TEST/direct/direct_Red_3.ppm -b 3 -c Red -out ../resource/TEST/output/direct/direct_Red_3_ppm.txt -p direct
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/test_m.txt ../resource/TEST/output/direct/direct_Red_3_ppm.txt | wc

   time ../reveal -in ../resource/TEST/direct/direct_Red_8.png -b 8 -c Red -out ../resource/TEST/output/direct/direct_red_8_png.txt -p direct
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/ammonium_chloride.txt ../resource/TEST/output/direct/direct_red_8_png.txt | wc

   time ../reveal -in ../resource/TEST/direct/direct_Red_Green_Blue_8.png -b 8 -c Red,Green,Blue -out ../resource/TEST/output/direct/direct_Red_Green_Blue_8_png.txt -p direct
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/adrien.txt ../resource/TEST/output/direct/direct_Red_Green_Blue_8_png.txt | wc

else
   echo "-- error"
fi
