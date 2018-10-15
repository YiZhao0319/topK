/*
 * This file function is hashing each URL in source file into sub files
 * The result is a hash sub file,name like resolved_1.txt,resolved_2.txt,resolved_3.txt ...
 *
 * Author:
 *   add zhaoyi 20181008
 */


#ifndef HASH_FILE
#define HASH_FILE

#include<iostream>
#include<string>
#include "urlelement.h"

//a hash function that uses this function to hash each url
unsigned int ELFhash(const char *url);

//Hash each URL into a sub file
void hashFiles(string source_file_name,int file_num);


#endif // HASH_FILE

