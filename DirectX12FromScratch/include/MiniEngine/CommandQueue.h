#pragma once

# include "MiniEngine/Fence.h"
# include "MiniEngine/CommandList.h"

namespace MiniEngine
{
    class CommandQueue
    {
    public:
        CommandQueue();
        virtual ~CommandQueue();

        virtual CommandList        *createCommandList(RenderTarget *target) = 0;
        virtual bool                wait(Fence &fence) = 0;

        virtual bool                executeCommandLists(unsigned int nb, CommandList *lists) = 0;
    };
}