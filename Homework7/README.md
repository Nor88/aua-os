Overview
This project is a simple CPU process scheduling simulator written in C, designed to demonstrate two fundamental non-preemptive scheduling algorithms:
First Come First Served (FCFS)
Shortest Job First (SJF)
The program calculates and displays important scheduling metrics for each process, including:
Turnaround Time (TAT) — total time from arrival to completion
Waiting Time (WT) — time spent waiting in the ready queue
Response Time (RT) — time from arrival until first CPU execution

Features
Accepts user input for:
Number of processes
Arrival time and burst time for each process
Implements both FCFS and SJF (non-preemptive) scheduling
Displays:
Gantt chart of process execution
Per-process statistics (PID, AT, BT, WT, TAT, RT)
Average waiting, turnaround, and response times

Algorithms
1. First Come First Served (FCFS)
Processes are executed in the order of their arrival time.
Non-preemptive — once a process starts, it runs to completion.
2. Shortest Job First (SJF)
Among the arrived processes, the one with the shortest burst time is executed next.
If two processes have the same burst time, the one with the earlier arrival time is chosen.

3. Run the program
Execute the compiled program with:
./task

4. Provide input
The program will prompt you to enter:
The number of processes
The arrival time and burst time for each process
Example:
Enter the number of processes: 4
Enter the arrival time and burst time for process 1: 0 8
Enter the arrival time and burst time for process 2: 1 4
Enter the arrival time and burst time for process 3: 2 9
Enter the arrival time and burst time for process 4: 3 5

