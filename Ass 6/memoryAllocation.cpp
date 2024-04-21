#include <iostream>
using namespace std;

void firstFit(int process[], int block[], int p, int b)
{
    int memoryCopy[b], allocatedProcess[p], allocatedBlock[b];

    for (int i = 0; i < b; i++)
    {
        memoryCopy[i] = block[i];
        allocatedBlock[i] = -1;
    }
    for (int i = 0; i < p; i++)
    {
        allocatedProcess[i] = -1;           //just a flag
    }

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (process[i] <= memoryCopy[j] && allocatedBlock[j] == -1)
            {
                allocatedProcess[i] = j;
                allocatedBlock[j] = 1;
                memoryCopy[j] -= process[i];
                break;
            }
        }
    }

    cout << "P No.\tProcess Size\tBlock no. \t Block Size\n";
    for (int i = 0; i < p; i++)
    {
        cout << "p" << i << " \t" << process[i] << "\t";
        if (allocatedProcess[i] != -1)
            cout << "B" << allocatedProcess[i] << "\t\t" << block[allocatedProcess[i]] << "\n";
        else
            cout << "Not Allocated\n";
    }
}

void bestFit(int process[], int block[], int p, int b)
{
    int memoryCopy[b], allocatedProcess[p], allocatedBlock[b];

    for (int i = 0; i < b; i++)
    {
        memoryCopy[i] = block[i];
        allocatedBlock[i] = -1;
    }
    for (int i = 0; i < p; i++)
    {
        allocatedProcess[i] = -1;
    }

    for (int i = 0; i < p; i++)
    {
        int bestindex = -1;
        for (int j = 0; j < b; j++)
        {
            if (process[i] <= memoryCopy[j] && allocatedBlock[j] == -1)
            {
                if (bestindex == -1)
                    bestindex = j;
                else if (memoryCopy[bestindex] > memoryCopy[j])
                    bestindex = j;
            }
        }

        if (bestindex != -1)
        {
            allocatedProcess[i] = bestindex;
            memoryCopy[bestindex] -= process[i];
            allocatedBlock[bestindex] = 1;
        }
    }

    cout << "P No.\tProcess Size\tBlock no. \t Block Size\n";
    for (int i = 0; i < p; i++)
    {
        cout << "p" << i << " \t" << process[i] << "\t";
        if (allocatedProcess[i] != -1)
            cout << "B" << allocatedProcess[i] << "\t\t" << block[allocatedProcess[i]] << "\n";
        else
            cout << "Not Allocated\n";
    }
}

void worstFit(int process[], int block[], int p, int b)
{
    int memoryCopy[b], allocatedProcess[p], allocatedBlock[b];

    for (int i = 0; i < b; i++)
    {
        memoryCopy[i] = block[i];
        allocatedBlock[i] = -1;
    }
    for (int i = 0; i < p; i++)
        allocatedProcess[i] = -1;

    for (int i = 0; i < p; i++)
    {
        int worstIndex = -1;
        for (int j = 0; j < b; j++)
        {
            if (process[i] <= memoryCopy[j] && allocatedBlock[j] == -1)
            {
                if (worstIndex == -1)
                    worstIndex = j;
                else if (memoryCopy[worstIndex] < memoryCopy[j])
                    worstIndex = j;
            }
        }

        if (worstIndex != -1)
        {
            allocatedProcess[i] = worstIndex;
            memoryCopy[worstIndex] -= process[i];
            allocatedBlock[worstIndex] = 1;
        }
    }

    cout << "P No.\tProcess Size\tBlock no. \t Block Size\n";
    for (int i = 0; i < p; i++)
    {
        cout << "p" << i << " \t" << process[i] << "\t";
        if (allocatedProcess[i] != -1)
            cout << "B" << allocatedProcess[i] << "\t\t" << block[allocatedProcess[i]] << "\n";
        else
            cout << "Not Allocated\n";
    }
}

void nextFit(int process[], int block[], int p, int b)
{
    int allocatedProcess[p], allocatedBlock[b], memoryCopy[b];

    // Initialize allocation statuses
    for (int i = 0; i < b; i++)
    {
        allocatedBlock[i] = -1; // -1 indicates not allocated
        memoryCopy[i] = block[i];
    }
    for (int i = 0; i < p; i++)
    {
        allocatedProcess[i] = -1; // -1 indicates not allocated
    }

    int j = 0;
    for (int i = 0; i < p; i++)
    {
        int start = j;
        do
        {
            if (process[i] <= memoryCopy[j] && allocatedBlock[j] == -1)
            {
                allocatedProcess[i] = j;
                allocatedBlock[j] = i; // Store the process index in allocatedBlock
                memoryCopy[j] -= process[i];
                break;
            }
            j = (j + 1) % b;
        } while (j != start);
    }

    cout << "P No.\tProcess Size\tBlock No.\tBlock Size\n";
    for (int i = 0; i < p; i++)
    {
        cout << "P" << i << "\t" << process[i] << "\t\t";
        if (allocatedProcess[i] != -1)
            cout << "B" << allocatedProcess[i] << "\t\t" << block[allocatedProcess[i]] << "\n";
        else
            cout << "Not Allocated\n";
    }
}

// int main()
// {
//      int p, b;
//      cout << "Enter no. of processes: ";
//      cin >> p;
//      cout << "Enter no. of blocks: ";
//      cin >> b;

//      int process[p], block[b];
//      cout << "Enter process size: ";
//      for (int i = 0; i < p; i++)
//      {
//          cin >> process[i];
//      }

//      cout << "Enter blocks size: ";
//      for (int i = 0; i < b; i++)
//      {
//          cin >> block[i];
//      }
 

//     // int process[] = {100, 500, 200, 300, 600};
//     // int block[] = {200, 400, 300, 250, 150};
//     // int p = sizeof(process) / sizeof(process[0]);
//     // int b = sizeof(block) / sizeof(block[0]);

//     cout << "First fit allocation\n";
//     firstFit(process, block, p, b);

//     cout << "Best Fit Allocation\n";
//     bestFit(process, block, p, b);

//     cout << "Worst Fit Allocation\n";
//     worstFit(process, block, p, b);

//     cout << "Next Fit Allocation\n";
//     nextFit(process, block, p, b);
// }

int main()
{
    int p, b;
    cout << "Enter no. of processes: ";
    cin >> p;
    cout << "Enter no. of blocks: ";
    cin >> b;

    int process[p], block[b];
    cout << "Enter process size: ";
    for (int i = 0; i < p; i++)
    {
        cin >> process[i];
    }

    cout << "Enter blocks size: ";
    for (int i = 0; i < b; i++)
    {
        cin >> block[i];
    }

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. First Fit Allocation\n";
        cout << "2. Best Fit Allocation\n";
        cout << "3. Worst Fit Allocation\n";
        cout << "4. Next Fit Allocation\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "First fit allocation\n";
            firstFit(process, block, p, b);
            break;
        case 2:
            cout << "Best Fit Allocation\n";
            bestFit(process, block, p, b);
            break;
        case 3:
            cout << "Worst Fit Allocation\n";
            worstFit(process, block, p, b);
            break;
        case 4:
            cout << "Next Fit Allocation\n";
            nextFit(process, block, p, b);
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 5);

    return 0;
}