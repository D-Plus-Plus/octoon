#ifndef OCTOON_SCRIPT_BINDER_H_
#define OCTOON_SCRIPT_BINDER_H_

typedef struct lua_State lua_State;

namespace octoon
{
	namespace script
	{
		class ScriptBinder
		{
		public:
			ScriptBinder() noexcept = default;
			virtual ~ScriptBinder() noexcept = default;

			virtual void bind(lua_State* j) noexcept = 0;
		};
	}
}

#endif