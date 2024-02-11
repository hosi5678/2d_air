#!/bin/bash

directory="./ez_timestep_csvs/"

if [ -d "$directory" ]; then
   echo "direcory:" "$directory found"
   cd "$directory"
   touch "dummy.csv"
   rm *.csv
   cd ..
else
   mkdir "$directory"
   cd "$directory"
   touch "dummy.csv"
   cd ..
fi

directory="./hx_timestep_csvs/"

if [ -d "$directory" ]; then
   echo "direcory:" "$directory found"
   cd "$directory"
   touch "dummy.csv"
   rm *.csv
   cd ..
else
   mkdir "$directory"
   cd "$directory"
   touch "dummy.csv"
   cd ..
fi

directory="./hy_timestep_csvs/"

if [ -d "$directory" ]; then
   echo "direcory:" "$directory found"
   cd "$directory"
   touch "dummy.csv"
   rm *.csv
   cd ..
else
   mkdir "$directory"
   cd "$directory"
   touch "dummy.csv"
   cd ..
fi



directory="./csv_files/"

if [ -d "$directory" ]; then
   echo "direcory:" "$directory found"
   cd "$directory"
   touch "dummy.csv"
   rm *.csv
   cd ..

else
   mkdir "$directory"
   cd "$directory"
   cd ..

fi

directory="./build/"

if [ -d "$directory" ]; then
   echo "directory:" "$directory found"
   rm -rf "$directory"
   echo "directory:" "$directory" " was deleted."

   mkdir "$directory"
   echo "directory:" "$directory" " was created."

else
   mkdir  "$directory"
fi

directory="./mp4/"

if [ -d "$directory" ]; then
   echo "directory" "$directory found"

   cd "$directory"
   touch "dummy.mp4"

   rm *.mp4

   cd ..

   tree > tree.txt

else
   mkdir  "$directory"
fi

cmake -B ./build -G Ninja
cd ./build
ninja -t clean
ninja
cd ..
