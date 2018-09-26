#ifndef OCTOON_VIDEO_MATERIAL_TYPES_H_
#define OCTOON_VIDEO_MATERIAL_TYPES_H_

#include <octoon/runtime/rtti.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/video/render_types.h>
#include <octoon/graphics/graphics_types.h>

namespace octoon
{
	namespace video
	{
		typedef std::shared_ptr<class MaterialPass> MaterialPassPtr;
		typedef std::shared_ptr<class MaterialTech> MaterialTechPtr;

		typedef std::vector<MaterialTechPtr> MaterialTechs;
		typedef std::vector<MaterialPassPtr> MaterialPasses;
	}
}

#endif