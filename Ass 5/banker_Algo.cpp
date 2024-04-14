#include <iostream>
using namespace std;

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 10;

int main() {
    int processes, resources, i, j, al[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], av[MAX_RESOURCES], need[MAX_PROCESSES][MAX_RESOURCES], temp, resource_cnt, process_cnt, completed, k;

    cout << "Enter number of processes: ";
    cin >> processes;

    cout << "Enter number of resources: ";
    cin >> resources;

    cout<<"\nCurrent Allocation "<<endl;
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            cout << "Enter instances for al[" << i << "][" << j << "]: ";
            cin >> al[i][j];
        }
    }

    cout<<"\nMax Need "<<endl;
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            cout << "Enter instances for max[" << i << "][" << j << "]: ";
            cin >> max[i][j];
        }
    }

    cout<<"\nCurrent Available "<<endl;
    for (i = 0; i < resources; i++) {
        cout << "Available Resource for av[" << i << "]: ";
        cin >> av[i];
    }

    cout << "Allocation Values :\n";
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            cout << "\t" << al[i][j];
        }
        cout << endl;
    }

    cout << "\n\nMax Values :\n";
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            cout << "\t" << max[i][j];
        }
        cout << endl;
    }

    cout << "\n\nNeed Values :\n";
    for (i = 0; i < processes; i++) {
        for (j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - al[i][j];
            cout << "\t" << need[i][j];
        }
        cout << endl;
    }

    cout<<"\nSafe Sequence -> ";
    completed = 1;
    process_cnt = 0;
    while (completed != 0) {
        for (i = 0; i < processes; i++) {
            resource_cnt = 0;
            for (j = 0; j < resources; j++) {
                if (need[i][j] <= av[j] && (need[i][0] != -1)) {
                    resource_cnt++;
                }
            }

            if (resource_cnt == resources) {
                for (k = 0; k < resources; k++) {
                    av[k] += al[i][k];
                }
                cout << "\n process " << i;
                need[i][0] = -1;
                process_cnt++;
            }
        }
        if (process_cnt == processes) {
            completed = 0;
        }
    }
    cout << endl;

    return 0;
}
