#pragma once

# include "Window.h"
# include "RenderTarget.h"

namespace MiniEngine
{
    class D3D12RenderWindow : public RenderTarget
    {
    public:
        D3D12RenderWindow(Window *window);
        ~D3D12RenderWindow();
    };
}