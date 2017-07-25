//
//  InterfaceBlock.cpp
//  ArbutusLite
//
//  Created by Daniel Almeida on 13/03/17.
//
//

#include "InterfaceBlock.hpp"
#include "ofApp.h"
#include "ofxFboPreview.hpp"



InterfaceBlock::InterfaceBlock(
                               json data,
                               unsigned int x,
                               unsigned int y
                               ) {
    panel.setup();
    panel.setPosition(x,y);
    setup(data);
}


InterfaceBlock::~InterfaceBlock() {
    
}


void
InterfaceBlock::setup(
                      json          data,
                      ofxGuiGroup    *parent
                      ) {
    
    if (parent == NULL) {
        parent = &panel;
    }
    
    
    try {
        for (auto& element : data) {
            
            
            //cout << element.dump() << endl;
            
            // Button
            if (element["type"].get<std::string>().compare("button") == 0) {
                if (element["label"].is_string()) {
                    addButton(
                              element["label"].get<std::string>(),
                              parent
                              );
                }
            }

            
            // Toggle
            if (element["type"].get<std::string>().compare("toggle") == 0) {
                if (element["label"].is_string() &&
                    element["value"].is_boolean()
                    ) {
                    addToggle(
                              element["label"].get<std::string>(),
                              element["value"].get<bool>(),
                              parent
                              );
                }
            }

            
            
            // Slider
            if (element["type"].get<std::string>().compare("slider") == 0) {
                 if (element["label"].is_string() &&
                     element["minValue"].is_number_float() &&
                     element["maxValue"].is_number_float() &&
                     element["value"].is_number_float()
                     ) {
                     addSlider(element["label"].get<std::string>(),
                               element["minValue"],
                               element["maxValue"],
                               element["value"],
                               parent);
                 }
             }
            
            
            // RGB
            if (element["type"].get<std::string>().compare("rgb") == 0) {
                addRGB(
                       (element["label"].is_string()) ? element["label"].get<std::string>() : "",
                       parent
                );
                
            }
            
            
            // Group
            if (element["type"].get<std::string>().compare("group") == 0) {
                addGroup(
                         element["children"],
                         (element["label"].is_string()) ? element["label"].get<std::string>() : "",
                         parent
                         );
            }
            
            
            // Preview
            if (element["type"].get<std::string>().compare("preview") == 0) {
                
                if (element["layer"].is_number()) {
                    ofFbo *fbo;
                    Engine *engine;
                    Layer *layer;
                    int layerNumber;
                    
                    layerNumber = element["layer"].get<int>() - 1;
                    engine = Engine::getInstance();
                    layer = engine->getLayer(layerNumber);
                    fbo = layer->getBuffer();
                    addPreview(
                               fbo,
                               parent
                               );
                }
                
            }
        }
        
    }
    catch (std::exception *e) {
        std::cout << e->what() << std::endl;
    }
}


void
InterfaceBlock::addLabel(
                         std::string caption,
                         ofxGuiGroup *parent
         ) {
    
    ofxLabel *label;
    
    label = new ofxLabel();
    parent->add(label->setup(caption));
}


void
InterfaceBlock::addButton(
                          std::string caption,
                          ofxGuiGroup *parent
                          ) {
    ofxButton *button;
    
    button = new ofxButton();
    //button->addListener(this, &InterfaceBlock::handleAction);
    parent->add(button->setup(caption));
}


void
InterfaceBlock::addToggle(
                          std::string caption,
                          bool value,
                          ofxGuiGroup *parent
                          ) {
    ofxToggle *toggle;
    //ofParameter<bool> *parameter;
    
    toggle = new ofxToggle();
    //toggle->addListener(this, &InterfaceBlock::handleButtonPress);
    
    parent->add(toggle->setup(caption, (bool) value));
}


void
InterfaceBlock::addSlider(
                          std::string caption,
                          float minVal,
                          float maxVal,
                          float val,
                          ofxGuiGroup    *parent
                          ) {
    ofParameter<float> *floatParameter;
    floatParameter =  new ofParameter<float>(caption, val, minVal, maxVal);
    floatParameter->addListener(this, &InterfaceBlock::handleAction);
    parent->add(*floatParameter);
}


void
InterfaceBlock::addRGB(
            std::string caption,
            ofxGuiGroup    *parent
            ) {
    ofParameter<ofColor> *colorParameter;
    
    colorParameter = new ofParameter<ofColor>(caption, ofColor(127),ofColor(0,0),ofColor(255));
    //colorParameter->addListener(this, &InterfaceBlock::handleAction);
    
    //std::function<void(ofColor & color)> lambda = [](ofColor) {};
    
    //colorParameter->addListener(this, lambda);
    
    parent->add(*colorParameter);

}


void
InterfaceBlock::addPreview(
           ofFbo *_fbo,
           ofxGuiGroup *parent
           ) {
    
    
    ofxFboPreview *preview;
    
    preview = new ofxFboPreview();
    
    parent->add(preview->setup(_fbo));
    
}

void
InterfaceBlock::handleAction(
                             const void * sender,
                             float & value
                             ) {
    ofApp* instance;
    string action;
    const ofParameterGroup parent;
    
    
   
    //cout << ((ofParameter<float> *)sender)->getName() << endl;
    //cout << "sender :" << typeid(sender).name()<<endl;
    //cout << "sender :" << typeid(((ofParameter<float> *)sender)).name()<<endl;
    //cout <<((ofParameter<float> *)sender)->toString() << endl;
    //cout << getSenderPath(sender)  << endl;

    instance = ofApp::instance();
    if (instance == NULL) return;
    
    action = ((ofParameter<float> *)sender)->getName();
    
    instance->handleAction(action, value);
}


void
InterfaceBlock::handleButtonPress() {
    cout << "!!!" <<endl;
}

// this doesn't work--- for deletion
string
InterfaceBlock::getSenderPath(const void * sender ) {
    string path, previous;
    return "";
    path = "";
    
    if (strcmp(typeid(sender).name(), "PKv") == 0) {
        ofxBaseGui *parent;
        
        parent = ((ofxBaseGui *)sender)->getParent();
        
        if (parent!=NULL) {
            path = getSenderPath((ofxBaseGui *) parent);
        }
        path = path + ((ofxBaseGui *)sender)->getName();
    }
    
     return path;
}



void InterfaceBlock::addGroup(
                              json        children,
                              string      label,
                              ofxGuiGroup *parent
                                    ) {
    ofxGuiGroup *group;
   
    group = new ofxGuiGroup();
    group->setup();
    /*
    if (!label.empty()) {
        children = json::array({
            {
                {"type", "label"},
                {"caption", label}
            }
        } + children);
    }
     */
    //cout << children.dump() << endl;
    group->setName(label);
    
    setup(children, group);
    parent->add(group);
}


void
InterfaceBlock::draw() {
    panel.draw();
}
