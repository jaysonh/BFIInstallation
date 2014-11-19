//
//  TitleScreens.cpp
//  opencvExample
//
//  Created by jayson on 13/10/14.
//
//

#include "TitleScreens.h"


void TitleScreens::init()
{
    titleStartMillis = ofGetElapsedTimeMillis();
    _startTime=ofGetElapsedTimeMillis();
    _currentBoard = 0;
    endTime = titleStartMillis + DISPLAY_BOARD_TIME;
    
    _titleBooth=NULL;
    _titleProjector=NULL;
    
    
	_font.loadFont("fonts/Gridnik.ttf", 30, true);
}


bool TitleScreens::finishedTitle()
{
    if(ofGetElapsedTimeMillis() >= endTime)
        return true;
    else
        return false;
}
void TitleScreens::draw(int displayScreen)
{
    printf("displaying title screen: %i\n",displayScreen);
    if(_titleBooth==NULL|| _titleProjector == NULL)
    {
        _titleProjector = new ofImage();
        _titleBooth = new ofImage();
        switch(displayScreen)
        {
            case 0:
                _titleProjector->loadImage(BOARD1_PROJECTOR);
                _titleBooth->loadImage(BOARD1_BOOTH);
                break;
            case 1:
                _titleProjector->loadImage(BOARD2_PROJECTOR);
                _titleBooth->loadImage(BOARD2_BOOTH);
                break;
            case 2:
                _titleProjector->loadImage(BOARD3_PROJECTOR);
                _titleBooth->loadImage(BOARD3_BOOTH);
                break;
        }
    }
    
    if(_titleBooth!=NULL|| _titleProjector != NULL)
    {
        _titleBooth->draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
        _titleProjector->draw(PROJECTOR_SCREEN_POS_X,0,PROJECTOR_SCREEN_SIZE_X,PROJECTOR_SCREEN_SIZE_Y);
        
        ofSetColor(255);
        char text[64];
        int timeDiff = (DISPLAY_BOARD_TIME-(ofGetElapsedTimeMillis() - _startTime))/1000;
        
        if(timeDiff < (DISPLAY_BOARD_TIME/1000))
        {
            sprintf(text,"%i",timeDiff);
            _font.drawString(text, YOUR_ON_TIME_POS_X, YOUR_ON_TIME_POS_Y);
        }
        
    }
}

bool TitleScreens::displayScene()
{
    if(ofGetElapsedTimeMillis() < endTime)
        return false;
    else
        return true;
}