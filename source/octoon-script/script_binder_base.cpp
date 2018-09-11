#include "script_binder_base.h"

#include <iostream>
#include <string.h>
#ifdef _WIN32
#	include <direct.h>
#else
#	include <unistd.h>
#endif

#include <lua.hpp>

namespace octoon
{
	namespace script
	{
		ScriptBinderBase::ScriptBinderBase() noexcept
		{
		}

		ScriptBinderBase::~ScriptBinderBase() noexcept
		{
		}

		void
		ScriptBinderBase::bind(lua_State* J) noexcept
		{
		}
	}
}