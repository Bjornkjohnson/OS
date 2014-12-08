//
//  PCB.cpp
//  OSprogram1
//
//  Created by Bjorn Johnson on 10/10/14.
//  Copyright (c) 2014 Bjorn Johnson. All rights reserved.
//

#include "PCB.h"



PCB::PCB(int PID){

    this->PID = PID;
    fileName = "";
    memStart = 0;
    readWrite = ' ';
    fileLength = 0;
    totalProcessTime = 0;
    cpuCount = 0;
    cylinderNum = 0;
    aveBurstTime = 0;
    
    
}
void PCB::setPID(int PID){
    this->PID = PID;
}
void PCB::setfileName(string fileName){
    this->fileName = fileName;
}
void PCB::setMemStart(int memStart){
    this->memStart = memStart;
}
void PCB::setReadWrite(char readWrite){
    this->readWrite = readWrite;
}
void PCB::setFileLength(int fileLength){
    this->fileLength = fileLength;
}
void PCB::setProcessSize(int processSize){
    this->processSize = processSize;
}
void PCB::printPCB(){
    cout << PID << endl;
}

int PCB::getPID(){
    return this->PID;
}

int PCB::getProcessSize(){
    return this->processSize;
}

ostream& operator<<(ostream& out, const PCB& dt){
    
    if (dt.readWrite == "r" && dt.cylinderNum == 0) {
        out << left << "| " <<  setw(5) << dt.PID
        << left << "| " <<  setw(9) << dt.fileName
        << left << "| " <<  setw(8) <<dt.memStart
        << left << "| " <<  setw(5)  <<dt.readWrite
        << left << "| " <<  setw(8) << "N/A"
        << left << "| " <<  setw(6)  << "N/A"
        << left << "| " <<  setw(6) << dt.totalProcessTime
        << left << "| " <<  setw(10) << ((float)dt.totalProcessTime)/dt.cpuCount
        << left << "| "
        << endl;
    }
    else if(dt.readWrite == "w" && dt.cylinderNum == 0){
        out << left << "| " <<  setw(5) << dt.PID
        << left << "| " <<  setw(9) << dt.fileName
        << left << "| " <<  setw(8) << dt.memStart
        << left << "| " <<  setw(5)  << dt.readWrite
        << left << "| " <<  setw(8) << dt.fileLength
        << left << "| " <<  setw(6)  << "N/A"
        << left << "| " <<  setw(6) << dt.totalProcessTime
        << left << "| " <<  setw(10) << ((float)dt.totalProcessTime)/dt.cpuCount
        << left << "| "
        << endl;
    }
    else if (dt.readWrite == "w" && dt.cylinderNum != 0){
        out << left << "| " <<  setw(5) << dt.PID
        << left << "| " <<  setw(9) <<  dt.fileName        //file
        << left << "| " <<  setw(8) << dt.memStart        //mem
        << left << "| " <<  setw(5)  <<  dt.readWrite       //read
        << left << "| " <<  setw(8) <<  dt.fileLength      //length
        << left << "| " <<  setw(6)  <<  dt.cylinderNum      //cyl#
        << left << "| " <<  setw(6) << dt.totalProcessTime              //CPUtime
        << left << "| " <<  setw(10) << ((float)dt.totalProcessTime)/dt.cpuCount               //AveBur
        << left << "| "
        << endl;

    }
    else {
        out << left << "| " <<  setw(5) << dt.PID
        << left << "| " <<  setw(9) << dt.fileName
        << left << "| " <<  setw(8) << dt.memStart
        << left << "| " <<  setw(5)  << dt.readWrite
        << left << "| " <<  setw(8) << "N/A"
        << left << "| " <<  setw(6)  << dt.cylinderNum
        << left << "| " <<  setw(6) << dt.totalProcessTime
        << left << "| " <<  setw(10) << ((float)dt.totalProcessTime)/dt.cpuCount
        << left << "| "
        << endl;
        
    }

    
    return out;
}

void PCB::fillPCB(char procType, bool isDisk, int cylinderMax){
    cout << "Please enter filename: ";
    cin >> this->fileName;
    cout << endl;
    
    //**********************************
    cout << "Please enter mem start: ";
    cin >> this->memStart;
    while(!cin)
    {
        cout << "That was not a number!" << endl;
        cout << "Please enter mem start: ";
        cin.clear();
        cin.ignore(100,'\n');
        cin >> this->memStart;
        cout << endl;
    }
    cout << endl;
    
    //*************************************
    if (procType == 'c' || procType == 'd') {
        cout << "Please enter 'r' for READ or 'w' for WRITE: ";
        cin >> this->readWrite;
        cout << endl;
        while(this->readWrite != "r" && this->readWrite != "w")
        {
            cout << "C'mon man, stop screwing around." << endl << endl;
            cout << "Please enter 'r' for READ or 'w' for WRITE: ";
            cin.clear();
            cin.ignore(100,'\n');
            cin >> this->readWrite;
            cout << endl;
        }
        cin.clear();
        cin.ignore(100,'\n');
        cout << endl;
    }
    else{
        this->readWrite = 'w';
    }
    
    //***************************************
    if (this->readWrite == "w") {
        cout << "Please enter file length: ";
        cin >> this->fileLength;
        cout << endl;
        while(!cin)
        {
            cout << "That was not a number!" << endl;
            cout << "Please enter file length: ";
            cin.clear();
            cin.ignore(100,'\n');
            cin >> this->fileLength;
            cout << endl;
        }
        
        cout << endl;

    }
    else{
        this->fileLength = 0;
    }
    
    //***************************************
    if (isDisk == true) {
        cout << "Please enter Cylinder number to access: ";
        cin >> this->cylinderNum;
        cout << endl;
        while(!cin || cylinderNum < 0 || cylinderNum > cylinderMax)
        {
            cout << "Cylinder number must be between 0 and "
                 << cylinderMax << endl << endl;
            cout << "Please enter Cylinder number to access: ";
            cin.clear();
            cin.ignore(100,'\n');
            cin >> this->cylinderNum;
            cout << endl;
        }
        cout << endl;
    }


}

void PCB::updateProcessTime(int timeSlice){
    totalProcessTime += timeSlice;
}

int PCB::getTotalProcessTime(){
    return totalProcessTime;

}

void PCB::increaseCpuCount(){
    cpuCount++;
    aveBurstTime = ((float)totalProcessTime)/cpuCount;
    
}

int PCB::getCpuCount(){
    return cpuCount;
}

float PCB::getAveBurstTime(){
    return aveBurstTime;
}

bool operator<(const PCB &lhs, const PCB &rhs){
    if (lhs.cylinderNum < rhs.cylinderNum) {
        return true;
    }
    
    return false;
    
    
}

bool operator==(const PCB &lhs, const PCB &rhs){
    if (lhs.cylinderNum == rhs.cylinderNum) {
        return true;
    }
    
    return false;
    
    
}

