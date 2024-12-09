#pragma once
#include <rack.hpp>

// Be very careful abut 'using namespace' in the global namespace of a shared header...
using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern Model* modelMyModule;
