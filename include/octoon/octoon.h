#ifndef OCTOON_H_
#define OCTOON_H_

#include <octoon/game_app.h>
#include <octoon/game_object.h>

#include <octoon/video/line_material.h>
#include <octoon/video/text_material.h>
#include <octoon/video/blinn_material.h>
#include <octoon/video/phong_material.h>
#include <octoon/video/ggx_material.h>

#include <octoon/input_feature.h>

#include <octoon/mesh_filter_component.h>
#include <octoon/transform_component.h>
#include <octoon/guizmo_component.h>
#include <octoon/first_person_camera_component.h>
#include <octoon/camera_component.h>
#include <octoon/mesh_renderer_component.h>

#include <octoon/rigidbody_component.h>
#include <octoon/sphere_collider_component.h>
#include <octoon/capsule_collider_component.h>
#include <octoon/mesh_collider_component.h>

#include <octoon/model/text_meshing.h>
#include <octoon/model/property.h>
#include <octoon/res_manager.h>
#include <octoon/ui/imgui.h>

namespace octoon
{
	typedef MeshFilterComponent MeshFilter;
	typedef TransformComponent Transform;
	typedef GuizmoComponent Guizmo;
	typedef FirstPersonCameraComponent FirstPersonCamera;
	typedef CameraComponent Camera;
	typedef MeshRendererComponent MeshRenderer;
}

#endif