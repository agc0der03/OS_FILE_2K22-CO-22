#include <iostream>
using namespace std;

int main() {
    // Matrix for storing Process Id, Burst Time, Waiting Time & Turnaround Time.
    int processes[100][4];
    int n, total_waiting_time = 0, index, temp;
    float avg_waiting_time, avg_turnaround_time;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Burst Time for each process:" << endl;

    // User Input Burst Time and assigning Process Id.
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> processes[i][1]; // Burst Time
        processes[i][0] = i + 1; // Process Id
    }

    // Sorting processes according to their Burst Time using Selection Sort.
    for (int i = 0; i < n; i++) {
        index = i;
        for (int j = i + 1; j < n; j++) {
            if (processes[j][1] < processes[index][1])
                index = j;
        }
        // Swap Burst Time
        temp = processes[i][1];
        processes[i][1] = processes[index][1];
        processes[index][1] = temp;

        // Swap Process Id
        temp = processes[i][0];
        processes[i][0] = processes[index][0];
        processes[index][0] = temp;
    }

    processes[0][2] = 0; // First process waiting time is 0

    // Calculation of Waiting Times
    for (int i = 1; i < n; i++) {
        processes[i][2] = 0;
        for (int j = 0; j < i; j++)
            processes[i][2] += processes[j][1]; // Sum of all previous burst times
        total_waiting_time += processes[i][2];
    }

    avg_waiting_time = (float)total_waiting_time / n;
    total_waiting_time = 0;

    cout << "P   BT   WT   TAT" << endl;

    // Calculation of Turnaround Time and printing the data.
    for (int i = 0; i < n; i++) {
        processes[i][3] = processes[i][1] + processes[i][2]; // Burst Time + Waiting Time
        total_waiting_time += processes[i][3];
        cout << "P" << processes[i][0] << "   " << processes[i][1] << "   " << processes[i][2] << "   " << processes[i][3] << endl;
    }

    avg_turnaround_time = (float)total_waiting_time / n;
    cout << "Average Waiting Time= " << avg_waiting_time << endl;
    cout << "Average Turnaround Time= " << avg_turnaround_time << endl;
    return 0;
}
