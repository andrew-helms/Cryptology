/*
CIS 4362 - Introduction to Cryptology
Final Project
Andrew Helms
12/09/20
*/

#include "framework.h"
#include "ADFGVX_Cipher.h"
#include "adfgvx.h"

#define ID_EBTN 1 //ID of the Erypt Button
#define ID_DBTN 2 //ID of the Decrypt Button
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hEncryptButton; //Encrpyt Button handler
HWND hDecryptButton; //Decrypt Button handler
HWND hPTTextBox; //Plaintext textbox handler
HWND hCTTextBox; //Ciphertext textbox handler
HWND hPSKeyTextBox; //Polyibus Square key textbox handler
HWND hCTKeyTextBox; //Columnar transposition key textbox handler

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ADFGVXCIPHER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ADFGVXCIPHER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ADFGVXCIPHER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ADFGVXCIPHER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: //On window create
        hEncryptButton = CreateWindow(TEXT("BUTTON"), TEXT("Encrypt"), WS_VISIBLE | WS_CHILD, 700, 100, 100, 50, hWnd, (HMENU)ID_EBTN, NULL, NULL); //Create the encrpyt button
        hDecryptButton = CreateWindow(TEXT("BUTTON"), TEXT("Decrypt"), WS_VISIBLE | WS_CHILD, 700, 300, 100, 50, hWnd, (HMENU)ID_DBTN, NULL, NULL); //Create the decrypt button
        hPTTextBox = CreateWindow(TEXT("EDIT"), TEXT("Plaintext"), WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL, 100, 100, 500, 100, hWnd, NULL, NULL, NULL); //Create the plaintext textbox
        hCTTextBox = CreateWindow(TEXT("EDIT"), TEXT("Ciphertext"), WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL, 100, 300, 500, 100, hWnd, NULL, NULL, NULL); //Create the ciphertext textbox
        hPSKeyTextBox = CreateWindow(TEXT("EDIT"), TEXT("Polybius Square Key"), WS_VISIBLE | WS_CHILD | ES_MULTILINE, 100, 500, 100, 100, hWnd, NULL, NULL, NULL); //Create the Polybius Square key textbox
        hCTKeyTextBox = CreateWindow(TEXT("EDIT"), TEXT("Columnar Transpose Key"), WS_VISIBLE | WS_CHILD | ES_MULTILINE, 300, 500, 100, 100, hWnd, NULL, NULL, NULL); //Create the columnar transpositon key textbox

        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            std::string plaintext;
            std::string ciphertext;
            std::string psKey;
            std::string ctKey;
            int len;
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_EBTN: //If the encrypt button was pressed
            {
                len = GetWindowTextLengthW(hPTTextBox);
                len += 1;
                wchar_t* ptext = new wchar_t[len + 1];
                GetWindowTextW(hPTTextBox, ptext, len); //Get the string from the plaintext textbox
                plaintext = CW2A(ptext);

                len = GetWindowTextLengthW(hPSKeyTextBox);
                len += 1;
                wchar_t* pstext = new wchar_t[len + 1];
                GetWindowTextW(hPSKeyTextBox, pstext, len); //Get the string from the Polybius Square key textbox
                psKey = CW2A(pstext);

                len = GetWindowTextLengthW(hCTKeyTextBox);
                len += 1;
                wchar_t* cttext = new wchar_t[len + 1];
                GetWindowTextW(hCTKeyTextBox, cttext, len); //Get the string from the columnar transposition key textbox
                ctKey = CW2A(cttext);

                ciphertext = adfgvxE(psKey, ctKey, plaintext);
                std::wstring stemp = s2ws(ciphertext);
                const wchar_t* ctext = stemp.c_str();
                SetWindowTextW(hCTTextBox, ctext);
            }
                break;
            case ID_DBTN: //If the decrypt button was pressed
            {
                len = GetWindowTextLengthW(hCTTextBox);
                len += 1;
                wchar_t* ctext = new wchar_t[len + 1];
                GetWindowTextW(hCTTextBox, ctext, len); //Get the string from the ciphertext textbox
                ciphertext = CW2A(ctext);

                len = GetWindowTextLengthW(hPSKeyTextBox);
                len += 1;
                wchar_t* pstext = new wchar_t[len + 1];
                GetWindowTextW(hPSKeyTextBox, pstext, len); //Get the string from the Polybius Square key textbox
                psKey = CW2A(pstext);

                len = GetWindowTextLengthW(hCTKeyTextBox);
                len += 1;
                wchar_t* cttext = new wchar_t[len + 1];
                GetWindowTextW(hCTKeyTextBox, cttext, len); //Get the string from the columnar transposition keytextbox
                ctKey = CW2A(cttext);

                plaintext = adfgvxD(psKey, ctKey, ciphertext);
                std::wstring stemp = s2ws(plaintext);
                const wchar_t* ptext = stemp.c_str();
                SetWindowTextW(hPTTextBox, ptext); //Write the new plaintext to the ciphertext textbox
            }
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
