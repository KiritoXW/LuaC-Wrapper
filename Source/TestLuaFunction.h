#pragma once

#ifdef LUA_FUNCTION_CLASS

// STL Includes
#include <iostream>
#include <memory>

// Inheritance Include
#include "LuaFunction.h"

class TestLuaFunction : public LuaFunction
{
public:
	TestLuaFunction() : LuaFunction("testFunc", vector<LuaType::LUA_TYPE>({ LuaType::LT_STRING })) { instance = this; }

protected:
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

#endif