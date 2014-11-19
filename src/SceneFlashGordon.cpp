//
//  SceneFlashGordon.cpp
//  opencvExample
//
//  Created by jayson on 9/10/14.
//
//

#include "SceneFlashGordon.h"

 SceneFlashGordon::SceneFlashGordon()
{
    _camImg.allocate(1280 - 400,720,OF_IMAGE_COLOR_ALPHA);
    
    
     newPixsSize = 1280*720 * 4;
     newPixs = new unsigned char[newPixsSize];
    
    _needsTracking=false;
    heroImg.allocate(1280, 720, OF_IMAGE_COLOR_ALPHA);
    
     _hoverBikeVideo.setPixelFormat(OF_PIXELS_RGBA);
     _hoverBikeVideo.loadMovie(HOVERBIKE_LAYER);
    
    _mainVideo.loadMovie(MAIN_VIDEO_PATH);
    _mainVideo.setLoopState(OF_LOOP_NONE);
     _mainVideo.play();
     _hoverBikeVideo.play();

     _backdropImg[0].loadImage(BACKDROP1_PATH);
     _backdropImg[1].loadImage(BACKDROP2_PATH);
     _backdropImg[2].loadImage(BACKDROP3_PATH);
    
    
    _cutSceneTimesList.push_back(new CutSceneTime(13.20, 20.00, 49.12));
    _cutSceneTimesList.push_back(new CutSceneTime(24.01, 30.00, 49.12));
    _cutSceneTimesList.push_back(new CutSceneTime(37.04, 43.03, 49.12));
    
    _emotionGuideList.clear();
    _emotionGuideList.push_back(new CutSceneTime(0.0, 20.00, 49.12));
    _emotionGuideList.push_back(new CutSceneTime(20.00, 30.00, 49.12));
    _emotionGuideList.push_back(new CutSceneTime(30.00, 49.12, 49.12));
    
    fboBuffer.allocate(BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
    
    _currentBackdrop=0;
    
}

void SceneFlashGordon::setGreenScreenVals(int r,int g, int b)
{
    _rThresh = r;
    _gThresh = g;
    _bThresh = b;
}


void SceneFlashGordon::draw(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox)
{
    _mainVideo.update();
    _hoverBikeVideo.update();
    
    if(!_mainVideo.isPlaying() && _mainVideo.isLoaded())
    {
        _mainVideo.play();
    }
    
    drawBooth(webCamImg,faceBoundingBox);
    drawProjector();
    
}

float SceneFlashGordon::getVideoPosition()
{
    return _mainVideo.getPosition();
}


void SceneFlashGordon::drawBooth(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox)
{
    fboBuffer.begin();
    ofEnableAlphaBlending();
    //ofClear(0,0,0);
    
    if(ofRandom(0,200)<10)
        _currentBackdrop = (int)ofRandom(0,NUM_BACKDROP_IMAGES);
    
    _backdropImg[_currentBackdrop].draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
    
    unsigned char *pixs = webCamImg.getPixels();
    
    
    int i =0;
    int j = 0;
    for(int y = 0; y < webCamImg.getHeight();y++)
    {
        for(int x = 0; x < webCamImg.getWidth();x++,i+=3,j+=4)
        {
            int r = pixs[i];
            int g = pixs[i+1];
            int b = pixs[i+2];
            
            if(x < 200 || x > webCamImg.getWidth()-200)
            {
                newPixs[j] = 0;
                newPixs[j+1] = 0;
                newPixs[j+2] = 0;
                newPixs[j+3] = 0;
            }else if(r < _rThresh && g > _gThresh && b < _bThresh)
            {
                newPixs[j] = 0;
                newPixs[j+1] = 0;
                newPixs[j+2] = 0;
                newPixs[j+3] = 0;
            }else
            {
                newPixs[j]   = r;
                newPixs[j+1] = g;
                newPixs[j+2] = b;
                newPixs[j+3] = 255;
                
            }
        }
    }
    for(int i = 0, j=0; i < webCamImg.getWidth() * webCamImg.getHeight() * 3;i+=3,j+=4)
    {
        
    }
    
    heroImg.setFromPixels(newPixs, webCamImg.getWidth(), webCamImg.getHeight(), OF_IMAGE_COLOR_ALPHA);
    heroImg.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    

    _hoverBikeVideo.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
        
    fboBuffer.end();
    
    
    
    fboBuffer.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
    /*
    if(isShowBoothOnProjector())
        fboBuffer.draw(BOOTH_SCREEN_SIZE_X - BOOTH_SCREEN_SIZE_X/4,BOOTH_SCREEN_SIZE_Y   - BOOTH_SCREEN_SIZE_Y/4,BOOTH_SCREEN_SIZE_X/4,BOOTH_SCREEN_SIZE_Y/4);
    else
        _mainVideo.draw(BOOTH_SCREEN_SIZE_X - BOOTH_SCREEN_SIZE_X/4,BOOTH_SCREEN_SIZE_Y   - BOOTH_SCREEN_SIZE_Y/4,BOOTH_SCREEN_SIZE_X/4,BOOTH_SCREEN_SIZE_Y/4);
    */
    
    _font.drawString("Outside Feed:", OUTSIDE_FEED_TEXT_POS_X, OUTSIDE_FEED_TEXT_POS_Y);
    
    _font2.drawString("LIVE",LIVE_TEXT_POS_X,LIVE_TEXT_POS_Y);
    
    if(isShowBoothOnProjector() >= 0)
    {
        ofSetColor(0,0,0);
        ofRect(LIVE_ICON_POS_X,LIVE_ICON_POS_Y,_liveIcon.getWidth()/4,_liveIcon.getHeight()/4);
        ofSetColor(255,255,255);
        _liveIcon.draw(LIVE_ICON_POS_X,LIVE_ICON_POS_Y,_liveIcon.getWidth(),_liveIcon.getHeight());
        fboBuffer.draw(BOOTH_PREVIEW_WINDOW_POS_X,BOOTH_PREVIEW_WINDOW_POS_Y,BOOTH_PREVIEW_WINDOW_SIZE_X,BOOTH_PREVIEW_WINDOW_SIZE_Y);
    }else
    {
        _notLiveIcon.draw(LIVE_ICON_POS_X,LIVE_ICON_POS_Y);
        _mainVideo.draw(BOOTH_PREVIEW_WINDOW_POS_X,BOOTH_PREVIEW_WINDOW_POS_Y,BOOTH_PREVIEW_WINDOW_SIZE_X,BOOTH_PREVIEW_WINDOW_SIZE_Y);
    }
    drawEmotionGuideLineText();
    
    //delete newPixs;
}

void SceneFlashGordon::drawProjector()
{
    if(isShowBoothOnProjector()>=0)
        fboBuffer.draw(PROJECTOR_SCREEN_POS_X,0,PROJECTOR_SCREEN_SIZE_X,PROJECTOR_SCREEN_SIZE_Y);
    else
        _mainVideo.draw(PROJECTOR_SCREEN_POS_X,0,PROJECTOR_SCREEN_SIZE_X,PROJECTOR_SCREEN_SIZE_Y);

}

int SceneFlashGordon::isShowBoothOnProjector()
{
    int indx=-1;
    for(int i = 0; i < _cutSceneTimesList.size();i++)
    {
        CutSceneTime * cutSceneTime = _cutSceneTimesList[i];
        
        if(cutSceneTime->isWithIn(_mainVideo.getPosition() ))
            indx=i;
    }
    return indx;
}

void SceneFlashGordon::closeAssets()
{
    
     _mainVideo.close();
     _hoverBikeVideo.close();
}

bool SceneFlashGordon::isFinished()
{
    
    if(_mainVideo.getPosition()>0.99f)
        return true;
    else
        return false;
    //return !_mainVideo.isPlaying();
}


void SceneFlashGordon::drawEmotionGuideLineText()
{
    int indx=0;
    
    for(int i = 0; i < _emotionGuideList.size() ;i++)
    {
        CutSceneTime * cutSceneTime = _emotionGuideList[i];
        
        if(cutSceneTime->isWithIn(_mainVideo.getPosition()))
        {
            indx=i ;
        }
    }
    
    _font.drawString("Notes:",EMOTION_GUIDELINES_TEXT_POS_X,EMOTION_GUIDELINES_TEXT_POS_Y);
    
    switch(indx)
    {
        case 0:
            _font.drawString(TEXT1,EMOTION_GUIDELINES_TEXT1_POS_X,EMOTION_GUIDELINES_TEXT1_POS_Y);
            break;
        case 1:
            _font.drawString(TEXT2,EMOTION_GUIDELINES_TEXT2_POS_X,EMOTION_GUIDELINES_TEXT2_POS_Y);
            break;
        case 2:
            _font.drawString(TEXT3,EMOTION_GUIDELINES_TEXT3_POS_X,EMOTION_GUIDELINES_TEXT3_POS_Y);
            break;
    }
}