#pragma once

// STL Includes
#include <iostream>
#include <memory>

// Inheritance Include
#include "LuaFunction.h"

class TestLuaFunction : public LuaFunction
{
	void function(vector<LuaTypePtr> paramList, vector<LuaTypePtr>& returnList)
	{
		// Process Params
		LuaString* str = std::dynamic_pointer_cast<LuaString>(paramList[0]).get();

		// Print text
		if (str)
		{
			std::cout << "Print text: " << std::endl;
		}

		// Return 0
		returnList.push_back(LuaFile::NewNum(0));
	}
};

// Initialize the LuaFunction
string TestLuaFunction::s_name = "";
vector<LuaType::LUA_TYPE> TestLuaFunction::s_paramTypes = { LuaType::LT_STRING };
LuaFunction* TestLuaFunction::instance = new TestLuaFunction();