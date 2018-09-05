#ifndef OCTOON_SCRIPT_BINDER_IO_H_
#define OCTOON_SCRIPT_BINDER_IO_H_

#include <octoon/script_binder.h>
#include <map>
#include <string>

namespace octoon
{
	class ScriptBinderIo final : public ScriptBinder
	{
	public:
		ScriptBinderIo() noexcept;
		virtual ~ScriptBinderIo() noexcept;

		void bind(js_State* j) noexcept;

	private:
		static void new_File(js_State *J);
		static void File_prototype_readByte(js_State *J);
		static void File_prototype_readLine(js_State *J);
		static void File_prototype_close(js_State *J);
	};
}

#endif