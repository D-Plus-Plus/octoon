#ifndef OCTOON_SCRIPT_CONTEXT_H_
#define OCTOON_SCRIPT_CONTEXT_H_

#include <mujs.h>

namespace octoon
{
	void js_setstate(js_State* state);
	js_State* js_getstate();
}

#endif