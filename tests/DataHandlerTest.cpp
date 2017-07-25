//
//  DataHandlerTest.cpp
//  ArbutusServer
//
//  Created by Daniel Almeida on 22/07/17.
//
//

#include <stdio.h>
#include "catch.hpp"
#include "DataHandler.h"

using json = nlohmann::json;


TEST_CASE("Test invalid inputs", "[handleRequest]") {
    DataHandler handler;
    json result;
    Engine *engine;
    
    // test empty json
    REQUIRE_THROWS_WITH(
                        handler.handleRequest(R"({})"_json),
                        "No action set."
                        );
    
    // test without the engine started
    REQUIRE_THROWS_WITH(
                        handler.handleRequest(R"({"action": "getState"})"_json),
                        "Engine not initialized"
                        );
    
   
    // test with the engine started
    engine = new Engine();
    REQUIRE_NOTHROW(result = handler.handleRequest(R"({"action":"getState"})"_json));
    
}
