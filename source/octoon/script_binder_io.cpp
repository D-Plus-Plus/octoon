#include "script_binder_io.h"
#include <mujs.h>

namespace octoon
{
	ScriptBinderIo::ScriptBinderIo() noexcept
	{
	}

	ScriptBinderIo::~ScriptBinderIo() noexcept
	{
	}

	void 
	ScriptBinderIo::bind(js_State* J) noexcept
	{
		js_getglobal(J, "Object");
		js_getproperty(J, -1, "prototype");
		js_newuserdata(J, "File", stdin, 0);
		{
			js_newcfunction(J, File_prototype_readByte, "File.prototype.readByte", 0);
			js_defproperty(J, -2, "readByte", JS_DONTENUM);

			js_newcfunction(J, File_prototype_readLine, "File.prototype.readLine", 0);
			js_defproperty(J, -2, "readLine", JS_DONTENUM);

			js_newcfunction(J, File_prototype_close, "File.prototype.close", 0);
			js_defproperty(J, -2, "close", JS_DONTENUM);
		}
		js_newcconstructor(J, new_File, new_File, "File", 1);
		js_defglobal(J, "File", JS_DONTENUM);
	}

	void 
	ScriptBinderIo::new_File(js_State *J)
	{
		FILE *file;

		if (js_isundefined(J, 1)) {
			file = stdin;
		} else {
			const char *filename = js_tostring(J, 1);
			file = fopen(filename, "r");
			if (!file)
				js_error(J, "cannot open file: '%s'", filename);
		}

		js_currentfunction(J);
		js_getproperty(J, -1, "prototype");
		js_newuserdata(J, "File", file, 0);
	}

	void 
	ScriptBinderIo::File_prototype_readByte(js_State *J)
	{
		FILE* file = (FILE*)js_touserdata(J, 0, "File");
		js_pushnumber(J, getc(file));
	}

	void 
	ScriptBinderIo::File_prototype_readLine(js_State *J)
	{
		char line[256], *s;
		FILE* file = (FILE*)js_touserdata(J, 0, "File");
		s = fgets(line, sizeof line, file);
		if (s)
			js_pushstring(J, line);
		else
			js_pushnull(J);
	}

	void 
	ScriptBinderIo::File_prototype_close(js_State *J)
	{
		FILE* file = (FILE*)js_touserdata(J, 0, "File");
		fclose(file);
		js_pushundefined(J);
	}
}