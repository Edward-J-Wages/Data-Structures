
/*  Project 3 - Data Structures (CS 2413)
    Edward Wages
    9-30-24

*/


class CPUJob 
{
    public:
    int job_id; // Unique identifier for the job
    int priority; // Priority level of the job (1-10)
    int job_type; // Job type (1-10)
    int cpu_time_consumed; // Total CPU time consumed by the job
    int memory_consumed; // Total memory consumed thus far

    CPUJob(int job_id, int priority, int job_type, int cpu_time_consumed, int memory_consumed) //Constructor
    {
        this->job_id = job_id;
        this->priority = priority;
        this->job_type = job_type;
        this->cpu_time_consumed = cpu_time_consumed;
        this->memory_consumed = memory_consumed;
    }
};

template <class DT>
class Queue 
{
    public:
    DT* JobPointer; // Pointer to a job (e.g., CPUJob)
    Queue<DT>* next; // Pointer to the next node in the queue
};

template <class DT>
class NovelQueue 
{
public:
Queue<DT>* front; // Pointer to the front of the queue
Queue<DT>** NodePtrs; // Array of pointers to Queue nodes
int size; // Number of elements in the queue)
};

#include <iostream>
using namespace std;
int main() 
{
int n; // Number of commands
cin >> n; // Read the number of commands

// Instantiate a NovelQueue for CPUJob pointers
NovelQueue<CPUJob*>* myNovelQueue = new NovelQueue<CPUJob*>();

char command; // Variable to store the command type

// Variables for job attributes
int job_id, priority, job_type, cpu_time_consumed, memory_consumed;

// Variables for modifying a job
int new_priority, new_job_type, new_cpu_time_consumed;
int new_memory_consumed;
int field_index, new_value;

// Variable for the number of positions in the 'Promote' command
int positions;
int attribute_index; // Variable for the 'Reorder' command

/************** Read each command Process ***************/
for (int i = 0; i < n; ++i) 
{
    cin >> command; // Read the command type
    switch (command) //Switch statement for each possible operation in the program
    {
        case 'A': // Add (Enqueue)
        { 
            cin >> job_id >> priority >> job_type;
            cin >> cpu_time_consumed >> memory_consumed;
            CPUJob* newJob = new CPUJob(job_id, priority, job_type,
            cpu_time_consumed, memory_consumed);
            (*myNovelQueue).enqueue(newJob);
            break;
        }

        case 'R': // Remove (Dequeue)
        { 
            CPUJob* removedJob = (*myNovelQueue).dequeue();
            if (removedJob) 
            {
                cout << "Dequeued Job: ";
                (*removedJob).display();
                delete removedJob; // Clean up memory after use
            }
            break;
        }

        case 'M': // Modify
        { 
            cin >> job_id >> new_priority >> new_job_type;
            cin >> new_cpu_time_consumed >> new_memory_consumed;
            (*myNovelQueue).modify(job_id, new_priority, new_job_type, new_cpu_time_consumed, new_memory_consumed);
            break;
        }

        case 'C': // Change Job Values
        { 
            cin >> job_id >> field_index >> new_value;
            (*myNovelQueue).change(job_id, field_index, new_value);

            break;
        }

        case 'P': // Promote
        {
            cin >> job_id >> positions;
            (*myNovelQueue).promote(job_id, positions);
            break;
        }

        case 'O': // Reorder
        { 
            cin >> attribute_index;
            NovelQueue<CPUJob*>* reorderedQueue =
            (*myNovelQueue).reorder(attribute_index);
            cout << "Reordered Queue:" << endl;
            (*reorderedQueue).display();

            break;
        }

        case 'D': // Display
        {
            (*myNovelQueue).display();
            break;
        }

        case 'N': // Count
        { 
            cout << "Number of elements in the queue: " <<
            (*myNovelQueue).count() << endl;
            break;
        }

        case 'L': // List Jobs
        {
            (*myNovelQueue).listJobs();
            break;
        }

        default:
        cout << "Invalid command!" << endl;
}

delete myNovelQueue; // Clean up the NovelQueue after all operations

return 0;
}

/*
    *****DOCUMENTATION*****

    AI USAGE:
    I did not use AI throughout the development of project 3


    DEBUGGING AND TESTING PLAN:

*/