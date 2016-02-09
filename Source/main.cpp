// STL Includes
#include <iostream>
#include <memory>

// Other Includes
#include "Lua.h"
#include "LuaFunction.h"

// Using Directives
using std::cout;
using std::endl;

int testFunction(lua_State* L)
{
	vector<LuaTypePtr> params;
	vector<LuaTypePtr> returns;
	LuaFunc::preCall(L, params, vector<LuaType::LUA_TYPE>({LuaType::LT_STRING}));

	std::cout << "Print text: " + LuaFile::ExtStr(params[0]) << std::endl;

	return LuaFunc::postCall(L, returns);
}

int testFunction2(lua_State* L)
{
	vector<LuaTypePtr> params;
	vector<LuaTypePtr> returns;
	LuaFunc::preCall(L, params, vector<LuaType::LUA_TYPE>({}));

	std::cout << "Testing Param-less Lua Function" << std::endl;

	return LuaFunc::postCall(L, returns);
}

int main(void)
{
	LuaFile lua("Source//test.lua");

	lua.RegisterFunction("testFunc", testFunction);
	lua.RegisterFunction("testFunc2", testFunction2);

	lua.RunScript();
	auto result = lua.Call("printFunc", 1, LuaFuncList{ LuaFile::NewStr("testMan") });

	cout << std::dynamic_pointer_cast<LuaString>(result).get()->String << endl;

	system("pause");
}