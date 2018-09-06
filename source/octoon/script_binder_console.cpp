#include "script_binder_console.h"
#include <iostream>
#include <mujs.h>
#include <chrono>

namespace octoon
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
	ScriptBinderConsole::bind(js_State* j) noexcept
	{
		js_getglobal(j, "Object");
		js_getproperty(j, -1, "prototype");
		js_newuserdata(j, "console", stdin, 0);
		{
			js_newcfunction(j, log, "console.prototype.log", 0);
			js_defproperty(j, -2, "log", JS_DONTENUM);

			js_newcfunction(j, log, "console.prototype.info", 0);
			js_defproperty(j, -2, "info", JS_DONTENUM);

			js_newcfunction(j, log, "console.prototype.error", 0);
			js_defproperty(j, -2, "error", JS_DONTENUM);

			js_newcfunction(j, log, "console.prototype.warn", 0);
			js_defproperty(j, -2, "warn", JS_DONTENUM);

			js_newcfunction(j, cls, "console.prototype.clear", 0);
			js_defproperty(j, -2, "clear", JS_DONTENUM);

			js_newcfunction(j, count, "console.prototype.count", 0);
			js_defproperty(j, -2, "count", JS_DONTENUM);

			js_newcfunction(j, time, "console.prototype.time", 0);
			js_defproperty(j, -2, "time", JS_DONTENUM);

			js_newcfunction(j, timeEnd, "console.prototype.timeEnd", 0);
			js_defproperty(j, -2, "timeEnd", JS_DONTENUM);
		}
		js_setglobal(j, "console");
		js_pop(j, 1);
	}

	void
	ScriptBinderConsole::log(js_State* j) noexcept
	{
		if (!js_isundefined(j, 1))
			std::cout << js_tostring(j, 1) << std::endl;
	}

	void
	ScriptBinderConsole::cls(js_State *j) noexcept
	{
#if defined(_WINDOWS)
		std::system("cls");
#else
		std::system("clear");
#endif
	}

	void
	ScriptBinderConsole::count(js_State *j) noexcept
	{
		const char* msg = js_tostring(j, 1);
		std::cout << ++count_[msg] << std::endl;
	}

	void 
	ScriptBinderConsole::time(js_State *j) noexcept
	{
		const char* name = js_tostring(j, 1);
		time_[name] = std::chrono::high_resolution_clock::now();
	}

	void 
	ScriptBinderConsole::timeEnd(js_State *j) noexcept
	{
		const char* name = js_tostring(j, 1);
		auto startTime = time_[name];
		auto us = (double)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
		std::cout << us * std::chrono::milliseconds::period::num / std::chrono::milliseconds::period::den << "ms" << std::endl;
	}
}