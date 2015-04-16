#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofEnableNormalizedTexCoords();
    ofImage img;
    img.loadImage("hci.png");
    img.mirror(false, true);
    tex.allocate(640, 640, GL_RGB, true);
    ang = 0;
    glEnable(GL_DEPTH_TEST); // enable depth testing, otherwise things will
    tex.loadData(img.getPixels(), 640, 640, GL_RGB);
    ofDisableNormalizedTexCoords();
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    openNIDevice.setup();
    openNIDevice.setLogLevel(OF_LOG_VERBOSE);
    openNIDevice.addDepthGenerator();
    openNIDevice.addImageGenerator(); // comment this out
    openNIDevice.start();
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
    selectedPoint = ofPoint(200,200);
    
    

    


}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
    
    if (depthLeft < 300){
        ang += 0.5;
    }else if(depthRight < 300){
        ang -= 0.5;
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);
    openNIDevice.drawDebug();
    ofShortPixels depthMap = openNIDevice.getDepthRawPixels();
    
    int posLeftWidth = viewSizeW * 1 / 4;
    int posLeftHeight = viewSizeH / 2;
    depthLeft = depthMap[posLeftWidth + posLeftHeight * viewSizeW];
    
    int posRightWidth = viewSizeW * 3 / 4;
    int posRightHeight = viewSizeH / 2;
    depthRight = depthMap[posRightWidth + posRightHeight * viewSizeW];
    
    ofSetColor(100, 100, 100);
    ofRect(posLeftWidth, posLeftHeight, 15, 15);
    ofRect(posRightWidth, posRightHeight, 15, 15);
    
    ofSetColor(50, 50, 50);
    string msg = "Depth: " + ofToString(depthLeft) + " | " + ofToString(depthRight);
    verdana.drawString(msg, 20, ofGetHeight() - 26);
    
    tex.bind();
    ofTranslate(ofGetWidth() * .5, ofGetHeight() * .5, 0);
    ofRotate(ang, 1.0, 1.0, 1.0);
    ofBox(200);
    tex.unbind();
    
}
//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
        case 'i':
            if (openNIDevice.isImageOn()){
                openNIDevice.removeImageGenerator();
                openNIDevice.addInfraGenerator();
                break;
            }
            if (openNIDevice.isInfraOn()){
                openNIDevice.removeInfraGenerator();
                openNIDevice.addImageGenerator();
                break;
            }
            break;
        default:
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
    selectedPoint.x = x;
    selectedPoint.y = y;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}