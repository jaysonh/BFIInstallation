#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    _showUI=false;
    displayTitle=true;
    _currentScene=0;
    drawnOnce=false;
    _showWebcamImg=false;
	vidGrabber.setDeviceID(1);
	    vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(WEBCAM_RES_X,WEBCAM_RES_Y);
	
    colorImg.allocate(WEBCAM_RES_X,WEBCAM_RES_Y);
	grayImage.allocate(WEBCAM_RES_X,WEBCAM_RES_Y);

	bLearnBakground = true;
	threshold = 80;
    
    faceFinder.setup("assets/opencv_files/haarcascade_frontalface_default.xml");
    
    
    faceBoundingBox.setX(0);
    faceBoundingBox.setY(0);
    faceBoundingBox.setWidth(0);
    faceBoundingBox.setHeight(0);
    
    _fullscreen=false;
    _showFPS=false;
    ofSetFullscreen(false);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    _gui.setup();
    _gui.add(_redThreshSlider.setup( "red", 0, 0, 255 ));
    _gui.add(_greenThreshSlider.setup( "green", 0, 0, 255 ));
    _gui.add(_blueThreshSlider.setup( "blue", 0, 0, 255 ));
	
    titleScreens.init();
	mainOutputSyphonServer.setName("Screen Output");
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);

    bool bNewFrame = false;

       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();

    
    colorImg.setFromPixels(vidGrabber.getPixels(), WEBCAM_RES_X,WEBCAM_RES_Y);
    
	if (bNewFrame && _scene != NULL){

	    
        // Flip image
        colorImg.mirror(false,true);
        _scene->setGreenScreenVals(_redThreshSlider,_greenThreshSlider,_blueThreshSlider);
        if(_scene->needsFaceTracking())
        {
            grayImage = colorImg;
            ofxCvGrayscaleImage scaledImg;
            scaledImg = grayImage;
            scaledImg.resize(HAAR_SCALE_DOWN_SIZE_X,HAAR_SCALE_DOWN_SIZE_Y);
            faceFinder.findHaarObjects(scaledImg);
            
            if(faceFinder.blobs.size()>0)
            {
            // Find bounding box that was closest to the last one
            
            
                faceBoundingBox = faceFinder.blobs[0].boundingRect;
                faceBoundingBox.x *= ((float)BOOTH_SCREEN_SIZE_X / HAAR_SCALE_DOWN_SIZE_X);
                faceBoundingBox.y *= ((float)BOOTH_SCREEN_SIZE_Y / HAAR_SCALE_DOWN_SIZE_Y);
                faceBoundingBox.width*= ((float)BOOTH_SCREEN_SIZE_X / HAAR_SCALE_DOWN_SIZE_X);
                faceBoundingBox.height*= ((float)BOOTH_SCREEN_SIZE_Y / HAAR_SCALE_DOWN_SIZE_Y);
                //faceBoundingBox.scale(8.0f,8.0f);
            
            }
        }
	}

}

void testApp::selectScene(int sceneNum)
{
    
    if(_scene != NULL)
        _scene->closeAssets();
    
    switch(sceneNum)
    {
        case 0:
            
            _scene = new SceneAliens();
            
            break;
        
        case 1:
            
            _scene = new ForbiddenPlanet();
            
            break;
        case 2:
            
            _scene = new SceneMetropolis();
            
            break;
    }
}

//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
	
    if(!displayTitle)
    {
        printf("drawing scene\n");
        
        if(_scene != NULL)
        {
            _scene->draw(colorImg,faceBoundingBox);
        
            if(_scene->isFinished())
            {
                printf("Scene finsihed\n");
                displayTitle=true;
                
                _currentScene++;
                if(_currentScene>= NUM_SCENES)
                    _currentScene=0;
                titleScreens.init();
            }
        }
        
    }
    else
    {
        
        titleScreens.draw(_currentScene);
       
        
        if(titleScreens.finishedTitle())
        {
            displayTitle=false;
            
            selectScene(_currentScene);
            
        }
        
    }
    
    if(_showUI)
        _gui.draw();
    
    if(_showWebcamImg)
        colorImg.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
    ofNoFill();
    ofSetColor(0,255,0);
    
    if(_showFPS)
    {
        displayFPSCounter();
    
        // Draw face detection zone
        ofNoFill();
        ofSetColor(0,255,0);
        ofRect(faceBoundingBox.x ,faceBoundingBox.y,faceBoundingBox.width,faceBoundingBox.height);
    }
    
	mainOutputSyphonServer.publishScreen();
    

}

void testApp::displayFPSCounter()
{
    char title[128];
    sprintf(title,"Framerate: %f Face Height Adjust: %i video position: %f",ofGetFrameRate(),_scene->isAdjustingFaceHeight(),_scene->getVideoPosition());
    ofSetColor(0,255,0);
    ofDrawBitmapString(title, 20,20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){
        case 'h':
            _scene->toggleHeightTracking();
            break;
        case '\t':
            _showWebcamImg=!_showWebcamImg;
            break;
        case 'f':
            _fullscreen = !_fullscreen;
            ofSetFullscreen(_fullscreen);
            break;
		case ' ':
			_showFPS = !_showFPS;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
        case 'u':
        case 'U':
           _showUI = !_showUI;
            break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    printf("mousepos: %i %i\n",x,y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
