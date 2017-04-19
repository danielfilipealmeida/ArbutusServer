//
//  Interface.cpp
//  ArbutusLite
//
//  Created by Daniel Almeida on 13/03/17.
//
//

#include "Interface.hpp"
#include "json.hpp"
using json = nlohmann::json;




Interface::Interface() {
    menuData = json::array(
                           {
                               {
                                   {"type", "button"},
                                   {"label", "New VJ Set"}
                                   
                               },
                               {
                                   {"type", "button"},
                                   {"label", "Open VJ Set"}
                                   
                               },
                               {
                                   {"type", "button"},
                                   {"label", "Save VJ Set"}
                                   
                               },
                               {
                                   {"type", "button"},
                                   {"label", "Save VJ Set As..."}
                                   
                               },
                               {
                                   {"type", "button"},
                                   {"label", "Exit"}
                                   
                               }
                           }
                           );
   
    layersData = loadFromFile("layerInterfaceData.json");
}




Interface::~Interface() {
    
}


json
Interface::loadFromFile(string file) {
    json result;
    
    std::ifstream i(file);
    if (i.is_open()) {
        i >> result;
        i.close();
    }
    
    return result;
}


json
Interface::prependStringToKeys(json input, string appendString) {
    json output;
    
    cout << input.dump() << endl;
    for (
         json::iterator it = input.begin();
         it != input.end();
         ++it)
    {
        string newKey;

        /*
         
        cout << it.key() << endl;
        newKey = appendString + it.key();
        output[newKey] = it.value();
         */
        if (it->is_array()) {
            json tmp = it.value();
            
            newKey = appendString + tmp[0].get<string>();
            //output.push_back([newKey, it[1]]);
            
            output.push_back(json::array({newKey, tmp[1]}));
            
        }
        else {
            cout << it.key() << endl;
            newKey = appendString + it.key();
            output[newKey] = it.value();

        }

    }

    cout << output.dump()src/Interface.hpp << endl;
    
    return output;
}


void
Interface::setup() {
    json currentLayerData;
    json currentLayerState;
    
    
    currentLayerData = layersData;
    
    Engine *engine = Engine::getInstance();
    Layer *currentLayer;
    
    currentLayer = engine->getCurrentLayer();
    currentLayerState = currentLayer->getState();
    
    
    currentLayerState = prependStringToKeys(currentLayerState, "Layer ");
    cout << currentLayerState.dump() << endl;
    //std::strcat("Layer ", ofToString(engine->getCurrentLayer()))
    
    updateInterfaceBlockDataWithState(currentLayerData, currentLayerState);
    currentLayerData[0]["layer"] = currentLayer->getLayerNumber() + 1;
    
    menu = new InterfaceBlock(menuData);
    layer1 = new InterfaceBlock(
                                json::array(
    {
        {
            {"type", "group"},
            {"label",   "Layer " + ofToString(engine->getCurrentLayerNumber() + 1)},
            {"children", currentLayerData}
        }
    }
                                            ),
                                200,
                                0);

    
    layerPreviews = new InterfaceBlock(
                                       json::array(
                                                 {
                                                     {
                                                         {"type", "preview"},
                                                         {"label","Layer Preview"},
                                                         {"layer", 1}
                                                     },
                                                     {
                                                         {"type", "preview"},
                                                         {"label","Layer Preview"},
                                                         {"layer", 2}
                                                     },
                                                     {
                                                         {"type", "preview"},
                                                         {"label","Layer Preview"},
                                                         {"layer", 3}
                                                     },
                                                     {
                                                         {"type", "preview"},
                                                         {"label","Layer Preview"},
                                                         {"layer", 4}
                                                     },

                                                     

                                                 }
                                      ),
                                       0,
                                       120
    );
    
    // setup visual interface
    std::ifstream i("visualInterfaceData.json");
    i >> visualInterfaceData;
    //cout << visualInterfaceData.dump() << endl;
    visual = new InterfaceBlock(visualInterfaceData, 400,0);
}


void
Interface::draw() {
    menu->draw();
    layer1->draw();
    layerPreviews->draw();
    visual->draw();
}


void
Interface::reload() {
    delete menu;
    delete layer1;
    delete layerPreviews;
    delete visual;
    setup();
    
}


void
Interface::updateInterfaceBlockDataWithState(
                                             json & interfaceBlockData,
                                             json state
                                             )
{
    // traverse the state
    for (auto& stateRecord : state) {
        cout << stateRecord[0]<<endl;
        for (auto& interfaceRecord : interfaceBlockData) {
            if (stateRecord[0].get<string>().compare(interfaceRecord["label"].get<string>()) == 0) {
                cout << "antes: " << interfaceRecord.dump() <<endl;
                interfaceRecord["value"] = stateRecord[1];
                cout << "depois: " << interfaceRecord.dump() << endl;
            }
        }
    }
    cout << interfaceBlockData.dump() <<endl;
    
}
