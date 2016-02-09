#include "LuaFunction.h"

// STL Includes
#include <exception>
#include <memory>

// Using Directives
using std::runtime_error;
using std::dynamic_pointer_cast;
using Lua::Number;
using Lua::String;
using Lua::Boolean;

void LuaFunc::preCall(lua_State* caller, vector<LuaTypePtr>& params, vector<Type::LUA_TYPE> paramsTypeList)
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
		case Type::LT_BOOL:
		{
			if (lua_isboolean(caller, luaIndex))
			{
				params.push_back(Lua::NewBool(lua_toboolean(caller, luaIndex)));
				valid = true;
			}
		}
		break;
		case Type::LT_NUMBER:
		{
			if (lua_isnumber(caller, luaIndex))
			{
				params.push_back(Lua::NewNum(lua_tonumber(caller, luaIndex)));
				valid = true;
			}
		}
		break;
		case Type::LT_STRING:
		{
			if (lua_isstring(caller, luaIndex))
			{
				params.push_back(Lua::NewStr(lua_tostring(caller, luaIndex)));
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
		Boolean* lb = dynamic_pointer_cast<Boolean>(retVal).get();
		Number* ln = dynamic_pointer_cast<Number>(retVal).get();
		String* ls = dynamic_pointer_cast<String>(retVal).get();

		// Push it in appropriately
		if (lb)
		{
			lua_pushboolean(caller, lb->Bool);
		}
		else if (ln)
		{
			lua_pushnumber(caller, ln->Num);
		}
		else if (ls)
		{
			lua_pushstring(caller, ls->Str.c_str());
		}
		else
		{
			throw new runtime_error("Incorrect type of return value attempted to be returned!");
		}
	}

	return returns.size();
}
