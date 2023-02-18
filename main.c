#include "sobre_engine.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif	// _DEBUG

#ifdef _DEBUG
#pragma comment(lib, "SDL2d.lib")
#else
#pragma comment(lib, "SDL2.lib")
#endif

#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "SDL2_gfx.lib")
#pragma comment(lib, "cjson.lib")

// rad to deg approx
inline double rad_to_deg_approx(double rad)
{
	return rad * 57;
}

#ifdef _WIN32
int APIENTRY WinMain
(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
#else
int main()
#endif // _WIN32
{
	#ifdef _WIN32
	// not used parameters!
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
	#endif // _WIN32

	SDL_Renderer* renderer;
	SDL_Window* main_window;
	unsigned char game_state = CMD_RUN_MAIN_MENU;

	// init SDL2
	if (!init_sdl(&renderer, &main_window))
	{
		#ifdef _WIN32
		MessageBox(NULL, L"SDL2.dll failure", L"Error", MB_ICONERROR | MB_OK);
		#endif // _WIN32
		return EXIT_FAILURE;
	}

	// init SDL2_ttf
	if (TTF_Init() == -1) {
		#ifdef _WIN32
		MessageBox(NULL, L"SDL2_ttf.dll failure", L"Error", MB_ICONERROR | MB_OK);
		#endif // _WIN32
		return EXIT_FAILURE;
	}

	// Initialize SDL2_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096) == -1)
	{
		#ifdef _WIN32
		MessageBox(NULL, L"SDL2_mixer.dll failure", L"Error", MB_ICONERROR | MB_OK);
		#endif // _WIN32
		return EXIT_FAILURE;
	}

	// init random seed
	srand((unsigned int)time(NULL));
	
	while (game_state != CMD_END_GAME)
	{
		switch (game_state)
		{
		case CMD_RUN_MAIN_MENU:
			game_state = run_game_1(renderer);
			break;
		case CMD_RUN_GAME_1:
			game_state = run_game_1(renderer);
			break;
		case CMD_RUN_FAIL:
			return EXIT_FAILURE;
		}
	}

	kill_sdl(renderer, main_window);
	TTF_Quit();
	Mix_CloseAudio();

	#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	#endif	//_DEBUG

	return EXIT_SUCCESS;
}
