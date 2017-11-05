#include "game.hpp"
#include <algorithm>

using namespace std;

const int userevent_tick = USEREVENT_TICK;

game::game() 
	: _running(false),
	_width(0),
	_height(0),
	_ticks(0),
	_full_screen(false) {
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

		INFO("Initialize SDL2");
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)  throw SDL_GetError();
		INFO("Create window");
		_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE);
		if (window_handle() == nullptr) throw SDL_GetError();
		INFO("Create renderer");
		_renderer = SDL_CreateRenderer(window_handle(), -1, SDL_RENDERER_ACCELERATED);
		//_renderer = SDL_CreateRenderer(window_handle(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (render_handle() == nullptr) throw SDL_GetError();
		update_logical_size();
	}

game::~game() {
	if (render_handle() != nullptr)
	{
		INFO("Destroy renderer");
		SDL_DestroyRenderer(render_handle());
	}
	if (window_handle() != nullptr) {
		INFO("Destroy window");
		SDL_DestroyWindow(window_handle());
	}
}

Uint32 tick_callback(Uint32 interval, void *param) {
	SDL_Event event;
	SDL_UserEvent userevent;

	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = (void*)&userevent_tick;
	userevent.data2 = nullptr;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return interval;
}

void game::event_loop() {
	_running = true;
	_tick_timer = SDL_AddTimer(1000/120, &tick_callback, this);
	SDL_Event event;
	while (running() && SDL_WaitEvent(&event)) {
		on_event(event);
	}
}

bool game::on_event( SDL_Event &event ) {
	switch (event.type) {
		case SDL_QUIT:
			stop();
			return true;
		case SDL_USEREVENT:
			if (*(int*)event.user.data1 == USEREVENT_TICK ) {
				//INFO("Tick");
				on_tick();
				render();
				return true;
			} else {
				return false;
			}
		case SDL_WINDOWEVENT:
			return on_window_event(event.window);
		case SDL_KEYDOWN: case SDL_KEYUP:
			return on_keyboard_event(event.key);
		default:
			return false;
	}
}

bool game::on_window_event( SDL_WindowEvent &event ) {
	switch(event.event) {
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			INFO("Size changed");
			update_logical_size();
			render();
			return true;
		default:
			return false;
	}
}

bool game::on_keyboard_event( SDL_KeyboardEvent &event ) {
	if (event.type == SDL_KEYUP) {
		switch (event.keysym.sym) {
			case SDLK_F11:
				toggle_fullscreen();
				return true;
			default:
				return false;
		}
	}
	return false;
}

void game::render() {
	on_render();
	SDL_RenderPresent(render_handle());
}

void game::on_render() {
	SDL_SetRenderDrawColor(render_handle(), 0, 0, 0, 255);
	SDL_RenderClear(render_handle());
}

void game::on_tick() {
	++_ticks;
}

void game::toggle_fullscreen() {
	if (is_fullscreen()) {
		INFO("Exit fullscreen");
		SDL_SetWindowFullscreen(window_handle(), 0);
		_full_screen = false;
	} else {
		INFO("Go fullscreen");
		SDL_SetWindowFullscreen(window_handle(), SDL_WINDOW_FULLSCREEN_DESKTOP);
		_full_screen = true;
	}
}

void game::update_logical_size() {
	int real_width, real_height;
	SDL_GetWindowSize(window_handle(), &real_width, &real_height);

	float scale_x = real_width / 1280.;
	float scale_y = real_width / 720.;
	float scale;

	if(scale_x < scale_y) {
		scale = scale_x;
	} else {
		scale = scale_y;
	}
	_width = real_width / scale;
	_height = real_height / scale;
	SDL_RenderSetScale(render_handle(), scale, scale);
}

