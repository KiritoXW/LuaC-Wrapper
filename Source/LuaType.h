/******************************************************************************/
/*!
\file	LuaType.h
\author Tng Kah Wei
\brief	Wrapper classes for primitive types used in Lua. This is to allow 
		seamless passing in and out of different variables between Lua script
		and native C++ code. Pointers are primarily used to interact with
		these types to allow storage in vectors for type-specific processing
		afterwards.

		Use the LuaType Producer functions to easily create a LuaType of the
		desired primitive type.

		Likewise, use the LuaType Extractor functions to easily obtain the
		C++ primitive type from the LuaType variant.
*/
/******************************************************************************/
#pragma once

// STL Includes
#include <string>
#include <memory>

// Using Directives
using std::string;
using std::shared_ptr;

namespace Lua
{
	/******************************************************************************/
	/*!
			Struct Type:
	\brief	The basic primitive type that all types inherit from.
	*/
	/******************************************************************************/
	struct Type
	{
		enum LUA_TYPE
		{
			LT_NUMBER,
			LT_BOOL,
			LT_STRING,
			LT_TOTAL
		};

		virtual ~Type() = 0 {};
	};

	// Type Definitions
	typedef shared_ptr<Type> LuaTypePtr;

	/******************************************************************************/
	/*!
			Struct Number:
	\brief	The numerical type that all Lua-C++ interactions in this Lua wrapper
			use.
	*/
	/******************************************************************************/
	struct Number : public Type
	{
		double Num;

		Number(double number = 0) : Num(number) {}
		~Number() {}
	};

	/******************************************************************************/
	/*!
			Struct Boolean:
	\brief	The boolean type that all Lua-C++ interactions in this Lua wrapper
			use.
	*/
	/******************************************************************************/
	struct Boolean : public Type
	{
		bool Bool;

		Boolean(bool boolean = 0) : Bool(boolean) {}
		~Boolean() {}
	};

	/******************************************************************************/
	/*!
			Struct String:
	\brief	The string type that all Lua-C++ interactions in this Lua wrapper
			use.
	*/
	/******************************************************************************/
	struct String : public Type
	{
		string Str;

		String(string str = 0) : Str(str) {}
		~String() {}
	};

	/*
	 * LuaType Producers
	 */
	LuaTypePtr NewNum(double num);
	LuaTypePtr NewBool(bool b);
	LuaTypePtr NewStr(string str);

	/*
	 * LuaType Extractors
	 */
	double ExtNum(LuaTypePtr numPtr);
	bool ExtBool(LuaTypePtr boolPtr);
	string ExtStr(LuaTypePtr strPtr);
}