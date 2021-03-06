#include <iostream>
#include "MainApplication.h"
#include "MiniEngine/SpotLight.h"
#include "MiniEngine/D3D12/D3D12RenderSystem.h"
#include "MiniEngine/D3D12/D3D12RenderWindow.h"

MainApplication::MainApplication(const std::string &windowType, HINSTANCE hInstance) : MiniEngine::Application(), _window(nullptr)
{
    float       clearColor[4] = { 0.2f, 0.2f, 0.2f, 0.0f };

    initWindow(windowType, hInstance);

    if (_window)
    {
        _root->setRenderSystem(new MiniEngine::D3D12RenderSystem);

        if (_root->getRenderSystem())
        {
            MiniEngine::RenderWindow        *renderTarget = _root->getRenderSystem()->createRenderWindow(_window);

            // Add render target
            _root->getRenderSystem()->addRenderTarget(renderTarget);

            // Change clear color
            renderTarget->setClearColor(clearColor);

            // Create Scene
            _sceneManager = _root->createSceneManager(MiniEngine::Root::SceneManagerType::BASIC);

            if (_sceneManager)
            {
                _camera = _sceneManager->createCamera();

                _camera->lookAt({ 60.0f, 100.0f, 0.0f }, { 0.0f, -0.1f, 0.0f }, { 0.0f, 1.0f, 0.0f });

                renderTarget->getDefaultViewport()->attachCamera(_camera);

                MiniEngine::SpotLight   *light = dynamic_cast<MiniEngine::SpotLight*>(_sceneManager->createLight(MiniEngine::Light::SPOT, _camera));

                light->setAmbient({0.1f, 0.1f, 0.1f});
                light->setDiffuse({ 0.5f, 0.5f, 0.5f });
                light->setSpecular({ 1.0f, 1.0f, 1.0f });

                light->setInnerCutOff(10.0f);
                light->setOuterCutOff(25.0f);

                light->setDirection({ 0.0f, 0.0f, 1.0f });

                _node = _sceneManager->getRootNode()->createChild(_root->getRenderSystem()->loadModel("./Assets/models/teapot.txt"));
            }
        }
    }
}

MainApplication::~MainApplication()
{
    delete _sceneManager;
}

void MainApplication::initWindow(const std::string &windowType, HINSTANCE hInstance)
{
    if (!_dllWindow.load("./" + DynamicLibrary::buildName(windowType.c_str())))
    {
        std::cerr << "Can't load dll : " << DynamicLibrary::buildName(windowType.c_str()) << std::endl;
        return;
    }

    std::function<Window*(void)> createWindow = (Window*(*)(void))_dllWindow.loadSymbol("entry");

    if (!createWindow)
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
        std::cerr << "Can't load dll entry point" << std::endl;
        return;
    }

    _window = createWindow();

    if (!_window)
    {
        std::cerr << "Can't create instance of Window" << std::endl;
        return;
    }

# if defined(SYSTEM_WINDOWS)
    if (!_window->create(800, 600, hInstance))
# else 
    if (!_window->create(800, 600))
# endif
    {
        std::cerr << "Can't create window" << std::endl;

        delete (_window);
        _window = nullptr;
    }
}

bool MainApplication::update(MiniEngine::Time elapsedTime)
{
    if (!_window || !_window->isOpen())
        return (false);

	float elapsedSeconds = elapsedTime.getSeconds();

	if (_window->isKeyPressed(Keyboard::Left))
		_camera->rotate(100 * elapsedSeconds, Vector3f(0, 1, 0), MiniEngine::TS_WORLD);
	if (_window->isKeyPressed(Keyboard::Right))
		_camera->rotate(100 * elapsedSeconds, Vector3f(0, -1, 0), MiniEngine::TS_WORLD);
	if (_window->isKeyPressed(Keyboard::Up))
		_camera->rotate(100 * elapsedSeconds, Vector3f(1, 0, 0), MiniEngine::TS_LOCAL);
	if (_window->isKeyPressed(Keyboard::Down))
		_camera->rotate(100 * elapsedSeconds, Vector3f(-1, 0, 0), MiniEngine::TS_LOCAL);

	if (_window->isKeyPressed(Keyboard::Z))
		_camera->translate(Vector3f(0, 0, -100 * elapsedSeconds), MiniEngine::TS_LOCAL);
	if (_window->isKeyPressed(Keyboard::S))
		_camera->translate(Vector3f(0, 0, 100 * elapsedSeconds), MiniEngine::TS_LOCAL);
	if (_window->isKeyPressed(Keyboard::Q))
		_camera->translate(Vector3f(-100 * elapsedSeconds, 0, 0), MiniEngine::TS_LOCAL);
	if (_window->isKeyPressed(Keyboard::D))
		_camera->translate(Vector3f(100 * elapsedSeconds, 0, 0), MiniEngine::TS_LOCAL);

	if (_window->isKeyPressed(Keyboard::Space))
		_camera->translate(Vector3f(0, 100 * elapsedSeconds, 0), MiniEngine::TS_WORLD);
	if (_window->isKeyPressed(Keyboard::LShift))
		_camera->translate(Vector3f(0, -100 * elapsedSeconds, 0), MiniEngine::TS_WORLD);

	Event event;

	while (_window->getEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				_window->destroy();
				return (false);
			}
		}

		if (event.type == Event::Closed)
		{
			_window->destroy();
			return (false);
		}
	}

    return (true);
}