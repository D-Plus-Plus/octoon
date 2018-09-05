#ifndef OCTOON_SCRIPT_BINDER_H_
#define OCTOON_SCRIPT_BINDER_H_

typedef struct js_State js_State;

namespace octoon
{
	class ScriptBinder
	{
	public:
		ScriptBinder() noexcept = default;
		virtual ~ScriptBinder() noexcept = default;

		virtual void bind(js_State* j) noexcept = 0;
	};
}

#endif