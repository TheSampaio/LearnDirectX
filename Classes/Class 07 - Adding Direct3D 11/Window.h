#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

class Window
{
public:
	// Window's display modes
	enum EDisplayMode
	{
		Bordless = 0,
		Fullscreen,
		Windowed
	};

	Window();

	// === Main Methods ===
	bool Create();
	void Close();

	bool GetKeyPressed(int KeyCode);
	bool GetKeyReleased(int KeyCode);

	// === Get Methods ===
	HWND GetId() const;
	HINSTANCE GetInstance() const;
	std::string GetTitle() const;
	std::array<unsigned int, 2> GetSize() const;
	std::array<unsigned int, 2> GetCenter() const;
	std::array<unsigned int, 2> GetPosition() const;
	unsigned int GetDisplayMode() const;
	COLORREF GetBackgroundColor() const;

	// === Set Methods ===
	void SetSize(unsigned int Width, unsigned int Height);
	void SetTitle(const std::string Title);
	void SetIcon(const unsigned int Icon);
	void SetCursor(const unsigned int Cursor);
	void SetDisplayMode(unsigned int DisplayMode);
	void SetBackgroundColor(unsigned int Red, unsigned int Green, unsigned int Blue);

	// === Static Properties ===
	static bool Keys[256];																		 // Store all keyboard's keys
	static std::array<int, 2> MousePosition;													 // Store mouse's positions
	static LRESULT CALLBACK Procedure(HWND hWindow, UINT Message, WPARAM wParam, LPARAM lParam); // Window's procedure function

private:
	// Window's properties
	HWND m_Id;
	HINSTANCE m_hInstance;
	DWORD m_Style;

	std::string m_Title;
	std::array<unsigned int, 2> m_Size, m_Screen, m_Center, m_Position;
	unsigned int m_DisplayMode;

	HICON m_hIcon;
	HCURSOR m_hCursor;
	COLORREF m_BackgroundColor;
};

#endif
