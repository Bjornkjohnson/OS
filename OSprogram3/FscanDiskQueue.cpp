//
//  FscanDiskQueue.cpp
//  OSprogram2
//
//  Created by Bjorn on 11/11/14.
//  Copyright (c) 2014 Bjorn Johnson. All rights reserved.
//

#include "FscanDiskQueue.h"



FscanDiskQueue::FscanDiskQueue(){
    deque<PCB> queue;
    fscanQueues.push_back(queue);
    fscanQueues.push_back(queue);
    
}

bool myfunction (PCB i,PCB j) { return (i<j); }

void FscanDiskQueue::printDiskQueue(){
    for (int i = 0; i < fscanQueues.size(); i++) {
        for (int j = 0; j < fscanQueues[i].size(); j++) {
            cout <<  fscanQueues[i][j];
        }
    }

}

bool FscanDiskQueue::empty(){
    if (fscanQueues[0].empty() && fscanQueues[1].empty()) {
        return true;
    }
    return false;
}

void FscanDiskQueue::push_back(PCB & current){
    fscanQueues[1].push_back(current);
    sort(fscanQueues[1].begin(), fscanQueues[1].end(), myfunction);

}

PCB FscanDiskQueue::front(){
    if (fscanQueues[0].empty()) {
        deque<PCB> queue;
        fscanQueues.pop_front();
        fscanQueues.push_back(queue);
    }
    return fscanQueues[0].front();
}

void FscanDiskQueue::pop_front(){
    if (fscanQueues[0].empty()) {
        deque<PCB> queue;
        fscanQueues.pop_front();
        fscanQueues.push_back(queue);
    }
    fscanQueues[0].pop_front();
}

bool FscanDiskQueue::findProcess(int PID){
    for (int i = 0; i < fscanQueues.size(); i++) {
        for (int j = 0; j < fscanQueues[i].size(); j++) {
            cout << "Searching Disk Queues" << endl;
            if (fscanQueues[i][j].getPID() == PID) {
                return true;
            }
            
        }
    }
    return false;

}

PCB FscanDiskQueue::killProcess(int PID){
    for (int i = 0; i < fscanQueues.size(); i++) {
        for (int j = 0; j < fscanQueues[i].size(); j++) {
            if (fscanQueues[i][j].getPID() == PID) {
                PCB temp = fscanQueues[i][j];
                fscanQueues[i].erase(fscanQueues[i].begin() + j);
                return temp;
            }
            
        }
    }
    PCB error(-1);
    return error;
}
