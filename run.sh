#!/bin/bash

# *.csv、*.mp4の削除
find ./ -type f -name "*.csv" -delete
find ./ -type f -name "*.mp4" -delete

directory="./ez_timestep_csvs/"

if [ -d "$directory" ]; then
   echo "direcory:" "$directory found"
else
   mkdir "$directory"
fi

directory="./hx_timestep_csvs/"

if [ -d "$directory" ]; then
   echo "direcory:" "$directory found"
else
   mkdir "$directory"
fi

directory="./hy_timestep_csvs/"

if [ -d "$directory" ]; then
   echo "direcory:" "$directory found"
else
   mkdir "$directory"
fi

directory="./csv_files/"

if [ -d "$directory" ]; then
   echo "direcory:" "$directory found"
else
   mkdir "$directory"
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
else
   mkdir  "$directory"
fi

tree > tree.txt

# ninjaでbuildする
cmake -B ./build -G Ninja
cd ./build
ninja -t clean
ninja
cd ..
