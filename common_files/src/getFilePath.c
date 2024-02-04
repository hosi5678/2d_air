#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/getFilePath.h"

// file名のみを与えて、dir,拡張子をつけて文字列ポインタを返す

char *getFilePath(const char *src_dir,const char *src_file_name,const char *extension){

   int dir_length;
   int file_name_length;
   int extension_length;
   int file_path_length;

   dir_length=strlen(src_dir);
   file_name_length=strlen(src_file_name);
   extension_length=strlen(extension);

   file_path_length=dir_length+file_name_length+extension_length;

   static char *file_path;

   file_path=(char *)calloc(file_path_length + 1 , sizeof(char));

   strcat(file_path,src_dir);
   strcat(file_path,src_file_name);
   strcat(file_path,extension);

   // printf("file_path=%s\n",file_path);

   return file_path;

}
