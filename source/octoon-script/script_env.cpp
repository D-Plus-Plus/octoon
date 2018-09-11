#include <octoon/script/script_env.h>
#include <octoon/script/script_context.h>
#include <octoon/runtime/except.h>
#include "script_binder_base.h"
#include "script_binder_console.h"

#include <lua.hpp>

namespace octoon
{
	namespace script
	{
		ScriptEnv::ScriptEnv() except
			: state_(nullptr)
		{
			this->setup();
		}

		ScriptEnv::~ScriptEnv() noexcept
		{
			this->close();
		}

		void
		ScriptEnv::setup() except
		{
			assert(state_ == nullptr);

			state_ = luaL_newstate();
			if (!state_)
				throw runtime::runtime_error::create("lua_newstate() failed");

			luaL_openlibs(state_);

			binders_.push_back(std::make_unique<ScriptBinderBase>());
			binders_.push_back(std::make_unique<ScriptBinderConsole>());

			for (auto& it : binders_)
				it->bind(state_);

			lua_setstate(state_);
		}

		void
		ScriptEnv::close() noexcept
		{
			binders_.clear();

			if (state_)
			{
				lua_close(state_);
				state_ = nullptr;
			}
		}

		void
		ScriptEnv::doString(const char* str)
		{
			luaL_dostring(state_, str);
		}

		void 
		ScriptEnv::get(const char* str, std::function<void()>& action)
		{
			lua_getglobal(state_, str);

			if (lua_isfunction(state_, -1))
			{
				action = std::bind([=]()
				{
					lua_getglobal(state_, str);
					lua_pcall(state_, 0, 0, 0);
				});
			}
		}
	}
}