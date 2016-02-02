#pragma once

#include "MiniEngine/RenderSystem.h"

namespace MiniEngine
{
	class ConstantBuffer
	{
	public:
		ConstantBuffer(RenderSystem&);
		virtual ~ConstantBuffer();

		virtual bool    init(unsigned int size, unsigned int nb) = 0;

        virtual bool    update(CommandList &commandList, unsigned int rootIdx, unsigned int size, void *data) = 0;

	protected:
		RenderSystem	&_system;
	};
};