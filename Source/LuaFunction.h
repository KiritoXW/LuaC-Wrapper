#pragma once


#ifdef LUA_FUNCTION_CLASS

// API Includes
#include "Lua.h"

class LuaFunction
{
protected:
	static LuaFunction* instance;
	static string s_name;
	static vector<LuaType::LUA_TYPE> s_paramTypes;

	LuaFunction(string functionName, vector<LuaType::LUA_TYPE> functionParams);

public:
	static LuaFunction* Instance();
	virtual ~LuaFunction(void);

	// Getters
	static string GetName(void);
	static lua_CFunction GetFunctionPtr(void);

protected:
	virtual void function(vector<LuaTypePtr> paramList, vector<LuaTypePtr>& returnList) = 0;

private:
	static int call(lua_State * caller);
};
#endif