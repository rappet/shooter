#pragma once
#include <SDL2/SDL.h>
#include <set>

#include "util.hpp"

enum userevent {
	USEREVENT_TICK = 100,
};

class game {
	public:
		game();
		virtual ~game();
		virtual void event_loop();
		void render();
		virtual void on_render();
		virtual void on_tick();
		virtual bool on_event( SDL_Event &event );
		virtual bool on_window_event( SDL_WindowEvent &event );
		virtual bool on_keyboard_event( SDL_KeyboardEvent &event );

		SDL_Window* window_handle() const { return _window; }
		SDL_Renderer* render_handle() const { return _renderer; }
		bool running() const { return _running; }
		void stop() { if (running()) INFO("Stoping game"); _running = false; }
		int width() const { return _width; }
		int height() const { return _height; }
		int ticks() const { return _ticks; }
		bool is_fullscreen() { return _full_screen; }
		void toggle_fullscreen();

	private:
		void update_logical_size();

		SDL_Window *_window;
		SDL_Renderer *_renderer;
		SDL_TimerID _tick_timer;
		bool _running;
		int _width, _height;
		int _ticks;
		bool _full_screen;
};
