/*
 * The function of this file is to build a Minheap and determine the final topk set of elements
 *
 * Author:
 *   add zhaoyi 20181008
 */


#include<iostream>
#include<string>
#include<fstream>
#include<assert.h>
#include<vector>
#include "find_topk.h"


/**
 * @brief Adjust the Minheap
 * @param arr[out]
 * @param i[in]
 * @param length[in]
 */
void adjustHeap(vector<UrlElement> &arr,int i,int length)
{
    UrlElement temp = arr[i];
    for(int k=i*2+1;k<length;k=k*2+1)
    {
        if(k+1<length && arr[k].count > arr[k+1].count)
            k++;
        if(arr[k].count < temp.count)
        {
            arr[i] = arr[k];
            i = k;
        }
        else
            break;
    }
    arr[i] = temp;
}

void swap(vector<UrlElement> &arr,int a ,int b)
{
    UrlElement temp=arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

/**
 * @brief Find topK URL set
 * @param url_heap[out] Minheap that has been built, containing the topk URLs
 * @param file_num[in]
 * @param topK[in]
 */
void findTopK(vector<UrlElement> &url_heap,int file_num,int topK)
{
    //idx[i] is marked as the i-th sub file access to the idx[i]-th URL,the initial value is 1
    int idx[file_num];
    for(int i = 0;i < file_num;i++)
    {
        idx[i] = 1;
    }
    int i = 0;

    int size = topK;
    string file_name;
    ifstream source_file;
    //1.Construct the Minheap that size is k with the contents of the first subfile,
    //  if the element is not enough then get element from the second subfile, and so on,
    //  until the full element is taken or the k elements are taken
    while(i < file_num )
    {
        file_name = "resolved_" + to_string((long long)i) + ".txt";
        file_name = "sorted_" + file_name;
        source_file.open(file_name);
        if(!source_file)
        {
            i++;
            continue;
        }
        UrlElement url;
        while(idx[i] <= size && getline(source_file,url.url))
        {
            string c;
            getline(source_file,c);
            url.count = atoi(c.c_str());
            url_heap.push_back(url);
            idx[i]++;
        }
        size = size - idx[i] + 1;
        if(size > 0)
        {
            i++;
            source_file.close();
        }
        else
            break;
    }

    //2.Building Minheap
    for(int j=url_heap.size()/2-1;j>=0;j--)
    {
        adjustHeap(url_heap,j,url_heap.size());
    }

    //3.Take out the remaining elements and compare them one by one with the top of the Minstack.
    //  If the number of occurrences is greater than the top, replace the top with the element,
    //  otherwise start comparing the elements in the next subfile.
    for(i ;i < file_num;i++)
    {
        if(idx[i] == 1)
        {
            file_name = "resolved_" + to_string((long long)i) + ".txt";
            file_name = "sorted_" + file_name;
            source_file.open(file_name);
            if(!source_file)
                continue;
        }
        UrlElement url;
        while(getline(source_file,url.url) && idx[i] <= topK)
        {
            string c;
            getline(source_file,c);
            url.count = atoi(c.c_str());
            idx[i]++;
            if(url.count > url_heap[0].count)
            {
                url_heap[0] = url;
                for(int t=url_heap.size()/2-1;t>=0;t--)
                {
                    adjustHeap(url_heap,t,url_heap.size());
                }
            }
            else
                break;
        }
        source_file.close();
    }
}
