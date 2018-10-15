/*
 * This file function is hashing each URL in source file into sub files
 * The result is a hash sub file,name like resolved_1.txt,resolved_2.txt,resolved_3.txt ...
 *
 * Author:
 *   add zhaoyi 20181008
 */


#include<iostream>
#include<string>
#include<fstream>
#include "hash_file.h"

/**
 * @brief a hash function that uses this function to hash each url
 * @param url[in] Url that needs hash
 * [out] hash value
 */
unsigned int ELFhash(const char *url)
{
        unsigned int hash=0;
        unsigned int x=0;
        char* str = const_cast<char *>(url);
        while(*str)
        {
                hash=(hash<<4)+*str;
                if((x=hash & 0xf0000000)!=0)
                {
                        hash^=(x>>24);
                        hash&=~x;
                }
                str++;
        }
        return (hash & 0x7fffffff);
}


/**
 * @brief Hash each URL into a sub file
 * @param source_file_name[in] original url set file
 * @param file_num[in] max sub file number
 * [out] sub files
 */
void hashFiles(string source_file_name,int file_num)
{
        string url;
        ifstream source_file;
        source_file.open(source_file_name);
        if(!source_file)
                return ;

        while(getline(source_file,url))
        {
                unsigned int file_hash = ELFhash(url.c_str()) % file_num;
                //The hashed sub file's name , eg:resolved_1.txt;
                string resolved = "resolved_" + to_string((long long)file_hash) + ".txt";
                ofstream resolved_file(resolved,ios::app);
                resolved_file << url << endl;
                resolved_file.close();
        }

        source_file.close();

}
