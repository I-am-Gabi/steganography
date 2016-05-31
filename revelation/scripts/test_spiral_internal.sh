#!/bin/sh
# to run: $ . file.sh
file="./test_spiral_internal.sh"

if [ -r $file ]
then
   echo ""
   echo "> spiral internal pattern"

   time ../reveal -in ../resource/TEST/internal/internal_Blue_3.png -b 3 -c Blue -out ../resource/TEST/output/spiral_internal/internal_Blue_3_png.txt -p internal_spiral
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/ammonium_chloride.txt ../resource/TEST/output/spiral_internal/internal_Blue_3_png.txt | wc

   time ../reveal -in ../resource/TEST/internal/internal_Blue_8.png -b 8 -c Blue -out ../resource/TEST/output/spiral_internal/internal_Blue_8_png.txt -p internal_spiral
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/ammonium_chloride.txt ../resource/TEST/output/spiral_internal/internal_Blue_8_png.txt | wc

   time ../reveal -in ../resource/TEST/internal/internal_Red_1.png -b 1 -c Red -out ../resource/TEST/output/spiral_internal/internal_Red_1_png.txt -p internal_spiral
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/ammonium_chloride.txt ../resource/TEST/output/spiral_internal/internal_Red_1_png.txt | wc

   time ../reveal -in ../resource/TEST/internal/internal_Green_1.png -b 1 -c Green -out ../resource/TEST/output/spiral_internal/internal_Green_1_png.txt -p internal_spiral
   echo "> diff"
   sdiff -B -b -s ../resource/TEST/txt/ammonium_chloride.txt ../resource/TEST/output/spiral_internal/internal_Green_1_png.txt | wc

else
   echo "-- error"
fi
