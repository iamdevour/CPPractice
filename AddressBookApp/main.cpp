#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI
    WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    HWND hwnd;
    WNDCLASSEX wcx;

    wcx.cbSize = sizeof(WNDCLASSEX); // Must always be sizeof(WNDCLASSEX)
    wcx.style = CS_DBLCLKS; // Class styles
    wcx.lpfnWndProc = MainWndProc; // Pointer to callback procedure
    wcx.cbClsExtra = 0; // Extra bytes to allocate following the wndclassex structure
    wcx.cbWndExtra = 0; // Extra bytes to allocate following an instance of the structure
    wcx.hInstance = hInst; // Instance of the application
    wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Class Icon
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW); // Class cursor
    wcx.hbrBackground = (HBRUSH) (COLOR_WINDOW); // Background brush
    wcx.lpszMenuName = NULL; // Menu Resource
    wcx.lpszClassName = "DrawLite"; // Name of this class
    wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Small icon for this class

    // Register this window class with MS-Windows
    if (!RegisterClassEx(&wcx))
        return 0;

    hwnd = CreateWindowEx(0, //Extended window style
            "DrawLite", // Window class name
            "Title Caption", // Window title
            WS_OVERLAPPEDWINDOW, // Window style
            CW_USEDEFAULT, CW_USEDEFAULT, // (x,y) pos of the window
            500, 400, // Width and height of the window
            HWND_DESKTOP, // HWND of the parent window (can be null also)
            NULL, // Handle to menu
            hInst, // Handle to application instance
            NULL); // Pointer to window creation data

    // Check if window creation was successful
    if (!hwnd)
        return 0;
    // Make the window visible
    ShowWindow(hwnd,SW_SHOW);

    // Process messages coming to this window
    while (GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_DESTROY: // User closed the window
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
