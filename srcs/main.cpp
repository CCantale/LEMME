/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*   main.cpp                                              by CanTale_Games   */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

#include "main.h"

int	LEMME::init(char const *title, int _window_posX, int _window_posY,
		int width, int height, int fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL: Couldn't init" << std::endl;
		return (FATAL_ERROR);
	}
	_window = SDL_CreateWindow(title, _window_posX, _window_posY, width,
			height, fullscreen);
	if (!_window)
	{
		std::cerr << "SDL: Couldn't open window" << std::endl;
		SDL_Quit();
		return (FATAL_ERROR);
	}
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if (!_renderer)
	{
		std::cerr << "SDL: Couldn't init renderer" << std::endl;
	}
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);
	_running = true;
	return (SUCCESS);
}

void	LEMME::doThis(std::function<void()> newFunction)
{
	userDefinedFunction = newFunction;
}

int	LEMME::start(void)
{
	while (_running)
	{
		calculateDelta();
		handleEvents();
		if (userDefinedFunction)
			userDefinedFunction();
		//update();
		SDL_Delay(1);
	}
	return (SUCCESS);
}

void	LEMME::handleEvents(void)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_running = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						_running = false;
						break ;
					default:
						break ;
				}
				break ;
			default:
				break ;
		}
	}
}


void	LEMME::quit(void)
{
	//if (_SDL2_image_init)
		//IMG_Quit();
	if (_renderer)
		SDL_DestroyRenderer(_renderer);
	if (_window)
	{
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}
	_running = false;
}
