/******************************************************************************/
/*!
\file	LuaFunction.h
\author Tng Kah Wei
\brief	Functions to make simplify the process of exporting a C++ function
		for use with Lua.
*/
/******************************************************************************/
#pragma once

// API Includes
#include "Lua.h"

// Using Directives
using Lua::Type;
using Lua::LuaTypePtr;

/******************************************************************************/
/*!
		Class LuaFunc:
\brief	The following static functions are meant to simplify C++ function
		export by doing type-checking and interfacing with the Lua API
		without the user's intervention.

		A Lua-C++ export function is defined as "int LuaFunction(lua_State)".

		To use preCall(), call it at the start of a Lua-C++ export function.
		It will do type-checking to ensure correct types are used and that
		sufficient parameters are provided.
		To use, specify 
			- the luaState who called the function,
			- the storage for the parameters (preCall() will help you obtain it
			  from Lua)
			- the parameter list for this function

		To use postCall(), use it to return the int requierd by a Lua-C++
		export function. It will send Lua the appropriate types of returns
		based on what you specified. It will also return the amount of
		variables returned for Lua.
		To use, specify
			- the luaState who called the function,
			- the storage for the variables to be returned
*/
/******************************************************************************/
class LuaFunc
{
public:
	static void preCall(lua_State* caller, vector<LuaTypePtr>& params, vector<Type::LUA_TYPE> paramsTypeList);
	static int postCall(lua_State* caller, vector<LuaTypePtr>& returns);
};