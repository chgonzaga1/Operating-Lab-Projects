#include<iostream>
#include<vector>
#include<string>
#include <iomanip>
#include "Partition.h"
#include "Job.h"

//complete the other functions, best to put it on a switch statement

void firstFit(vector<Job>& jobs, vector<partition>& partitions);
void nextFit(vector<Job>& jobs, vector<partition>& partitions);
void bestFit(vector<Job>& jobs, vector<partition>& partitions);
void worstFitFix(vector<Job>& jobs, vector<partition>& partitions);
void worstFitDyn(vector<Job>& jobs, vector<partition>& partitions);


int intakePartitions(vector<partition>& partitions);
int ReadJobs(vector<Job>& jobs);
void assignPartition(Job& job, int iPart, partition& partition);
void PrintResult(vector<Job>& jobs, vector<partition>& partitions, bool dynamic);

using namespace std;


int main() {
    cout << "Hello World" << endl;
 
    vector<Job> jobs;
    vector<partition> partitions;
    /*implente these functions read data for job information
    and Partitions */
    intakePartitions(partitions);
    ReadJobs(jobs);
    cout << endl;
    cout << "Please select a number from 1 to 5 to choose a fit: " << endl;
    cout << "1. First Fit Algorithm" << endl;
    cout << "2. Next Fit Algorithm " << endl;
    cout << "3. Best Fit Algorithm" << endl;
    cout << "4. Worst Fit Fix Algorithm" << endl;
    cout << "5. Worst Fit Dynamically Algorithm" << endl;

    int select;
    cin >> select;

    switch (select) {
    case 1:
        firstFit(jobs, partitions);
        break;
    case 2:
        nextFit(jobs, partitions);
        break;
    case 3:
        bestFit(jobs, partitions);
        break;
    case 4:
        worstFitFix(jobs, partitions);
        break;
    case 5:
        worstFitDyn(jobs, partitions);
        break;
    default:
        cout << "Restart Program :(" << endl;
    }

   
    PrintResult(jobs, partitions, select == 5);


    return 0;

}


// Read partition number and its sizes
// Function return partition number
int intakePartitions(vector<partition>& partitions)
{
    int n;
    cout << endl << "How many partitions do we require?: ";
    cin >> n;
    partitions.resize(n + 1);     // leave 0-entry empty 
    cout << "Now enter each size of the Partition" << endl;
    for (int i = 1; i <= n; i++) {
        int size;
        cout << "Partition " << i << " size: ";
        cin >> size;
        partitions[i].pSize = size;
        partitions[i].pAssigned = false;
    }
    return n;
}

//Reads number of jobs that are needed and the size of each job/process required
//Returns the number of process/jobs
int ReadJobs(vector<Job>& jobs)
{
    int n;
    cout << endl << "Enter a number of jobs: ";
    cin >> n;
    jobs.resize(n + 1);           // don't use 0-entry
    cout << "Now enter each size of the job/process" << endl;
    for (int i = 1; i <= n; i++) {
        int size;
        jobs[i].jName = "Job" + to_string(i);
        cout << "Size for " << jobs[i].jName << ": ";
        cin >> size;
        jobs[i].mRequest = size;
        jobs[i].jStatus = waiting;
        jobs[i].partition = 0;
    }

    return n;
}

/* Functions that assigns a partitions to a job
 Parameters: job, iPar, Partition
    job - a job to be put in a partition
   iPar - a number of partion to be assigne d to    
   partition - a memory partitions which is to be assigned, helps us to decide if assigned or not
   */

void assignPartition(Job& job, int iPart, partition& partition)
{
    job.partition = iPart;
    job.jStatus = running;
    partition.pAssigned = true;
}


/*
   First Fit Algorithm, parameters include jobs - an array of jobs and array of memory partitions
*/


void firstFit(vector<Job>& jobs, vector<partition>& partitions)
{
    for (int iJob = 1; iJob < jobs.size(); iJob++) {
        for (int iPart = 1; iPart < partitions.size(); iPart++) {
            if (partitions[iPart].pAssigned)
                // Partion is assigned
                continue;//skip if it is assigned
            if (partitions[iPart].pSize >= jobs[iJob].mRequest) {
                // The job now fits in the partition
                assignPartition(jobs[iJob], iPart, partitions[iPart]);
                // switch to next one
                break;
            }
        }
    }
}

// Next Fit algorithm,  



void nextFit(vector<Job>& jobs, vector<partition>& partitions)
{
    int iPart = 1;                                  // Partition to start
    for (int i = 1; i < jobs.size(); i++) {
        while (iPart < partitions.size()) {
            if (!partitions[iPart].pAssigned && partitions[iPart].pSize >= jobs[i].mRequest) {
                // The partition is not assigned and the job is takenn
                assignPartition(jobs[i], iPart, partitions[iPart]);
                break; //stop
            }
            iPart++;    // move up o the next partition  
        }
    }
}

//Best-fit Algorithm

void bestFit(vector<Job>& jobs, vector<partition>& partitions)
{
    int bestPart;
    int bestWaste;
    for (int i = 1; i < jobs.size(); i++) {
        bestPart = 0; //starting
              for (int iPart = 1; iPart < partitions.size(); iPart++) {
              if (partitions[iPart].pAssigned)
                // If a partision is assigned, skip this and we keep going
                continue; 
                   if (partitions[iPart].pSize >= jobs[i].mRequest) {
                if (bestPart == 0) {
                    // First not assigned partion
                    bestPart = iPart;   // Set partiation as the best
                    bestWaste = partitions[iPart].pSize - jobs[i].mRequest;
                }
                else {
                    int waste = partitions[iPart].pSize - jobs[i].mRequest;
                    if (waste < bestWaste) {
                        // Find better fitting
                        bestPart = iPart;
                        bestWaste = waste;
                    }
                }
            }
        }
        if (bestPart) { //after finding bestt
            // Now finds partiion in which job fit
            assignPartition(jobs[i], bestPart, partitions[bestPart]);
        }
    }
}
//worstFitFix Algorithm

void worstFitFix(vector<Job>& jobs, vector<partition>& partitions)
{
    int worstPart;
    int worstWaste;
    for (int iJob = 1; iJob < jobs.size(); iJob++) {
        worstPart = 0; //start at 0 to find worst Partition                                       
        for (int iPart = 1; iPart < partitions.size(); iPart++) {
            if (partitions[iPart].pAssigned)
                // The partition is assigned, skip this and wekeep going
                continue;
            if (partitions[iPart].pSize >= jobs[iJob].mRequest) {
                if (worstPart == 0) {
                    //
                    worstPart = iPart;
                    worstWaste = partitions[iPart].pSize - jobs[iJob].mRequest;
                }
                else {
                    int waste = partitions[iPart].pSize - jobs[iJob].mRequest;
                    if (waste > worstWaste) {
                        // currently found the worst, time to test 
                        worstPart = iPart;
                        worstWaste = waste;
                    }
                }
            }
        }
        if (worstPart) {
            //free partition baby
            assignPartition(jobs[iJob], worstPart, partitions[worstPart]);
        }
    }
}

//Worst Fit Dynamic algorithm
void worstFitDyn(vector<Job>& jobs, vector<partition>& partitions)
{
    int worstPart;
    int worstWaste;
    for (int i = 1; i < jobs.size(); i++) { //go every job
        worstPart = 0;    //start with no worst partition yet


        //j goes through every partition

        for (int j = 1; j < partitions.size(); j++) {
            if (partitions[j].pSize >= jobs[i].mRequest) {
                // THe partion has now extra pace for the job
                if (worstPart == 0) {
                    // This is a first partion in which the job fit
                    worstPart = j;
                    worstWaste = partitions[j].pSize - jobs[j].mRequest;
                }
                else {
                    int waste = partitions[i].pSize - jobs[i].mRequest;
                    if (waste > worstWaste) {
                        // worst has been found
                      worstPart = j;
                      worstWaste = waste;
                    }
                }
            }
        }
        if (worstPart) {
            // Put the job into partition
            assignPartition(jobs[i], worstPart, partitions[worstPart]);
            // reset the size of the partition
            partitions[worstPart].pSize -= jobs[i].mRequest;
        }
    }

}




void PrintResult(vector<Job>& jobs, vector<partition>& partitions, bool dynamic = false) {
    int totWaste = 0;

    cout << endl << "---------------------------------------------" << endl;
    // Header
    cout << setw(8) << "Job Name" << setw(15) << "Part assigned" << setw(12) << "Part waste"
        << setw(10) << "Job state" << endl;

    for (int i = 1; i < jobs.size(); i++) {
        cout << setw(8) << jobs[i].jName;
        int part = jobs[i].partition;
        if (part > 0) {
            cout << setw(15) << part;
            int waste;
            if (dynamic) {
                // If dynamic allocation - waste is a useless size of the partition then
                waste = partitions[part].pSize;
            }
            else {
                waste = partitions[part].pSize - jobs[i].mRequest;
            }
            totWaste += waste;
            cout << setw(12) << waste;
        }
        else {
            cout << setw(15) << "NA" << setw(12) << " ";
        }
        cout << setw(10) << (jobs[i].jStatus == running ? "Run" : "Wait") << endl;
    }

    cout << "---------------------------------------------" << endl;
    if (dynamic) {
        // Calculate total waste as a sum of residuary sizes of all assigned partitions
        totWaste = 0;
        for (int i = 1; i < partitions.size(); i++) {
            if (partitions[i].pAssigned) {
                totWaste += partitions[i].pSize;
            }
        }
    }
    cout << "Total Waste:           " << setw(12) << totWaste << endl;
}