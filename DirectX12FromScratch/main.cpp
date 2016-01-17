
#include <iostream>
#include <d3d12.h>
#include <dxgi1_4.h>

//#include "IWindow.h"
#include "Window_SFML.h"
#include "Graphics_DX12.h"
//#include <D3Dcompiler.h>
//#include <DirectXMath.h>

int	main()
{
	IWindow *win = new Window_SFML();
	IGraphics *grph = new Graphics_DX12();

	win->createWindow(800, 600);
	grph->Init(800, 600, win->getHandle());

	while (win->isOpen())
	{
//		IWindow::EVENT_TYPE event;

		grph->Display();
//		while (event = )
		//IEvent::EVENT_TYPE Window_SFML::getEvent() const
//		if ((IEvent*)win->getEvent() == IEvent::EVENT_TYPE::ESCAPE)
//		if (reinterpret_cast<Window_SFML*>(win)->getEvent() == IEvent::EVENT_TYPE::ESCAPE)
		if (win->getEvent() == IWindow::EVENT_TYPE::ESCAPE)
		{
			win->close();
		}
	}
	grph->Quit();
	delete (grph);
	delete (win);

	return (EXIT_SUCCESS);
}