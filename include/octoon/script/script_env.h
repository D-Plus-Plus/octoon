#ifndef OCTOON_SCRIPT_ENV_H_
#define OCTOON_SCRIPT_ENV_H_

#include <octoon/runtime/platform.h>
#include <octoon/script/script_binder.h>
#include <vector>
#include <memory>
#include <functional>

namespace octoon
{
	namespace script
	{
		class OCTOON_EXPORT ScriptEnv final
		{
		public:
			ScriptEnv() except;
			~ScriptEnv() noexcept;

			void doString(const char* str);
			void get(const char* str, std::function<void()>& action);

		private:
			void setup() except;
			void close() noexcept;

		private:
			ScriptEnv(const ScriptEnv&) = delete;
			ScriptEnv& operator=(const ScriptEnv&) = delete;

		private:
			lua_State* state_;
			std::vector<std::unique_ptr<ScriptBinder>> binders_;
		};
	}
}

#endif