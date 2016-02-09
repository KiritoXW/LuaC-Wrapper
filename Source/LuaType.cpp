#include "LuaType.h"

// Using Directives
using Lua::LuaTypePtr;
using Lua::Number;
using Lua::String;
using Lua::Boolean;
using std::dynamic_pointer_cast;

LuaTypePtr Lua::NewNum(double num)
{
	return LuaTypePtr(new Number(num));
}

LuaTypePtr Lua::NewBool(bool b)
{
	return LuaTypePtr(new Boolean(b));
}

LuaTypePtr Lua::NewStr(string str)
{
	return LuaTypePtr(new String(str));
}

LuaTypePtr Lua::NewPtr(void * ptr)
{
	return LuaTypePtr(new Pointer(ptr));
}

double Lua::ExtNum(LuaTypePtr numPtr)
{
	return dynamic_pointer_cast<Number>(numPtr).get()->Num;
}

bool Lua::ExtBool(LuaTypePtr boolPtr)
{
	return dynamic_pointer_cast<Boolean>(boolPtr).get()->Bool;
}

string Lua::ExtStr(LuaTypePtr strPtr)
{
	return dynamic_pointer_cast<String>(strPtr).get()->Str;
}

void * Lua::ExtPtr(LuaTypePtr ptrPtr)
{
	return dynamic_pointer_cast<Pointer>(ptrPtr).get()->Ptr;
}
