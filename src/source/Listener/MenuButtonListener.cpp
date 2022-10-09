#include "Listener/MenuButtonListener.h"
#include "DataModelV2/ToggleImageButtonInstance.h"
#include "Application.h"
#include "Globals.h"
#include "resource.h"

INT_PTR CALLBACK InsertDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
		return TRUE;
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					//g_dataModel->setMessage("lol u thought");
					EndDialog(hwnd, IDOK);
				break;
				case IDCANCEL:
					EndDialog(hwnd, IDCANCEL);
				break;
			}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}


BOOL CALLBACK InsertDialog(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    return TRUE;
}

void MenuButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	if(button->name == "go")
	{
		g_dataModel->toggleRun();
		((ToggleImageButtonInstance*)button)->checked = g_dataModel->isRunning();
	}
	else if(button->name == "file")
	{
		HMENU mainmenu = CreatePopupMenu();
		AppendMenu(mainmenu, MF_STRING, 100, "New");
		AppendMenu(mainmenu, MF_STRING, 101, "Open...");
		AppendMenu(mainmenu, MF_STRING, IDM_CONTEXTCLOSE, "Close");
		AppendMenu(mainmenu, MF_SEPARATOR, 0, NULL);
		POINT p;
		GetCursorPos(&p);
		int menuClick = TrackPopupMenu(mainmenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, p.x, p.y, 0, Globals::mainHwnd, 0);
		switch (menuClick)
		{
		case 100:
			g_usableApp->clearInstances();
			g_usableApp->onInit();
			break;
		case 101:
			g_dataModel->getOpen();
			break;
		case IDM_CONTEXTCLOSE:
			g_usableApp->QuitApp();
			break;
		}
	}
	else if(button->name == "insert")
	{
		HMENU mainmenu = CreatePopupMenu();
		AppendMenu(mainmenu, MF_STRING, IDM_INSERT_OBJECT, "Object...");
		AppendMenu(mainmenu, MF_SEPARATOR, 0, NULL);
		POINT p;
		GetCursorPos(&p);
		int menuClick = TrackPopupMenu(mainmenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, p.x, p.y, 0, Globals::mainHwnd, 0);
		switch (menuClick)
		{
		case IDM_INSERT_OBJECT:
			
			HWND aDiag2 = CreateDialog((HINSTANCE) GetWindowLong(Globals::mainHwnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_INS_DIALOG), Globals::mainHwnd, (DLGPROC)InsertDlgProc);

			break;
		}
	}
}