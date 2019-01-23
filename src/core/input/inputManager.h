#pragma once

#include <windows.h>
#include <WindowsX.h>
#include <string>
#include <XInput.h>

// for high-definition mouse
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif

const int KEYS_ARRAY_LEN = 256;     // size of key arrays

// what values for clear(), bit flag
const UCHAR KEYS_DOWN = 1;
const UCHAR KEYS_PRESSED = 2;
const UCHAR MOUSE = 4;
const UCHAR TEXT_IN = 8;
const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;

class InputManager 
{
private:
	bool keysDown[KEYS_ARRAY_LEN];     // true if specified key is down
	bool keysPressed[KEYS_ARRAY_LEN];  // true if specified key was pressed
	std::string textIn;                         // user entered text
	char charIn;                                // last character entered
	bool newLine;                               // true on start of new line

	int  mouseX, mouseY;                        // mouse screen coordinates
	int  mouseRawX, mouseRawY;                  // high-definition mouse data
	RAWINPUTDEVICE Rid[1];                      // for high-definition mouse
	bool mouseCaptured;                         // true if mouse captured
	bool mouseLButton;                          // true if left mouse button down
	bool mouseMButton;                          // true if middle mouse button down
	bool mouseRButton;                          // true if right mouse button down
	bool mouseX1Button;                         // true if X1 mouse button down
	bool mouseX2Button;                         // true if X2 mouse button down

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
	//      capture = true to capture mouse.
	void Initialize(HWND hwnd, bool capture);

	bool ProccessKeyMessage(UINT msg, WPARAM wParam, LPARAM lParam);

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

	// Reads mouse screen position into mouseX, mouseY
	void MouseIn(LPARAM);

	// Reads raw mouse data into mouseRawX, mouseRawY
	// This routine is compatible with a high-definition mouse
	void MouseRawIn(LPARAM);

	// Save state of mouse button
	void SetMouseLButton(bool b) { mouseLButton = b; }

	// Save state of mouse button
	void SetMouseMButton(bool b) { mouseMButton = b; }

	// Save state of mouse button
	void SetMouseRButton(bool b) { mouseRButton = b; }

	// Save state of mouse button
	void SetMouseXButton(WPARAM wParam) {
		mouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
		mouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
	}
	// Return mouse X position
	int  GetMouseX()        const { return mouseX; }

	// Return mouse Y position
	int  GetMouseY()        const { return mouseY; }

	// Return raw mouse X movement. Left is <0, Right is >0
	// Compatible with high-definition mouse.
	int  GetMouseRawX()     const { return mouseRawX; }

	// Return raw mouse Y movement. Up is <0, Down is >0
	// Compatible with high-definition mouse.
	int  GetMouseRawY()     const { return mouseRawY; }

	// Return state of left mouse button.
	bool GetMouseLButton()  const { return mouseLButton; }

	// Return state of middle mouse button.
	bool GetMouseMButton()  const { return mouseMButton; }

	// Return state of right mouse button.
	bool GetMouseRButton()  const { return mouseRButton; }

	// Return state of X1 mouse button.
	bool GetMouseX1Button() const { return mouseX1Button; }

	// Return state of X2 mouse button.
	bool GetMouseX2Button() const { return mouseX2Button; }
};
