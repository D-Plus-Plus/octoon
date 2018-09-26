#ifndef OCTOON_VIDEO_MATERIAL_PASS_H_
#define OCTOON_VIDEO_MATERIAL_PASS_H_

#include <octoon/video/material_types.h>

namespace octoon
{
	namespace video
	{
		class OCTOON_EXPORT MaterialPass final
		{
		public:
			MaterialPass() noexcept;
			~MaterialPass() noexcept;

			void setName(const std::string& name) noexcept;
			void setName(std::string&& name) noexcept;
			const std::string& getName() const noexcept;

			/*void setGraphicsState(GraphicsStatePtr& state) noexcept;
			void setGraphicsProgram(GraphicsProgramPtr& program) noexcept;
			void setGraphicsInputLayout(GraphicsInputLayoutPtr& inputLayout) noexcept;
			void setGraphicsDescriptorPool(GraphicsDescriptorPoolPtr& pool) noexcept;
			void setGraphicsDescriptorSetLayout(GraphicsDescriptorSetLayoutPtr& descriptorSetLayout) noexcept;

			void setGraphicsState(GraphicsStatePtr&& state) noexcept;
			void setGraphicsProgram(GraphicsProgramPtr&& program) noexcept;
			void setGraphicsInputLayout(GraphicsInputLayoutPtr&& inputLayout) noexcept;
			void setGraphicsDescriptorPool(GraphicsDescriptorPoolPtr&& pool) noexcept;
			void setGraphicsDescriptorSetLayout(GraphicsDescriptorSetLayoutPtr&& descriptorSetLayout) noexcept;

			const GraphicsStatePtr& getGraphicsState() const noexcept;
			const GraphicsProgramPtr& getGraphicsProgram() const noexcept;
			const GraphicsInputLayoutPtr& getGraphicsInputLayout() const noexcept;
			const GraphicsDescriptorPoolPtr& getGraphicsDescriptorPool() const noexcept;
			const GraphicsDescriptorSetLayoutPtr& getGraphicsDescriptorSetLayout() const noexcept;
			const GraphicsPipelinePtr& getRenderPipeline() const noexcept;
			const GraphicsDescriptorSetPtr& getDescriptorSet() const noexcept;

			void update(const MaterialSemanticManager& semanticManager) noexcept;*/

			MaterialPassPtr clone() const noexcept;

		/*private:
			void updateSemantic(GraphicsUniformSet& uniform, const MaterialSemantic& semantic) noexcept;

		private:
			MaterialPass(const MaterialPass&) = delete;
			MaterialPass& operator=(const MaterialPass&) = delete;

		private:
			typedef std::vector<std::unique_ptr<MaterialParamBinding>> MaterialParamBindings;
			typedef std::vector<MaterialSemanticBinding> MaterialSemanticBindings;*/

			std::string _name;
			/*MaterialParamBindings _bindingParams;
			MaterialSemanticBindings _bindingSemantics;

			GraphicsStatePtr _state;
			GraphicsProgramPtr _program;
			GraphicsDescriptorSetPtr _descriptorSet;
			GraphicsDescriptorPoolPtr _descriptorPool;
			GraphicsDescriptorSetLayoutPtr _descriptorSetLayout;
			GraphicsInputLayoutPtr _inputLayout;
			GraphicsPipelinePtr _pipeline;*/
		};
	}
}

#endif