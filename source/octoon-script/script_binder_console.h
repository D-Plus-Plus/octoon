#ifndef OCTOON_SCRIPT_BINDER_CONSOLE_H_
#define OCTOON_SCRIPT_BINDER_CONSOLE_H_

#include <octoon/script/script_binder.h>
#include <map>
#include <string>
#include <chrono>

namespace octoon
{
	namespace script
	{
		class ScriptBinderConsole final : public ScriptBinder
		{
		public:
			ScriptBinderConsole() noexcept;
			virtual ~ScriptBinderConsole() noexcept;

			void bind(lua_State* j) noexcept;

		private:
			static int log(lua_State *j) noexcept;
			static int cls(lua_State *j) noexcept;
			static int count(lua_State *j) noexcept;
			static int time(lua_State *j) noexcept;
			static int timeEnd(lua_State *j) noexcept;

		private:
			static thread_local std::map<std::string, std::uint32_t> count_;
			static thread_local std::map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>> time_;
		};
	}
}

#endif