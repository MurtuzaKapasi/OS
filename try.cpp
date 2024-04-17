#include <iostream>
#include <vector>
using namespace std;

void firstFit(int process[], int block[], int p, int b){
    int memoryCopy[b] , allocatedProcess[p] , allocatedBlock[b];
    for(int i=0 ; i < b ; i++){
        memoryCopy[i] = block[i];
        allocatedBlock[i] = -1;
    }    

    for(int i=0 ; i< p ; i++){
        allocatedProcess[i] = -1;
    }

    for(int i=0 ; i< p ; i++){
        for(int j=0  ; j< b ; j++){
            if(process[i] <= memoryCopy[j] && allocatedBlock[j] == -1){
                allocatedProcess[i] = j;
                allocatedBlock[j] = 1;
                memoryCopy[j] - process[i];
                break;
            }
        }
    }

        //printing results
        cout<<"P No \t Process Size \t Block No. \t Block Size"<<endl;
        for(int i=0 ; i< p ; i++){
            cout<<"p"<<i+1<<"\t"<<process[i]<<"\t";
            if(allocatedProcess[i] != -1){
                cout<<"B"<<allocatedProcess[i]<<"\t"<<block[allocatedProcess[i]]<<endl;
            }
            else    cout<<"Not Allocated"<<endl;
        }


}

void nextFit(int process[], int block[], int p, int b){
    int memoryCopy[b] , allocatedProcess[p] , allocatedBlock[b];
    for(int i=0 ; i < b ; i++){
        memoryCopy[i] = block[i];
        allocatedBlock[i] = -1;
    }

    for(int i=0 ; i< p ; i++){
        allocatedProcess[i] = -1;
    }

    int j=0;
    for(int i=0 ; i< p ; i++){
     int start = j;
        do{     if(process[i] <= memoryCopy[j] && allocatedBlock[j] == -1){
                allocatedProcess[i] = j;
                allocatedBlock[j] = 1;
                memoryCopy[j] -= process[i];
                break;
            }
            j = (j+ 1)% b;

        }while(j!=start);
    }

}


int main(){
//    int p, b;
//    cout<<"Enter number of processesss: ";
//    cin>>p;
//    cout<<"Enter number of blocks: ";
//    cin>>b;
//    int process[p],block[b];

//    cout<<"Enter processesss: ";
//    for(int i = 0; i < p; i++){
//        cin>>process[i];
//    }

//    cout<<"Enter blocks: ";
//    for(int i = 0; i < b; i++){
//        cin>>block[i];
//    }

int process[] = {100, 500, 200, 300, 600};
    int block[] = {200, 400, 300, 250, 150};
    int p = sizeof(process) / sizeof(process[0]);
    int b = sizeof(block) / sizeof(block[0]);

cout<<"First fit"<<endl;
firstFit(process, block, p, b);

cout<<"Next fit"<<endl;
nextFit(process, block, p, b);



}