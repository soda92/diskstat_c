#define UNICODE
#define  _UNICODE
#include <windows.h>
#include <CommCtrl.h>

static int button_id =1;
static int p0 = 0;
HWND g_wndPB;
static int g_width = 800;
static int g_height = 600;

static int pbar_width = 400;
static int pbar_height = 100;

// Window procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE: {
    RECT rcClient;
    GetClientRect(hwnd, &rcClient);

    int cyVScroll = GetSystemMetrics(SM_CYVSCROLL);

    HWND hwndPB = CreateWindowEx(
        0, PROGRESS_CLASS, (LPTSTR)NULL, WS_CHILD | WS_VISIBLE, rcClient.left,
        rcClient.bottom - cyVScroll, rcClient.right, cyVScroll, hwnd, (HMENU)0,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    g_wndPB = hwndPB;

    SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, 5));
    SendMessage(hwndPB, PBM_SETSTEP, (WPARAM)1, 0);
    SendMessage(hwndPB, PBM_SETPOS, 2, 0);

    // Create a button
    HWND hwndButton = CreateWindowEx(
        0,
        L"BUTTON", // Predefined class; Unicode assumed
        L"OK",     // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        10,                                                    // x position
        10,                                                    // y position
        200,                                                   // Button width
        40,                                                    // Button height
        hwnd,                                                  // Parent window
        (HMENU)button_id, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL); // Pointer not needed.
    return 0;
  }
    case WM_COMMAND:
      if (LOWORD(wParam) == button_id) {
        SendMessage(g_wndPB, PBM_STEPIT, 0, 0);
      }
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
  InitCommonControls();
  // Register the window class
  const wchar_t CLASS_NAME[] = L"MyWindowClass";

  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  RECT r;
  GetClientRect(GetDesktopWindow(), &r);

  RECT clientRect = {0, 0, g_width, g_height}; // Desired client area size
  DWORD windowStyle = WS_OVERLAPPEDWINDOW;
  DWORD extendedStyle = 0;

  AdjustWindowRectEx(&clientRect, windowStyle, FALSE, extendedStyle);

  int windowWidth = clientRect.right - clientRect.left;
  int windowHeight = clientRect.bottom - clientRect.top;

  int pos_x = (r.right - windowWidth)/2;
  int pos_y = (r.bottom* 33/35 - windowHeight) /2;

  // Create the window
  HWND hwnd = CreateWindowEx(
    0, // Optional window styles
    CLASS_NAME, // Window class name
    L"Disk Size Used", // Window text
    WS_OVERLAPPEDWINDOW, // Window style

    // position and size
    pos_x, pos_y, windowWidth, windowHeight,

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
