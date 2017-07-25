#include "ofApp.h"
#include "Utils.h"



//--------------------------------------------------------------
void ofApp::setup(){
   // theApp = this;
    
    ofSetVerticalSync(true);

    try {
        ofSetDataPathRoot("./");
        engine.setMixerResolution(800, 600);
        
        server.setup(8080);
        
        //startServer(9002);
        
        
        //engine.openSet("demo.vjs");
        
        /*
        engine.setActiveVisualInstanceNumberForLayer(2, 1);
        //engine.setActiveVisualInstanceNumberForLayer(1, 1);
        engine.setActiveLayer(1);
        
        interface.setup();
         */
    }
    catch (std::exception &e) {
        std::cout << e.what() << endl;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0;
         i < server.getLastID();
         i++)
    {
        if (!server.isClientConnected(i)) continue;
    
        std::string str = server.receive(i);
        
        json j = str;
        
        json response = dataHandler.handleRequest(j);
        
        if (response) {
            server.send(i, "you sent: " + str);
            
        }
        
        //cout << " ..> " <<  j.dump() << endl;
    }
    
    engine.render();
    fpsCounter.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    engine.drawOutput(0, 0, ofGetWidth(), ofGetHeight());
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()-100, ofGetHeight()-20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << "key code: " << key << endl;
    switch (key) {
            
        default:
            break;
            
    }

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

/* ********************** */

#pragma mark My methods


void
ofApp::changeLayer(unsigned int layer) {
    engine.setActiveLayer(layer);
    interface.reload();
}


