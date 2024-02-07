#!/bin/bash

directory="./csv_files"

if [ -d "$directory" ]; then
   echo "direcory:" "$directory found"
   cd "$directory"
   rm *.csv
   touch "dummy.csv"
   cd ..

else
   mkdir "$directory"
   cd "$directory"
   touch "dummy.csv"
   cd ..

fi

if [ -d "$directory" ]; then
   cd "$directory"

# 文字列が空でないかどうか,-nは文字列が "non-zero"、
# つまり空でない場合に真（true）となる。
   if [ -n "$directory" ]; then
      # ls *.csv
      rm *.csv
      echo "$directory csv files deleted suceeded."
   else
      echo "$directory no csv files found."
   fi

else
   echo "Error. $directory directory not found."
   exit 1
fi

cd ..

directory="./ey_timestep_csvs/"

if [ -d "$directory" ]; then
   echo "directory:" "$directory found"
   cd "$directory"
   touch "dummy.csv"
   cd ..

else
   mkdir  "$directory"
   cd  "$directory"
   touch "dummy.csv"
   cd ..

fi

if [ -d "$directory" ]; then
   cd "$directory"
   # csv_files=$(ls *.csv 2>/dev/null)
   # echo "$csv_files"

   if [ -n "$directory" ]; then
      # ls *.csv
      rm *.csv
      echo "$directory csv files deleted suceeded."
   else
      echo "$directory no csv files found."
   fi

else
   echo "Error. $directory directory not found."
   exit 1
fi

cd ..

directory="./mp4/"

if [ -d "$directory" ]; then
   echo "directory:" "$directory found"

   cd "$directory"

   touch "dummy.mp4"

   rm *.mp4

else
   mkdir "$directory"
   
   touch "dummy.mp4"

fi

cd ..

tree > tree.txt
# cp -r "../project/ ../Dropbox/c/project/"

# CMakeLists.txtでgaussianとsinの切り替えを行うので、./build/を一旦削除する

directory="./build/"

if [ -d "$directory" ]; then
   echo "directory:" "$directory found"
   rm -rf "$directory"
   echo "directory:" "$directory" " was deleted."

   mkdir "$directory"

else
   mkdir  "$directory"
fi

cmake -B ./build -G Ninja
cd ./build
ninja -t clean
ninja
cd ..
