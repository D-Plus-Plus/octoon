#ifndef OCTOON_RTTI_H_
#define OCTOON_RTTI_H_

#include <string>
#include <memory>
#include <vector>

#include <octoon/runtime/rtti_macros.h>

namespace octoon
{
	namespace runtime
	{
		class RttiInterface;

		class OCTOON_EXPORT Rtti
		{
		public:
			typedef RttiInterface*(*RttiConstruct)();
		public:
			Rtti(const std::string& name, RttiConstruct creator, const Rtti* parent) noexcept;
			~Rtti() = default;

			std::shared_ptr<class RttiInterface> create() const throw(std::bad_alloc);

			const Rtti* getParent() const noexcept;

			const std::string& type_name() const noexcept;

			bool isDerivedFrom(const Rtti* other) const noexcept;
			bool isDerivedFrom(const Rtti& other) const noexcept;
			bool isDerivedFrom(const char* const name) const noexcept;
			bool isDerivedFrom(const std::string& name) const noexcept;

		private:
			std::string name_;
			const Rtti* parent_;
			RttiConstruct construct_;
		};
	}
}

#endif