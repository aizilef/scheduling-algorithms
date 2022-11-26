// Christine SG. Dela Rosa, 191645
// Felizia C. Tiburcio, 194984
// April 2, 2022

// we certify that this submission complies with the DISCS Academic Integrity
// Policy.

// If we have discussed my C++ language code with anyone other than
// my instructor(s), the teaching assistant(s),
// the extent of each discussion has been clearly noted along with a proper
// citation in the comments of my program.

// If any C++ language code or documentation used in our program
// was obtained from another source, either modified or unmodified, such as a
// textbook, website, or another individual, the extent of its use has been
// clearly noted along with a proper citation in the comments of our program.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Queue for cpp Retrieved from: https://www.geeksforgeeks.org/queue-cpp-stl/
// Printing the correct number of decimal points with cout. Retrieved from: https://stackoverflow.com/questions/5907031/printing-the-correct-number-of-decimal-points-with-cout
// Understanding C++ Retrieved from: https://www.youtube.com/channel/UCM-yUTYGmrNvKOCcAl21g3w
// Accessing C++ queue elements like an array. Retrieved from: https://stackoverflow.com/questions/5877504/access-c-queue-elements-like-an-array
// Difference between Preemptive and Non-preemptive priority. Retrieved from: https://www.geeksforgeeks.org/difference-between-preemptive-priority-based-and-non-preemptive-priority-based-cpu-scheduling-algorithms/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

struct process
{
    int id;
    int AT;       // arrival time
    int BT;       // burst time
    int BTR;      // burst time remaining
    int ST;       // start time
    int CT;       // completion time
    int TAT;      // turnaround time
    int WT;       // waiting time
    int RT;       // response time
    int PR;       // priority number
    int consumed; // cpu consumed before context switch
    bool complete = false;
    bool queued = false;
};

void FCFS(int X)
{
    int completed = 0;
    int elapsedTime = 0;

    process p[X];

    // accept values
    for (int i = 0; i < X; i++)
    {
        int AT;
        int BT;
        int PR;
        cin >> AT;
        cin >> BT;
        cin >> PR;
        p[i].id = i + 1;
        p[i].AT = AT;
        p[i].BT = BT;
        p[i].BTR = BT;
        p[i].PR = PR;
        p[i].consumed = 0;
    }

    while (completed < X)
    {
        int idx = -1;
        int minAT = 99999;

        for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
        {

            if (p[i].AT < minAT && p[i].complete == false && elapsedTime >= p[i].AT)
            {
                idx = i;
                minAT = p[i].AT;
            }
        }

        if (idx != -1)
        { // found minimum AT

            p[idx].ST = elapsedTime;  // start
            elapsedTime += p[idx].BT; // run
            p[idx].consumed += p[idx].BT;
            p[idx].CT = elapsedTime; // completion

            p[idx].TAT = p[idx].CT - p[idx].AT;
            p[idx].WT = p[idx].TAT - p[idx].BT;
            p[idx].RT = p[idx].ST - p[idx].AT;

            cout << p[idx].ST << " " << p[idx].id << " " << p[idx].consumed << "X" << endl;

            p[idx].complete = true; // mark as complete
            completed++;
        }
        else
        {
            elapsedTime++;
        }
    }

    // output
    double totalBT = 0;
    double totalWT = 0;
    double totalTAT = 0;
    double totalRT = 0;
    double throughput = 1.0 * X / elapsedTime;

    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        totalBT += p[i].BT;
        totalWT += p[i].WT;
        totalTAT += p[i].TAT;
        totalRT += p[i].RT;
    }

    int ultCPU = (totalBT / elapsedTime) * 100;

    cout << "Total time elapsed: " << elapsedTime << "ns" << endl;
    cout << "Total CPU burst time: " << totalBT << "ns" << endl;
    cout << "CPU Utilization: " << ultCPU << "%" << endl;
    cout << "Throughput: " << setprecision(16) << throughput << " processes/ns " << endl;

    cout << "Waiting times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].WT << "ns" << endl;
    }
    cout << "Average waiting time: " << totalWT / X << "ns" << endl;

    cout << "Turnaround times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].TAT << "ns" << endl;
    }

    cout << "Average turnaround time: " << totalTAT / X << "ns" << endl;

    cout << "Response times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].RT << "ns" << endl;
    }
    cout << "Average response time: " << totalRT / X << "ns" << endl;
}

void SJF(int X)
{

    int completed = 0;
    int elapsedTime = 0;

    process p[X];

    for (int i = 0; i < X; i++)
    {
        int AT;
        int BT;
        int PR;
        cin >> AT;
        cin >> BT;
        cin >> PR;
        p[i].id = i + 1;
        p[i].AT = AT;
        p[i].BT = BT;
        p[i].BTR = BT;
        p[i].PR = PR;
        p[i].consumed = 0;
    }

    while (completed < X)
    {
        int idx = -1;
        int minBT = 99999;

        for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
        {

            if (p[i].BT < minBT && p[i].complete == false && elapsedTime >= p[i].AT)
            {
                idx = i;
                minBT = p[i].BT;
            }
        }

        if (idx != -1)
        {

            p[idx].ST = elapsedTime;  // start
            elapsedTime += p[idx].BT; // run
            p[idx].consumed += p[idx].BT;
            p[idx].CT = elapsedTime; // completion

            p[idx].TAT = p[idx].CT - p[idx].AT;
            p[idx].WT = p[idx].TAT - p[idx].BT;
            p[idx].RT = p[idx].ST - p[idx].AT;

            cout << p[idx].ST << " " << p[idx].id << " " << p[idx].consumed << "X" << endl;

            p[idx].complete = true; // mark as complete
            completed++;
        }
        else
        {
            elapsedTime++;
        }
    }

    // output
    double totalBT = 0;
    double totalWT = 0;
    double totalTAT = 0;
    double totalRT = 0;
    double throughput = 1.0 * X / elapsedTime;

    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        totalBT += p[i].BT;
        totalWT += p[i].WT;
        totalTAT += p[i].TAT;
        totalRT += p[i].RT;
    }

    int ultCPU = (totalBT / elapsedTime) * 100;

    cout << "Total time elapsed: " << elapsedTime << "ns" << endl;
    cout << "Total CPU burst time: " << totalBT << "ns" << endl;
    cout << "CPU Utilization: " << ultCPU << "%" << endl;
    cout << "Throughput: " << setprecision(16) << throughput << " processes/ns " << endl;

    cout << "Waiting times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].WT << "ns" << endl;
    }
    cout << "Average waiting time: " << totalWT / X << "ns" << endl;

    cout << "Turnaround times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].TAT << "ns" << endl;
    }

    cout << "Average turnaround time: " << totalTAT / X << "ns" << endl;

    cout << "Response times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].RT << "ns" << endl;
    }
    cout << "Average response time: " << totalRT / X << "ns" << endl;
}

void SRTF(int X)
{

    int completed = 0;
    int elapsedTime = 0;

    process p[X];

    // accept values
    for (int i = 0; i < X; i++)
    {
        int AT;
        int BT;
        int PR;
        cin >> AT;
        cin >> BT;
        cin >> PR;
        p[i].id = i + 1;
        p[i].AT = AT;
        p[i].BT = BT;
        p[i].BTR = BT;
        p[i].PR = PR;
        p[i].consumed = 0;
    }

    int prev = -1;

    while (completed < X)
    {
        int idx = -1;
        int minBTR = 99999;

        for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
        {

            if (p[i].BTR < minBTR && p[i].complete == false && elapsedTime >= p[i].AT)
            {

                idx = i;
                minBTR = p[i].BTR;
            }
        }

        if (idx != -1)
        {

            if (prev != idx && prev != -1 && p[prev].complete == false)
            {

                cout << p[prev].consumed << endl;
                p[prev].consumed = 0;
            }

            if (p[idx].BTR == p[idx].BT) // first time
            {
                p[idx].ST = elapsedTime;
                cout << elapsedTime << " " << p[idx].id << " ";
            }
            else if (prev != idx)
            { // switch

                cout << elapsedTime << " " << p[idx].id << " ";
            }
            else if (p[idx].BTR == 0) // complete
            {
                p[idx].CT = elapsedTime;
                p[idx].TAT = p[idx].CT - p[idx].AT;
                p[idx].WT = p[idx].TAT - p[idx].BT;
                p[idx].RT = p[idx].ST - p[idx].AT;

                p[idx].complete = true;
                completed++;
                cout << p[idx].consumed << "X" << endl;
            }

            if (p[idx].complete == false)
            {

                p[idx].BTR -= 1;
                p[idx].consumed += 1; // consume

                elapsedTime += 1;
            }

            prev = idx; // process in prev iteration
        }
        else
        {
            elapsedTime++;
        }
    }

    // OUTPUT

    double totalBT = 0;
    double totalWT = 0;
    double totalTAT = 0;
    double totalRT = 0;
    double throughput = 1.0 * X / elapsedTime;

    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        totalBT += p[i].BT;
        totalWT += p[i].WT;
        totalTAT += p[i].TAT;
        totalRT += p[i].RT;
    }

    int ultCPU = (totalBT / elapsedTime) * 100;

    cout << "Total time elapsed: " << elapsedTime << "ns" << endl;
    cout << "Total CPU burst time: " << totalBT << "ns" << endl;
    cout << "CPU Utilization: " << ultCPU << "%" << endl;
    cout << "Throughput: " << setprecision(16) << throughput << " processes/ns " << endl;

    cout << "Waiting times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].WT << "ns" << endl;
    }
    cout << "Average waiting time: " << totalWT / X << "ns" << endl;

    cout << "Turnaround times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].TAT << "ns" << endl;
    }

    cout << "Average turnaround time: " << totalTAT / X << "ns" << endl;

    cout << "Response times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].RT << "ns" << endl;
    }
    cout << "Average response time: " << totalRT / X << "ns" << endl;
}

void P(int X)
{
    int completed = 0;
    int elapsedTime = 0;

    process p[X];

    // accept values
    for (int i = 0; i < X; i++)
    {
        int AT;
        int BT;
        int PR;
        cin >> AT;
        cin >> BT;
        cin >> PR;
        p[i].id = i + 1;
        p[i].AT = AT;
        p[i].BT = BT;
        p[i].BTR = BT;
        p[i].PR = PR;
        p[i].consumed = 0;
    }

    int prev = -1;
    // while processes in queue
    while (completed < X)
    {

        int idx = -1;
        int minPR = 99999;

        for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
        {

            if (p[i].PR < minPR && p[i].complete == false && elapsedTime >= p[i].AT)
            {

                idx = i;
                minPR = p[i].PR;
            }
        }

        if (idx != -1)
            if (idx != -1)
            {

                if (prev != idx && prev != -1 && p[prev].complete == false)
                {

                    cout << p[prev].consumed << endl;
                    p[prev].consumed = 0;
                }

                if (p[idx].BTR == p[idx].BT) // first time
                {
                    p[idx].ST = elapsedTime;
                    cout << elapsedTime << " " << p[idx].id << " ";
                }
                else if (prev != idx)
                { // switch

                    cout << elapsedTime << " " << p[idx].id << " ";
                }
                else if (p[idx].BTR == 0) // complete
                {
                    p[idx].CT = elapsedTime;
                    p[idx].TAT = p[idx].CT - p[idx].AT;
                    p[idx].WT = p[idx].TAT - p[idx].BT;
                    p[idx].RT = p[idx].ST - p[idx].AT;

                    p[idx].complete = true;
                    completed++;
                    cout << p[idx].consumed << "X" << endl;
                }

                if (p[idx].complete == false)
                {

                    p[idx].BTR -= 1;
                    p[idx].consumed += 1; // consume

                    elapsedTime += 1;
                }

                prev = idx; // process in prev iteration
            }
            else
            {
                elapsedTime++;
            }
    }

    // OUTPUT

    double totalBT = 0;
    double totalWT = 0;
    double totalTAT = 0;
    double totalRT = 0;
    double throughput = 1.0 * X / elapsedTime;

    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        totalBT += p[i].BT;
        totalWT += p[i].WT;
        totalTAT += p[i].TAT;
        totalRT += p[i].RT;
    }

    cout << "Total time elapsed: " << elapsedTime << "ns" << endl;
    cout << "Total CPU burst time: " << totalBT << "ns" << endl;
    cout << "CPU Utilization: " << (totalBT / elapsedTime) * 100 << "%" << endl;
    cout << "Throughput: " << setprecision(16) << throughput << " processes/ns " << endl;

    cout << "Waiting times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].WT << "ns" << endl;
    }
    cout << "Average waiting time: " << totalWT / X << "ns" << endl;

    cout << "Turnaround times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].TAT << "ns" << endl;
    }

    cout << "Average turnaround time: " << totalTAT / X << "ns" << endl;

    cout << "Response times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].RT << "ns" << endl;
    }
    cout << "Average response time: " << totalRT / X << "ns" << endl;
}

void RR(int X, int Q)
{

    int completed = 0;
    int elapsedTime = 0;

    process p[X];
    queue<process> aq; // arrival queue - newly arrived processes

    // accept values
    for (int i = 0; i < X; i++)
    {
        int AT;
        int BT;
        int PR;
        cin >> AT;
        cin >> BT;
        cin >> PR;
        p[i].id = i + 1;
        p[i].AT = AT;
        p[i].BT = BT;
        p[i].PR = PR;
        p[i].BTR = BT;
        p[i].consumed = 0;
    }

    // while processes in queue
    while (completed < X)
    {
        int idx = -1;
        int minAT = 99999;

        // with the queue
        for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
        {

            if (p[i].AT < minAT && p[i].complete == false && elapsedTime >= p[i].AT && p[i].queued == false)
            { // is minimum and not yet completed, not in queue

                // newly arrived AT to the queue
                idx = i;
                minAT = p[i].AT;
            }
        }

        if (idx == -1)
        {
            // no newly arrived process, get from queue

            idx = aq.front().id - 1;
        }

        if (idx != -1)
        { // found minimum AT (first in queue)

            if (p[idx].BTR == p[idx].BT) // FIRST TIME
            {
                p[idx].ST = elapsedTime; // start
            }

            if (p[idx].BTR - Q <= 0)
            { // Finished

                elapsedTime += p[idx].BTR;

                p[idx].CT = elapsedTime;
                p[idx].TAT = p[idx].CT - p[idx].AT;
                p[idx].WT = p[idx].TAT - p[idx].BT;
                p[idx].RT = p[idx].ST - p[idx].AT;

                cout << elapsedTime << " " << p[idx].id << " " << p[idx].BTR << "X" << endl;

                p[idx].BTR = 0;

                p[idx].complete = true; // mark as complete
                completed++;

                if (p[idx].queued == true)
                { // if process is from queue
                    aq.pop();
                }
            }
            else
            { // Not Finished, BTR > 0

                elapsedTime += Q;
                p[idx].BTR -= Q;

                cout << p[idx].ST << " " << p[idx].id << " " << Q << endl;

                // add unfinished process to queue
                p[idx].queued = true;
                aq.push(p[idx]);
            }
        }
        else
        {
        }
    }
    // output
    double totalBT = 0;
    double totalWT = 0;
    double totalTAT = 0;
    double totalRT = 0;
    double throughput = 1.0 * X / elapsedTime;

    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        totalBT += p[i].BT;
        totalWT += p[i].WT;
        totalTAT += p[i].TAT;
        totalRT += p[i].RT;
    }

    cout << "Total time elapsed: " << elapsedTime << "ns" << endl;
    cout << "Total CPU burst time: " << totalBT << "ns" << endl;
    cout << "CPU Utilization: " << (totalBT / elapsedTime) * 100 << "%" << endl;
    cout << "Throughput: " << setprecision(16) << throughput << " processes/ns " << endl;

    cout << "Waiting times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].WT << "ns" << endl;
    }
    cout << "Average waiting time: " << totalWT / X << "ns" << endl;

    cout << "Turnaround times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].TAT << "ns" << endl;
    }

    cout << "Average turnaround time: " << totalTAT / X << "ns" << endl;

    cout << "Response times: " << endl;
    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        cout << " Process " << p[i].id << ": " << p[i].RT << "ns" << endl;
    }
    cout << "Average response time: " << totalRT / X << "ns" << endl;
}

int main()
{

    int T;

    cin >> T;

    for (int i = 0; i < T; i++)
    {

        int X;
        string AL;

        cin >> X;
        cin >> AL;

        if (AL == "FCFS")
        {
            FCFS(X);
        }
        else if (AL == "SJF")
        {
            SJF(X);
        }
        else if (AL == "SRTF")
        {
            SRTF(X);
        }
        else if (AL == "P")
        {
            P(X);
        }
        else if (AL == "RR")
        {
            int Q;
            cin >> Q;
            RR(X, Q);
        }
    }

    return 0;
}
