// Lab_calulator.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab_calulator.h"
#include <string>
#include "BigNumber.h"
#include <iostream>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
std::string result;
int operation = 0; // 0 - сложение, 1 - вычитание
std::string Err1 = "-1000000000000.0", Err2 = "1000000000000.0";
bgn::BigNumber e1 = Err1;
bgn::BigNumber e2 = Err2;
WCHAR szStudentInfo[MAX_LOADSTRING] = L"ФИО: Жуковская Дарья Вячеславовна\nКурс: 4\nГруппа: 4\nГод: 2023";
std::string GetDlgItemDouble(HWND hDlg, int nIDDlgItem);
void SetDlgItemDouble(HWND hDlg, int nIDDlgItem, std::string value);
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
    LoadStringW(hInstance, IDC_LABCALULATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABCALULATOR));

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
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABCALULATOR));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LABCALULATOR);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            50, 50, 200, 25, hWnd, (HMENU)101, NULL, NULL);

        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            300, 50, 200, 25, hWnd, (HMENU)102, NULL, NULL);

        // Создадим выпадающий список для выбора операции.
        CreateWindowW(L"ComboBox", L"", CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD,
            225, 100, 100, 100, hWnd, (HMENU)103, NULL, NULL);
        SendMessage(GetDlgItem(hWnd, 103), CB_ADDSTRING, 0, (LPARAM)L"Сложение");
        SendMessage(GetDlgItem(hWnd, 103), CB_ADDSTRING, 0, (LPARAM)L"Вычитание");
        SendMessage(GetDlgItem(hWnd, 103), CB_ADDSTRING, 0, (LPARAM)L"Умножение");
        SendMessage(GetDlgItem(hWnd, 103), CB_ADDSTRING, 0, (LPARAM)L"Деление");

        // Создадим кнопку для выполнения вычислений.
        CreateWindowW(L"BUTTON", L"Вычислить", WS_VISIBLE | WS_CHILD,
            225, 150, 100, 30, hWnd, (HMENU)104, NULL, NULL);

        // Создадим поле для вывода результата.
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
            175, 200, 200, 25, hWnd, (HMENU)105, NULL, NULL);

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
            std::string nu1 = GetDlgItemDouble(hWnd, 101);
            std::string nu2 = GetDlgItemDouble(hWnd, 102);
            bgn::BigNumber num1 = nu1;
            bgn::BigNumber num2 = nu2;
            // Считаем выбранную операцию из выпадающего списка.
            operation = SendMessage(GetDlgItem(hWnd, 103), CB_GETCURSEL, 0, 0);
            std::string nul = "0.0";
            bgn::BigNumber nu = nul;
            // Выполним вычисления в зависимости от выбранной операции.
            if (operation == 0) // Сложение
                result = num1 + num2;
            else if (operation == 1) // Вычитание
                result = num1 - num2;
            else if (operation == 2)
                result = num1 * num2;
            else if (operation == 3) {
                if (num2 == nu) {
                    MessageBox(hWnd, L"Деление на ноль запрещено", L"Ошибка", MB_OK | MB_ICONERROR);
                    result = 0.0;
                }
                result = num1 / num2;
            }

            bgn::BigNumber res = result;
            if (nu1 == "Err" || nu2 == "Err") {
                result = 0.0;
            }
            // Проверим диапазон результата.
            if (res < e1 || res > e2)
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
bool IsNumericString(const wchar_t* str)
{
    for (size_t i = 0; i < wcslen(str); ++i)
    {
        if (!iswdigit(str[i]) && str[i] != L'.' && str[i] != L',' && str[0] != L'-' && str[i] != L' ') {
            return false;
        }
    }

    return true;
}
bool HaveSpace(const wchar_t* str)
{
    for (size_t i = 0; i < wcslen(str); ++i)
    {
        if (str[i] == L' ') {
            return true;
        }
    }

    return false;
}
bool WithGoodSpace(std::string str)
{
    std::wstring float1, integer1, end;
    std::wstring wstr = std::wstring(str.begin(), str.end());
    std::string min = "- ";
    std::wstring wmin = std::wstring(min.begin(), min.end());

    size_t found1 = wstr.find('.');
    integer1 = wstr;
    if (found1 != std::string::npos) {
        integer1 = wstr.substr(0, found1);
        float1 = wstr.substr(found1 + 1, wstr.size() - found1);
    }

    if (integer1.at(0) == min.at(0)) {
        integer1 = integer1.substr(1, integer1.size() - 1);
    }

    int sizeInt = integer1.size();

    int numSpace = 0;
    if (sizeInt > 3) {
        if (sizeInt % 4 == 0) {
            return false;
        }
        else {
            numSpace = sizeInt / 4;
        }
    }
    if (numSpace > 0) {
        reverse(integer1.begin(), integer1.end());
        for (int i = 1; i < numSpace + 1; i++) {
            if (integer1.at(4 * i - 1) != min.at(1)) {
                return false;
            }
        }
    }
    for (int i = 0; i < float1.size(); i++) {
        if (!iswdigit(float1[i])) {
            return false;
        }
    }
    return true;
}
std::string NormalStr(std::string notnorm) {
    std::string float1, integer1;
    std::string min = "- ";
    std::string norm = "";
    size_t found1 = notnorm.find('.');
    integer1 = notnorm;
    if (found1 != std::string::npos) {
        integer1 = notnorm.substr(0, found1);
        float1 = notnorm.substr(found1 + 1, notnorm.size() - found1);
    }
    int sizeInt = integer1.size();
    bool isNegat = false;
    if (integer1.at(0) == min.at(0)) {
        isNegat = true;
        integer1 = integer1.substr(1, integer1.size() - 1);
    }

    int numSpace;
    numSpace = sizeInt / 4;
    if (numSpace > 0) {
        for (int i = 1; i < numSpace + 1; i++) {
            integer1.erase(std::find(integer1.begin(), integer1.end(), ' '));
        }
    }
    if (isNegat) {
        reverse(integer1.begin(), integer1.end());
        integer1.push_back(min[0]);
        reverse(integer1.begin(), integer1.end());
    }
    if (float1.size() > 0) {
        norm = integer1 + "." + float1;
    }
    else { norm = integer1; }
    return norm;

}
// Вспомогательная функция для получения числа из текстового поля.
std::string GetDlgItemDouble(HWND hDlg, int nIDDlgItem)
{
    wchar_t buffer[256];
    GetDlgItemTextW(hDlg, nIDDlgItem, buffer, 256);

    // Проверяем, состоит ли строка только из цифр, точек и запятых.
    if (!IsNumericString(buffer))
    {
        MessageBox(hDlg, L"Пожалуйста, введите только числа.", L"Ошибка", MB_OK | MB_ICONERROR);
        return "Err";
    }


    // Заменяем запятую на точку перед преобразованием в число.
    for (size_t i = 0; i < wcslen(buffer); ++i)
    {
        if (buffer[i] == L',')
            buffer[i] = L'.';
    }
    //convert from wide char to narrow char array
    char ch[260];
    char DefChar = ' ';
    WideCharToMultiByte(CP_ACP, 0, buffer, -1, ch, 260, &DefChar, NULL);

    //A std:string  using the char* constructor.
    std::string value1(ch);
    bool nice = WithGoodSpace(value1);
    bool space = HaveSpace(buffer);
    if (space && !nice) {
        {
            MessageBox(hDlg, L"Пожалуйста, проверьте пробелы. Ошибка ввода", L"Ошибка", MB_OK | MB_ICONERROR);
            return "Err";
        }
    }
    std::string value(ch);
    if (space) {
        value.clear();
        value = NormalStr(value1);
    }
    bgn::BigNumber b = value;

    if (b < e1 || b > e2)
    {
        MessageBox(hDlg, L"Число выходит за пределы допустимого диапазона.", L"Ошибка", MB_OK | MB_ICONERROR);
        return "Err";
    }

    return value;
}


// Вспомогательная функция для установки значения в текстовое поле.
void SetDlgItemDouble(HWND hDlg, int nIDDlgItem, std::string value)
{
    /*   wchar_t buffer[256];*/
    std::wstring float1, integer1, end;
    std::wstring wstr = std::wstring(value.begin(), value.end());
    std::string min = "-0";
    std::wstring wmin = std::wstring(min.begin(), min.end());
    //std::string zero = "0";
    //std::wstring wzero = std::wstring(zero.begin(), zero.end());
    bool isNegat = false;
    //if (wstr[0] == wmin[0]) {
    //    isNegat = true;

    //}
    size_t found1 = wstr.find('.');

    integer1 = wstr;
    if (found1 != std::string::npos) {
        integer1 = wstr.substr(0, found1);
        float1 = wstr.substr(found1 + 1, wstr.size() - found1);
    }

    if (wstr[0] == wmin[0]) {
        isNegat = true;
        integer1 = integer1.substr(1, integer1.size() - 1);

    }
    int numZer = 0;
    for (int i = 0; i < integer1.size(); i++) {
        if (integer1[i] == wmin[1]) {
            numZer++;
        }
        else { break; }
    }
    reverse(integer1.begin(), integer1.end());
    if (integer1.size() > 1) {
        integer1.erase(integer1.end() - numZer, integer1.end());
    }
    int sizeInt = integer1.size();
    int NumSpace = 0;
    if (sizeInt % 3 == 0) {
        NumSpace = (sizeInt / 3) - 1;
    }
    else {
        NumSpace = (sizeInt / 3);
    }
    if (NumSpace != 0) {
        for (int i = 1; i < NumSpace + 1; i++) {
            integer1.insert(4 * i - 1, L" ");
        }
    }
    if (isNegat) {
        integer1.push_back(wmin[0]);
    }
    reverse(integer1.begin(), integer1.end());

    if (float1.size() > 0) {
        if (float1.size() > 6) {
            end = float1[6];
            int prend = (int)float1[5];
            if (end == L"5" || end == L"6" || end == L"7" || end == L"8" || end == L"9") {
                prend++;
            }
            float1.erase(float1.begin() + 5, float1.end());
            float1.push_back(prend);
        }
        reverse(float1.begin(), float1.end());
        int numZer = 0;
        for (int i = 0; i < float1.size(); i++) {
            if (float1[i] == wmin[1]) {
                numZer++;
            }
            else { break; }
        }
        reverse(float1.begin(), float1.end());
        float1.erase(float1.end() - numZer, float1.end());
        if (float1.empty()) {
            wstr = integer1;
        }
        else { wstr = integer1 + L"." + float1; }
    }
    else { wstr = integer1; }


    const wchar_t* widecstr = wstr.c_str();

    SetDlgItemTextW(hDlg, nIDDlgItem, widecstr);
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
