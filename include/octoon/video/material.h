#ifndef OCTOON_MATERIAL_H_
#define OCTOON_MATERIAL_H_

#include <octoon/video/render_types.h>
#include <octoon/video/material_tech.h>
#include <octoon/graphics/graphics_types.h>

namespace octoon
{
	namespace video
	{
		class OCTOON_EXPORT Material
		{
		public:
			Material() noexcept;
			Material(std::string&& name) noexcept;
			Material(const std::string& name) noexcept;
			virtual ~Material() noexcept;

			void setName(std::string&& name) noexcept;
			void setName(const std::string& name) noexcept;
			const std::string& getName() const noexcept;

			void addTech(MaterialTechPtr& pass);
			void addTech(MaterialTechPtr&& pass);
			void removeTech(MaterialTechPtr& pass);
			void removeTech(MaterialTechPtr&& pass);
			MaterialTechPtr getTech(const std::string& name) noexcept;
			MaterialTechPtr getTech(std::size_t index) noexcept;
			const MaterialTechs& getAllTech() const noexcept;

			virtual void setTransform(const math::float4x4& vp) noexcept = 0;
			virtual void setViewProjection(const math::float4x4& vp) noexcept = 0;

			virtual const graphics::GraphicsPipelinePtr& getPipeline() const noexcept = 0;
			virtual const graphics::GraphicsDescriptorSetPtr& getDescriptorSet() const noexcept = 0;

			virtual graphics::GraphicsUniformSetPtr at(const std::string& name) const;

			virtual MaterialPtr clone() const noexcept = 0;

		private:
			Material(const Material&) = delete;
			Material& operator=(const Material&) = delete;

		private:
			std::string _name;
			MaterialTechs _techs;
		};
	}
}

#endif