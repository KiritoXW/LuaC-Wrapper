#pragma once

// API Includes
#include "Lua.h"

class LuaFunction
{
private:
	static LuaFunction* instance;

protected:
	static string s_name;
	static vector<LuaType::LUA_TYPE> s_paramTypes;

	LuaFunction(void);
public:
	virtual ~LuaFunction(void);

	// Getters
	static string GetName(void);
	static lua_CFunction GetFunctionPtr(void);

protected:
	virtual void function(vector<LuaTypePtr> paramList, vector<LuaTypePtr>& returnList) = 0;

private:
	static int call(lua_State * caller);
};