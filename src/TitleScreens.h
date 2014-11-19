//
//  TitleScreens.h
//  opencvExample
//
//  Created by jayson on 13/10/14.
//
//

#ifndef __opencvExample__TitleScreens__
#define __opencvExample__TitleScreens__

#include <iostream>
#include "ofMain.h"
#include "global.h"

#define DISPLAY_BOARD_TIME 15000
#define NUM_BOARDS 3

#define BOARD1_BOOTH        "assets/titles/Motivations_Alien.png"
#define BOARD1_PROJECTOR    "assets/titles/Nextup_Alien.png"
#define BOARD2_BOOTH        "assets/titles/Motivations_ForbiddenPlanet.png"
#define BOARD2_PROJECTOR    "assets/titles/Nextup_ForbiddenPlanet.png"
#define BOARD3_BOOTH        "assets/titles/Motivations_Metropolis.png"
#define BOARD3_PROJECTOR    "assets/titles/Nextup_Metropolis.png"

#define YOUR_ON_TIME_POS_X 1155
#define YOUR_ON_TIME_POS_Y 650

class TitleScreens
{
public:
    void init();
    void draw(int displayScreen);
    bool displayScene();
    bool finishedTitle();
private:
    
    
    long titleStartMillis,endTime,_startTime;
    int _currentBoard;
    
    ofImage * _titleProjector;
    ofImage * _titleBooth;
    
    ofTrueTypeFont	_font;
};

#endif /* defined(__opencvExample__TitleScreens__) */
