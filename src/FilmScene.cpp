//
//  FilmScene.cpp
//  opencvExample
//
//  Created by jayson on 6/10/14.
//
//

#include "FilmScene.h"

FilmScene::FilmScene()
{
    _font2.loadFont("fonts/Gridnik.ttf", 30, true);
	_font.loadFont("fonts/Gridnik.ttf", 18, true);
    
    _liveIcon.loadImage(LIVE_ICON_PATH);
    _notLiveIcon.loadImage(NOT_LIVE_ICON_PATH);
}
void FilmScene::toggleHeightTracking()
{
    _heightTracking=!_heightTracking;
    _showUI=false;
    
}


bool FilmScene::isAdjustingFaceHeight()
{
    return _heightTracking;
}

bool FilmScene::needsFaceTracking()
{
    return _needsTracking;
}

void FilmScene::toggleUI()
{
    _showUI = !_showUI;
}