#include <octoon/video/material_tech.h>

namespace octoon
{
	namespace video
	{
		MaterialTech::MaterialTech() noexcept
		{
		}

		MaterialTech::MaterialTech(const std::string& name) noexcept
		{
			this->setName(name);
		}

		MaterialTech::MaterialTech(std::string&& name) noexcept
		{
			this->setName(name);
		}

		MaterialTech::~MaterialTech() noexcept
		{
		}

		void
		MaterialTech::setName(const std::string& name) noexcept
		{
			_name = name;
		}

		void
		MaterialTech::setName(std::string&& name) noexcept
		{
			_name = std::move(name);
		}

		const std::string&
		MaterialTech::getName() const noexcept
		{
			return _name;
		}

		void
		MaterialTech::addPass(MaterialPassPtr& pass)
		{
			assert(std::find(_passes.begin(), _passes.end(), pass) == _passes.end());
			_passes.push_back(pass);
		}

		void
		MaterialTech::addPass(MaterialPassPtr&& pass)
		{
			assert(std::find(_passes.begin(), _passes.end(), pass) == _passes.end());
			_passes.push_back(std::move(pass));
		}

		void
		MaterialTech::removePass(MaterialPassPtr& pass)
		{
			auto it = std::find(_passes.begin(), _passes.end(), pass);
			if (it != _passes.end())
			{
				_passes.erase(it);
			}
		}

		void
		MaterialTech::removePass(MaterialPassPtr&& pass)
		{
			auto it = std::find(_passes.begin(), _passes.end(), pass);
			if (it != _passes.end())
			{
				_passes.erase(it);
			}
		}

		MaterialPassPtr
		MaterialTech::getPass(const std::string& name) noexcept
		{
			for (auto& it : _passes)
			{
				if (it->getName() == name)
					return it;
			}

			return nullptr;
		}

		MaterialPassPtr
		MaterialTech::getPass(std::size_t index) noexcept
		{
			assert(index < _passes.size());
			return _passes[index];
		}

		const MaterialPasses&
		MaterialTech::getAllPass() const noexcept
		{
			return _passes;
		}

		MaterialTechPtr
		MaterialTech::clone() const noexcept
		{
			auto tech = std::make_shared<MaterialTech>(this->getName());
			for (auto& pass : _passes)
				tech->addPass(pass->clone());
			return tech;
		}
	}
}