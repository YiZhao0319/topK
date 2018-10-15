/*
 * The function of this file is to build a Minheap and determine the final topk set of elements
 *
 * Author:
 *   add zhaoyi 20181008
 */


#ifndef FIND_TOPK
#define FIND_TOPK

#include<iostream>
#include<string>
#include "urlelement.h"
using namespace std;

//Adjust the Minheap
void adjustHeap(vector<UrlElement> &arr,int i,int length);
void swap(vector<UrlElement> &arr,int a ,int b);
//Find topK URL set
void findTopK(vector<UrlElement> & url_heap,int file_num,int topK);

#endif // FIND_TOPK

