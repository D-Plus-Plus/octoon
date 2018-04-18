#ifndef OCTOON_GAME_OBJECT_H_
#define OCTOON_GAME_OBJECT_H_

#include <octoon/game_types.h>
#include <octoon/io/serializable.h>

namespace octoon
{
	class OCTOON_EXPORT GameObject : public serializable, public runtime::RttiInterface
	{
		OctoonDeclareSubClass(GameObject, runtime::RttiInterface)
	public:
		GameObject() noexcept;
		virtual ~GameObject() noexcept;

		void set_name(const std::string& name) noexcept;
		void set_name(std::string&& name) noexcept;
		const std::string& get_name() const noexcept;

		void set_active(bool active) except;
		void set_active_upwards(bool active) except;
		void set_active_downwards(bool active) except;
		bool get_active() const noexcept;

		void set_layer(std::uint8_t layer) noexcept;
		std::uint8_t get_layer() const noexcept;

		std::size_t id() const noexcept;

		void set_parent(const GameObjectPtr& parent) noexcept;
		GameObject* get_parent() const noexcept;

		void add_child(GameObjectPtr& child) noexcept;
		void add_child(GameObjectPtr&& child) noexcept;
		void remove_child(GameObjectPtr& child) noexcept;
		void cleanup_children() noexcept;
		GameObjectPtr find_child(const std::string& name, bool recurse = true) noexcept;

		std::size_t get_child_count() const noexcept;
		GameObjects& get_children() noexcept;
		const GameObjects& get_children() const noexcept;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameComponent, T>::value>>
		void add_component() except { this->add_component(std::make_shared<T>()); }
		void add_component(const GameComponentPtr& component) except;
		void add_component(GameComponentPtr&& component) except;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameComponent, T>::value>>
		std::shared_ptr<T> get_component() const noexcept { return std::dynamic_pointer_cast<T>(this->get_component(T::RTTI)); }
		GameComponentPtr get_component(const runtime::Rtti* type) const noexcept;
		GameComponentPtr get_component(const runtime::Rtti& type) const noexcept;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameComponent, T>::value>>
		void get_components(GameComponents& components) const noexcept { this->get_components(T::RTTI, components); }
		void get_components(const runtime::Rtti* type, GameComponents& components) const noexcept;
		void get_components(const runtime::Rtti& type, GameComponents& components) const noexcept;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameComponent, T>::value>>
		std::shared_ptr<T> get_component_in_children() const noexcept { return std::dynamic_pointer_cast<T>(this->get_component_in_children(T::RTTI)); }
		GameComponentPtr get_component_in_children(const runtime::Rtti* type) const noexcept;
		GameComponentPtr get_component_in_children(const runtime::Rtti& type) const noexcept;

		template<typename T, typename = std::enable_if_t<std::is_base_of<GameComponent, T>::value>>
		void get_components_in_children(GameComponents& components) const noexcept { this->get_components_in_children(T::RTTI, components); }
		void get_components_in_children(const runtime::Rtti* type, GameComponents& components) const noexcept;
		void get_components_in_children(const runtime::Rtti& type, GameComponents& components) const noexcept;

		const GameComponents& get_components() const noexcept;

		void remove_component(const GameComponentPtr& component) noexcept;
		void cleanup_components() noexcept;

		void add_component_dispatch(GameDispatchTypes type, const GameComponentPtr& component) noexcept;
		void remove_component_dispatch(GameDispatchTypes type, const GameComponentPtr& component) noexcept;
		void remove_component_dispatchs(const GameComponentPtr& component) noexcept;

		void destroy() noexcept;

		virtual GameScene* get_game_scene() noexcept;
		virtual const GameScene* get_game_scene() const noexcept;

		GameObjectPtr clone() const except;

		virtual void serialize(BinaryWriter& out) except override
		{
			// todo
			JsonObject json = *this;
			out << json;
		}

		virtual void serialize(StreamWriter& out) except override
		{
			JsonObject json = *this;
			out << json;
		}

		static GameObject deserialize(BinaryReader& in) except
		{
			// todo
			JsonObject json;
			in >> json;
			return json.get<GameObject>();
		}

		static GameObject deserialize(StreamReader& in) except
		{
			JsonObject json;
			in >> json;
			return json.get<GameObject>();
		}

	private:
		friend class GameObjectManager;
		friend class TransformComponent;

		void on_activate() except;
		void on_deactivate() noexcept;

		void on_frame_begin() except;
		void on_frame() except;
		void on_frame_end() except;

		void on_move_before() except;
		void on_move_after() except;

		void on_layer_change_before() except;
		void on_layer_change_after() except;

		void on_gui() except;

		friend void to_json(json& j, const GameObject& p);
		friend void from_json(const json& j, GameObject& p);

	private:
		GameObject(const GameObject& copy) noexcept = delete;
		GameObject& operator=(const GameObject& copy) noexcept = delete;

	private:
		bool active_;

		std::uint8_t layer_;
		std::size_t instance_id_;

		std::string name_;

		GameObjects children_;
		GameObjectWeakPtr parent_;

		GameComponents components_;
		std::vector<GameComponents> dispatch_components_;
	};

	void to_json(json& j, const GameObject& p);
	void from_json(const json& j, GameObject& p);
}

#endif