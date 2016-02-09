// STL Includes
#include <iostream>

// Other Includes
#include "Lua.h"

// Using Directives
using std::cout;
using std::endl;

int testFunction(lua_State* L)
{
	if (lua_gettop(L) == 1)
	{
		string print = lua_tostring(L, 0);

		std::cout << "Print text: " + print << std::endl;

		lua_pushnumber(L, 0);
	}
	else
	{
		lua_pushnumber(L, -1);
	}

	return 1;
}

int main(void)
{
	LuaFile lua("Source//test.lua");

	//lua.RegisterFunction("testFunc", testFunction);

	auto result = lua.Call("testFunc", 1, LuaFuncList{ LuaFile::NewStr("testMan") });

	cout << result << endl;

	system("pause");
}