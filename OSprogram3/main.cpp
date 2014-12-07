//
//  main.cpp
//  OSprogram1
//
//  Created by Bjorn Johnson on 10/10/14.
//  Copyright (c) 2014 Bjorn Johnson. All rights reserved.
//

#include <iostream>
#include <queue>
#include "PCB.h"
#include <string>
#include "FscanDiskQueue.h"
using namespace std;

void printWelcome(){
    cout << "Welcome SIMPLE OS" << endl;
    cout << "*****************************************************" << endl;
    cout << "This OS can interact with the following devices:" << endl;
    cout << "Printers" << endl;
    cout << "Disks" << endl;
    cout << "CDRWs" << endl;
    cout << "To create a new process in the Ready Queue press 'A'" << endl;
    cout << "Sys Calls are: "<< endl;
    cout << "'p#' for Printers" <<endl;
    cout << "'d#' for Disks" <<endl;
    cout << "'c#' for CDRWs" <<endl;
    cout << "where '#' is the number of the device" << endl;
    cout << "'t' to terminate a process" <<endl;
    cout << endl;
    cout << "Interupts are:" << endl;
    cout << "'P#' for Printers" << endl;
    cout << "'D#' for Disks" << endl;
    cout << "'C#' for CDRWs" << endl;
    cout << "where '#' is the number of the device" << endl;
    cout << endl;
    cout << "For Snapshot:" << endl;
    cout << "'S' followed by 'r', 'p', 'd', or 'c'" << endl;
    cout << "*****************************************************" << endl;
    cout << "Averages only calculated after burst ends" << endl;
    cout << "or on termination of process" << endl;
    cout << "*****************************************************" << endl;
    cout << "Press 'Q' or 'q' to quit" << endl;
    cout << endl;
    
    
}

void printListHeader(float totAVetermCpuTime){
    
    cout << "Average Total CPU Time of Terminated Process: " << totAVetermCpuTime << endl;
    cout <<" ------------------------------------------------------------------------"<<endl;
    
    cout << left << "| " <<  setw(5) << "PID"
    << left << "| " <<  setw(9) << "Filename"
    << left << "| " <<  setw(8) << "Mem"
    << left << "| " <<  setw(5) << "R/W"
    << left << "| " <<  setw(8) << "File"
    << left << "| " <<  setw(6) << "Cyl #"
    << left << "| " <<  setw(6) << "CPU"
    << left << "| " <<  setw(10) << "Ave Burst"
    << left << "| "
    << endl;
    
    cout << left << "| " <<  setw(5) << ""
    << left << "| " <<  setw(9) << ""
    << left << "| " <<  setw(8) << "Start"
    << left << "| " <<  setw(5) << ""
    << left << "| " <<  setw(8) << "Length"
    << left << "| " <<  setw(6) << ""
    << left << "| " <<  setw(6) << "Time"
    << left << "| " <<  setw(10) << "Time"
    << left << "| "
    << endl;
    
    cout <<" ------------------------------------------------------------------------"<<endl;

    
    
}

bool checkValidNum(string num, int maxNum){
    //cout << "checking..." << endl;
    string error = "error";
    for (int i = 0; i < num.length(); i++) {
        if (!isdigit(num[i])) {
            throw error;
            return false;
        }
    }
    if (num.length()<1) {
        throw error;
    }

    
    int inum = stoi(num);
    //cout << inum << endl;
    
    if (inum > 0 && inum <= maxNum ) {
        return true;
    }
    return false;
}

int readTimeSlice(PCB & current, int maxSlice){
    int timeSlice;
    cout << "How long was this process in the CPU: ";
    cin >> timeSlice;
    cout << endl;
    while(!cin || timeSlice < 0 || timeSlice > maxSlice)
    {
        cout << "Time must be between 0 and " << maxSlice << "ms" << endl << endl;
        cout << "How long was this process in the CPU: ";
        cin.clear();
        cin.ignore(100,'\n');
        cin >> timeSlice;
        cout << endl;
    }
    
    current.updateProcessTime(timeSlice);
    //current.increaseCpuCount();
    
    cout <<"Total CPU Process time has been updated" << endl << endl;
    cout <<"Current CPU Time is " << current.getTotalProcessTime()
         << "ms for process " << current.getPID() << endl;
    cout << endl;

    return timeSlice;

}


int main(int argc, const char * argv[]) {
    int printerNum;
    int cdrwNum;
    int diskNum;
    int timeSlice;
    int terminatedProcessCount = 0;
    int terminatedProcessTotalTime = 0;
    float totalAveTerminatedCpuTime = 0;
    //int cylinderNum;
    int systemPID = 0;
    int totalMemSize;
    int maxProcessSize;
    int pageSize;
    string userInput;
    vector<int> cylinderNum;
    vector<deque<PCB> > printers;
    vector<FscanDiskQueue> disks;
    vector<deque<PCB> > cdrws;
    deque<PCB> printerQueue;
    FscanDiskQueue diskQueue;
    deque<PCB> cdrwQueue;
    deque<PCB> readyQueue;
    
    
    printWelcome();
    
    cout << "*************SYS GEN***************" << endl;
    
    //SYS GEN*****************************************
    //************Timeslice****************
    cout << "How long is a time slice (in milliseconds): ";
    cin >> timeSlice;
    cout << endl;
    while(!cin || timeSlice < 1)
    {
        cout << "Invalid Input!" << endl;
        cout << "How long is a time slice (in milliseconds) ";
        cin.clear();
        cin.ignore(100,'\n');
        cin >> timeSlice;
        cout << endl;
    }
    cout << " A Timeslice is " << timeSlice << " milliseconds" << endl;
    cout << endl;
    
    //**************Printers**************
    cout << "How Many Printers would you like: ";
    cin >> printerNum;
    cout << endl;
    while(!cin || printerNum < 1)
    {
        cout << "Invalid Input!" << endl;
        cout << "How Many Printers: ";
        cin.clear();
        cin.ignore(100,'\n');
        cin >> printerNum;
        cout << endl;
    }
    cout << printerNum << " Printers added" << endl;
    cout << endl;
    
    //*************Disks***************
    cout << "How Many Disks would you like: ";
    cin >> diskNum;
    cout << endl;
    while(!cin || diskNum < 1)
    {
        cout << "Invalid Input!" << endl;
        cout << "How Many Disks: ";
        cin.clear();
        cin.ignore(100,'\n');
        cin >> diskNum;
        cout << endl;
    }
    cout << diskNum << " Disks added" << endl;
    cout << endl;
    
    //**************Cylinders**************
    
    for (int i = 0; i < diskNum; i++) {
        cout << "How Many Cylinders does disk " << i + 1 << " have: ";
        int cylNum;
        cin >> cylNum;
        cout << endl;
        while(!cin || cylNum < 1)
        {
            cout << "Invalid Input!" << endl;
            cout << "How Many Cylinders: ";
            cin.clear();
            cin.ignore(100,'\n');
            cin >> cylNum;
            cout << endl;
        }
        cylinderNum.push_back(cylNum);
    }
    for (int i = 0 ; i < diskNum; i++) {
        cout << "Disk " << i+1 << " has " << cylinderNum[i] << " cylinders" << endl;
    }
    //cout << "Each Disk has " << cylinderNum << " Cylinders" << endl;
    cout << endl;
    
    //*************CDRW***************
    cout << "How Many CD/RWs would you like: ";
    cin >> cdrwNum;
    cout << endl;
    while(!cin || cdrwNum < 1)
    {
        cout << "Invalid Input!" << endl;
        cout << "How Many CD/RWs: ";
        cin.clear();
        cin.ignore(100,'\n');
        cin >> cdrwNum;
        cout << endl;
    }
    cout << cdrwNum << " CD/RWs added" << endl;
    cout << endl;
    
    //*************MakeQueues***************
    for (int i = 0; i < printerNum+1; i++) {
        printers.push_back(printerQueue);
    }
    
    for (int i = 0; i < diskNum+1; i++) {
        disks.push_back(diskQueue);
    }
    
    for (int i = 0; i < cdrwNum+1; i++) {
        cdrws.push_back(cdrwQueue);
    }
    
    
    
    cout << "*************STARTING OS***************" << endl;
    
    //RUNNING*****************************************
    
    try {
        while (true) {
            
            
            try {
                userInput = "";
                cout << "Commands examples: {A, S, t, T, p1, d2, c3, P3, D2, C1}" << endl;
                cout << '>' ;
                cin >> userInput;
                cout << endl;
                
                if (userInput == "q" || userInput == "Q") {
                    throw -1;
                }
                
                
                //ADD PROCESSES*****************************************
                if (userInput == "A") {
                    PCB newProcess(systemPID);
                    readyQueue.push_back(newProcess);
                    systemPID++;
                    cout << "Process added to ready queue" << endl << endl;
                }
                
                //SNAPSHOTS*****************************************
                else if(userInput == "S"){
                    
                    do{
                        cout << "Please choose the snapshot you'd like:" << endl;
                        cout << "'r', 'p', 'd', or 'c' : ";
                        
                        cin >> userInput;
                        
                        cout << endl;
                    }
                    while (userInput != "r" && userInput != "p" && userInput != "d" && userInput != "c");
                    
                    //READY QUEUE PRINT*****************************************
                    if (userInput == "r") {
                        cout << endl << "READY QUEUE" << endl;
                        printListHeader(totalAveTerminatedCpuTime);
                        for (int i = 0; i < readyQueue.size(); i++) {
                            float aveBurst = 0;
                            if (readyQueue[i].getCpuCount() > 0) {
                                aveBurst = ((float)readyQueue[i].getTotalProcessTime())/readyQueue[i].getCpuCount();
                            }
                            
                            cout << left << "| " <<  setw(5) << readyQueue[i].getPID()
                            << left << "| " <<  setw(9) << "N/A"
                            << left << "| " <<  setw(8) << "N/A"
                            << left << "| " <<  setw(5)  << "N/A"
                            << left << "| " <<  setw(8) << "N/A"
                            << left << "| " <<  setw(6)  << "N/A"
                            << left << "| " <<  setw(6) << readyQueue[i].getTotalProcessTime()
                            << left << "| " <<  setw(10) << readyQueue[i].getAveBurstTime()
                            << left << "| "
                            << endl;

                            //cout << readyQueue[i].getPID() << endl;
                        }
                        cout <<" ------------------------------------------------------------------------"<<endl;
                        cout  << endl;
                    }
                    
                    //PRINTER QUEUE PRINT*****************************************
                    else if (userInput == "p") {
                        cout << endl << "PRINTER QUEUE" << endl;
                        printListHeader(totalAveTerminatedCpuTime);
                        
                        for (int i = 1; i < printers.size(); i++) {
                            cout << " --"<< "p" << i << endl;
                            //<<"--------------------------------------------------------------------"<< endl;
                            for (int j = 0; j < printers[i].size(); j++) {
                                
                                cout << printers[i][j];
                            }
                        }
                        cout <<" ------------------------------------------------------------------------"<<endl;
                        cout  << endl;
                    }
                    
                    
                    //DISK QUEUE PRINT*****************************************
                    else if (userInput == "d") {
                        cout << endl << "DISK QUEUE" << endl;
                        printListHeader(totalAveTerminatedCpuTime);
                        
                        for (int i = 1; i < disks.size(); i++) {
                            cout << " --"<< "d" << i << endl;
                            //<<"--------------------------------------------------------------------" << endl;
                            disks[i].printDiskQueue();
                        }
                        cout <<" ------------------------------------------------------------------------"<<endl;
                        cout  << endl;
                    }
                    
                    //CDRW QUEUE PRINT*****************************************
                    else if (userInput == "c") {
                        cout << endl << "CDRW QUEUE" << endl;
                        printListHeader(totalAveTerminatedCpuTime);
                        
                        for (int i = 1; i < cdrws.size(); i++) {
                            cout << " --"<< "c" << i << endl;
                            //<<"--------------------------------------------------------------------" << endl;
                            for (int j = 0; j < cdrws[i].size(); j++) {
                                cout << cdrws[i][j];
                            }
                        }
                        cout <<" ------------------------------------------------------------------------"<<endl;
                        cout  << endl;
                    }
                    
                    
                    else{
                        throw userInput;
                    }
                    
                }
                
                //TERMINATE PROCESS*****************************************
                else if(userInput == "t"){
                    if (readyQueue.empty()) {
                        cout << "The Ready Queue is empty" << endl << endl;
                    }
                    else{
                        readTimeSlice(readyQueue.front(), timeSlice);
                        cout << "Terminating Process " << readyQueue.front().getPID() << endl;
                        cout << "Total CPU time was " << readyQueue.front().getTotalProcessTime() << endl;
                        
                        terminatedProcessCount++;
                        terminatedProcessTotalTime += readyQueue.front().getTotalProcessTime();
                        readyQueue.pop_front();
                        cout  << endl;
                        totalAveTerminatedCpuTime = (float)terminatedProcessTotalTime/terminatedProcessCount;
                        
                    }
                }

                else if(userInput == "T"){
                    if (readyQueue.empty()) {
                        cout << "The Ready Queue is empty" << endl << endl;
                    }
                    else{
                        cout << "Moving Process " << readyQueue.front().getPID()
                             << " to back of the Ready Queue " << endl << endl;
                        
                        readyQueue.push_back(readyQueue.front());
                        readyQueue.pop_front();
                        readyQueue.back().updateProcessTime(timeSlice);
                        
                        cout <<"Total CPU Process time has been updated" << endl << endl;
                        cout <<"Current CPU Time is " << readyQueue.back().getTotalProcessTime()
                        << "ms for Process " << readyQueue.back().getPID() << endl;
                        cout << endl;
                    }
                }
                
                
                
                
                //ADD TO PRINTER QUEUE*****************************************
                else if(userInput[0] == 'p'){
                    userInput.erase(0,1);
                    if (checkValidNum(userInput, printerNum)) {
                        if (!readyQueue.empty()) {
                            readyQueue.front().fillPCB('p', false, 0);
                            printers[stoi(userInput)].push_back(readyQueue.front());
                            readyQueue.pop_front();
                            readTimeSlice(printers[stoi(userInput)].back(), timeSlice);
                            printers[stoi(userInput)].back().increaseCpuCount();
                        }
                        else{
                            cout << "There are no available processes in the Ready Queue" << endl;
                            cout << "Please populate the Ready Queue and try again" << endl << endl;
                        }
                        
                    }
                    else{
                        cout << "Printer does not exist" << endl << endl;
                    }
                    
                
                    
                }
                //ADD TO DISK QUEUE*****************************************
                else if(userInput[0] == 'd'){
                    userInput.erase(0,1);
                    if (checkValidNum(userInput,diskNum)) {
                        if (!readyQueue.empty()) {
                            readyQueue.front().fillPCB('d', true, cylinderNum[stoi(userInput)-1]);
                            readTimeSlice(readyQueue.front(), timeSlice);
                            readyQueue.front().increaseCpuCount();
                            disks[stoi(userInput)].push_back(readyQueue.front());
                            readyQueue.pop_front();

                        }
                        else{
                            cout << "There are no available processes in the Ready Queue" << endl;
                            cout << "Please populate the Ready Queue and try again" << endl << endl;
                        }
                        
                    }
                    else{
                        cout << "Printer does not exist" << endl << endl;
                    }
                }
                //ADD TO CDRW QUEUE*****************************************
                else if(userInput[0] == 'c'){
                    userInput.erase(0,1);
                    if (checkValidNum(userInput,cdrwNum)) {
                        if (!readyQueue.empty()) {
                            readyQueue.front().fillPCB('c', false, 0);
                            cdrws[stoi(userInput)].push_back(readyQueue.front());
                            readyQueue.pop_front();
                            readTimeSlice(cdrws[stoi(userInput)].back(), timeSlice);
                            cdrws[stoi(userInput)].back().increaseCpuCount();

                        }
                        else{
                            cout << "There are no available processes in the Ready Queue" << endl;
                            cout << "Please populate the Ready Queue and try again" << endl << endl;
                        }
                        
                    }
                    else{
                        cout << "CDRW does not exist" << endl << endl;
                    }
                    
                }
                //REMOVE FROM PRINTER QUEUE*****************************************
                else if(userInput[0] == 'P'){
                    userInput.erase(0,1);
                    if (userInput.length()<1) {
                        throw userInput;
                    }
                    if (checkValidNum(userInput, printerNum)) {
                        if (printers[stoi(userInput)].empty()) {
                            cout << "Printer Queue is empty" << endl << endl;
                        }
                        else{
                            readyQueue.push_back(printers[stoi(userInput)].front());
                            printers[stoi(userInput)].pop_front();
                            cout << "Printer Interrupt Handled" << endl << endl;
                        }
                    }
                    else{
                        cout << "Printer does not exist" << endl << endl;
                    }
                    
                }
                //REMOVE FROM DISK QUEUE*****************************************
                else if(userInput[0] == 'D'){
                    userInput.erase(0,1);
                    if (userInput.length()<1) {
                        throw userInput;
                    }
                    if (checkValidNum(userInput, diskNum)) {
                        if (disks[stoi(userInput)].empty()) {
                            cout << "Disk Queue is empty" << endl << endl;
                        }
                        else{
                            readyQueue.push_back(disks[stoi(userInput)].front());
                            disks[stoi(userInput)].pop_front();
                            cout << "Disk Interrupt Handled" << endl << endl;
                        }
                    }
                    else{
                        cout << "Disk does not exist" << endl << endl;
                    }
                    
                }
                //REMOVE FROM CDRW QUEUE*****************************************
                else if(userInput[0] == 'C'){
                    userInput.erase(0,1);
                    if (userInput.length()<1) {
                        throw userInput;
                    }
                    if (checkValidNum(userInput, cdrwNum)) {
                        if (cdrws[stoi(userInput)].empty()) {
                            cout << "CDRW Queue is empty" << endl << endl;
                        }
                        else{
                            readyQueue.push_back(cdrws[stoi(userInput)].front());
                            cdrws[stoi(userInput)].pop_front();
                            cout << "CD/RW Interrupt Handled" << endl << endl;
                        }
                    }
                    else{
                        cout << "CDRW does not exist" << endl << endl;
                    }
                    
                    
                    
                }
                
                
                else{
                    throw userInput;
                }
                
            } catch (string) {
                cout << "Input error: Please try again" << endl << endl;
            }
            //cout << endl;
        }
    } catch (int) {
        cout << "Exiting OS" << endl;
    }
    

    
    
    return 0;
}
