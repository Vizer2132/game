#include <SFML/Graphics.hpp> 
#include <math.h> 
//#include <Windows.h> // не работает вместе с afxdlgs
#include <iostream>
#include <string>
//
#include <memory>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>

#include <shobjidl.h> 



using namespace sf;
using namespace std;

float timee;
Mouse mouse;
Vector2i windowPos(8, 39);

template <typename T>
static void clearPtrVector(vector<T*> v) {
	//cout << typeid(&v).name() /*<< " " << v.size() */<< endl;
	for (auto p : v) {
		delete p;
	}
	v.clear();
}

//Clock s;
//float ps = s.getElapsedTime().asSeconds();
//float f = 0;
//static void showFPS() {
//	if (ps > 1) {
//		f = 0;
//		s.restart();
//	}
//	f++;
//	ps = s.getElapsedTime().asSeconds();
//	cout << f / ps << endl;
//}

//static string wstos(const wstring& wstr) {
//	using convert_typeX = codecvt_utf8<wchar_t>;
//	wstring_convert<convert_typeX, wchar_t> converterX;
//	return converterX.to_bytes(wstr);
//}

//string openFileDialog() {
//	CFileDialog dlg(TRUE);
//	if (dlg.DoModal() == IDOK) {
//		CFile file;
//		VERIFY(file.Open(dlg.GetPathName(), CFile::modeRead));
//		cout << wstos(dlg.GetPathName().GetString());
//		return wstos(dlg.GetPathName().GetString());
//	}
//	return "";
//}
//template <typename T>
//void swap(T &t1, T &t2) {
//	T t = t1;
//	t1 = t2;
//	t2 = t;
//};


static vector<string> openFile() {
	std::string sSelectedFile;
	std::string sFilePath;

	//  CREATE FILE OBJECT INSTANCE
	HRESULT f_SysHr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(f_SysHr))
		return { "0" };

	// CREATE FileOpenDialog OBJECT
	IFileOpenDialog* f_FileSystem;
	f_SysHr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&f_FileSystem));
	if (FAILED(f_SysHr)) {
		CoUninitialize();
		return { "1" };
	}

	//  SHOW OPEN FILE DIALOG WINDOW
	f_SysHr = f_FileSystem->Show(NULL);
	if (FAILED(f_SysHr)) {
		f_FileSystem->Release();
		CoUninitialize();
		return { "2" };
	}

	//  RETRIEVE FILE NAME FROM THE SELECTED ITEM
	IShellItem* f_Files;
	f_SysHr = f_FileSystem->GetResult(&f_Files);
	if (FAILED(f_SysHr)) {
		f_FileSystem->Release();
		CoUninitialize();
		return { "3" };
	}

	//  STORE AND CONVERT THE FILE NAME
	PWSTR f_Path;
	f_SysHr = f_Files->GetDisplayName(SIGDN_FILESYSPATH, &f_Path);
	if (FAILED(f_SysHr)) {
		f_Files->Release();
		f_FileSystem->Release();
		CoUninitialize();
		return { "4" };
	}

	//  FORMAT AND STORE THE FILE PATH
	std::wstring path(f_Path);
	std::string c(path.begin(), path.end());
	sFilePath = c;

	//  FORMAT STRING FOR EXECUTABLE NAME
	const size_t slash = sFilePath.find_last_of("/\\");
	sSelectedFile = sFilePath.substr(slash + 1);

	//  SUCCESS, CLEAN UP
	CoTaskMemFree(f_Path);
	f_Files->Release();
	f_FileSystem->Release();
	CoUninitialize();
	return { sSelectedFile, sFilePath };
}

static int randomNumber(int min, int max) {
	return rand() % (max - min + 1) + min;
}

static void closeWindow(RenderWindow& window) {
	Event event; while (window.pollEvent(event)) { if (event.type == Event::Closed) { window.close(); } }
	if (((Keyboard::isKeyPressed(Keyboard::Escape)))) { window.close(); }
}

const int SIZE_WINDOW_W = 1200;
const int SIZE_WINDOW_H = 675;

string strkey[] = {
	"A",
	"B",            //!< The B key
	"C",            //!< The C key
	"D",            //!< The D key
	"E",            //!< The E key
	"F",            //!< The F key
	"G",            //!< The G key
	"H",            //!< The H key
	"I",            //!< The I key
	"J",            //!< The J key
	"K",            //!< The K key
	"L",            //!< The L key
	"M",            //!< The M key
	"N",            //!< The N key
	"O",            //!< The O key
	"P",            //!< The P key
	"Q",            //!< The Q key
	"R",            //!< The R key
	"S",            //!< The S key
	"T",            //!< The T key
	"U",            //!< The U key
	"V",            //!< The V key
	"W",            //!< The W key
	"X",            //!< The X key
	"Y",            //!< The Y key
	"Z",            //!< The Z key
	"0",         //!< The 0 key
	"1",         //!< The 1 key
	"2",         //!< The 2 key
	"3",         //!< The 3 key
	"4",         //!< The 4 key
	"5",         //!< The 5 key
	"6",         //!< The 6 key
	"7",         //!< The 7 key
	"8",         //!< The 8 key
	"9",         //!< The 9 key
};
static Keyboard::Key getPressedKey() {
	Keyboard::Key key[] = {
		Keyboard::Key::Unknown,
		Keyboard::Key::A,
		Keyboard::Key::B,            //!< The B key
		Keyboard::Key::C,            //!< The C key
		Keyboard::Key::D,            //!< The D key
		Keyboard::Key::E,            //!< The E key
		Keyboard::Key::F,            //!< The F key
		Keyboard::Key::G,            //!< The G key
		Keyboard::Key::H,            //!< The H key
		Keyboard::Key::I,            //!< The I key
		Keyboard::Key::J,            //!< The J key
		Keyboard::Key::K,            //!< The K key
		Keyboard::Key::L,            //!< The L key
		Keyboard::Key::M,            //!< The M key
		Keyboard::Key::N,            //!< The N key
		Keyboard::Key::O,            //!< The O key
		Keyboard::Key::P,            //!< The P key
		Keyboard::Key::Q,            //!< The Q key
		Keyboard::Key::R,            //!< The R key
		Keyboard::Key::S,            //!< The S key
		Keyboard::Key::T,            //!< The T key
		Keyboard::Key::U,            //!< The U key
		Keyboard::Key::V,            //!< The V key
		Keyboard::Key::W,            //!< The W key
		Keyboard::Key::X,            //!< The X key
		Keyboard::Key::Y,            //!< The Y key
		Keyboard::Key::Z,            //!< The Z key
		Keyboard::Key::Num0,         //!< The 0 key
		Keyboard::Key::Num1,         //!< The 1 key
		Keyboard::Key::Num2,         //!< The 2 key
		Keyboard::Key::Num3,         //!< The 3 key
		Keyboard::Key::Num4,         //!< The 4 key
		Keyboard::Key::Num5,         //!< The 5 key
		Keyboard::Key::Num6,         //!< The 6 key
		Keyboard::Key::Num7,         //!< The 7 key
		Keyboard::Key::Num8,         //!< The 8 key
		Keyboard::Key::Num9,         //!< The 9 key
		Keyboard::Key::BackSpace,
	};

	for (size_t i = 0; i < sizeof(key) / sizeof(*key); i++) {
		if (Keyboard::isKeyPressed(key[i])) {
			return key[i];
		}

	}
	return key[0];

}




#include "Area.h"

#include "Slider.h"
#include "Button.h"
#include "WindowMenu.h"
#include "Objects.h"

class Entity
{
protected:
	float posX = 0;
	float posY = 0;

public:


};


static bool LBM_press_No_Button() {
	for (auto b : Button::GETALLBUTTONS()) {
		//cout << b->pointing();
		if (b->pointing()) return 0;
	}
	return mouse.isButtonPressed(mouse.Left);
}
static bool LBM_press() { return mouse.isButtonPressed(mouse.Left); }
static bool RBM_press() { return mouse.isButtonPressed(mouse.Right); }






float glength;
class Grid : public Drawable {
// private:
	
public:

	Grid(float len = 0) {
		glength = len;
	}

	void setGrid(float len = 0) {
		glength = len;
	}

	virtual void draw(RenderTarget& target, RenderStates states) const {
		RectangleShape line(Vector2f(1, SIZE_WINDOW_H));

		line.setFillColor(Color(255, 255, 255, 20));
		for (size_t i = 0; i <= SIZE_WINDOW_W; i += glength) {
			line.setPosition(i, 0);
			target.draw(line, states);
		}

		line.setSize(Vector2f(SIZE_WINDOW_W, 1));
		for (size_t i = 0; i <= (SIZE_WINDOW_H); i += glength) {
			line.setPosition(0, i);
			target.draw(line, states);
		}

	}



};



class Windows
{
public:
	Windows() {
		
	}
	~Windows() {
	
	}

private:

};




vector<Objects*> objectsVector;
static void CREATE(RenderWindow& window, int i = objectsVector.size()) {
	CircleShape cc(5);
	cc.setFillColor(Color(255, 0, 0));

	CircleShape cent(5);
	cent.setPosition(SIZE_WINDOW_W/2.0-cent.getLocalBounds().width/2.0, SIZE_WINDOW_H/2.0 - cent.getLocalBounds().height/2.0);
	cent.setFillColor(Color(0, 0, 0, 0));
	cent.setOutlineThickness(2);
	cent.setOutlineColor(Color(80, 80, 80));

	WindowMenu cwm;
	cwm.freeButton(SIZE_WINDOW_W-70, 0, "TRASH", 0, 1);
	cwm.button("X");
	cwm.button("EDIT");
		cwm.inButton("SIZE", "EDIT"); 
			cwm.inSlider("sizew", "SIZE", "EDIT", -100, 100, 50); 
			cwm.inSlider("sizeh", "SIZE", "EDIT", -100, 100, 50);
		cwm.inButton("SET IMAGE", "EDIT", 0, Button::DEFAULT);
		
	cwm.button("AREA");
		cwm.inButton("ADD", "AREA", 0, Button::DEFAULT);
		cwm.inButton("CLEAR", "AREA", 0, Button::DEFAULT);
		cwm.inButton("BODY", "AREA");

	cwm.button("PIC");
		cwm.inButton("LOCK", "PIC", 1); // блокировать позицию картинки
	




	objectsVector.push_back(new Objects);

	float mousex, mousey;
	RectangleShape AREARECT; AREARECT.setFillColor(Color(100, 100, 0, 100));
	bool hold = 0;
	
	Area* area = objectsVector[i]->getArea();

	bool xTouch = 0;
	Vector2f emwd = objectsVector[i]->getScale();
	Vector2f obpos = Vector2f(0, 0);

	vector<string> of = {};


	objectsVector[i]->setOrigin(
		objectsVector[i]->getSize().x / 2,
		objectsVector[i]->getSize().y / 2
	);


	
	while (!xTouch && !(Keyboard::isKeyPressed(Keyboard::Key::Escape) || cwm.touch("X"))) {
		windowPos = Vector2i(window.getPosition().x + 8, window.getPosition().y + 39);	
		mousey = mouse.getPosition().y - windowPos.y;
		mousex = mouse.getPosition().x - windowPos.x;
		

		if (cwm.touch("SET IMAGE", "EDIT")) {
			of = openFile();
			if (of.size() == 2) {
				objectsVector[i]->setPath(of[1]);
			}
			else {
				cout << "ошибка загрузки " << of[0] << endl;
			}
		}
		if (cwm.touch("BODY", "AREA")) {
			if (LBM_press_No_Button() && !hold) {
				AREARECT.setPosition(mousex, mousey);
				hold = 1;
			}
			if (hold) {		
				AREARECT.setSize(Vector2f(mousex, mousey) - AREARECT.getPosition());

			}
			if (!LBM_press_No_Button()) {
				hold = 0;
			}
		}
		if (cwm.touch("ADD", "AREA")) {
			area->add("body", AREARECT);

			AREARECT.setPosition(-1000, -1000);
			AREARECT.setSize(Vector2f(0, 0));
		}
		if (cwm.touch("CLEAR", "AREA")) {
			AREARECT.setPosition(-1000, -1000);
			AREARECT.setSize(Vector2f(0, 0));
		}
		if (cwm.touch("TRASH")) {
			delete objectsVector[i]; 
			objectsVector.erase(objectsVector.cbegin() + i);
			cout << objectsVector.size();

			break;
		}

		if (cwm.touch("LOCK", "PIC")) {

		}

		//if (LBM_press_No_Button()) {
		//	objectsVector[i]->setPosition(mousex, mousey);
		//	obpos = Vector2f(mousex, mousey);
		//}
	
		//window.setView(view);

		window.clear();

		
		window.draw(*objectsVector[i]);
		window.draw(AREARECT);
		window.draw(cent);
		

		window.draw(cc);
		window.draw(cwm);
		window.display();




		Event event;
		while (window.pollEvent(event)) { 
			if (event.type == Event::Closed) { xTouch = 1; } 

			if (event.type == Event::MouseWheelMoved) {
				if (Keyboard::isKeyPressed(Keyboard::LShift)) { if (emwd.x + event.mouseWheel.delta * 0.01 > 0) emwd += Vector2f(event.mouseWheel.delta * 0.01, event.mouseWheel.delta * 0.01); }
				else if (Keyboard::isKeyPressed(Keyboard::LControl)) { if (emwd.x + event.mouseWheel.delta * 0.5 > 0) emwd += Vector2f(event.mouseWheel.delta * 0.5, event.mouseWheel.delta * 0.5); }
				else if (emwd.x + event.mouseWheel.delta * 0.05 > 0) { emwd += Vector2f(event.mouseWheel.delta * 0.05, event.mouseWheel.delta * 0.05); }
				cout << emwd.x << endl;

				//view.setSize(SIZE_WINDOW_W*emwd.x, SIZE_WINDOW_H*emwd.y);
				
				if (LBM_press_No_Button()) {
					objectsVector[i]->setOrigin(SIZE_WINDOW_W/2.0, SIZE_WINDOW_H/2.0);
					cc.setPosition(objectsVector[i]->getOrigin() - Vector2f(cc.getRadius(), cc.getRadius()));

				}

				objectsVector[i]->setPosition(
					SIZE_WINDOW_W / 2.0,
					SIZE_WINDOW_H / 2.0
				);
				

				
				
				//objectsVector[i]->setOrigin(
				//	SIZE_WINDOW_W / 2.0 - objectsVector[i]->getPosition().x + objectsVector[i]->getSize().x / 2,
				//	SIZE_WINDOW_H / 2.0 - objectsVector[i]->getPosition().y + objectsVector[i]->getSize().y / 2
				//);
				
				
				//objectsVector[i]->setOrigin(
				//	SIZE_WINDOW_W / 2.0 - objectsVector[i]->getPosition().x + objectsVector[i]->getSize().x * objectsVector[i]->getScale().x / 2.0,
				//	SIZE_WINDOW_H / 2.0 - objectsVector[i]->getPosition().y + objectsVector[i]->getSize().y * objectsVector[i]->getScale().y / 2.0
				//);
				//objectsVector[i]->setPosition(obpos);
				
				objectsVector[i]->setScale(emwd);


			}
		}


	}
}
 

int main() {
	RenderWindow window(VideoMode(SIZE_WINDOW_W, SIZE_WINDOW_H), "htlfrnjh", sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(1);
	
	Mouse mouse;
	string path = "";
	Clock clock, s;


	float ps = s.getElapsedTime().asSeconds();
	s.restart();
	string in, out;
	
	WindowMenu wm;

	wm.button("FILE");
		wm.inButton("CREATE\nCREATURE", "FILE");
		wm.inButton("CREATE\nOBJECT", "FILE");

	wm.button("EDIT");
		wm.inButton("SHOW GRID", "EDIT", 1);

	wm.button("LIST");
		wm.inButton("OBJECT", "LIST", 1);

	Grid g(50);
	//int f = 0;


	while (window.isOpen()) {

		timee = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		timee = timee / 800;

		windowPos = Vector2i(window.getPosition().x + 8, window.getPosition().y + 39);

		//cout << 1;

		window.clear();

		if (wm.touch("CREATE\nCREATURE", "FILE")) {
			CREATE(window);
			wm.change("CREATE\nCREATURE", "FILE");
		}

		//if (wm.touch("SELECT", "EDIT")) {
		//	wm.off("UNSELECT", "EDIT");
		//	for (auto p : vob) {
		//		if (p->touch()) {
		//			p->is_select = 1;
		//		}
		//	}
		//}
		//
		//if (wm.touch("UNSELECT", "EDIT")) {
		//	wm.off("SELECT", "EDIT");
		//	for (auto p : vob) {
		//		if (p->touch()) {
		//			p->is_select = 0;
		//		}
		//	}
		//}
		//
		//if (wm.touch("UNSELECT ALL", "EDIT")) {
		//	wm.off("SELECT", "EDIT");
		//	wm.off("UNSELECT", "EDIT");
		//	for (auto p : vob) {
		//		p->is_select = 0;
		//	}
		//	wm.change("UNSELECT ALL", "EDIT");
		//}
		//
		//for (auto p : vob) {
		//	window.draw(*p);
		//	
		//	//if (p->is_select) {	
		//	//p->drag();
		//	//}
		//}


		//cout << wm.touch("EDIT") << endl;

		if (wm.touch("SHOW GRID", "EDIT")) {
			window.draw(g);
		}

		if (objectsVector.size() > 0) {
			window.draw(*objectsVector[0]);
		}

		window.draw(wm);
		window.display();
		closeWindow(window);
	}

	clearPtrVector(objectsVector);
	clearPtrVector(Button::GETALLBUTTONS());
}