#!/bin/sh
# to run: $ . file.sh
file="./build_test.sh"

if [ -r $file ]
then
   echo "-- run reveal test"

   chmod 777 *

   ./test_direct.sh

   ./test_reverse.sh

   ./test_spiral_external.sh

   #./test_spiral_internal.sh
else
   echo "-- error"
fi
