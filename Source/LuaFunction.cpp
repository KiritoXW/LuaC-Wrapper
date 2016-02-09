#include "LuaFunction.h"

#ifdef LUA_FUNCTION_CLASS

// STL Includes
#include <exception>
#include <memory>

// Using Directives
using std::runtime_error;
using std::dynamic_pointer_cast;

// Initialize the LuaFunction
string LuaFunction::s_name = "";
vector<LuaType::LUA_TYPE> LuaFunction::s_paramTypes = {};
LuaFunction* LuaFunction::instance = nullptr;

LuaFunction::LuaFunction(string functionName, vector<LuaType::LUA_TYPE> functionParams)
{
	s_name = functionName;
	s_paramTypes = functionParams;
}

LuaFunction * LuaFunction::Instance()
{
	return instance;
}

LuaFunction::~LuaFunction(void)
{
}

string LuaFunction::GetName(void)
{
	return s_name;
}

lua_CFunction LuaFunction::GetFunctionPtr(void)
{
	return call;
}

int LuaFunction::call(lua_State * caller)
{
	vector<LuaTypePtr> params;
	vector<LuaTypePtr> returns;

	// Params
	// -- Check if the correct number of params is passed in
	if (lua_gettop(caller) != s_paramTypes.size())
	{
		throw new runtime_error("Incorrect number of parameters passed in!");
	}
	// -- Check the params passed in
	for (size_t i = 0; i < s_paramTypes.size(); ++i)
	{
		bool valid = false;

		switch (s_paramTypes[i])
		{
			case LuaType::LT_BOOL:
			{
				if (lua_isboolean(caller, i))
				{
					params.push_back(LuaFile::NewBool(lua_toboolean(caller, i)));
					valid = true;
				}
			}
			break;
			case LuaType::LT_NUMBER:
			{
				if (lua_isnumber(caller, i))
				{
					params.push_back(LuaFile::NewNum(lua_tonumber(caller, i)));
					valid = true;
				}
			}
			break;
			case LuaType::LT_STRING:
			{
				if (lua_isstring(caller, i))
				{
					params.push_back(LuaFile::NewStr(lua_tostring(caller, i)));
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

	// Function Logic
	instance->function(params, returns);

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

	// -- Report the Returns
	return returns.size();
}

#endif