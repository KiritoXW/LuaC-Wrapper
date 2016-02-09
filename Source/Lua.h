/******************************************************************************/
/*!
\file	Lua.h
\author Tng Kah Wei
\brief	Lua Wrapper for working with Lua with clean and simple syntax.
*/
/******************************************************************************/
#pragma once

// STL Includes
#include <string>
#include <vector>

// LUA Includes
extern "C"
{
	#include "Lua/include/lua.h"
	#include "Lua/include/lualib.h"
	#include "Lua/include/lauxlib.h"
}

// Other Includes
#include "LuaType.h"

// Using Directives
using std::string;
using std::vector;

namespace Lua
{
	// Type Definitions
	typedef vector<LuaTypePtr> LuaFuncList;

	/******************************************************************************/
	/*!
			Class State:
	\brief	A LuaFile is a class that holds a single lua_State and works with it.
			Using LuaFile, you can:
				- Get a Global Value
				- Execute Lua Scripts
				- Register a C++ function for exporting for use in the Lua Script
				- Call Lua Functions from C++ via LuaFile

			Note that RunScript() must be called to execute the code in the Lua
			Script. However, if other functions such as GetValue() and Call()
			require the script to be run before it can be used. Therefore,
			calling GetValue() and Call() will trigger RunScript() and thus
			execute scripts in the Lua Script.

			As such, it is advised to not have any scripts globally in the Lua
			Script.
	*/
	/******************************************************************************/
	class LuaFile
	{
	private:
		lua_State* m_luaState;
		bool m_scriptExecuted;

	public:
		LuaFile(string luaFile);
		~LuaFile(void);

		// Life time
		bool RunScript(void);

		/*
		 * Variable Acquisition
		 */
		 // Functions to get values from the stack
		LuaTypePtr GetValue(string varName);
		double GetNumber(string varName);
		bool GetBoolean(string varName);
		string GetString(string varName);
		void* GetPointer(string varName);

		/*
		 * Lua Function Importing
		 */
		LuaTypePtr Call(string functionName, int expectedResults, vector<LuaTypePtr> params);

		/*
		 * C++ Function Exporting
		 */
		void RegisterFunction(string funcName, lua_CFunction func);

	private:
		// For script loading
		bool loadScript(string filename);
		// For converting the top value in the stack into a LuaTypePtr
		LuaTypePtr getTopLuaValue(void);
	};
}