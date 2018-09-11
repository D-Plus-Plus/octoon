#ifndef OCTOON_SCRIPT_BINDER_BASE_H_
#define OCTOON_SCRIPT_BINDER_BASE_H_

#include <octoon/script/script_binder.h>

namespace octoon
{
	namespace script
	{
		class ScriptBinderBase final : public ScriptBinder
		{
		public:
			ScriptBinderBase() noexcept;
			virtual ~ScriptBinderBase() noexcept;

			void bind(lua_State* j) noexcept;
		};
	}
}

#endif