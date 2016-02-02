#pragma once

# include "MiniEngine/Viewport.h"
# include "MiniEngine/RenderSystem.h"
# include "MiniEngine/GraphicPipeline.h"
# include "MiniEngine/ConstantBuffer.h"

namespace MiniEngine
{
    class RenderTarget
    {
    public:
        RenderTarget(RenderSystem &system);
        virtual ~RenderTarget();

		virtual bool		    init() = 0;
        virtual bool            render() = 0;

        void                    addViewport(Viewport *viewport);
        void                    setClearColor(const float color[4]);

        virtual GraphicPipeline *getGraphicPipeline() = 0;

        unsigned int            getFrameIdx();
        unsigned int            getFrameCount();

    protected:
        RenderSystem            &_system;
        float                   _clearColor[4];
        std::list<Viewport*>    _viewports;

        unsigned int            _frameIdx;
        unsigned int            _frameCount;
    };
}