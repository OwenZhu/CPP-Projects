#include <sstream>
#include <string>

#include "Window.h"


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow) {

	Window wnd1(800, 300, "Test");

	// Message pump
	MSG msg;
	BOOL gResult;

	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	if (gResult == -1) {
		return -1;
	}
	else {
		return msg.wParam;
	}
}
