#pragma once

#include <windows.h>
#include <WindowsX.h>
#include <string>
#include <XInput.h>

const int KEYS_ARRAY_LEN = 256;     // size of key arrays

// what values for clear(), bit flag
const UCHAR KEYS_DOWN = 1;
const UCHAR KEYS_PRESSED = 2;
const UCHAR TEXT_IN = 8;
const UCHAR KEYS_TEXT = KEYS_DOWN + KEYS_PRESSED + TEXT_IN;

class InputManager 
{
private:
	bool keysDown[KEYS_ARRAY_LEN];     // true if specified key is down
	bool keysPressed[KEYS_ARRAY_LEN];  // true if specified key was pressed
	std::string textIn;                         // user entered text
	char charIn;                                // last character entered
	bool newLine;                               // true on start of new line
	// Save key down state
	void KeyDown(WPARAM);

	// Save key up state
	void KeyUp(WPARAM);

	// Save the char just entered in textIn string
	void KeyIn(WPARAM);
public:
	InputManager();

	~InputManager();

	// Initialize mouse and controller input.
	// Throws GameError
	// Pre: hwnd = window handle
	// capture = true to capture mouse.
	bool ProccessKeyMessage(UINT msg, WPARAM wParam);

	// Returns true if the specified VIRTUAL KEY is down, otherwise false.
	bool IsKeyDown(UCHAR vkey) const;

	// Return true if the specified VIRTUAL KEY has been pressed in the most recent frame.
	// Key presses are erased at the end of each frame.
	bool WasKeyPressed(UCHAR vkey) const;

	// Return true if any key is down
	bool AnyKeyDown() const;

	// Clear the specified key press
	void ClearKeyPress(UCHAR vkey);

	// Clear specified input buffers where what is any combination of
	// KEYS_DOWN, KEYS_PRESSED, MOUSE, TEXT_IN or KEYS_MOUSE_TEXT.
	// Use OR '|' operator to combine parmeters.
	void Clear(UCHAR what);

	// Clears key and text input data
	void ClearAll();

	// Clear text input buffer
	void ClearTextIn();

	// Return text input as a string
	std::string GetTextIn();

	// Return text input as a string with a limit no of char
	std::string GetTextInWithLimit(int limit, char charLimit);

	// Return last character entered
	char GetCharIn();
};
