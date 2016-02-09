#include "Lua.h"

// STL Include
#include <cstdarg>		// For Variable Argument Lists
#include <exception>

// Other Includes
#include "LuaFunction.h"

// Using Directives
using std::dynamic_pointer_cast;
using std::runtime_error;
using namespace Lua;

LuaFile::LuaFile(string luaFile)
	: m_luaState(nullptr)
	, m_scriptExecuted(false)
{
	m_luaState = lua_open();
	luaL_openlibs(m_luaState);

	if (luaFile != "")
	{
		if (!loadScript(luaFile))
		{
			throw new runtime_error("Failed to load " + luaFile + "!");
		}
	}
	else
	{
		throw new runtime_error("Cannot load an empty Lua file!");
	}
}

LuaFile::~LuaFile(void)
{
	lua_close(m_luaState);
	m_luaState = nullptr;
}

bool LuaFile::RunScript(void)
{
	if (m_luaState)
	{
		if (lua_pcall(m_luaState, 0, 0, 0))
		{
			throw new runtime_error("Failed to execute Lua script!");
			return false;
		}

		m_scriptExecuted = true;

		return true;
	}

	return false;
}

LuaTypePtr LuaFile::GetValue(string varName)
{
	LuaTypePtr luaResult;

	if (!m_scriptExecuted)
	{
		RunScript();
	}

	// Only check if we have a luaState set up
	if (m_luaState)
	{
		// Push this on to the lua stack
		lua_getglobal(m_luaState, varName.c_str());

		luaResult = getTopLuaValue();

		// Pop it off since we've read it
		lua_pop(m_luaState, 1);
	}

	// Return the result
	return luaResult;
}

double LuaFile::GetNumber(string varName)
{
	return dynamic_pointer_cast<Number>(GetValue(varName)).get()->Num;
}

bool LuaFile::GetBoolean(string varName)
{
	return dynamic_pointer_cast<Boolean>(GetValue(varName)).get()->Bool;;
}

string LuaFile::GetString(string varName)
{
	return dynamic_pointer_cast<String>(GetValue(varName)).get()->Str;
}

LuaTypePtr LuaFile::Call(string functionName, int expectedResults, vector<LuaTypePtr> params)
{
	// Push the function to the top
	lua_getglobal(m_luaState, functionName.c_str());

	// Loop through all elements in the Variable Argument List
	for (auto param : params)
	{
		if (auto luaNum = dynamic_pointer_cast<Number>(param))
		{
			lua_pushnumber(m_luaState, luaNum->Num);
		}
		else if (auto luaBool = dynamic_pointer_cast<Boolean>(param))
		{
			lua_pushboolean(m_luaState, luaBool->Bool);
		}
		else if (auto luaStr = dynamic_pointer_cast<String>(param))
		{
			lua_pushstring(m_luaState, luaStr->Str.c_str());
		}
	}

	// Call the function
	lua_call(m_luaState, params.size(), expectedResults);

	// Obtain the result
	LuaTypePtr luaResult = getTopLuaValue();

	// Pop the result
	lua_pop(m_luaState, expectedResults);

	return luaResult;
}

void LuaFile::RegisterFunction(string funcName, lua_CFunction func)
{
	lua_register(m_luaState, funcName.c_str(), func);
}

bool LuaFile::loadScript(string filename)
{
	if (m_luaState)
	{
		if (luaL_loadfile(m_luaState, filename.c_str()))
		{
			return false;
		}

		return true;
	}

	return false;
}

LuaTypePtr LuaFile::getTopLuaValue(void)
{
	LuaTypePtr luaResult;

	// If this global is a number,
	if (lua_isnumber(m_luaState, lua_gettop(m_luaState)))
	{
		// Store this in a LuaNumber in luaResult
		luaResult.reset(new Number(lua_tointeger(m_luaState, lua_gettop(m_luaState))));
	}
	// If this global is a boolean,
	else if (lua_isboolean(m_luaState, lua_gettop(m_luaState)))
	{
		// Store this in a LuaBoolean in luaResult
		luaResult.reset(new Boolean(lua_toboolean(m_luaState, lua_gettop(m_luaState))));
	}
	// If this global is a string,
	else if (lua_isstring(m_luaState, lua_gettop(m_luaState)))
	{
		// Store this in a LuaBoolean in luaResult
		luaResult.reset(new String(lua_tostring(m_luaState, lua_gettop(m_luaState))));
	}

	return luaResult;
}
