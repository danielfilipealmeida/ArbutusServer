#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    try {
        ofSetDataPathRoot("./");
        engine.setMixerResolution(640, 480);
        engine.openSet("demo.vjs");
        engine.setActiveVisualInstanceNumberForLayer(2, 1);
    }
    catch (std::exception &e) {
        std::cout << e.what() << endl;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    engine.render();
}

//--------------------------------------------------------------
void ofApp::draw(){
    engine.drawOutput(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
