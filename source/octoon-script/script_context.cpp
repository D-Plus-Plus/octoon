#include <octoon/script/script_context.h>

namespace octoon
{
	thread_local lua_State* state_;

	void lua_setstate(lua_State* state)
	{
		state_ = state;
	}

	lua_State* lua_getstate()
	{
		return state_;
	}
}