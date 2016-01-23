#include "Window_SFML.h"
#include "Config.h"

Window_SFML::Window_SFML()
{
    _window = nullptr;
    _map[sf::Keyboard::Escape] = ESCAPE;
}

Window_SFML::~Window_SFML()
{
	if (_window && _window->isOpen())
		_window->close();

	delete (_window);
}

bool Window_SFML::create(unsigned int h, unsigned int w, HINSTANCE)
{
    _window = new sf::Window(sf::VideoMode(h, w), "My window");

    if (_window)
        return (true);

    return (false);
}

void * Window_SFML::getHandle()
{
	if (_window)
		return _window->getSystemHandle();

	return (nullptr);
}

bool Window_SFML::isOpen() const
{
	if (_window)
		return (_window->isOpen());

	return (false);
}

void Window_SFML::destroy()
{
	_window->close();
}

IWindow::EVENT_TYPE Window_SFML::getEvent()
{
	sf::Event event;

	if (_window->pollEvent(event))
	{
		return (_map.find(event.key.code) != _map.end() ? _map.at(event.key.code) : IWindow::EVENT_TYPE::UNDEFINED);
	}

	return IWindow::EVENT_TYPE::UNDEFINED;
}