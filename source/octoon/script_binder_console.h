#ifndef OCTOON_SCRIPT_BINDER_CONSOLE_H_
#define OCTOON_SCRIPT_BINDER_CONSOLE_H_

#include <octoon/script_binder.h>
#include <map>
#include <string>

namespace octoon
{
	class ScriptBinderConsole final : public ScriptBinder
	{
	public:
		ScriptBinderConsole() noexcept;
		virtual ~ScriptBinderConsole() noexcept;

		void bind(js_State* j) noexcept;

	private:
		static void log(js_State *j) noexcept;
		static void cls(js_State *j) noexcept;
		static void count(js_State *j) noexcept;

	private:
		static thread_local std::map<std::string, std::uint32_t> count_;
	};
}

#endif