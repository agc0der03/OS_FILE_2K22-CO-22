//shortest remaining time job first

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Process {
public:
    int pid; // Process ID
    int burst_time; // Burst Time
    int arrival_time; // Arrival Time

    Process(int id, int bt, int at) : pid(id), burst_time(bt), arrival_time(at) {}
};

class Scheduler {
private:
    vector<Process> processes;

public:
    Scheduler(const vector<Process>& p) : processes(p) {}

    void findWaitingTime(vector<int>& wt) {
        int n = processes.size();
	    vector<int> rt(n);

	    // Copy the burst time of each process into the remaining time vector
	    for (int i = 0; i < n; i++)
	        rt[i] = processes[i].burst_time;

	    int complete = 0, t = 0, minm = INT_MAX;
	    int shortest = 0, finish_time;
	    bool check = false;

	    // Loop until all processes are completed
	    while (complete != n) {
	        // Iterate over all processes to find the one with the shortest remaining time
	        for (int j = 0; j < n; j++) {
	            // Check if the process has arrived and has remaining burst time less than the minimum found so far
	            if ((processes[j].arrival_time <= t) && (rt[j] < minm) && rt[j] > 0) {
	                minm = rt[j]; // Update the minimum remaining time
	                shortest = j; // Update the index of the shortest process
	                check = true; // Set check to true to indicate that a process is found
	            }
	        }
	        // If no process is found, increment time and continue the loop
	        if (!check) {
	            t++;
	            continue;
	        }

	        // Decrement the remaining time of the shortest process
	        rt[shortest]--;

	        minm = rt[shortest]; // Update the minimum remaining time
	        if (minm == 0) // If the remaining time becomes zero, update minm to INT_MAX
	            minm = INT_MAX;

	        // If the process has completed its execution
	        if (rt[shortest] == 0) {
	            complete++; // Increment the count of completed processes
	            check = false; // Reset check to false
	            finish_time = t + 1; // Calculate the finish time of the process
	            // Calculate the waiting time of the process
	            wt[shortest] = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;
	            // If waiting time is negative, set it to zero
	            if (wt[shortest] < 0)
	                wt[shortest] = 0;
	        }
	        // Increment the time
	        t++;
	    }
    }

    void findTurnAroundTime(const vector<int>& wt, vector<int>& tat) {
        int n = processes.size();
        for (int i = 0; i < n; i++)
            tat[i] = processes[i].burst_time + wt[i];
    }

    void findAvgTime() {
        int n = processes.size();
        vector<int> wt(n), tat(n);
        int total_wt = 0, total_tat = 0;

        findWaitingTime(wt);
        findTurnAroundTime(wt, tat);

        cout << " P\t\t" << "BT\t\t" << "WT\t\t" << "TAT\t\t\n";

        for (int i = 0; i < n; i++) {
            total_wt += wt[i];
            total_tat += tat[i];
            cout << " " << processes[i].pid << "\t\t" << processes[i].burst_time << "\t\t " << wt[i] << "\t\t " << tat[i] << endl;
        }
        
        cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
        cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
    }
};

int main() {
    vector<Process> processes = { {1, 7, 3}, {2, 4, 5}, {3, 9, 1}, {4, 3, 0}, {5, 4, 4} };
    Scheduler scheduler(processes);
    scheduler.findAvgTime();
    
    return 0;
}
