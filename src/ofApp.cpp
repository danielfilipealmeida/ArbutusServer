#include "ofApp.h"
#include "Utils.h"

ofApp *theApp = NULL;

json keyboardMappings = {
    {"113", {
        {"key", "q"},
        {"action", "triggerVisual"},
        {"actionData", {
            {"layer", 1},
            {"visual", 1}
        }
        }
    }
    },
    {"119",  {
        {"key", "w"},
        {"action", "triggerVisual"},
        {"actionData", {
            {"layer", 1},
            {"visual", 2}
        }
        }
    }},
    {"101",  {
        {"key", "e"},
        {"action", "triggerVisual"},
        {"actionData", {
            {"layer", 1},
            {"visual", 3}
        }
        }
    }},
    {"114",  {
        {"key", "r"},
        {"action", "triggerVisual"},
        {"actionData", {
            {"layer", 1},
            {"visual", 4}
        }
        }
    }},
    
    {"97", {
        {"key", "q"},
        {"action", "triggerVisual"},
        {"actionData", {
            {"layer", 2},
            {"visual", 1}
        }
        }
    }
    },
    {"115",  {
        {"key", "w"},
        {"action", "triggerVisual"},
        {"actionData", {
            {"layer", 2},
            {"visual", 2}
        }
        }
    }},
    {"100",  {
        {"key", "e"},
        {"action", "triggerVisual"},
        {"actionData", {
            {"layer", 2},
            {"visual", 3}
        }
        }
    }},
    {"102",  {
        {"key", "r"},
        {"action", "triggerVisual"},
        {"actionData", {
            {"layer", 2},
            {"visual", 4}
        }
        }
    }}

};


ofApp* ofApp::instance() {
    return theApp;
}



void
ofApp::handleGUIAction(
                       const void * sender,
                       float & value
                       )
{
    //cout << "here" << endl;
}

void
ofApp::handleAction(
                    string parameter,
                    float newValue
                    )
{
    try {
        engine.handleAction(parameter, {
            {"value", newValue}
        });
    }
    catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::setup(){
    theApp = this;
    
    ofSetVerticalSync(true);

    try {
        ofSetDataPathRoot("./");
        engine.setMixerResolution(800, 600);
        engine.openSet("demo.vjs");
        
        engine.setActiveVisualInstanceNumberForLayer(2, 1);
        //engine.setActiveVisualInstanceNumberForLayer(1, 1);
        engine.setActiveLayer(1);
        
        interface.setup();
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
    interface.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << "key code: " << key << endl;
    switch (key) {
        case '1':
        case '2':
        case '3':
        case '4':
            // 1 -> keycode 49
            changeLayer(key-48);
            
            break;
            
        default:
            
            json keyData;
            
           
            keyData = keyboardMappings[ofToString(key)];
            if (!keyData.is_null()) {
                cout << keyData["action"] << endl;
                switch (str2int(keyData["action"].get<string>().c_str())) {
                        
                        // triggers a visual. move this into a method
                    case str2int("triggerVisual"):
                        if (
                            keyData["actionData"]["layer"].is_number() &&
                            keyData["actionData"]["visual"].is_number()
                        ) {
                            int layer, visual;
                            
                            visual = keyData["actionData"]["visual"].get<int>() - 1;
                            layer = keyData["actionData"]["layer"].get<int>() - 1;
                            engine.setActiveVisualInstanceNumberForLayer(visual, layer);

                        }
                        break;
                }
                
                
            }
            else {
                cout << "Unandled keypressed" << endl;
                
            }
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
