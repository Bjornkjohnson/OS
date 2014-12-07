//
//  FscanDiskQueue.h
//  OSprogram2
//
//  Created by Bjorn on 11/11/14.
//  Copyright (c) 2014 Bjorn Johnson. All rights reserved.
//

#ifndef __OSprogram2__FscanDiskQueue__
#define __OSprogram2__FscanDiskQueue__

#include <stdio.h>
#include <iostream>
#include <queue>
#include "PCB.h"
#include <string>
#include <algorithm>

class FscanDiskQueue{
private:
    deque<deque<PCB> > fscanQueues;
    
    
public:
    FscanDiskQueue();
    void printDiskQueue();
    bool empty();
    void push_back(PCB &);
    PCB front();
    void pop_front();


};

#endif /* defined(__OSprogram2__FscanDiskQueue__) */
