#include "PCH.h"
#include "Window.h"

bool Window::s_Keys[256] = { false };
bool Window::s_Ctrl[256] = { false };

void Window::SetSize(unsigned short width, unsigned short height)
{
	m_Size = { width, height };

	// Recalculates window's position
	m_Position = { static_cast<unsigned short>(m_Screen[0] / 2 - m_Size[0] / 2), static_cast<unsigned short>(m_Screen[1] / 2 - m_Size[1] / 2) };
}

Window::Window()
	: m_hId(nullptr), m_hInstance(nullptr)
{
	m_hInstance = GetModuleHandle(0);
	m_Messages = { 0 };
	m_Title = "Window";
	m_Screen = { static_cast<unsigned short>(GetSystemMetrics(SM_CXSCREEN)), static_cast<unsigned short>(GetSystemMetrics(SM_CYSCREEN)) };
	m_Size = { 800, 600 };
	m_Position = { static_cast<unsigned short>(m_Screen[0] / 2 - m_Size[0] / 2), static_cast<unsigned short>(m_Screen[1] / 2 - m_Size[1] / 2) };
}

bool Window::Create()
{
	// Defines and registers a new "Window" class
	std::wstring wndClassName = L"Window";

	WNDCLASS wnd{};
	wnd.lpfnWndProc = Window::Procedure;
	wnd.hInstance = m_hInstance;
	wnd.lpszClassName = wndClassName.c_str();

	RegisterClass(&wnd);

	// Creates the registered window
	m_hId = CreateWindowEx(
		0,															// Optional window styles
		wndClassName.c_str(),										// Window class
		std::wstring(m_Title.begin(), m_Title.end()).c_str(),		// Window text
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,	// Window style
		m_Position[0], m_Position[1],								// Position
		m_Size[0], m_Size[1],										// Size
		nullptr,													// Parent window
		nullptr,													// Menu
		m_hInstance,												// Instance handle
		nullptr														// Additional application data
	);

	return (m_hId) ? true : false;
}

void Window::PollEvents()
{
	// Translate and dispatch messages (Events) continually
	if (PeekMessage(&m_Messages, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_Messages);
		DispatchMessage(&m_Messages);
	}
}

bool Window::GetKeyTap(EKeyCode keyCode)
{
	if (s_Ctrl[keyCode])
	{
		if (GetKeyRelease(keyCode))
		{
			s_Ctrl[keyCode] = false;
			return true;
		}
	}

	else if (GetKeyPress(keyCode))
		s_Ctrl[keyCode] = true;

	return false;
}

LRESULT Window::Procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SYSKEYUP:
		s_Keys[wParam] = false;
		return 0;

	case WM_SYSKEYDOWN:
		s_Keys[wParam] = true;

		if (s_Keys[F4])
		{
			SendMessage(Window::GetInstance().m_hId, WM_DESTROY, 0, 0);
			s_Keys[F4] = false;
		}

		return 0;

	case WM_KEYUP:
		s_Keys[wParam] = false;
		return 0;

	case WM_KEYDOWN:
		s_Keys[wParam] = true;
		return 0;


	case WM_DESTROY:
		PostQuitMessage(WM_DESTROY);
		return 0;

	case WM_CLOSE:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
