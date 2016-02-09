#pragma once

// STL Includes
#include <string>
#include <memory>

// Using Directives
using std::string;
using std::shared_ptr;

namespace Lua
{
	struct Type
	{
		enum LUA_TYPE
		{
			LT_NUMBER,
			LT_BOOL,
			LT_STRING,
			LT_TOTAL
		};

		virtual ~Type() {}
	};

	// Type Definitions
	typedef shared_ptr<Type> LuaTypePtr;

	struct Number : public Type
	{
		double Num;

		Number(double number = 0) : Num(number) {}
		~Number() {}
	};

	struct Boolean : public Type
	{
		bool Bool;

		Boolean(bool boolean = 0) : Bool(boolean) {}
		~Boolean() {}
	};

	struct String : public Type
	{
		string Str;

		String(string str = 0) : Str(str) {}
		~String() {}
	};

	/*
	* Functions to easily produce LuaTypes
	*/
	LuaTypePtr NewNum(double num);
	LuaTypePtr NewBool(bool b);
	LuaTypePtr NewStr(string str);

	/*
	* Functions to easily extract LuaTypes
	*/
	double ExtNum(LuaTypePtr numPtr);
	bool ExtBool(LuaTypePtr boolPtr);
	string ExtStr(LuaTypePtr strPtr);
}