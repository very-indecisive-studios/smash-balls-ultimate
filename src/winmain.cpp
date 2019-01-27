#include "pch.h"

#define _CRTDBG_MAP_ALLOC       // for detecting memory leaks
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <stdlib.h>             // for detecting memory leaks
#include <crtdbg.h>             // for detecting memory leaks
#include <Mmsystem.h>
#include "constants.h"
#include "game/resources.h"
#include "context/context.h"
#include "winresource.h"

// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

HWND hwnd = NULL;

//=============================================================================
// Starting point for a Windows application
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#if defined(DEBUG) | defined(_DEBUG)
	// Check for memory leak if debug build.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Attach to console for debugging.
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
#endif

	// Try creating a window.
	if (!CreateMainWindow(hwnd, hInstance, nCmdShow)) 
	{
		return 1;
	}

	// Install fonts required by game.
	AddFontResource(Resources::FONT_NAME.c_str());
	AddFontResource(Resources::FONT_NAME_BOLD.c_str());

	// Initialize application context.
	Context::Initialize();

	// Initialize graphics.
	Context::GraphicsRenderer()->Initialize(hwnd, Constants::GAME_WIDTH, Constants::GAME_HEIGHT, Constants::FULLSCREEN);
	
	// Initialize audio.
	Context::AudioEngine()->Initialize();

	// Initialize game.
	Context::Game()->Initialize();

	// Initialize input.
	Context::InputManager()->Initialize(hwnd, false);

	// Main message loop.
	MSG msg;
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// look for quit message
			if (msg.message == WM_QUIT)
				done = 1;

			// decode and pass messages on to WinProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Run game.
			Context::Game()->Run();
		}
	}

	Context::ReleaseAll();

	// Uninstall fonts required by game.
	RemoveFontResource(Resources::FONT_NAME.c_str());
	RemoveFontResource(Resources::FONT_NAME_BOLD.c_str());

	return msg.wParam;
}

//=============================================================================
// window event callback function
//=============================================================================
LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	// Let input manager process any input messages.
	if (
		Context::IsInitialized() && 
		Context::InputManager()->ProccessKeyMessage(msg, wParam, lParam)
	)
	{
		return 0;
	}

	// Let Windows handle it instead.
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//=============================================================================
// Create the window
// Returns: false on error
//=============================================================================
bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;

	// Fill in the window class structure with parameters 
	// that describe the main window. 
	wcx.cbSize = sizeof(wcx);           // size of structure 
	wcx.style = CS_HREDRAW | CS_VREDRAW;    // redraw if size changes 
	wcx.lpfnWndProc = WinProc;          // points to window procedure 
	wcx.cbClsExtra = 0;                 // no extra class memory 
	wcx.cbWndExtra = 0;                 // no extra window memory 
	wcx.hInstance = hInstance;          // handle to instance 
	wcx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);   // predefined arrow 
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // black background 
	wcx.lpszMenuName = NULL;           // name of menu resource 
	wcx.lpszClassName = Constants::CLASS_NAME;     // name of window class 
	wcx.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); // small class icon 

	// Register the window class. 
	// RegisterClassEx returns 0 on error.
	if (RegisterClassEx(&wcx) == 0)    // if error
		return false;

	//set up the screen in windowed or fullscreen mode?
	DWORD style;
	if (Constants::FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU;

	// Create window
	hwnd = CreateWindow(
		Constants::CLASS_NAME,             // name of the window class
		Constants::GAME_TITLE,             // title bar text
		style,                  // window style
		CW_USEDEFAULT,          // default horizontal position of window
		CW_USEDEFAULT,          // default vertical position of window
		Constants::GAME_WIDTH * Constants::GAME_WINDOW_SCALE,             // width of window
		Constants::GAME_HEIGHT * Constants::GAME_WINDOW_SCALE,            // height of the window
		(HWND)NULL,            // no parent window
		(HMENU)NULL,           // no menu
		hInstance,              // handle to application instance
		(LPVOID)NULL);         // no window parameters

	// if there was an error creating the window
	if (!hwnd)
		return false;

	if (!Constants::FULLSCREEN)             // if window
	{
		// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);   // get size of client area of window
		MoveWindow(
			hwnd,
			0,												// Left
			0,												// Top
			(Constants::GAME_WIDTH * Constants::GAME_WINDOW_SCALE) + (Constants::GAME_WIDTH * Constants::GAME_WINDOW_SCALE - clientRect.right),		// Right
			(Constants::GAME_HEIGHT * Constants::GAME_WINDOW_SCALE) + (Constants::GAME_HEIGHT * Constants::GAME_WINDOW_SCALE - clientRect.bottom),	// Bottom
			TRUE											// Repaint the window
		);
	}

	// Show the window
	ShowWindow(hwnd, nCmdShow);

	return true;
}
