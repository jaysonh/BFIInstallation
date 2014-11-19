//
//  CutSceneTime.cpp
//  opencvExample
//
//  Created by jayson on 6/10/14.
//
//

#include "CutSceneTime.h"



CutSceneTime::CutSceneTime(float start, float end,float totalTime)
{
    startTime = calcPercentageTime(start,totalTime);
    endTime   = calcPercentageTime(end,totalTime);
    
}

bool CutSceneTime::isAfter(float currentPlayBackTime)
{
    printf("current: %f end %f\n",currentPlayBackTime,endTime);
    if(currentPlayBackTime > endTime)
        return true;
    else
        return false;

}

bool CutSceneTime::isWithIn(float currentPlayBackTime)
{
   
    if(currentPlayBackTime >=startTime && currentPlayBackTime < endTime)
        return true;
    else
        return false;
}

float CutSceneTime::calcPercentageTime(float time, float totalTime)
{
    float totalTimeWholeSeconds = (float)((int)totalTime);
    float totalTimePartSeconds  = totalTime - totalTimeWholeSeconds;
    float totalTimeSecondFraction = totalTimePartSeconds / 25.0f;
    
    float wholeSeconds = (float)((int)time);
    float partSeconds  = time - wholeSeconds;
    float secondFraction = partSeconds / 25.0f;
    
    
    
    return (wholeSeconds + secondFraction)/ (totalTimeSecondFraction + totalTimeWholeSeconds);;
}