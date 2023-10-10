// WindowsProject2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
double num1 = 0.0, num2 = 0.0, result = 0.0;
int operation = 0; // 0 - сложение, 1 - вычитание
WCHAR szStudentInfo[MAX_LOADSTRING] = L"ФИО: Жуковская Дарья Вячеславовна\nКурс: 4\nГруппа: 4\nГод: 2023";
double GetDlgItemDouble(HWND hDlg, int nIDDlgItem);
void SetDlgItemDouble(HWND hDlg, int nIDDlgItem, double value);

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // Создадим текстовые поля для ввода чисел.
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER ,
            50, 50, 150, 25, hWnd, (HMENU)101, NULL, NULL);

        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER ,
            250, 50, 150, 25, hWnd, (HMENU)102, NULL, NULL);

        // Создадим выпадающий список для выбора операции.
        CreateWindowW(L"ComboBox", L"", CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD,
            150, 100, 100, 100, hWnd, (HMENU)103, NULL, NULL);
        SendMessage(GetDlgItem(hWnd, 103), CB_ADDSTRING, 0, (LPARAM)L"Сложение");
        SendMessage(GetDlgItem(hWnd, 103), CB_ADDSTRING, 0, (LPARAM)L"Вычитание");

        // Создадим кнопку для выполнения вычислений.
        CreateWindowW(L"BUTTON", L"Вычислить", WS_VISIBLE | WS_CHILD,
            150, 150, 100, 30, hWnd, (HMENU)104, NULL, NULL);

        // Создадим поле для вывода результата.
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
            150, 200, 150, 25, hWnd, (HMENU)105, NULL, NULL);

        // Создадим поле для отображения информации о студенте.
        CreateWindowW(L"STATIC", szStudentInfo, WS_VISIBLE | WS_CHILD,
            50, 250, 300, 50, hWnd, NULL, NULL, NULL);
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
            // Обработаем нажатие кнопки "Вычислить".
        case 104:
        {
            // Считаем числа из текстовых полей.
            num1 = GetDlgItemDouble(hWnd, 101);
            num2 = GetDlgItemDouble(hWnd, 102);

            // Считаем выбранную операцию из выпадающего списка.
            operation = SendMessage(GetDlgItem(hWnd, 103), CB_GETCURSEL, 0, 0);

            // Выполним вычисления в зависимости от выбранной операции.
            if (operation == 0) // Сложение
                result = num1 + num2;
            else if (operation == 1) // Вычитание
                result = num1 - num2;

            // Проверим диапазон результата.
            if (result < -1000000000000.0 || result > 1000000000000.0)
            {
                MessageBox(hWnd, L"Результат вычислений выходит за пределы допустимого диапазона.", L"Ошибка", MB_OK | MB_ICONERROR);
                result = 0.0;
            }

            // Выведем результат в текстовое поле.
            SetDlgItemDouble(hWnd, 105, result);
        }
        break;
        }
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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
// Вспомогательная функция для проверки, состоит ли строка только из цифр, точек и запятых.
bool IsNumericString(const wchar_t* str)
{
    for (size_t i = 0; i < wcslen(str); ++i)
    {
        if (!iswdigit(str[i]) && str[i] != L'.' && str[i] != L',' && str[i] != L'-')
            return false;
    }
    return true;
}
// Вспомогательная функция для получения числа из текстового поля.
double GetDlgItemDouble(HWND hDlg, int nIDDlgItem)
{
    wchar_t buffer[256];
    GetDlgItemTextW(hDlg, nIDDlgItem, buffer, sizeof(buffer) / sizeof(buffer[0]));

    // Проверяем, состоит ли строка только из цифр, точек и запятых.
    if (!IsNumericString(buffer))
    {
        MessageBox(hDlg, L"Пожалуйста, введите только числа.", L"Ошибка", MB_OK | MB_ICONERROR);
        return 0.0;
    }

    // Заменяем запятую на точку перед преобразованием в число.
    for (size_t i = 0; i < wcslen(buffer); ++i)
    {
        if (buffer[i] == L',')
            buffer[i] = L'.';
    }

    double value = wcstod(buffer, NULL);

    // Проверяем диапазон числа.
    if (value < -1000000000000.0 || value > 1000000000000.0)
    {
        MessageBox(hDlg, L"Число выходит за пределы допустимого диапазона.", L"Ошибка", MB_OK | MB_ICONERROR);
        return 0.0;
    }

    return value;
}


// Вспомогательная функция для установки значения в текстовое поле.
void SetDlgItemDouble(HWND hDlg, int nIDDlgItem, double value)
{
    wchar_t buffer[256];
    swprintf_s(buffer, L"%.6f", value);

    // Заменяем точку на запятую перед установкой значения.
    for (size_t i = 0; i < wcslen(buffer); ++i)
    {
        if (buffer[i] == L'.')
            buffer[i] = L',';
    }

    SetDlgItemTextW(hDlg, nIDDlgItem, buffer);
}
// Обработчик сообщений для окна "О программе".
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
