#include "PCH.h"
#include "Window.h"

#include "Application.h"

// Initialize static variables
bool CWindow::Keys[256] = { false };
std::array<int, 2> CWindow::Mouse = { 0 };

CWindow::CWindow()
	: m_Id(NULL), m_hInstance (GetModuleHandle(NULL)), m_Style(WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_EX_TOPMOST | WS_VISIBLE)
{
	// Title
	m_Title = std::string("CWindow");

	// Screen's size
	m_Screen[0] = GetSystemMetrics(SM_CXSCREEN);
	m_Screen[1] = GetSystemMetrics(SM_CYSCREEN);

	// CWindow's size
	m_Size[0] = 800;
	m_Size[1] = 600;

	// CWindow's center
	m_Center[0] = m_Size[0] / 2;
	m_Center[1] = m_Size[1] / 2;

	// CWindow's position
	m_Position[0] = 0;
	m_Position[1] = 0;

	// CWindow's icon and cursor
	m_hIcon = NULL;
	m_hCursor = NULL;

	// CWindow's display mode and background's color
	m_DisplayMode = EDisplayMode::WINDOWED;
	m_BackgroundColor = RGB(0, 0, 0);
}

// === Main Methods ===
bool CWindow::Create()
{
	// Create and define window's class
	WNDCLASSEX CWindow{ NULL };
	CWindow.cbSize = sizeof(CWindow);
	CWindow.lpfnWndProc = CWindow::Procedure;
	CWindow.style = CS_HREDRAW | CS_VREDRAW;
	CWindow.cbClsExtra = NULL;
	CWindow.cbWndExtra = NULL;
	CWindow.lpszMenuName = NULL;
	CWindow.hCursor = m_hCursor;
	CWindow.hIcon = m_hIcon;
	CWindow.hIconSm = m_hIcon;
	CWindow.hInstance = m_hInstance;
	CWindow.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(m_BackgroundColor));
	CWindow.lpszClassName = "BasicWindow";

	// Register window's class
	(!RegisterClassEx(&CWindow)) ? false : true;

	// Create window
	m_Id = CreateWindowEx
	(
		NULL,							// CWindow's EXTRA style
		"BasicWindow",					// CWindow's class's name
		m_Title.c_str(),				// CWindow's title
		m_Style,						// CWindow's DEFAULT style
		m_Position[0], m_Position[1],	// CWindow's position
		m_Size[0], m_Size[1],			// CWindow's size
		NULL,							// CWindow's parent
		NULL,							// CWindow's menu
		m_hInstance,					// CWindow's instance (Id)
		NULL							// CWindow's long pointer param
	);

	// Setup client area
	if (m_DisplayMode == EDisplayMode::WINDOWED)
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

void CWindow::Close()
{
	// Send destroy message to the current window
	PostMessage(m_Id, WM_DESTROY, NULL, NULL);
}

bool CWindow::GetKeyPressed(int KeyCode)
{	
	// Return true if key is activate
	return (Keys[KeyCode]) ? true : false;
}

bool CWindow::GetKeyReleased(int KeyCode)
{
	// Return true if key is deactivate
	return (!Keys[KeyCode]) ? true : false;
}

// === Set Methods ===
void CWindow::SetSize(unsigned int Width, unsigned int Height)
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
	if (m_DisplayMode == EDisplayMode::WINDOWED)
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

// Sets window's display mode
void CWindow::SetDisplayMode(unsigned int DisplayMode)
{
	m_DisplayMode = DisplayMode;

	if (DisplayMode == CWindow::EDisplayMode::WINDOWED)
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

// === Procedure ===
LRESULT CALLBACK CWindow::Procedure(HWND hWindow, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	/* ========== KEYBOARD ==================== */
	// If keyboard's key was pressed
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		Keys[wParam] = true;

		if (Keys[VK_F4])
		{
			// Ask if user want to close the window
			if (MessageBox(hWindow, "Do you really want to close the window?", "Window", MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES)
			{
				PostMessage(hWindow, WM_DESTROY, NULL, NULL);
				return 0;
			}

			else
			{
				Keys[VK_F4] = false;
				return 0;
			}
		}

		return 0;

	// If keyboard's key was released
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keys[wParam] = false;
		return 0;

	/* ========== MOUSE ==================== */
	// If mouse move
	case WM_MOUSEMOVE:
		Mouse[0] = GET_X_LPARAM(lParam);
		Mouse[1] = GET_Y_LPARAM(lParam);
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
	// If window was focused
	case WM_SETFOCUS:
		CApplication::Resume();
		return 0;

	// If window NOT was focused
	case WM_KILLFOCUS:
		CApplication::Pause();
		return 0;

	// If window was destroyed
	case WM_DESTROY:
		PostQuitMessage(NULL);
		return 0;

	// Else return default behavior
	default:
		return DefWindowProc(hWindow, Message, wParam, lParam);
	}
}