#pragma once
#include<string>
using namespace std;
enum Status
{
    running, waiting
};

//jobs or process
struct Job
{

    string jName;        // processor name
    Status jStatus;      // state for job 
    int partition;      // which the processor is assigned to
    int mRequest;     // amount of memory needed/requested for processor

};

