#include "pch.h"

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

	 // mouse data
	mouseX = 0;                         // screen X
	mouseY = 0;                         // screen Y
	mouseRawX = 0;                      // high-definition X
	mouseRawY = 0;                      // high-definition Y
	mouseLButton = false;               // true if left mouse button is down
	mouseMButton = false;               // true if middle mouse button is down
	mouseRButton = false;               // true if right mouse button is down
	mouseX1Button = false;              // true if X1 mouse button is down
	mouseX2Button = false;              // true if X2 mouse button is down
}

InputManager::~InputManager() { }

void InputManager::Initialize(HWND hwnd, bool capture)
{
	mouseCaptured = capture;

	// register high-definition mouse
	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	Rid[0].dwFlags = RIDEV_INPUTSINK;
	Rid[0].hwndTarget = hwnd;
	RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

	if (mouseCaptured)
		SetCapture(hwnd);           // capture mouse
}

bool InputManager::ProccessKeyMessage(UINT msg, WPARAM wParam, LPARAM lParam)
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
	case WM_MOUSEMOVE:                      // mouse moved
		MouseIn(lParam);
		return 0;
	case WM_INPUT:                          // raw mouse data in
		MouseRawIn(lParam);
		return 0;
	case WM_LBUTTONDOWN:                    // left mouse button down
		SetMouseLButton(true);
		MouseIn(lParam);             // mouse position
		return 0;
	case WM_LBUTTONUP:                      // left mouse button up
		SetMouseLButton(false);
		MouseIn(lParam);             // mouse position
		return 0;
	case WM_MBUTTONDOWN:                    // middle mouse button down
		SetMouseMButton(true);
		MouseIn(lParam);             // mouse position
		return 0;
	case WM_MBUTTONUP:                      // middle mouse button up
		SetMouseMButton(false);
		MouseIn(lParam);             // mouse position
		return 0;
	case WM_RBUTTONDOWN:                    // right mouse button down
		SetMouseRButton(true);
		MouseIn(lParam);             // mouse position
		return 0;
	case WM_RBUTTONUP:                      // right mouse button up
		SetMouseRButton(false);
		MouseIn(lParam);             // mouse position
		return 0;
	case WM_XBUTTONDOWN: case WM_XBUTTONUP: // mouse X button down/up
		SetMouseXButton(wParam);
		MouseIn(lParam);             // mouse position
		return 0;
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
	Clear(KEYS_MOUSE_TEXT);
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

// Reads mouse screen position into mouseX, mouseY
void InputManager::MouseIn(LPARAM lParam)
{
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);
}

// Reads raw mouse data into mouseRawX, mouseRawY
// This routine is compatible with a high-definition mouse
void InputManager::MouseRawIn(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT,
		lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		mouseRawX = raw->data.mouse.lLastX;
		mouseRawY = raw->data.mouse.lLastY;
	}
}