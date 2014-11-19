//
//  CutSceneTime.h
//  opencvExample
//
//  Created by jayson on 6/10/14.
//
//

#ifndef __opencvExample__CutSceneTime__
#define __opencvExample__CutSceneTime__

#include <iostream>

class CutSceneTime
{
public:
    
    CutSceneTime(float start, float end,float totalTime);
    bool isWithIn(float currentPlayBackTime);
    bool isAfter(float currentPlayBackTime);
    float startTime,endTime;
private:
    float calcPercentageTime(float t, float totalTime);
    
};
#endif /* defined(__opencvExample__CutSceneTime__) */
