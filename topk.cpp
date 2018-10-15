/*
 * Title:find topK URLs
 * 1.Hash each URL into a sub file
 * 2.Count the topK URLs in each sub file
 * 3.Create a heap of size k and then compare the count of occurrences of urls in subsequent files
 *
 * you need to set :
 * 1.the value of topK,that means you want to select topK URLs;
 * 2.the value of file_num and file_size ,hash files to sub files that number does not exceed file_num, and each file
 *   size does not exceed file_size.So you can So you can adjust file_num and file_size for better performance;
 * 3.the value of source_file_name,that is original URL set file,and one line per URL.
 *
 *
 * Author:
 *      add zhaoyi 20181008
 *
 */


#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"find_topk.h"
#include"handle_file.h"
#include"hash_file.h"
#include"urlelement.h"
using namespace std;
const int file_num = 125;//max sub file number
const int topK = 100;//select topK URLs
const long long file_size = 800*1024*1024;//sub file max size

int main()
{
        string source_file_name = "data.txt";//original url set file
        //1.hash each URL in source file into sub files
        hashFiles(source_file_name,file_num);
        //2.count the topK URLs in each sub file
        handle_and_sort(file_num,file_size,topK);
        //3.find topK URL set
        vector<UrlElement> url_heap;
        findTopK(url_heap,file_num,topK);
        //4.sort topK URL
        for(int j=url_heap.size()-1;j>0;j--){
            swap(url_heap,0,j);
            adjustHeap(url_heap,0,j);
        }
        //5.print the result
        cout << "the result is " << endl;
        for(int i = 0 ;i < url_heap.size();i++)
        {
                cout << "top "<< i + 1 << " is " << url_heap[i].url <<  " " <<url_heap[i].count << endl;
        }
        cout << endl;
        return 0;
 }
