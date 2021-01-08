# Operating-Lab-Projects
My 2 O.S lab projects for my Comp Sci Course

First Project: Memory Managment Algorithms(Best-Fit,First-Fit, Next-Fit, Worst-Fit)

This program must do the following:
1.	Program Input:
            User will input to the program
a.	 Main Memory information, including
i.	 The Number of Memory partitions.
ii.	The Size of each memory partition.
b.	Process information (assign a unique identifier to each job)
i.	User will input the number of processes
ii.	Memory requirements for each process/job
2.	For each algorithm, your program should have a data structure(class or struct) that will include the following,
•	Name of the process/ job(number or word)
•	Process/job status (Run/Wait),
•	partition number the process/job was assigned to 
You can create an array or list of the object to represent the job queue.
3. Program output:
a) Initial memory allocation: Calculate and display a list of initial memory allocation, i.e which partitions contain which process after the first round of allocation
b) Memory waste: Program will calculate and display the memory waste for each partition
c. total waste for each algorithm.
e. A list of Processes in the waiting State(was not assigned to a partition).

Second Project: Process Management

Program had to run on Linux Servers

Algorithms:
1.First Come – First Serve  : non-preemptive
2.Priority : -pre-emptive
3.Shortest Job Next – non-preemptive

Inputs for program:
Information necessary for the calculation of average turnaround time including:
•	Time required for a job execution;(ie.Burst time)
•	Arrival time;
•	Priority
Program Output/Results:
The output of each algorithm should include:
•	Starting Time for each job/process
•	Completion time for each job/process,
•	Turnaround time for each job/process,
•	Average Turnaround time.
•	Order of execution of the processes.

Using real time is not necessary, relative start and stop time is sufficient provided that the job start times are all using relative time, and turnaround time calculation are accurate and consistent.

For each algorithm, you should create a data structure (class or struct) that will include the following,
•	Name of the process/Job(number or word)
•	Job Priority
•	Turnaround time
•	Start time
•	Completion time
•	Required Burst time/ Execution time
