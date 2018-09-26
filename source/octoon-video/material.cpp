#include <octoon/video/material.h>
#include <octoon/graphics/graphics.h>

namespace octoon
{
	namespace video
	{
		Material::Material() noexcept
		{
		}

		Material::Material(std::string&& name) noexcept
		{
			this->setName(std::move(name));
		}

		Material::Material(const std::string& name) noexcept
		{
			this->setName(name);
		}

		Material::~Material() noexcept
		{
		}

		void
		Material::setName(std::string&& name) noexcept
		{
			_name = std::move(name);
		}

		void
		Material::setName(const std::string& name) noexcept
		{
			_name = name;
		}

		const std::string&
		Material::getName() const noexcept
		{
			return _name;
		}

		void
		Material::addTech(MaterialTechPtr& pass)
		{
			assert(std::find(_techs.begin(), _techs.end(), pass) == _techs.end());
			_techs.push_back(pass);
		}

		void
		Material::addTech(MaterialTechPtr&& pass)
		{
			assert(std::find(_techs.begin(), _techs.end(), pass) == _techs.end());
			_techs.push_back(std::move(pass));
		}

		void
		Material::removeTech(MaterialTechPtr& pass)
		{
			auto it = std::find(_techs.begin(), _techs.end(), pass);
			if (it != _techs.end())
			{
				_techs.erase(it);
			}
		}

		void
		Material::removeTech(MaterialTechPtr&& pass)
		{
			auto it = std::find(_techs.begin(), _techs.end(), pass);
			if (it != _techs.end())
			{
				_techs.erase(it);
			}
		}

		MaterialTechPtr
		Material::getTech(const std::string& name) noexcept
		{
			for (auto& it : _techs)
			{
				if (it->getName() == name)
					return it;
			}

			return nullptr;
		}

		MaterialTechPtr
		Material::getTech(std::size_t index) noexcept
		{
			assert(index < _techs.size());
			return _techs[index];
		}

		const MaterialTechs&
		Material::getAllTech() const noexcept
		{
			return _techs;
		}

		graphics::GraphicsUniformSetPtr 
		Material::at(const std::string& name) const
		{
			auto begin = this->getDescriptorSet()->getUniformSets().begin();
			auto end = this->getDescriptorSet()->getUniformSets().end();

			auto it = std::find_if(begin, end, [&](const graphics::GraphicsUniformSetPtr& set){ return set->getName() == name; });
			if (it != end)
				return *it;

			return nullptr;
		}		
	}
}