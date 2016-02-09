// STL Includes
#include <iostream>
#include <memory>

// Other Includes
#include "Lua.h"
#include "LuaFunction.h"

// Using Directives
using std::cout;
using std::endl;
using Lua::Type;
using Lua::LuaFile;
using Lua::LuaTypePtr;
using Lua::LuaFuncList;

int testFunction(lua_State* L)
{
	vector<LuaTypePtr> params;
	vector<LuaTypePtr> returns;
	LuaFunc::preCall(L, params, vector<Type::LUA_TYPE>({Type::LT_STRING}));

	std::cout << "Print text: " + Lua::ExtStr(params[0]) << std::endl;

	return LuaFunc::postCall(L, returns);
}

int testFunction2(lua_State* L)
{
	vector<LuaTypePtr> params;
	vector<LuaTypePtr> returns;
	LuaFunc::preCall(L, params, vector<Type::LUA_TYPE>({}));

	std::cout << "Testing Param-less Lua Function" << std::endl;

	return LuaFunc::postCall(L, returns);
}

int main(void)
{
	LuaFile lua("Source//test.lua");

	lua.RegisterFunction("testFunc", testFunction);
	lua.RegisterFunction("testFunc2", testFunction2);

	lua.RunScript();
	auto result = lua.Call("printFunc", 1, LuaFuncList{ Lua::NewStr("testMan") });

	cout << Lua::ExtStr(result) << endl;

	system("pause");
}