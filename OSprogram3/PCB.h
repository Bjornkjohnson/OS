//
//  PCB.h
//  OSprogram1
//
//  Created by Bjorn Johnson on 10/10/14.
//  Copyright (c) 2014 Bjorn Johnson. All rights reserved.
//

#ifndef __OSprogram1__PCB__
#define __OSprogram1__PCB__

#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class PCB{
private:
    int PID;
    string fileName;
    int memStart;
    string readWrite;
    int fileLength;
    int totalProcessTime;
    int cpuCount;
    int cylinderNum;
    float aveBurstTime;
    int processSize;
    vector<int> frames;
    int physicalAddress;
    
public:
    PCB(int);
    void setPID(int);
    void setfileName(string);
    void setMemStart(int);
    void setReadWrite(char);
    void setFileLength(int);
    void setProcessSize(int);
    void printPCB();
    int getPID();
    int getProcessSize();
    int getFramesSize();
    vector<int> getFrames();
    void printFrames() const;
    friend ostream& operator<<(ostream& out, const PCB& dt);
    void fillPCB(char, bool, int, int);
    void updateProcessTime(int);
    int getTotalProcessTime();
    void increaseCpuCount();
    int getCpuCount();
    float getAveBurstTime();
    void updateFrames(int);
    void setPhysicalAddress(int, int);
    int getPhysicalAddress();
    friend bool operator<(const PCB&, const PCB &);
    
    friend bool operator==(const PCB&, const PCB &);
    


};

#endif /* defined(__OSprogram1__PCB__) */
