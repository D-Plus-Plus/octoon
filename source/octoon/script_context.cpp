#include "script_context.h"

namespace octoon
{
	thread_local js_State* state_;

	void js_setstate(js_State* state)
	{
		state_ = state;
	}

	js_State* js_getstate()
	{
		return state_;
	}
}