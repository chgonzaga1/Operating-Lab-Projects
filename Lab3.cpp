// Lab3.cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
using namespace std;

struct Job {
    string name;
    int priority;
    int arrival_time;
    int start_time;
    int end_time;
    int time2complete;
};

class ArrTimeComp
{
public:
    ArrTimeComp() {}
    bool operator()(const Job& a, const Job& b) const
    {
        return a.arrival_time > b.arrival_time;
    }
};

//renaming data type
typedef priority_queue<Job, vector<Job>, ArrTimeComp> ArrivalQueue;


 //Read job inputs from text file
 //Paramters: ArrivalQueues
 //file name of the text
 //returns the number of jobs being red
int ReadJobs(ArrivalQueue& jobs, string filename)
{
    string str;
    Job job;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening file " << filename << endl;
        return -1;
    }
    getline(fin, str);  // Get header

    while (getline(fin, str)) {
        istringstream iss (str);
        iss >> job.name >> job.arrival_time >> job.priority >> job.time2complete;
        job.start_time = job.end_time = 0;
        jobs.push(job);
    }

    return jobs.size();
}

 //simulating First Come First Schedulerr
 //Paramieters: Arirvial jobs, finisd jobs, history which brings the sequences of executing jobs, needouput to indicate additional output
 //returns finished time
int FCFSSched(ArrivalQueue& jobs, deque<Job>& finished, deque<Job>& history, bool needOutput=true)
{
    deque<Job> waited;
       Job curJob, job;
    int clock = 0;

    while (jobs.size() > 0 || waited.size() > 0) {

        if (waited.size() == 0) {
            // No waiting job, get next arrival job
            curJob = jobs.top();
            jobs.pop();
            clock = curJob.arrival_time;
        }
        else {
            // Get first waiting job
            curJob = waited.front();
            waited.pop_front();
        }
		if (needOutput) {
			cout << "Time: " << clock;
			cout << "  started job " << curJob.name << endl;
		}
        curJob.start_time =  clock;
		history.push_back(curJob);

        //now to Execute current job
        clock += curJob.time2complete;
        curJob.time2complete = 0;
        curJob.end_time = clock;
        finished.push_back(curJob);

        // To ccheck for new arrived jobs
        while (jobs.size()>0) {
            job = jobs.top();
            if (job.arrival_time <= clock) {
                jobs.pop();
                waited.push_back(job);
            }
            else {
                break;
            }
        }
    }
    return clock;
}




//Priority Queues
class PriorityComp
{
public:
    PriorityComp() {}
    bool operator()(const Job& a, const Job& b) const
    {
        return a.priority > b.priority;
    }
};

typedef priority_queue<Job, vector<Job>, PriorityComp> PriorityQueue;



 //Simulating Priority Prempemtive Scheudler
 //Inputs are for job arrival, finished jobs, history as for sequence jobs
 //has been executed
 //needOuput -if needed additional output
 //returns finished time
int PrioritySched(ArrivalQueue& jobs, deque<Job>& finished, deque<Job>& history, bool needOutput=true)
{
    const int INF = 1073741824; //largest number
    PriorityQueue waited;
    Job curJob, job;
    bool isJobExec = false;
    int clock = 0;

    while (jobs.size() > 0 || waited.size() > 0) {
		if (needOutput) {
			cout << "Time: ";
		}
        int next_job_arrive_time = INF;
        int finished_job_time = INF;
        if (jobs.size() > 0) {
            job =  jobs.top();
            next_job_arrive_time = job.arrival_time;
        }
        if (isJobExec) {
            finished_job_time =  clock + curJob.time2complete;
        }

        if (next_job_arrive_time < finished_job_time) {
			if (needOutput) {
				cout << next_job_arrive_time << " ";
			}
            // Add new job(s) to waited
            while (jobs.size() > 0) {
                job = jobs.top();
                if (job.arrival_time == next_job_arrive_time) {
                    jobs.pop();
                    waited.push(job);
                }
                else {
                    break;
                }
            }
            if (!isJobExec ) {
                curJob = waited.top();
                isJobExec = true;
                waited.pop();
                if ( curJob.start_time == 0 ) {
                    curJob.start_time = next_job_arrive_time;
                }
				history.push_back(curJob);
				if (needOutput) {
					cout << " started job " << curJob.name;
				}
            }
            else {
                // Check if need preempt job
                job = waited.top();
                if (curJob.priority > job.priority ) {
					if (needOutput) {
						cout << "job " << curJob.name << " preempted ";
					}
                    curJob.time2complete -= next_job_arrive_time - clock;
                    waited.pop();
                    waited.push(curJob);
                    curJob = job;
                    if ( curJob.start_time == 0 ) {
                        curJob.start_time = next_job_arrive_time;
                    }
					history.push_back(curJob);
					if (needOutput) {
						cout << "by job " << curJob.name;
					}
                }
                else {
                    // Continue current job
                    curJob.time2complete -= next_job_arrive_time - clock;
					if (needOutput) {
						cout << " job " << curJob.name << " continued";
					}
                }
            }
            // Adjust clock
            clock = next_job_arrive_time;
            if (needOutput) {
                cout << endl;
            }
        }
        else {
            // Finished current job
			if (needOutput) {
				cout << finished_job_time << " ";
			}
            curJob.end_time = finished_job_time;
            curJob.time2complete = 0;
            finished.push_back(curJob);
            if (waited.size() > 0) {
                // Have waited job
                curJob = waited.top();
                waited.pop();
				if (needOutput) {
					cout << "started job " << curJob.name;
				}
                if ( curJob.start_time == 0 ) {
                        curJob.start_time = finished_job_time;
                }
				history.push_back(curJob);
            }
            else {
                // Idle wait for arrival job
                isJobExec = false;
            }
            clock = finished_job_time;
			if (needOutput) {
				cout << endl;
			}
        }
    }
	// Add the last job
	clock += curJob.time2complete;
	curJob.end_time = clock;
	curJob.time2complete = 0;
	finished.push_back(curJob);
    return clock;
}

class TimeComp
{
public:
	TimeComp() {}
	bool operator()(const Job& a, const Job& b) const
	{
		return a.time2complete > b.time2complete;
	}
};

typedef priority_queue<Job, vector<Job>, TimeComp> ShortestQueue;

/**************************************************
 * Simulate SJN sheduler
 * Input:
 *      jobs - a queue of arrival
 *      finished - a queue of finished jobs
 *		history - sequence of job execution
 *		fVerbose - if need additional output
 * Return:
 *      finished time
 *************************************************/

 //Simulating SJN Schedule
 //parameters are for arrival jobs, que of finished jobs, sequence of jobs execution and for more additional output
 //return finished time
int SJNSched(ArrivalQueue& jobs, deque<Job>& finished, deque<Job>& history, bool needOutput=true)
{
	ShortestQueue waited;
	Job curJob, job;
	int clock = 0;

	while (jobs.size() > 0 || waited.size() > 0) {

		if (waited.size() == 0) {
			// No waiting job, get next arrival job
			curJob = jobs.top();
			jobs.pop();
			clock = curJob.arrival_time;
		}
		else {
			// Get first waiting job
			curJob = waited.top();
			waited.pop();
		}
		if (needOutput) {
			cout << "Time: " << clock;
			cout << "  started job " << curJob.name << endl;
		}
		curJob.start_time = clock;
		history.push_back(curJob);

		// Execute current job
		clock += curJob.time2complete;
		curJob.time2complete = 0;
		curJob.end_time = clock;
		finished.push_back(curJob);

		// Check for new arrived jobs
		while (jobs.size() > 0) {
			job = jobs.top();
			if (job.arrival_time <= clock) {
				jobs.pop();
				waited.push(job);
			}
			else {
				break;
			}
		}
	}
	return clock;
}


/**************************************************
 * Print finished jobs statistics
 * Input:
 *      jobs - finished jobs queue
 *		history - sequence of job execution
 **************************************************/

 //Print the current jobs output
 //
 //history of seuqence of job execution
void PrintJobs(const deque<Job>& jobs, const deque<Job>& history)
{
    int TaT, totTaT = 0;
	cout << endl;
    cout << setw(8) << "PID" << setw(8) << "Start" << setw(8)  << "End"
         << setw(8) << "TaT" << endl;
    for (auto i=jobs.begin(); i!=jobs.end(); i++)  {
        TaT = i->end_time - i->arrival_time;
        cout << setw(8) << i->name << setw(8) << i->start_time << setw(8)
             << i->end_time << setw(8) << TaT << endl;
        totTaT += TaT; //increase the total
    }
	auto i = history.begin();
	cout << "Order of execution: " << i->name;
	for (i++; i != history.end(); i++)
	{
		cout << " -> " << i->name;
	}
	cout << endl;
    cout << "      Average TaT:             " << static_cast<double>(totTaT) / jobs.size() << endl;
    // cout << "      Average TaT:             " << static_cast<double>(totTaT) / jobs.length() << endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3 || (argc == 3 && argv[2] != string("-v")) )  {
        cerr << "Use: " << argv[0] << " <Data.txt> [-v]" << endl;
        exit(1);
    }
	bool fVerbose = argc == 3;
    ArrivalQueue jobs;
    ReadJobs(jobs, argv[1]);

    deque<Job> finished;
	deque<Job> history;
	cout << "Select scheduler:" << endl;
	cout << " 1 - FCFS" << endl;
	cout << " 2 - Priority" << endl;
	cout << " 3 - SJN" << endl;
	cout << "   - ";
	int ch;
	cin >> ch;

	switch (ch) {
	case 1:
		FCFSSched(jobs, finished, history, fVerbose);
		break;
	case 2:
		PrioritySched(jobs, finished, history, fVerbose);
		break;
	case 3:
		SJNSched(jobs, finished, history, fVerbose);
		break;
	default:
		cout << "Incorrect scheduler" << endl;
		exit(1);
	}

    PrintJobs(finished, history);

    return 0;
}
