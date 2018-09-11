#ifndef OCTOON_SCRIPT_CONTEXT_H_
#define OCTOON_SCRIPT_CONTEXT_H_

struct lua_State;

namespace octoon
{
	void lua_setstate(lua_State* state);
	lua_State* lua_getstate();
}

#endif