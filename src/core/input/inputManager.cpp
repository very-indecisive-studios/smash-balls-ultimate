#include "inputManager.h"
#include <iostream>

InputManager::InputManager() 
{
	// clear key down array
	for (size_t i = 0; i < KEYS_ARRAY_LEN; i++)
		keysDown[i] = false;
	// clear key pressed array
	for (size_t i = 0; i < KEYS_ARRAY_LEN; i++)
		keysPressed[i] = false;
	newLine = true;                     // start new line
	textIn = "";                        // clear textIn
	charIn = 0;                         // clear charIn
}

InputManager::~InputManager() { }

bool InputManager::ProccessKeyMessage(UINT msg, WPARAM wParam)
{
	switch (msg) 
	{
	case WM_KEYDOWN: 
	case WM_SYSKEYDOWN:    // key down
		KeyDown(wParam);
		return true;
	case WM_KEYUP: 
	case WM_SYSKEYUP:        // key up
		KeyUp(wParam);
		return true;
	case WM_CHAR:                           // character entered
		KeyIn(wParam);
		return true;
	}

	return false;
}

// Set true in the keysDown and keysPessed array for this key
// Pre: wParam contains the virtual key code (0--255)
void InputManager::KeyDown(WPARAM wParam)
{
	// make sure key code is within buffer range
	if (wParam < KEYS_ARRAY_LEN)
	{
		keysDown[wParam] = true;    // update keysDown array
		// key has been "pressed, erased by clear()
		keysPressed[wParam] = true; // update keysPressed array
	}
}

// Set false in the keysDown array for this key
// Pre: wParam contains the virtual key code (0--255)
void InputManager::KeyUp(WPARAM wParam)
{
	// make sure key code is within buffer range
	if (wParam < KEYS_ARRAY_LEN)
		// update state table
		keysDown[wParam] = false;
}

// Save the char just entered in textIn string
// Pre: wParam contains the char
void InputManager::KeyIn(WPARAM wParam)
{
	if (newLine)                            // if start of new line
	{
		textIn.clear();
		newLine = false;
	}

	if (wParam == '\b')                     // if backspace
	{
		if (textIn.length() > 0)             // if characters exist
			textIn.erase(textIn.size() - 1);  // erase last character entered
	}
	else
	{
		textIn += wParam;                   // add character to textIn
		charIn = wParam;                    // save last char entered
	}

	if ((char)wParam == '\r')               // if return    
		newLine = true;                     // start new line
}

// Returns true if the specified VIRTUAL KEY is down, otherwise false.
bool InputManager::IsKeyDown(UCHAR vkey) const
{
	if (vkey < KEYS_ARRAY_LEN)
		return keysDown[vkey];
	else
		return false;
}

// Return true if the specified VIRTUAL KEY has been pressed in the most recent frame. Key presses are erased at the end of each frame.
bool InputManager::WasKeyPressed(UCHAR vkey) const
{
	if (vkey < KEYS_ARRAY_LEN)
		return keysPressed[vkey];
	else
		return false;
}

// Return true if any key was pressed in the most recent frame.
// Key presses are erased at the end of each frame.
bool InputManager::AnyKeyDown() const
{
	for (size_t i = 0; i < KEYS_ARRAY_LEN; i++)
		if (keysDown[i] == true)
			return true;
	return false;
}

// Clear the specified key press
void InputManager::ClearKeyPress(UCHAR vkey)
{
	if (vkey < KEYS_ARRAY_LEN)
		keysPressed[vkey] = false;
}

// Clear specified input buffers
void InputManager::Clear(UCHAR what)
{
	if (what & KEYS_DOWN)       // if clear keys down
	{
		for (size_t i = 0; i < KEYS_ARRAY_LEN; i++)
			keysDown[i] = false;
	}
	if (what & KEYS_PRESSED)    // if clear keys pressed
	{
		for (size_t i = 0; i < KEYS_ARRAY_LEN; i++)
			keysPressed[i] = false;
	}
	if (what & TEXT_IN)
	{
		ClearTextIn();
	}
}

void InputManager::ClearAll() 
{
	Clear(KEYS_TEXT);
}

void InputManager::ClearTextIn() 
{
	textIn.clear();
}

std::string InputManager::GetTextIn()
{
	return textIn;
}

std::string InputManager::GetTextInWithLimit(int limit, char charLimit)
{
	if (textIn.length() > limit ) // erase last character entered if past limit
	{
		textIn.erase(textIn.size() - 1);
	}

	if (!textIn.empty() && textIn[textIn.size() - 1] == charLimit) // if last char is charLimit 
	{
		textIn.erase(textIn.size() - 1);
	}

	return textIn;
}

char InputManager::GetCharIn() 
{ 
	return charIn;
}