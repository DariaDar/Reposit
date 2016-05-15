#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <CommCtrl.h>

const char g_szClassName[] = "myWindowClass";
HINSTANCE hInst;

WNDPROC OldButtonIncProc;
WNDPROC OldButtonDecProc;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ButtonDecProc (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK ButtonIncProc (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

enum{
    ID_BUTTON_INCR = 1,
    ID_BUTTON_DECR,
    ID_STATIC_INDEX,
    ID_STATIC_INFO,
    ID_LB
};

typedef struct PERSIONERS
{
	char name[20];
	char surname[20];
	int  birthday;
	int pension;
	char profession[20];
}PENSIONERS;

int WINAPI WinMain(
                   HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow
                  )
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    hInst = hInstance;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_MENU);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Pensioners",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 580, 400,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hButtonInc, hButtonDec;
    static HWND hStaticIndex;
	static HWND hStaticInfo;
	static HWND hWndList;
	static char buf[100];
	static char text[260];
    static int selected = -1;

    static int cnt = 5;
    static PENSIONERS p[] =
    {
        {"Jess", "Day", 62, 3600, "Teacher"},
        {"Nick", "Miller", 64, 1200, "Barman"},
        {"Schmidt", "Sh", 63, 5500, "Manager"},
        {"Winston", "Bishop", 64, 4300, "Policeman"},
        {"Coach", "C", 63, 3000, "Teacher"}
    };

     switch(msg)
    {
    case WM_CREATE:
        //Increment
        hButtonInc = CreateWindowEx(0,
                              WC_BUTTON,
                              "Increment Index",
                              WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
                              200, 50, 135, 23,
                              hwnd,
                              (HMENU)ID_BUTTON_INCR,
                              hInst,
                              NULL);
        OldButtonIncProc = (WNDPROC) SetWindowLong (hButtonInc, GWL_WNDPROC, (LONG) ButtonIncProc);

        //Decrement
        hButtonDec = CreateWindowEx(0,
                              WC_BUTTON,
                              "Decrement Index",
                              WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
                              420, 50, 135, 23,
                              hwnd,
                              (HMENU)ID_BUTTON_DECR,
                              hInst,
                              NULL);
        OldButtonDecProc = (WNDPROC) SetWindowLong (hButtonDec, GWL_WNDPROC, (LONG) ButtonDecProc);
        //Text for current index
        hStaticIndex = CreateWindowEx(0,
                              WC_STATIC,
                              "0",
                              WS_CHILD | WS_VISIBLE | WS_BORDER,
                              350, 50, 50, 23,
                              hwnd,
                              (HMENU)ID_STATIC_INDEX,
                              hInst,
                              NULL);
        SetWindowText(hStaticIndex, TEXT("0"));
        //Text for pensioner info
        hStaticInfo = CreateWindowEx(0,
                              WC_STATIC,
                              "",
                              WS_CHILD | WS_VISIBLE | WS_BORDER,
                              10, 180, 185, 125,
                              hwnd,
                              (HMENU)ID_STATIC_INFO,
                              hInst,
                              NULL);

        //Pensioner list
        hWndList = CreateWindowEx(0,
					WC_LISTBOX,
                    "listbox",
                    WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | WS_BORDER | LBS_NOTIFY,
                    10, 50, 185, 125,
                    hwnd, (HMENU) ID_LB, NULL, NULL
				);

        for(int i = 0; i < cnt; i++)
        {
            SendMessage(hWndList, LB_ADDSTRING, i, (LPARAM)p[i].name);
        }
        SendMessage (hWndList, LB_SETCURSEL, 0, 0);

        WPARAM wp;
		wp = MAKEWPARAM(ID_LB, LBN_SELCHANGE);
		SendMessage(hwnd, WM_COMMAND, wp, (LPARAM)hWndList);
		SetFocus (hWndList);

        break;

    case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_LB:// It's our listbox, check the notification code
                    switch(HIWORD(wParam))
                    {
                        case LBN_SELCHANGE: // Selection changed, do stuff here.
                            //Define index of pensioner that was chosen
                            selected = SendMessage(hWndList, LB_GETCURSEL, 0, 0);

                            if(selected != -1)
                            {
                                SetWindowText(hStaticIndex, _itoa(selected, buf, 10));
                                sprintf(text, "Name: %s\nSurname: %s\nAge: %d\nPension: %d\nProfession: %s",
                                        p[selected].name, p[selected].surname, p[selected].birthday, p[selected].pension, p[selected].profession);
                                SetWindowText(hStaticInfo, text);
                            }
                            break;
                    }
                    break;
            }
            break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ButtonIncProc (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static int selected;
	static char buf[100];

    HWND parent = GetParent(hwnd);
    HWND hStaticIndex = GetDlgItem(parent, ID_STATIC_INDEX);
	HWND hWndList = GetDlgItem(parent, ID_LB);

    //getPensCount
    int cntListItem = SendMessage (hWndList, LB_GETCOUNT, 0, 0);
    WPARAM wParam;

    switch (msg)
	{
	    case WM_LBUTTONUP:
	        selected =  SendMessage (hWndList, LB_GETCURSEL, 0, 0);
	        if(selected != -1)
            {
                if(selected < cntListItem - 1)
                    selected++;
                //index
                SetWindowText(hStaticIndex, _itoa(selected, buf, 10));
                //new choise in LB
                SendMessage (hWndList, LB_SETCURSEL, selected, 0);
                //cmd for showing new info
                wParam = MAKEWPARAM(ID_LB, LBN_SELCHANGE);
                SendMessage(parent, WM_COMMAND, wParam, (LPARAM)hWndList);
            }
            break;
	}
	return CallWindowProc(OldButtonIncProc, hwnd, msg, wp, lp);
}

LRESULT CALLBACK ButtonDecProc (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static int selected;
	static char buf[100];
    HWND parent = GetParent(hwnd);
    HWND hStaticIndex = GetDlgItem(parent, ID_STATIC_INDEX);
	HWND hWndList = GetDlgItem(parent, ID_LB);

	WPARAM wParam;

	switch(msg)
	{
        case WM_LBUTTONUP:
            selected = SendMessage (hWndList, LB_GETCURSEL, 0, 0);
            if(selected != -1)
            {
                if(selected > 0)
                    selected--;
                //index
                SetWindowText(hStaticIndex, _itoa(selected, buf, 10));
                //new choise in LB
                SendMessage (hWndList, LB_SETCURSEL, selected, 0);
                //cmd for showing new info
                wParam = MAKEWPARAM(ID_LB, LBN_SELCHANGE);
                SendMessage(parent, WM_COMMAND, wParam, (LPARAM)hWndList);
            }
            break;
	}
	return CallWindowProc(OldButtonDecProc, hwnd, msg, wp, lp);
}
