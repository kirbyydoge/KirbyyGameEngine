#include "Application.h"
#include "Game.h"
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GL_CALL(x) gl_clear_errors();\
	x;\
	ASSERT(gl_log_error(#x, __FILE__, __LINE__))

static void gl_clear_errors() {
	while (glGetError() != GL_NO_ERROR);
}

static bool gl_log_error(const char* function, const char* file, int line) {
	while (unsigned int error = glGetError()) {
		std::cout << "GL ERR: " << error << std::endl;
		std::cout << function << " at " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

int main(void) {
	Game *game = new Game(640, 480, "Fine, I'll do it myself.");
	Application::set_game(game);
	return 0;
}