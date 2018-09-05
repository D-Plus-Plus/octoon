#include "script_binder_console.h"
#include <iostream>
#include <mujs.h>

namespace octoon
{
	thread_local std::map<std::string, std::uint32_t> ScriptBinderConsole::count_;

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
		}
		js_setglobal(j, "console");
		js_pop(j, 1);
	}

	void 
	ScriptBinderConsole::log(js_State* j) noexcept
	{
		const char* msg = js_tostring(j, 1);
		std::cout << msg << std::endl;
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
}