//
//  FrameList.h
//  OSprogram3
//
//  Created by Bjorn on 8/12/14.
//  Copyright (c) 2014 Bjorn Johnson. All rights reserved.
//

#ifndef __OSprogram3__FrameList__
#define __OSprogram3__FrameList__

#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;



class FrameList{
private:
    vector<int> frameList;
        

public:
    FrameList(int);
    void updateFrameList(int);
    void clearFrames(int);
};


#endif /* defined(__OSprogram3__FrameList__) */
