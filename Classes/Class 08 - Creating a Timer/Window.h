#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

class CWindow
{
public:
	// Window's display modes
	enum EDisplayMode
	{
		BORDLESS = 0,
		FULLSCREEN,
		WINDOWED
	};

	CWindow();

	// === Main Methods ===
	bool Create();
	void Close();

	bool GetKeyPressed(int KeyCode);
	bool GetKeyReleased(int KeyCode);

	// === Get Methods ===
	inline HWND GetId() const								{ return m_Id; }
	inline HINSTANCE GetInstance() const					{ return m_hInstance; }
	inline std::string GetTitle() const						{ return m_Title; }
	inline std::array<unsigned int, 2> GetSize() const		{ return m_Size; }
	inline std::array<unsigned int, 2> GetCenter() const	{ return m_Center; }
	inline std::array<unsigned int, 2> GetPosition() const	{ return m_Position; }
	inline unsigned int GetDisplayMode() const				{ return m_DisplayMode; }
	inline COLORREF GetBackgroundColor() const				{ return m_BackgroundColor; }

	// === Set Methods ===
	void SetSize(unsigned int Width, unsigned int Height);
	void SetDisplayMode(unsigned int DisplayMode);

	inline void SetTitle(const std::string Title)											{ m_Title = Title; }
	inline void SetIcon(const unsigned int Icon)											{ m_hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(Icon)); }
	inline void SetCursor(const unsigned int Cursor)										{ m_hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(Cursor)); }
	inline void SetBackgroundColor(unsigned int Red, unsigned int Green, unsigned int Blue)	{ m_BackgroundColor = RGB(Red, Green, Blue); }

	// === Static Properties ===
	static bool Keys[256];																		 // Store all keyboard's keys
	static std::array<int, 2> Mouse;															 // Store mouse's positions
	static LRESULT CALLBACK Procedure(HWND hWindow, UINT Message, WPARAM wParam, LPARAM lParam); // Window's procedure function

private:
	// Window's properties
	HWND m_Id;
	HINSTANCE m_hInstance;
	DWORD m_Style;

	std::string m_Title;
	std::array<unsigned int, 2> m_Size;
	std::array<unsigned int, 2> m_Screen;
	std::array<unsigned int, 2> m_Center;
	std::array<unsigned int, 2> m_Position;
	unsigned int m_DisplayMode;

	HICON m_hIcon;
	HCURSOR m_hCursor;
	COLORREF m_BackgroundColor;
};

#endif
