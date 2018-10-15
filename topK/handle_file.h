/*
 * The function of this file is spliting large subfiles and counting the topK of each subfile.
 *
 * Author:
 *   add zhaoyi 20181008
 */


#ifndef HANDLE_FILE
#define HANDLE_FILE

#include<iostream>
#include<string>
#include<limits.h>
#include "urlelement.h"

using namespace std;

//Split large subfiles and count the topK of each subfile
void handle_and_sort(int file_num, int file_size,int topK);
long long getFileSize(string file_name);
//Split large files which size larger than file_size into multiple small files
void cut_big_file(string filename,int &sub_file_num,int file_size);
//Merge small files that count the number of URL occurrences, and superimpose the same URL in different small files.
void merge(string pre_file_name,int n,int topK);
//Sort the number of occurrences of URL in the file
void sortFiles(string source_file_name,int topK = INT_MAX);

#endif // HANDLE_FILE

