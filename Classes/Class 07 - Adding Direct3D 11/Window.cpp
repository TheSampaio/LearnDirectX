#include "PCH.h"
#include "Window.h"

// Initialize static variables
bool Window::Keys[256] = { false };
std::array<int, 2> Window::MousePosition = { 0 };

Window::Window()
	: m_Id(NULL), m_hInstance (GetModuleHandle(NULL)), m_Style(WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_EX_TOPMOST | WS_VISIBLE)
{
	// Title
	m_Title = std::string("Window");

	// Screen's size
	m_Screen[0] = GetSystemMetrics(SM_CXSCREEN);
	m_Screen[1] = GetSystemMetrics(SM_CYSCREEN);

	// Window's size
	m_Size[0] = 800;
	m_Size[1] = 600;

	// Window's center
	m_Center[0] = m_Size[0] / 2;
	m_Center[1] = m_Size[1] / 2;

	// Window's position
	m_Position[0] = 0;
	m_Position[1] = 0;

	// Window's icon and cursor
	m_hIcon = NULL;
	m_hCursor = NULL;

	// Window's display mode and background's color
	m_DisplayMode = EDisplayMode::Windowed;
	m_BackgroundColor = RGB(0, 0, 0);
}

// === Main Methods ===
bool Window::Create()
{
	// Create and define window's class
	WNDCLASSEX Window{ NULL };
	Window.cbSize = sizeof(Window);
	Window.lpfnWndProc = Window::Procedure;
	Window.style = CS_HREDRAW | CS_VREDRAW;
	Window.cbClsExtra = NULL;
	Window.cbWndExtra = NULL;
	Window.lpszMenuName = NULL;
	Window.hCursor = m_hCursor;
	Window.hIcon = m_hIcon;
	Window.hIconSm = m_hIcon;
	Window.hInstance = m_hInstance;
	Window.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(m_BackgroundColor));
	Window.lpszClassName = "BasicWindow";

	// Register window's class
	(!RegisterClassEx(&Window)) ? false : true;

	// Create window
	m_Id = CreateWindowEx
	(
		NULL,							// Window's EXTRA style
		"BasicWindow",					// Window's class's name
		m_Title.c_str(),				// Window's title
		m_Style,						// Window's DEFAULT style
		m_Position[0], m_Position[1],	// Window's position
		m_Size[0], m_Size[1],			// Window's size
		NULL,							// Window's parent
		NULL,							// Window's menu
		m_hInstance,					// Window's instance (Id)
		NULL							// Window's long pointer param
	);

	// Setup client area
	if (m_DisplayMode == EDisplayMode::Windowed)
	{
		// Create new rect
		RECT Rect{ 0, 0, static_cast<LONG>(m_Size[0]), static_cast<LONG>(m_Size[1]) };

		// Change current window's rect to the new one
		AdjustWindowRectEx
		(
			&Rect,
			GetWindowStyle(m_Id),
			GetMenu(m_Id) != NULL,
			GetWindowStyle(m_Id)
		);

		// Update window's position
		m_Position[0] = (m_Screen[0] / 2) - ((Rect.right - Rect.left) / 2);
		m_Position[1] = (m_Screen[1] / 2) - ((Rect.bottom - Rect.top) / 2);
	}

	else
	{
		// Update window's position and size
		m_Position[0] = 0;
		m_Position[1] = 0;

		m_Size[0] = m_Screen[0];
		m_Size[1] = m_Screen[1];
	}

	// Apply changes
	MoveWindow(m_Id, m_Position[0], m_Position[1], m_Size[0], m_Size[1], true);
	return (m_Id) ? true : false;
}

void Window::Close()
{
	// Send destroy message to the current window
	PostMessage(m_Id, WM_DESTROY, NULL, NULL);
}

bool Window::GetKeyPressed(int KeyCode)
{	
	// Return true if key is activate
	return (Keys[KeyCode]) ? true : false;
}

bool Window::GetKeyReleased(int KeyCode)
{
	// Return true if key is deactivate
	return (!Keys[KeyCode]) ? true : false;
}

// === Get Methods ===
HWND Window::GetId() const
{
	// Gets window's id
	return m_Id;
}

HINSTANCE Window::GetInstance() const
{
	// Gets application's id
	return m_hInstance;
}

std::string Window::GetTitle() const
{
	// Gets window's title
	return m_Title;
}

std::array<unsigned int, 2> Window::GetSize() const
{
	// Gets window's size
	return m_Size;
}

std::array<unsigned int, 2> Window::GetCenter() const
{
	// Gets window's center
	return m_Center;
}

std::array<unsigned int, 2> Window::GetPosition() const
{
	// Gets window's position
	return m_Position;
}

unsigned int Window::GetDisplayMode() const
{
	// Gets window's display mode
	return m_DisplayMode;
}

COLORREF Window::GetBackgroundColor() const
{
	// Gets window's background color
	return m_BackgroundColor;
}

// === Set Methods ===
void Window::SetSize(unsigned int Width, unsigned int Height)
{	
	// Set new size
	m_Size[0] = Width;
	m_Size[1] = Height;

	// Calculate new center position
	m_Center[0] = m_Size[0] / 2;
	m_Center[1] = m_Size[1] / 2;

	// Get user's screen's size agains (Just to prevent bugs)
	m_Screen[0] = GetSystemMetrics(SM_CXSCREEN);
	m_Screen[1] = GetSystemMetrics(SM_CYSCREEN);

	// Calculate new position based in display mode
	if (m_DisplayMode == EDisplayMode::Windowed)
	{		
		m_Position[0] = (m_Screen[0] / 2) - (m_Size[0] / 2);
		m_Position[1] = (m_Screen[1] / 2) - (m_Size[1] / 2);
	}

	else
	{
		m_Position[0] = 0;
		m_Position[1] = 0;
	}
}

// Sets window's title
void Window::SetTitle(const std::string Title)
{
	m_Title = Title;
}

// Sets window's icon
void Window::SetIcon(const unsigned int Icon)
{
	m_hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(Icon));
}

// Sets window's cursor
void Window::SetCursor(const unsigned int Cursor)
{
	m_hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(Cursor));
}

// Sets window's display mode
void Window::SetDisplayMode(unsigned int DisplayMode)
{
	m_DisplayMode = DisplayMode;

	if (DisplayMode == Window::EDisplayMode::Windowed)
	{
		// Windowed
		m_Style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_EX_TOPMOST | WS_VISIBLE;
	}

	else
	{
		// Fullscreen and Bordless
		m_Style = WS_POPUP | WS_EX_TOPMOST | WS_VISIBLE;
	}
}

// Sets window's background color
void Window::SetBackgroundColor(unsigned int Red, unsigned int Green, unsigned int Blue)
{
	m_BackgroundColor = RGB(Red, Green, Blue);
}

// === Procedure ===
LRESULT CALLBACK Window::Procedure(HWND hWindow, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	/* ========== KEYBOARD ==================== */
	// If keyboard's key was pressed
	case WM_KEYDOWN:
		Keys[wParam] = true;
		return 0;

	// If keyboard's key was released
	case WM_KEYUP:
		Keys[wParam] = false;
		return 0;

	/* ========== MOUSE ==================== */
	// If mouse move
	case WM_MOUSEMOVE:
		MousePosition[0] = GET_X_LPARAM(lParam);
		MousePosition[1] = GET_Y_LPARAM(lParam);
		return 0;

	// If mouse's left button pressed
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		Keys[VK_LBUTTON] = true;
		return 0;

	// If mouse's left button released
	case WM_LBUTTONUP:
		Keys[VK_LBUTTON] = false;
		return 0;

	// If mouse's right button pressed
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		Keys[VK_RBUTTON] = true;
		return 0;

	// If mouse's right button released
	case WM_RBUTTONUP:
		Keys[VK_RBUTTON] = false;
		return 0;

	/* ========== WINDOW ==================== */
	// If window was closed
	case WM_CLOSE:

		// Ask if user want to close the window
		if (MessageBox(hWindow, "Do you really want to close the window?", "Window", MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES)
		{
			PostMessage(hWindow, WM_DESTROY, NULL, NULL);
			return 0;
		}

		else
		{
			return 0;
		}

	// If window was destroyed
	case WM_DESTROY:
		PostQuitMessage(NULL);
		return 0;

	// Else return default behavior
	default:
		return DefWindowProc(hWindow, Message, wParam, lParam);
	}
}