#include "LuaFunction.h"

// STL Includes
#include <exception>
#include <memory>

// Using Directives
using std::runtime_error;
using std::dynamic_pointer_cast;

void LuaFunc::preCall(lua_State* caller, vector<LuaTypePtr>& params, vector<LuaType::LUA_TYPE> paramsTypeList)
{
	// Params
	// -- Check if the correct number of params is passed in
	if (lua_gettop(caller) != paramsTypeList.size())
	{
		throw new runtime_error("Incorrect number of parameters passed in!");
	}

	// -- Check the params passed in 
	for (size_t i = 0; i < paramsTypeList.size(); ++i)
	{
		bool valid = false;
		int luaIndex = i + 1; // Lua starts at 1, not 0

		switch (paramsTypeList[i])
		{
		case LuaType::LT_BOOL:
		{
			if (lua_isboolean(caller, luaIndex))
			{
				params.push_back(LuaFile::NewBool(lua_toboolean(caller, luaIndex)));
				valid = true;
			}
		}
		break;
		case LuaType::LT_NUMBER:
		{
			if (lua_isnumber(caller, luaIndex))
			{
				params.push_back(LuaFile::NewNum(lua_tonumber(caller, luaIndex)));
				valid = true;
			}
		}
		break;
		case LuaType::LT_STRING:
		{
			if (lua_isstring(caller, luaIndex))
			{
				params.push_back(LuaFile::NewStr(lua_tostring(caller, luaIndex)));
				valid = true;
			}
		}
		break;
		}

		if (!valid)
		{
			throw new runtime_error("Incorrect type of parameters passed in!");
		}
	}
}

int LuaFunc::postCall(lua_State* caller, vector<LuaTypePtr>& returns)
{
	// Returns
	// -- Push returns onto the Stack
	for (auto retVal : returns)
	{
		// Determine the type of return
		LuaBoolean* lb = dynamic_pointer_cast<LuaBoolean>(retVal).get();
		LuaNumber* ln = dynamic_pointer_cast<LuaNumber>(retVal).get();
		LuaString* ls = dynamic_pointer_cast<LuaString>(retVal).get();

		// Push it in appropriately
		if (lb)
		{
			lua_pushboolean(caller, lb->Boolean);
		}
		else if (ln)
		{
			lua_pushnumber(caller, ln->Number);
		}
		else if (ls)
		{
			lua_pushstring(caller, ls->String.c_str());
		}
		else
		{
			throw new runtime_error("Incorrect type of return value attempted to be returned!");
		}
	}

	return returns.size();
}
