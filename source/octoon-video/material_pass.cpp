#include <octoon/video/material_pass.h>

namespace octoon
{
	namespace video
	{
		MaterialPass::MaterialPass() noexcept
		{
		}

		MaterialPass::~MaterialPass() noexcept
		{
		}

		void
		MaterialPass::setName(const std::string& name) noexcept
		{
			_name = name;
		}

		void
		MaterialPass::setName(std::string&& name) noexcept
		{
			_name = std::move(name);
		}

		const std::string&
		MaterialPass::getName() const noexcept
		{
			return _name;
		}

		MaterialPassPtr
		MaterialPass::clone() const noexcept
		{
			auto pass = std::make_shared<MaterialPass>();
			return pass;
		}
	}
}