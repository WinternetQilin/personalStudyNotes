#include"ExWindow.h"
#include"ExLine.h"

int main(){

	ExWindow* window = new ExWindow(800, 600, "C:\\Users\\zmq\\coding\\C++\\��ͼС���ߣ�easyx��c++���װ��\\bg.gif");
	ExLine* line = new ExLine;
	while (true)
	{
		ExMessage msg;
		while (peekmessage(&msg)) {
			line->draw(msg);
		}
	}
	return 0;
}
