// DrawingShapes.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#include "framework.h"
#include "DrawingShapes.h"

#define MAX_LOADSTRING 100

// Globale Variablen:
HINSTANCE hInst;                                // Aktuelle Instanz
WCHAR szTitle[MAX_LOADSTRING];                  // Titelleistentext
WCHAR szWindowClass[MAX_LOADSTRING];            // Der Klassenname des Hauptfensters.

std::vector<std::shared_ptr<GeoForm>> vecGeoForms;

// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
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

    // TODO: Hier Code einfügen.

    // Globale Zeichenfolgen initialisieren
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DRAWINGSHAPES, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Anwendungsinitialisierung ausführen:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAWINGSHAPES));

    MSG msg;

    // Hauptnachrichtenschleife:
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
//  FUNKTION: MyRegisterClass()
//
//  ZWECK: Registriert die Fensterklasse.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAWINGSHAPES));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DRAWINGSHAPES);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKTION: InitInstance(HINSTANCE, int)
//
//   ZWECK: Speichert das Instanzenhandle und erstellt das Hauptfenster.
//
//   KOMMENTARE:
//
//        In dieser Funktion wird das Instanzenhandle in einer globalen Variablen gespeichert, und das
//        Hauptprogrammfenster wird erstellt und angezeigt.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Instanzenhandle in der globalen Variablen speichern

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   if (!AllocConsole()) {
       return FALSE;
   }
   else {
       // std::cin, std::cout und std::cerr in Konsole umleiten.
       FILE* fTmp;
       freopen_s(&fTmp, "CONIN$", "r", stdin);
       freopen_s(&fTmp, "CONOUT$", "w", stdout);
       freopen_s(&fTmp, "CONOUT$", "w", stderr);
       std::cin.clear();
       std::cout.clear();
       std::cerr.clear();
       std::clog.clear();

       // Für wcin & etc.
       HANDLE hConsoleIn = CreateFile(_T("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
       HANDLE hConsoleOut = CreateFile(_T("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
       SetStdHandle(STD_INPUT_HANDLE, hConsoleIn);
       SetStdHandle(STD_OUTPUT_HANDLE, hConsoleOut);
       SetStdHandle(STD_ERROR_HANDLE, hConsoleOut);
       std::wcin.clear();
       std::wcout.clear();
       std::wcerr.clear();
       std::wclog.clear();

       // Initialisiere Formen vor dem Draw - Call
       InitShapes();
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ZWECK: Verarbeitet Meldungen für das Hauptfenster.
//
//  WM_COMMAND  - Verarbeiten des Anwendungsmenüs
//  WM_PAINT    - Darstellen des Hauptfensters
//  WM_DESTROY  - Ausgeben einer Beendenmeldung und zurückkehren
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Menüauswahl analysieren:
            switch (wmId)
            {
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
            // TODO: Zeichencode, der hdc verwendet, hier einfügen...
            
            // Transparente
            SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

            std::vector<std::shared_ptr<GeoForm>>::iterator vecIterator;
            for (vecIterator = vecGeoForms.begin(); vecIterator != vecGeoForms.end(); vecIterator++) {
                GeoForm* tmpForm = vecIterator->get();
                tmpForm->RufeAnzeige();
                tmpForm->Zeichne(hdc, ps);
            }

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

// Meldungshandler für Infofeld.
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

void InitShapes() {
    vecGeoForms = std::vector<std::shared_ptr<GeoForm>>();

    // Linien.
    Linie linie1 = Linie(Punkt(100, 100), Punkt(200, 300), _T("Linie 1"));
    Linie linie2 = Linie(Punkt(200, 100), Punkt(150, 90), _T("Linie 2"));

    vecGeoForms.push_back(_AP_GEOFORM_TO_SHARED_PTR(Linie, linie1));
    vecGeoForms.push_back(_AP_GEOFORM_TO_SHARED_PTR(Linie, linie2));

    // Kreise.
    Kreis kreis1 = Kreis(Punkt(200, 200), 100, _T("Kreis 1"));
    Kreis kreis2 = Kreis(Punkt(200, 200), 50, _T("Kreis 2"));
    Kreis kreis3 = Kreis(Punkt(100, 200), 75, _T("Kreis 3"));

    vecGeoForms.push_back(_AP_GEOFORM_TO_SHARED_PTR(Kreis, kreis1));
    vecGeoForms.push_back(_AP_GEOFORM_TO_SHARED_PTR(Kreis, kreis2));
    vecGeoForms.push_back(_AP_GEOFORM_TO_SHARED_PTR(Kreis, kreis3));

    // Rechtecke
    Rechteck rechteck1 = Rechteck(Punkt(200, 350), Punkt(320, 500), Punkt(300, 10), Punkt(500, 100), _T("Rechteck 1"));
    Rechteck rechteck2 = Rechteck(Punkt(10, 10), Punkt(60, 10), Punkt(60, 30), Punkt(10, 30), _T("Fläche"));
    vecGeoForms.push_back(_AP_GEOFORM_TO_SHARED_PTR(Rechteck, rechteck1));
    vecGeoForms.push_back(_AP_GEOFORM_TO_SHARED_PTR(Rechteck, rechteck2));
}
