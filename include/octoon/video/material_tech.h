#ifndef OCTOON_VIDEO_MATERIALTECH_H_
#define OCTOON_VIDEO_MATERIALTECH_H_

#include <octoon/video/material_pass.h>

namespace octoon
{
	namespace video
	{
		class OCTOON_EXPORT MaterialTech final : public runtime::RttiInterface
		{
		public:
			MaterialTech() noexcept;
			MaterialTech(std::string&& name) noexcept;
			MaterialTech(const std::string& name) noexcept;
			~MaterialTech() noexcept;

			void setName(std::string&& name) noexcept;
			void setName(const std::string& name) noexcept;
			const std::string& getName() const noexcept;

			void addPass(MaterialPassPtr& pass);
			void addPass(MaterialPassPtr&& pass);
			void removePass(MaterialPassPtr& pass);
			void removePass(MaterialPassPtr&& pass);
			MaterialPassPtr getPass(const std::string& name) noexcept;
			MaterialPassPtr getPass(std::size_t index) noexcept;
			const MaterialPasses& getAllPass() const noexcept;

			MaterialTechPtr clone() const noexcept;

		private:
			MaterialTech(const MaterialTech&) = delete;
			MaterialTech& operator=(const MaterialTech&) = delete;

		private:
			std::string _name;
			MaterialPasses _passes;
		};
	}
}

#endif