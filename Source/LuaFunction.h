#pragma once

// API Includes
#include "Lua.h"

// Using Directives
using Lua::Type;
using Lua::LuaTypePtr;

class LuaFunc
{
public:
	static void preCall(lua_State* caller, vector<LuaTypePtr>& params, vector<Type::LUA_TYPE> paramsTypeList);
	static int postCall(lua_State* caller, vector<LuaTypePtr>& returns);
};