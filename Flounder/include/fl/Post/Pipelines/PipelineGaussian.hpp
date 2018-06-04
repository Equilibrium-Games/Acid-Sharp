#pragma once

#include "Post/Filters/FilterBlurVertical.hpp"
#include "Post/Filters/FilterBlurHorizontal.hpp"
#include "Post/IPostPipeline.hpp"

namespace fl
{
	class FL_EXPORT PipelineGaussian :
		public IPostPipeline
	{
	private:
		FilterBlurVertical m_filterBlurVertical;
		FilterBlurHorizontal m_filterBlurHorizontal;
	public:
		PipelineGaussian(const GraphicsStage &graphicsStage, const float &scale = 2.0f);

		~PipelineGaussian();

		void Render(const CommandBuffer &commandBuffer) override;
	};
}
