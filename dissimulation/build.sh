#!/bin/sh
# to run: $ . file.sh
file="./build.sh"

if [ -r $file ]
then
   echo "-- build the module"
   mkdir class
   javac -d class -sourcepath Java/src/ Java/src/kgms/*.java
   jar cvmf MANIFEST.MF dissimulation.jar -C ./class .
   echo "-- build with success"
   echo "#!/bin/bash" > ./dissimulate
   echo "java -jar dissimulation.jar \"\$@\"" >> ./dissimulate
   chmod 774 dissimulate
else
   echo "-- error"
fi
