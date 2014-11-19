//
//  ForbiddenPlanet.cpp
//  opencvExample
//
//  Created by jayson on 7/10/14.
//
//

#include "ForbiddenPlanet.h"



 ForbiddenPlanet::ForbiddenPlanet()
{
    _lastBounds = new ofRectangle(0,0,0,0);
    _needsTracking=true;
    _contrast = 0.0f;
    fboBuffer.allocate(BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    _cutSceneTimesList.push_back(new CutSceneTime(8.15, 14.01, 50.00));
    _cutSceneTimesList.push_back(new CutSceneTime(19.15, 28.08, 50.00));
    _cutSceneTimesList.push_back(new CutSceneTime(36.18, 45.05, 50.00));
    
    _emotionGuideList.clear();
    _emotionGuideList.push_back(new CutSceneTime(0.0, 14.01, 50.00));
    _emotionGuideList.push_back(new CutSceneTime(14.01, 50.00, 50.00));
    
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
    
    
    _mainVideo.loadMovie(FORBIDDENPLANET_MAIN_VIDEO);
    _mainVideo.setLoopState(OF_LOOP_NONE);
    _laserVideo.setPixelFormat(OF_PIXELS_RGBA);
    _laserVideo.loadMovie(LASER_VIDEO);
    _backdropImg.loadImage(BACKGROUND_IMAGE);
    
    _mainVideo.play();
    _laserVideo.play();
    learnBackground = true;
}

float ForbiddenPlanet::getVideoPosition()
{
    return 0.0f;
}
void ForbiddenPlanet::draw(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox)
{
    _laserVideo.update();
    _mainVideo.update();
    if(!_mainVideo.isPlaying() && _mainVideo.isLoaded())
    {
        _mainVideo.play();
    }
    drawBoothScreen(webCamImg,faceBoundingBox);
    drawProjectorScreen();
    
}

void ForbiddenPlanet::drawProjectorScreen()
{
    
    
    if(isShowBoothOnProjector()>=0)
        fboBuffer.draw(PROJECTOR_SCREEN_POS_X,0,PROJECTOR_SCREEN_SIZE_X,PROJECTOR_SCREEN_SIZE_Y);
    else
        _mainVideo.draw(PROJECTOR_SCREEN_POS_X,0,PROJECTOR_SCREEN_SIZE_X,PROJECTOR_SCREEN_SIZE_Y);
}

void ForbiddenPlanet::drawBoothScreen(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox)
{
    // increase top and bottom of facebounding box by 35%
    float newHeight = faceBoundingBox.height * 1.35f;
    float heightDiff = newHeight - faceBoundingBox.height;
    
    float newY = faceBoundingBox.y - heightDiff/2.0;
    
    faceBoundingBox.y = newY;
    faceBoundingBox.height = newHeight;
    
    
    fboBuffer.begin();
    ofClear(0,0,0);
    
    float sizeMultX = 1.5f;//(float)BOOTH_SCREEN_SIZE_X / (float)webCamImg.width;
    float sizeMultY = 1.5f;//(float)BOOTH_SCREEN_SIZE_Y / (float)webCamImg.height;
    
    
    
    ofSetColor(255,255,255);
    ofSetLineWidth(2.5f);
    
    ofSetColor(255,255,255);
    _backdropImg.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    ofNoFill();
    ofSetColor(255,0,50);
    
    // Find position of face
    ofPoint faceCentre = faceBoundingBox.getCenter();
    
    float faceCentreDiffY = BOOTH_SCREEN_SIZE_Y/2.0-25.0f-faceCentre.y;
    float faceCentreDiffX = BOOTH_SCREEN_SIZE_X/2.0-faceCentre.x;
    
    float faceSizeDiff = 384.000000 / faceBoundingBox.width;
    
    float w = faceSizeDiff * (float)BOOTH_SCREEN_SIZE_X;
    float h = faceSizeDiff * (float)BOOTH_SCREEN_SIZE_Y * 1.25f;
    
    float xPos = (BOOTH_SCREEN_SIZE_X/2) - FACE_TARGET_POS_X + faceCentreDiffX;
    float yPos = (BOOTH_SCREEN_SIZE_Y/2) - FACE_TARGET_POS_Y + faceCentreDiffY;
    
    ofRectangle faceBounds;
    
    float currentMult = 0.25f;
    float prevMult = 0.75f;
    if(_lastBounds->x != 0 &&_lastBounds->y != 0 &&_lastBounds->width != 0 &&_lastBounds->height != 0)
    {
        if(_lastBounds->x !=NULL && _lastBounds->y != NULL && _lastBounds->width !=NULL && _lastBounds->height != NULL)
        {
            printf("%f %f %f %f\n",_lastBounds->x,_lastBounds->y,_lastBounds->width,_lastBounds->height);
            faceBounds = ofRectangle(xPos* currentMult + _lastBounds->x*prevMult,yPos * currentMult + _lastBounds->y * prevMult,w * currentMult + _lastBounds->width * prevMult,h * currentMult + _lastBounds->height*prevMult );
        }
    }else
        faceBounds = ofRectangle(xPos,yPos,w,h);
    

    // Use face bounds to chop out contour image
    //printf("roi: %f %f %f %f\n",faceBoundingBox.x,faceBoundingBox.y,faceBoundingBox.width,faceBoundingBox.height);
    if(faceBoundingBox.width > 0 && faceBoundingBox.height > 0 && faceBoundingBox.width>0 && faceBoundingBox.height > 0)
    {
        ofxCvGrayscaleImage grayConvert;
        grayConvert = webCamImg;
        
        
        ofImage img;
        img.setFromPixels(grayConvert.getPixels(), grayConvert.width, grayConvert.height, OF_IMAGE_GRAYSCALE);
        img.resize(1280,720);
        img.crop(faceBoundingBox.x,faceBoundingBox.y,faceBoundingBox.width,faceBoundingBox.height);
   
        
        //grayConvert.resize(640,480);
        ofPushMatrix();
        ofTranslate(15,0);
        ofSetColor(200,0,75);
        drawContours(0.4 + abs(sin(_contrast))*0.6f,img,sizeMultX,sizeMultY,faceBoundingBox);
        
        ofTranslate(5,7);
        drawContours(1.0f-0.4 + abs(sin(_contrast))*0.6f,img,sizeMultX,sizeMultY,faceBoundingBox);
        ofPopMatrix();
        
    }
    _contrast += 0.025f;
    
    ofFill();
    ofSetColor(255,255,255);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    _laserVideo.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
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
    
    printf("show booth on projector: %i\n",isShowBoothOnProjector());
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
}


void ForbiddenPlanet::setGreenScreenVals(int r,int g, int b)
{
   
}

void ForbiddenPlanet::drawContours(float contrast, ofImage img,float sizeMultX,float sizeMultY, ofRectangle faceBoundingBox)
{
    
    
    ofxCvGrayscaleImage faceImg;
    
    faceImg.setFromPixels(img.getPixelsRef());
    
    faceImg.brightnessContrast(0.05f,contrast);
    
    contourFinder.findContours(faceImg, 5, (340*240), 45, true);
    ofSetColor(200,0,50);
    
    for (int i = 0; i < contourFinder.nBlobs; i++){
        
        float lastX = 0;
        float lastY = 0;
        
        glBegin(GL_LINES);
        for(int j =0; j < contourFinder.blobs[i].nPts;j++)
        {
            float x = FACE_TARGET_POS_X - (faceImg.width*sizeMultX)/2+ contourFinder.blobs[i].pts[j].x * sizeMultX;
            float y = FACE_TARGET_POS_Y - (faceImg.height*sizeMultY)/2 + contourFinder.blobs[i].pts[j].y * sizeMultY;
            
            if(ofDist(lastX,lastY,x,y) < 25.0 && (int)lastX != 0 && (int)lastY != 0)
            {
                glVertex2f(x,y);
                glVertex2f(lastX,lastY);
            }
            lastX = x;
            lastY = y;
            //ofCurveVertex( contourFinder.blobs[i].pts[j].x, contourFinder.blobs[i].pts[j].y);
            
        }
        glEnd();
    }
}
/*bool ForbiddenPlanet::isShowBoothOnProjector()
{
    bool showBoothOnProjector=false;
    for(int i = 0; i < _cutSceneTimesList.size();i++)
    {
        CutSceneTime * cutSceneTime = _cutSceneTimesList[i];
        
        if(cutSceneTime->isWithIn(_mainVideo.getPosition() ))
            showBoothOnProjector=true;
    }
    return showBoothOnProjector;
}*/

int ForbiddenPlanet::isShowBoothOnProjector()
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

bool ForbiddenPlanet::isFinished()
{
    
    if(_mainVideo.getPosition()>0.99f)
        return true;
    else
        return false;
   // return !_mainVideo.isPlaying();
}


void ForbiddenPlanet::closeAssets()
{
    
    _mainVideo.close();
    _laserVideo.close();
}


void ForbiddenPlanet::drawEmotionGuideLineText()
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
    }
}