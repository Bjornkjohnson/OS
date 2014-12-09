//
//  FrameList.cpp
//  OSprogram3
//
//  Created by Bjorn on 8/12/14.
//  Copyright (c) 2014 Bjorn Johnson. All rights reserved.
//

#include "FrameList.h"
FrameList::FrameList(int size){
    bool active = false;
    for (int i = 0; i < size; i++) {
        frameList.push_back(active);
    }
}

void FrameList::updateFrameList(int numberOfFrames){
    int i = 0;
    int j = 0;
    while (i < numberOfFrames && j < frameList.size()) {
        if (frameList[j] == false) {
            frameList[j] = true;
            i++;
        }
        j++;
    }
}

void FrameList::clearFrames(int numberOfFrames){
    
}