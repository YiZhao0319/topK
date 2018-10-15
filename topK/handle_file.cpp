/*
 * The function of this file is spliting large subfiles and counting the topK of each subfile.
 *
 * Author:
 *   add zhaoyi 20181008
 */


#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<assert.h>
#include<sys/stat.h>
#include "handle_file.h"

long long getFileSize(string file_name)
{
        struct stat statbuff;
        stat(file_name.c_str(),&statbuff);
        long long size = statbuff.st_size;
        return size;
}

/**
 * @brief Split large files which size larger than file_size into multiple small files
 * @param filename[in]
 * @param sub_file_num[out]  The number of small files that have been Split
 * @param file_size[in]
 */
void cut_big_file(string filename, int &sub_file_num, int file_size)
{
    //Determine if the file size is oversize
    if(getFileSize(filename) > file_size)
    {
        ifstream source_file;
        source_file.open(filename);
        if(!source_file)
            return ;
        string url;
        long long size = 0;

        //Construct a small file prefix
        //eg:source file name is resolved_1.txt, small file prefix is resolved_1_ ,
        //   and the small file's name will be resolved_1_0.txt , resolved_1_1.txt...
        string pre_file_name = filename.substr(0, filename.length()-4);
        pre_file_name = filename.substr(0, filename.length()-4) + "_";
        ofstream sub_file;
        int i = 0;
        string sub_file_name = pre_file_name + to_string((long long)i) + ".txt";
        sub_file.open(sub_file_name,ios::ate);
        assert(sub_file.is_open());

        //If the size of the URL is larger than the remaining size of the file, recreate a file,
        //otherwise append to the existing file
        while(getline(source_file,url))
        {
            long long length = url.length();
            if(size + length > file_size)
            {
                sub_file.close();
                i++;
                sub_file_name = pre_file_name + to_string((long long)i) + ".txt";
                sub_file.open(sub_file_name,ios::ate);
                assert(sub_file.is_open());
                size = 0;
            }
            sub_file << url << endl;
            size += length;
        }
        sub_file.close();
        source_file.close();
        sub_file_num = i+1;
    }
}


/**
 * @brief Merge small files that count the number of URL occurrences,
 *        and superimpose the same URL in different small files.
 * @param pre_file_name[in] The same prefix of the files that need to be merged
 * @param n[in] Number of files that need to be merged
 * @param topK[in]
 */
void merge(string pre_file_name,int n,int topK)
{
    map<string,int> url_count;
    for(int i = 0;i < n;i++)
    {
        string file_name = pre_file_name + to_string((long long)i) + ".txt";
        ifstream sub_file;
        sub_file.open(file_name);
        assert(sub_file.is_open());

        string url;
        while(getline(sub_file,url))
        {
            string c;
            getline(sub_file,c);
            int count = atoi(c.c_str());
            if(url_count.find(url) != url_count.end())
            {
                map<string,int>::iterator it = url_count.find(url);
                it->second += count;
            }
            else
            {
                url_count.insert(make_pair(url,count));
            }
        }
        sub_file.close();
    }

    //Write the merged result to a file
    string out_file_name = pre_file_name.substr(0, pre_file_name.length()-1) + ".txt";
    ofstream out_file(out_file_name,ios::ate);
    map<string,int>::iterator it;
    multimap<int,string> count_url;
    for(it = url_count.begin();it != url_count.end();it++)
    {
            count_url.insert(make_pair(it->second,it->first));
    }
    multimap<int,string>::reverse_iterator  rit ;
    int size = 0;
    for(rit = count_url.rbegin();rit != count_url.rend() && size < topK;rit++)
    {
            size++;
            out_file << rit->second << endl;
            out_file << rit->first << endl;
    }
    out_file.close();
}


/**
 * @brief Sort the number of occurrences of URL in the file
 * @param source_file_name[in]
 * @param topK[in]
 */
void sortFiles(string source_file_name,int topK)
{
        ifstream source_file;
        source_file.open(source_file_name);
        if(!source_file)
                return ;

        string url;
        map<string,int> url_count;
        //Count url occurrences
        while(getline(source_file,url))
        {
                if(url_count.find(url) != url_count.end())
                {
                        map<string,int>::iterator it = url_count.find(url);
                        it->second ++;
                }
                else
                {
                        url_count.insert(make_pair(url,1));
                }
        }

        source_file.close();

        //Write the statistics to a file with the file name sorted_resolved_X.txt,eg:sorted_resolved_1.txt
        string sorted = "sorted_" + source_file_name;
        ofstream sorted_file(sorted,ios::app);
        map<string,int>::iterator it ;
        multimap<int,string> count_url;
        for(it = url_count.begin();it != url_count.end();it++)
        {
                count_url.insert(make_pair(it->second,it->first));
        }
        multimap<int,string>::reverse_iterator  rit ;
        int size = 0;
        for(rit = count_url.rbegin();rit != count_url.rend() && size < topK;rit++)
        {
                size++;
                sorted_file << rit->second << endl;
                sorted_file << rit->first << endl;
        }
        sorted_file.close();
}


/**
 * @brief Split large subfiles and count the topK of each subfile
 * @param file_num[in]
 * @param file_szie[in]
 * @param topK[in]
 */
void handle_and_sort(int file_num,int file_size,int topK)
{
    for(int i = 0;i < file_num;i++)
    {
            string file_name = "resolved_" + to_string((long long)i) + ".txt";
            int sub_file_num = 0;
            cut_big_file(file_name,sub_file_num,file_size);
            //File size meets regulations
            if(sub_file_num == 0)
                sortFiles(file_name,topK);
            //File size is out of limits and needs to be separated
            else
            {
                string pre_file_name = file_name.substr(0, file_name.length()-4);
                pre_file_name = pre_file_name + "_";
                for(int j = 0;j < sub_file_num;j++)
                {
                    string sub_file_name = pre_file_name + to_string((long long)j) + ".txt";
                    sortFiles(sub_file_name);
                }
                pre_file_name = "sorted_" + pre_file_name;
                merge(pre_file_name,sub_file_num,topK);
            }
    }
}
