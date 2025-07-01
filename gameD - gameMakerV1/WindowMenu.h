#pragma once


class WindowMenu : public Drawable, public Transformable {
private:
	float indentx = 0;
	vector<float> indentxv;
	vector<float> indenty;
	
	float x = 0;
	float y = 0;

	int buttonIndentX = 2;
	int buttonIndentY = 3;

	vector<vector<Button*>> buttonsVector;



	Button* findButton(string t, string nb) {
		size_t i = 0;
		size_t j = 0;

		for (; i < buttonsVector.size(); i++) if (buttonsVector[i][0]->getName() == nb) break;
		for (; j < buttonsVector[i].size(); j++) if (buttonsVector[i][j]->getName() == t) break;

		return buttonsVector[i][j];
	}


public:

	WindowMenu(float nx = 0, float ny = 0) {
		x = nx;
		y = ny;

		indentx = x;
	}
	~WindowMenu() {

	}


	void freeButton(float x, float y, string t, bool aa = 0, int mode = Button::SWITCH) {
		indenty.push_back(0);
		indentxv.push_back(0);

		vector<Button*> vb = { new Button(x, y, t, aa, mode) };
		buttonsVector.push_back(vb);
	}
	void button(string t) {
		Font font; font.loadFromFile("shrift.ttf");
		Text te(t, font); te.setCharacterSize(25);

		indenty.push_back(te.getLocalBounds().height + buttonIndentY*2);
		indentxv.push_back(indentx);

		vector<Button*> vb = { new Button(indentx, y, t, 0, Button::SWITCH) };
		buttonsVector.push_back(vb);

		indentx += vb[0]->getSize().x + buttonIndentX;
	}

	void inButton(string t, string nb, bool alwAct = 0, Button::Mode m = Button::SWITCH) {
		size_t i = 0;
		for (; i < buttonsVector.size(); i++) if (buttonsVector[i][0]->getName() == nb) break;

		buttonsVector[i].push_back(new Button(indentxv[i], y + indenty[i], t, alwAct, m));
		
		indenty[i] += buttonsVector[i][buttonsVector[i].size()-1]->getSize().y + buttonIndentY;
	}

	void inSlider(string n, string t, string nb, float mn = 0, float mx = 100, float sp = -100000) {
		//buttonsVector[buttonsVector.size()-1][buttonsVector[buttonsVector.size()-1].size()-1]->linkSlider(mn, mx);
		findButton(t, nb)->linkSlider(n, mn, mx, sp);
	}


	bool touch(string t) {
		for (size_t i = 0; i < buttonsVector.size(); i++) {
			if (buttonsVector[i][0]->getName() == t) {
				return buttonsVector[i][0]->touch();
			}
		}
	
		return 0;
	}
	bool touch(string t, string nb) {
		size_t i = 0;
		size_t j = 0;

		for (; i < buttonsVector.size(); i++) if (buttonsVector[i][0]->getName() == nb) break;

		if (buttonsVector[i][0]->touch()) {
			for (; j < buttonsVector[i].size(); j++) if (buttonsVector[i][j]->getName() == t) break;
			return buttonsVector[i][j]->touch();
		}

		for (; j < buttonsVector[i].size(); j++) if (buttonsVector[i][j]->getName() == t) break;
		if (buttonsVector[i][j]->alwAct) {
			for (; j < buttonsVector[i].size(); j++) if (buttonsVector[i][j]->getName() == t) break;
			return buttonsVector[i][j]->press;
		}

		return 0;
	}
	float getValue(string n, string t, string nb) {
		return findButton(t, nb)->getValue(n);

	}


	virtual void draw(RenderTarget& target, RenderStates states) const {
		states.transform *= getTransform();

		for (size_t i = 0; i < buttonsVector.size(); i++) {
			target.draw(*buttonsVector[i][0], states);

			if (buttonsVector[i][0]->touch()) {
				for (size_t j = 1; j < buttonsVector[i].size(); j++) {
					target.draw(*buttonsVector[i][j], states);
				}
			}
		}
	}

	Vector2f getButtonPosition(string t, string nb) {
		size_t i = 0;
		size_t j = 0;
		for (; i < buttonsVector.size(); i++) if (buttonsVector[i][0]->getName() == nb) break;
		if (buttonsVector[i][0]->touch()) {
			for (; j < buttonsVector[i].size(); j++) if (buttonsVector[i][j]->getName() == t) break;
			return buttonsVector[i][j]->getPosition();
		}
		return Vector2f(-1000, -1000);

	}
	vector<vector<Button*>> getAllButtons() {
		return buttonsVector;
	}

	float getIndentx() {
		return indentx;
	}
	void setIndentx(float ix = 0) {
		indentx = ix;
	}
	void setIndentx(Button b) {
		indentx = b.getSize().x + 5;
	}
	void addIndentx(float aix = 0) {
		indentx += aix;
	}
	void addIndentx(Button b) {
		indentx += b.getSize().x + 5;
	}
	void addButton(Button *b) {
		buttonsVector.push_back(vector<Button*> {b});
		indentx += b->getSize().x + 5;

	}

	void change(string t, string nb) {
		size_t i = 0;
		size_t j = 0;
		auto fb = findButton(t, nb);

		fb->press = !fb->press;
	}
	void off(string t, string nb) {
		size_t i = 0;
		size_t j = 0;

		findButton(t, nb)->press = 0;
	}
	void on(string t, string nb) {
		size_t i = 0;
		size_t j = 0;

		findButton(t, nb)->press = 1;
	}
};
