/*
 * Record the URL and number of occurrences in the file
 *
 * Author:
 *   add zhaoyi 20181008
 *
 */


#ifndef URLELEMENT
#define URLELEMENT

#include<iostream>
using namespace std;

struct UrlElement
{
        string url;//URL content
        int count;//The number of occurrences
        UrlElement():url(""),count(0){}
};

#endif // URLELEMENT

