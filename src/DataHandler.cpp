//
//  DataHandler.cpp
//  ArbutusServer
//
//  Created by Daniel Almeida on 22/07/17.
//
//

#include "DataHandler.h"


constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}


DataHandler::DataHandler() {
    
}

DataHandler::~DataHandler() {
    
}


json DataHandler::handleRequest(json requestJson) {
    json responseJson;
    std::string action;
    
    if (!requestJson["action"].is_string()) {
        throw "No action set.";
    }
    
    action = requestJson["action"];
    switch (str2int(action.c_str())){
        case str2int("ping"):
            responseJson = R"({'message':'ping'})"_json;
            break;
            
    case str2int("getState"):
        responseJson = getStateResponse();
        break;
    }
    
    return responseJson;
}



json DataHandler::getStateResponse() {
    Engine *engine;
    
    engine = Engine::getInstance();
    
    if (engine == NULL) {
        throw "Engine not initialized";
    }
    
    return engine->getState();
}
