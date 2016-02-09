#pragma once

// API Includes
#include "Lua.h"

class LuaFunc
{
public:
	static void preCall(lua_State* caller, vector<LuaTypePtr>& params, vector<LuaType::LUA_TYPE> paramsTypeList);
	static int postCall(lua_State* caller, vector<LuaTypePtr>& returns);
};