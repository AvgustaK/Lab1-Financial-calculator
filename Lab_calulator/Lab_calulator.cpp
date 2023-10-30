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
std::string result1, result2, result3;
int operation1 = 0, operation2 = 0, operation3 = 0; // 0 - сложение, 1 - вычитание
int RoundType = 0;
std::string Err1 = "-1000000000000.0000000000", Err2 = "1000000000000.0000000000";
bgn::BigNumber e1 = Err1;
bgn::BigNumber e2 = Err2;
WCHAR szStudentInfo[MAX_LOADSTRING] = L"ФИО: Жуковская Дарья Вячеславовна\nКурс: 4\nГруппа: 4\nГод: 2023";
WCHAR szSk1[MAX_LOADSTRING] = L"(";
WCHAR szSk2[MAX_LOADSTRING] = L")";
WCHAR szRound[MAX_LOADSTRING] = L"Выберите вид округления";
WCHAR szRoundInt[MAX_LOADSTRING] = L"Результат округленный до целых";
WCHAR szRes[MAX_LOADSTRING] = L"=";
std::string GetDlgItemDouble(HWND hDlg, int nIDDlgItem);
void SetDlgItemDouble(HWND hDlg, int nIDDlgItem, std::string value, int nIDDlgItem1);
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
std::string Сalculation(bgn::BigNumber num1, bgn::BigNumber num2, int operation, HWND hWnd) {
    std::string res;
    res.erase();
    std::string nul = "0.0";
    bgn::BigNumber nu = nul;
    // Выполним вычисления в зависимости от выбранной операции.
    if (operation == 0) // Сложение
        res = num1 + num2;
    else if (operation == 1) // Вычитание
        res = num1 - num2;
    else if (operation == 2)
        res = num1 * num2;
    else if (operation == 3) {
        if (num2 == nu) {
            MessageBox(hWnd, L"Деление на ноль запрещено", L"Ошибка", MB_OK | MB_ICONERROR);
            res = "Err";
        }
        res = num1 / num2;
    }
    bgn::BigNumber r = res;
    if (r < e1 || r > e2)
    {
        MessageBox(hWnd, L"Результат вычислений выходит за пределы допустимого диапазона.", L"Ошибка", MB_OK | MB_ICONERROR);
        res = "Err";
    }
    return res;

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // Создадим текстовые поля для ввода чисел.
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            50, 50, 200, 25, hWnd, (HMENU)101, NULL, NULL); //1
        CreateWindowW(L"STATIC", szSk1, WS_VISIBLE | WS_CHILD,
            275, 53, 200, 25, hWnd, NULL, NULL, NULL); // (
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            300, 50, 200, 25, hWnd, (HMENU)102, NULL, NULL);//2

        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            550, 50, 200, 25, hWnd, (HMENU)106, NULL, NULL);//3
        CreateWindowW(L"STATIC", szSk2, WS_VISIBLE | WS_CHILD,
            775, 53, 200, 25, hWnd, NULL, NULL, NULL);// )
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            800, 50, 200, 25, hWnd, (HMENU)107, NULL, NULL); //4

        // Создадим выпадающий список для выбора операции.
        //1
        CreateWindowW(L"ComboBox", L"", CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD,
            225, 100, 100, 100, hWnd, (HMENU)103, NULL, NULL);
        SendMessage(GetDlgItem(hWnd, 103), CB_ADDSTRING, 0, (LPARAM)L"Сложение");
        SendMessage(GetDlgItem(hWnd, 103), CB_ADDSTRING, 0, (LPARAM)L"Вычитание");
        SendMessage(GetDlgItem(hWnd, 103), CB_ADDSTRING, 0, (LPARAM)L"Умножение");
        SendMessage(GetDlgItem(hWnd, 103), CB_ADDSTRING, 0, (LPARAM)L"Деление");
        //2
        CreateWindowW(L"ComboBox", L"", CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD,
            475, 100, 100, 100, hWnd, (HMENU)108, NULL, NULL);
        SendMessage(GetDlgItem(hWnd, 108), CB_ADDSTRING, 0, (LPARAM)L"Сложение");
        SendMessage(GetDlgItem(hWnd, 108), CB_ADDSTRING, 0, (LPARAM)L"Вычитание");
        SendMessage(GetDlgItem(hWnd, 108), CB_ADDSTRING, 0, (LPARAM)L"Умножение");
        SendMessage(GetDlgItem(hWnd, 108), CB_ADDSTRING, 0, (LPARAM)L"Деление");
        //3
        CreateWindowW(L"ComboBox", L"", CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD,
            725, 100, 100, 100, hWnd, (HMENU)109, NULL, NULL);
        SendMessage(GetDlgItem(hWnd, 109), CB_ADDSTRING, 0, (LPARAM)L"Сложение");
        SendMessage(GetDlgItem(hWnd, 109), CB_ADDSTRING, 0, (LPARAM)L"Вычитание");
        SendMessage(GetDlgItem(hWnd, 109), CB_ADDSTRING, 0, (LPARAM)L"Умножение");
        SendMessage(GetDlgItem(hWnd, 109), CB_ADDSTRING, 0, (LPARAM)L"Деление");

        // Создадим кнопку для выполнения вычислений.
        CreateWindowW(L"BUTTON", L"Вычислить", WS_VISIBLE | WS_CHILD,
            1100, 100, 100, 30, hWnd, (HMENU)104, NULL, NULL);

        // Создадим поле для вывода результата.
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
            1050, 50, 200, 25, hWnd, (HMENU)105, NULL, NULL);
        // округление
        CreateWindowW(L"STATIC", szRound, WS_VISIBLE | WS_CHILD,
            50, 200, 200, 25, hWnd, NULL, NULL, NULL);// 

        CreateWindowW(L"ComboBox", L"", CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD,
            50, 250, 200, 100, hWnd, (HMENU)110, NULL, NULL);
        SendMessage(GetDlgItem(hWnd, 110), CB_ADDSTRING, 0, (LPARAM)L"Mатематическое");
        SendMessage(GetDlgItem(hWnd, 110), CB_ADDSTRING, 0, (LPARAM)L"Бухгалтерское");
        SendMessage(GetDlgItem(hWnd, 110), CB_ADDSTRING, 0, (LPARAM)L"Усечение");
        /*CreateWindowW(L"BUTTON", L"Округлить", WS_VISIBLE | WS_CHILD,
            275, 225, 100, 30, hWnd, (HMENU)113, NULL, NULL);*/
        CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
            400, 250, 200, 25, hWnd, (HMENU)112, NULL, NULL);

        CreateWindowW(L"STATIC", szRoundInt, WS_VISIBLE | WS_CHILD,
            400, 200, 200, 40, hWnd, NULL, NULL, NULL);// 
   
        // Создадим поле для отображения информации о студенте.
        CreateWindowW(L"STATIC", szStudentInfo, WS_VISIBLE | WS_CHILD,
            800, 200, 300, 50, hWnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", szRes, WS_VISIBLE | WS_CHILD,
            1025, 53, 10, 25, hWnd, NULL, NULL, NULL);// 
        SetDlgItemDouble(hWnd, 101, "0.0", 112);
        SetDlgItemDouble(hWnd, 102, "0.0", 112);
        SetDlgItemDouble(hWnd, 106, "0.0", 112);
        SetDlgItemDouble(hWnd, 107, "0.0", 112);
        SendMessage(GetDlgItem(hWnd, 103), CB_SETCURSEL, 0, 0); 
        SendMessage(GetDlgItem(hWnd, 110), CB_SETCURSEL, 0, 0);
        SendMessage(GetDlgItem(hWnd, 108), CB_SETCURSEL, 0, 0); 
        SendMessage(GetDlgItem(hWnd, 109), CB_SETCURSEL, 0, 0); 
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
            std::string nu1 = GetDlgItemDouble(hWnd, 102);
            std::string nu2 = GetDlgItemDouble(hWnd, 106);
            bgn::BigNumber num1 = nu1;
            bgn::BigNumber num2 = nu2;
            // Считаем выбранную операцию из выпадающего списка.
            operation1 = SendMessage(GetDlgItem(hWnd, 108), CB_GETCURSEL, 0, 0);
            result1 = Сalculation(num1, num2, operation1, hWnd);
            if (result1 == "error") {
                result3 = 0.0;
                SetDlgItemDouble(hWnd, 105, result3, 112);
                break;
            }
            //std::string nul = "0.0";
            //bgn::BigNumber nu = nul;
            //// Выполним вычисления в зависимости от выбранной операции.
            //if (operation1 == 0) // Сложение
            //    result = num1 + num2;
            //else if (operation1 == 1) // Вычитание
            //    result = num1 - num2;
            //else if (operation1 == 2)
            //    result = num1 * num2;
            //else if (operation1 == 3) {
            //    if (num2 == nu) {
            //        MessageBox(hWnd, L"Деление на ноль запрещено", L"Ошибка", MB_OK | MB_ICONERROR);
            //        result = 0.0;
            //    }
            //    result = num1 / num2;
            //}
            /////////////
            std::string nu3 = GetDlgItemDouble(hWnd, 101);
            std::string nu4 = GetDlgItemDouble(hWnd, 107);
            bgn::BigNumber num3 = nu3;
            bgn::BigNumber num4 = nu4;
            /////////////
            operation2 = SendMessage(GetDlgItem(hWnd, 103), CB_GETCURSEL, 0, 0);
            operation3 = SendMessage(GetDlgItem(hWnd, 109), CB_GETCURSEL, 0, 0);
            int priority = 1;
            if (operation3 == 2 || operation3 == 3) {
                priority = 2;
            }
            //
            bgn::BigNumber res1 = result1;
            if (priority == 1) {
                result2 = Сalculation(num3, res1, operation2, hWnd);
                bgn::BigNumber res2 = result2;
                result3 = Сalculation(res2, num4, operation3, hWnd);
            }
            else {
                result2 = Сalculation(res1, num4, operation3, hWnd);
                bgn::BigNumber res2 = result2;
                result3 = Сalculation(num3, res2, operation2, hWnd);
            }
            if (result2 == "error" || result3 == "error") {
                result3 = 0.0;
                SetDlgItemDouble(hWnd, 105, result3, 112);
                break;
            }
            /*bgn::BigNumber res = result;*/
            if (nu1 == "Err" || nu2 == "Err" || nu3 == "Err" || nu4 == "Err") {
                result3 = 0.0;
            }
           

            // Выведем результат в текстовое поле.
            //RoundType = SendMessage(GetDlgItem(hWnd, 110), CB_GETCURSEL, 0, 0);
            SetDlgItemDouble(hWnd, 105, result3, 112);
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
    if (wcslen(buffer) == 0)
    {
        MessageBox(hDlg, L"Введите данные!", L"Ошибка", MB_OK | MB_ICONERROR);
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
}std::wstring AddSpace(std::wstring integer1) {
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
    return integer1;
}
std::wstring Push1(std::wstring wstr) {
    int size = wstr.size();
    std::wstring One = L"1";
    if (size > One.size()) { //Заполняем нулями
        int nZero = size - One.size();
        One.insert(One.size(), nZero, '0');
    }
    reverse(wstr.begin(), wstr.end());
    //reverse(One.begin(), One.end());
    std::wstring res = wstr;
    res.push_back('0');
    int i;
    int carry = 0;
    for (i = 0; i < One.size(); ++i) {
        int tmp = res[i] - '0' + One[i] - '0' + carry;
        int v = tmp % 10;
        carry = tmp / 10;
        res[i] = v + '0';
    }

    if (carry > 0) {
        res[i] += carry;
    }
    else if (res.back() == '0') {
        res.erase(res.size() - 1, 1);
    }

    reverse(res.begin(), res.end());
    return res;

}
std::wstring Round(std::wstring float1, std::wstring integer1, bool Flag) {
    std::wstring wstr;
    std::wstring firstFloat;
    firstFloat = float1[0];
    int EndInt = integer1[integer1.size() - 1];
    int temp = 0;
    if (firstFloat == L"6" || firstFloat == L"7" || firstFloat == L"9" || firstFloat == L"8" || (firstFloat == L"5" && !Flag )
        || (firstFloat == L"5" && EndInt % 2 == 1 && Flag && float1.size() == 1)
        || (firstFloat == L"5" && Flag && float1.size() != 1)) {
        temp++;
    }
    if (temp != 0) {
        integer1 = Push1(integer1);
    }
    reverse(integer1.begin(), integer1.end());
    integer1 = AddSpace(integer1);
    reverse(integer1.begin(), integer1.end());
    wstr = integer1;
    return wstr;
}

void SetDlgItemRound(HWND hDlg, int nIDDlgItem, std::wstring float1, std::wstring integer1, bool isNegat) {
    std::wstring wstr;
    RoundType = SendMessage(GetDlgItem(hDlg, 110), CB_GETCURSEL, 0, 0);
    bool BankRound;
    if (float1.size() == 0 || RoundType == 2) {
        reverse(integer1.begin(), integer1.end());
        integer1 = AddSpace(integer1);
        reverse(integer1.begin(), integer1.end());

        wstr = integer1;
    }
    else if (RoundType == 0) {
        BankRound = false;
        wstr = Round(float1, integer1, BankRound);
    }
    else if (RoundType == 1) {
        BankRound = true;
        wstr = Round(float1, integer1, BankRound);
    }
    

    if (isNegat) {
        reverse(wstr.begin(), wstr.end());
        std::wstring wmin = L"-";
        wstr.push_back(wmin[0]);
        reverse(wstr.begin(), wstr.end());
    }
    const wchar_t* widecstr = wstr.c_str();
    SetDlgItemTextW(hDlg, nIDDlgItem, widecstr);
}
//std::wstring AddSpace(std::wstring integer1) {
//    int sizeInt = integer1.size();
//    int NumSpace = 0;
//    if (sizeInt % 3 == 0) {
//        NumSpace = (sizeInt / 3) - 1;
//    }
//    else {
//        NumSpace = (sizeInt / 3);
//    }
//    if (NumSpace != 0) {
//        for (int i = 1; i < NumSpace + 1; i++) {
//            integer1.insert(4 * i - 1, L" ");
//        }
//    }
//    return integer1;
//}
// Вспомогательная функция для установки значения в текстовое поле.
void SetDlgItemDouble(HWND hDlg, int nIDDlgItem, std::string value, int nIDDlgItem1)
{
    /*   wchar_t buffer[256];*/
    std::wstring float1, integer1, end, integer2;
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
    integer2 = integer1;
    reverse(integer2.begin(), integer2.end());
    integer1 = AddSpace(integer1);
    /*integer2 = integer1;*/
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
    SetDlgItemRound(hDlg, nIDDlgItem1, float1, integer2, isNegat);
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
