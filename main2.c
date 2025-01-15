#define UNICODE
#define  _UNICODE
#include <windows.h>

// Window procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_CREATE: {
      // Create a button
      HWND hwndButton = CreateWindowEx(
        0,
        L"BUTTON",  // Predefined class; Unicode assumed
        L"OK",      // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        10,         // x position
        10,         // y position
        200,        // Button width
        40,        // Button height
        hwnd,     // Parent window
        (HMENU)1,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
      return 0;
    }
    case WM_COMMAND:
      if (LOWORD(wParam) == 1) { // Button ID
        MessageBox(hwnd, L"Button clicked!", L"Information", MB_OK);
      }
      return 0;
    case WM_USER + 2:
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
                   int nCmdShow) {
  // Register the window class
  const wchar_t CLASS_NAME[] = L"MyWindowClass";

  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  // Create the window
  HWND hwnd = CreateWindowEx(
    0, // Optional window styles
    CLASS_NAME, // Window class name
    L"Simple Win32 App", // Window text
    WS_OVERLAPPEDWINDOW | WS_SYSMENU | WS_CAPTION |WS_VSCROLL |WS_MAXIMIZE, // Window style

    // Size and position
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

    NULL, // Parent window
    NULL, // Menu
    hInstance, // Instance handle
    NULL // Additional application data
  );

  if (hwnd == NULL) {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  // Message loop
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
