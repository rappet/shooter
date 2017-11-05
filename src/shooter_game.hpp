#pragma once
#include "game.hpp"

class shooter_game : public game {
	public:
		shooter_game();
		bool on_event( SDL_Event &event );
		void on_tick();
		void on_render();
};
