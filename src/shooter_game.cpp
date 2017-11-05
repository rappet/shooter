#include "shooter_game.hpp"

shooter_game::shooter_game() : game() {

}

bool shooter_game::on_event( SDL_Event &event ) {
	if (game::on_event(event)) return true;
	return false;
}

void shooter_game::on_tick() {
	game::on_tick();
}

void shooter_game::on_render() {
	game::on_render();

	SDL_SetRenderDrawColor(render_handle(), 255, 255, 255, 255);
	SDL_RenderDrawLine(render_handle(), 0, 0, width(), height());
	SDL_RenderDrawLine(render_handle(), ticks() % width(), 0, ticks() % width(), height());
	SDL_SetRenderDrawColor(render_handle(), 255, 0, 0, 255);
	SDL_Rect rect = { 0, 0, 20, 20 };
	SDL_RenderFillRect(render_handle(), &rect);
	rect = { width() - 20, 0, 20, 20 };
	SDL_RenderFillRect(render_handle(), &rect);
	rect = { 0, height() - 20, 20, 20 };
	SDL_RenderFillRect(render_handle(), &rect);
	rect = { width() - 20, height() - 20, 20, 20 };
	SDL_RenderFillRect(render_handle(), &rect);
}

