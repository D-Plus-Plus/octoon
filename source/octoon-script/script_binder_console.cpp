#include "script_binder_console.h"
#include <iostream>
#include <chrono>
#include <lua.hpp>

namespace octoon
{
	namespace script
	{
		thread_local std::map<std::string, std::uint32_t> ScriptBinderConsole::count_;
		thread_local std::map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>> ScriptBinderConsole::time_;

		ScriptBinderConsole::ScriptBinderConsole() noexcept
		{
		}

		ScriptBinderConsole::~ScriptBinderConsole() noexcept
		{
		}

		void
		ScriptBinderConsole::bind(lua_State* L) noexcept
		{
			auto lib = [](lua_State* L) -> int
			{
				static const struct luaL_Reg consolelib[] =
				{
					{"log", ScriptBinderConsole::log},
					{"info", ScriptBinderConsole::log},
					{"error", ScriptBinderConsole::log},
					{"warn", ScriptBinderConsole::log},
					{"clear", ScriptBinderConsole::cls},
					{"count", ScriptBinderConsole::count},
					{"time", ScriptBinderConsole::time},
					{"timeEnd", ScriptBinderConsole::timeEnd},
					{0, 0},
				};

				luaL_newlib(L, consolelib);
				return 1;
			};

			luaL_requiref(L, "console", lib, 1);
		}

		int
		ScriptBinderConsole::log(lua_State* j) noexcept
		{
			if (!lua_isnoneornil(j, 1))
				std::cout << lua_tostring(j, 1) << std::endl;
			return 0;
		}

		int
		ScriptBinderConsole::cls(lua_State *j) noexcept
		{
	#if defined(_WINDOWS)
			std::system("cls");
	#else
			std::system("clear");
	#endif
			return 0;
		}

		int
		ScriptBinderConsole::count(lua_State *j) noexcept
		{
			const char* msg = lua_tostring(j, 1);
			std::cout << ++count_[msg] << std::endl;
			return 0;
		}

		int 
		ScriptBinderConsole::time(lua_State *j) noexcept
		{
			const char* name = lua_tostring(j, 1);
			time_[name] = std::chrono::high_resolution_clock::now();
			return 0;
		}

		int 
		ScriptBinderConsole::timeEnd(lua_State *j) noexcept
		{
			const char* name = lua_tostring(j, 1);
			auto startTime = time_[name];
			auto us = (double)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
			std::cout << us * std::chrono::milliseconds::period::num / std::chrono::milliseconds::period::den << "ms" << std::endl;
			return 0;
		}
	}
}