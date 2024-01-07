#pragma once

// Enumerates all keyboard keys
enum EKeyCode
{
	// Letters keys
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,

	// Alpha numbers
	Alpha0 = 0x30,
	Alpha1 = 0x31,
	Alpha2 = 0x32,
	Alpha3 = 0x33,
	Alpha4 = 0x34,
	Alpha5 = 0x35,
	Alpha6 = 0x36,
	Alpha7 = 0x37,
	Alpha8 = 0x38,
	Alpha9 = 0x39,

	// Numpad keys
	Numpad0 = 0x60,
	Numpad1 = 0x61,
	Numpad2 = 0x62,
	Numpad3 = 0x63,
	Numpad4 = 0x64,
	Numpad5 = 0x65,
	Numpad6 = 0x66,
	Numpad7 = 0x67,
	Numpad8 = 0x68,
	Numpad9 = 0x69,

	Add = 0x6B,
	Subtract = 0x6D,
	Multiply = 0x6A,
	Divide = 0x6F,
	Decimal = 0x6E,

	// Functional keys
	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7A,
	F12 = 0x7B,

	// Arrow keys
	Up = 0x26,
	Down = 0x28,
	Right = 0x27,
	Left = 0x25,

	// Other keys
	Tab = 0x09,
	End = 0x23,
	Esc = 0x1B,
	Menu = 0x12,
	Home = 0x24,
	Minus = 0xBD,
	Space = 0x20,
	Comma = 0xBC,
	Pause = 0x13,
	Return = 0x0D,
	Period = 0xBE,
	Insert = 0x2D,
	Delete = 0x2D,
	Backspace = 0x08,
	Backslash = 0xE2,

	Win = 0x5B,
	Alt = 0x12,
	Shift = 0x10,
	Control = 0x11,

	PageUp = 0x21,
	PageDown = 0x22,

	LockNum = 0x90,
	LockCaps = 0x14,
	LockScroll = 0x091
};

class Window
{
public:
	// Gets the class's static reference
	static Window& GetInstance() { static Window s_Instance; return s_Instance; }

	// === MAIN methods

	// Creates the window
	bool Create();

	// Closes the window
	void Close() { SendMessage(m_hId, WM_CLOSE, 0, 0); }

	// Process all window's events
	void PollEvents();

	// === GET methods

	// Gets window's id
	HWND GetId() const { return m_hId; }

	// Gets window's instance handle
	HINSTANCE GetInstanceHandle() const { return m_hInstance; }

	// Gets window's messages
	MSG GetMessages() const { return m_Messages; }

	// Gets window's title
	std::string GetTitle() const { return m_Title; }

	// Gets screen's size
	std::array<unsigned short, 2> GetScreen() const { return m_Screen; }

	// Gets window's size
	std::array<unsigned short, 2> GetSize() const { return m_Size; }

	// Gets a pressed key
	bool GetKeyPress(EKeyCode KeyCode) { return s_Keys[KeyCode]; }

	// Gets a released key
	bool GetKeyRelease(EKeyCode KeyCode) { return !s_Keys[KeyCode]; }

	// Gets a tapped key
	bool GetKeyTap(EKeyCode KeyCode);

	// === SET methods

	// Sets window's title
	void SetTitle(const char* title) { m_Title = title; }

	// Sets window's size
	void SetSize(unsigned short width, unsigned short height);

protected:
	Window();

	// Deletes copy constructor and assigment operator
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;

private:
	// === Attributes

	HWND m_hId;
	HINSTANCE m_hInstance;
	MSG m_Messages;
	std::string m_Title;
	std::array<unsigned short, 2> m_Screen;
	std::array<unsigned short, 2> m_Size;
	std::array<unsigned short, 2> m_Position;

	// === STATIC attributes

	static bool	s_Keys[256];
	static bool s_Ctrl[256];

	// === STATIC methods

	// Set-up window's behaviour
	static LRESULT CALLBACK Procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
