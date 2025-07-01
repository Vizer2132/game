#pragma once

class Button : public Drawable, public Transformable {
private:
	RectangleShape button;

	float wButton = 0, hButton = 0;
	Mouse mouse;
	Font font;
	string text = "";
	int textSize = 20;

	Color pointColor = Color(230, 230, 230);



	int LBM_press() const { return mouse.isButtonPressed(mouse.Left); }
	int RBM_press() const { return mouse.isButtonPressed(mouse.Right); }

	bool act = 0;

	int mode = 0;
	float mousex, mousey;
	float indentsx = 0;

	vector<Slider*> slidersVector;
	static vector<Button*> ALLBUTTONS;

public:
	enum Mode {
		DEFAULT,
		HOLD,
		SWITCH,
	};


	bool press = 0;
	bool alwAct = 0;

	void linkSlider(string n, float mn, float mx, float sp) {
		slidersVector.push_back(new Slider(n, getPosition().x + button.getLocalBounds().width + 10 + indentsx, getPosition().y + (button.getLocalBounds().height - 5) / 2, mn, mx, sp));
		indentsx += 110;
	}

	vector<Slider*> getLinkSliders() {
		return slidersVector;
	}

	Button(float x, float y, float w, float h, string t = "", bool aa = 0, int hold = DEFAULT) {
		//xButton = x;
		//yButton = y;
		wButton = w;
		hButton = h;

		alwAct = aa;

		text = t;
		Font f;
		f.loadFromFile("shrift.ttf");
		font = f;

		setPosition(x, y);
		button.setPosition(x, y);
		button.setSize(Vector2f(w, h));

		mode = hold;

		ALLBUTTONS.push_back(this);
	}
	Button(float x, float y, string t = "", bool aa = 0, int hold = DEFAULT) {
		alwAct = aa;

		text = t;
		Font f;
		f.loadFromFile("shrift.ttf");
		Text te(t, f); te.setCharacterSize(textSize);
		font = f;


		wButton = te.getLocalBounds().width+5;
		hButton = te.getLocalBounds().height+5;

		if (wButton < hButton) wButton = hButton;
		
		setPosition(x, y);
		button.setPosition(x, y);
		button.setSize(Vector2f(wButton, hButton));

		mode = hold;


		ALLBUTTONS.push_back(this);
	}
	Button(string t = "", bool aa = 0, int hold = DEFAULT) {
		setPosition(0, 0);
		//xButton = 0;
		//yButton = 0;
		wButton = 0;
		hButton = 0;
		
		alwAct = aa;

		text = t;
		Font f;
		f.loadFromFile("shrift.ttf");
		font = f;

		button.setPosition(0, 0);
		button.setSize(Vector2f(5, 5));

		mode = hold;
		
		ALLBUTTONS.push_back(this);
	}
	~Button() {
		clearPtrVector(slidersVector);
	}

	bool pointing() {
		//cout << mousex << " " << mousey << " ";
		mousey = mouse.getPosition().y - windowPos.y;
		mousex = mouse.getPosition().x - windowPos.x;

		return mousex > getPosition().x && mousex < getPosition().x + wButton && mousey > getPosition().y && mousey < getPosition().y + hButton;
	}

	bool touch() {
		button.setPosition(getPosition().x, getPosition().y);
		button.setSize(Vector2f(wButton, hButton));

		//mousey = mouse.getPosition().y - windowPos.y;
		//mousex = mouse.getPosition().x - windowPos.x;





		if (mode == DEFAULT) {
			if (pointing() && LBM_press()) {
				button.setFillColor(Color(0, 230, 0));
			}
			else {
				button.setFillColor(Color(255, 255, 255));
			}
			if (!act && pointing() && LBM_press()) {
				press = 1;
				act = 1;
			}
			else {
				press = 0;
				if (!LBM_press()) act = 0;
			}
		}
		else if (mode == HOLD) {
			if (pointing() && LBM_press()) {
				press = 1;
			}
			else {
				press = 0;
			}
		}
		else if (mode == SWITCH) {
			if (pointing()) {
				if (LBM_press()) {
					if (!act) {
						press = !press;
						act = 1;
					}
				}
				else {
					act = 0;
				}
			}
		}


		if (mode != DEFAULT) {
			if (press) {
				if (pointing()) button.setFillColor(Color(0, 230, 0));
				else button.setFillColor(Color(0, 255, 0));
			}
			else {
				if (pointing()) button.setFillColor(Color(230, 230, 230));
				else button.setFillColor(Color(255, 255, 255));
			}
		}

		return press;
	}

	float getValue(string n) {
		for (size_t i = 0; i < slidersVector.size(); i++) {
			if (slidersVector[i]->getName() == n)
				return slidersVector[i]->getValue();

		}
	}

	virtual void draw(RenderTarget& target, RenderStates states) const {
		Text t(text, font);
		t.setCharacterSize(textSize);
		t.setFillColor(Color(0, 0, 0));

		t.setPosition(getPosition());
		t.setPosition(getPosition().x + wButton / 2.0 - t.getLocalBounds().width / 2.0, getPosition().y + hButton / 2.0 - (t.getLocalBounds().height) / 2.0 - textSize * 0.25);		


		//states.transform *= getTransform(); // я незнаю почему оно не работает
		if (slidersVector.size() > 0) {
			for (size_t i = 0; i < slidersVector.size(); i++) {
				target.draw(*slidersVector[i]);
			}
		}
		target.draw(button, states);
		target.draw(t, states);
	}

	static vector<Button*>& GETALLBUTTONS() {
		return ALLBUTTONS;
	}
	void setSize(float w, float h) {
		wButton = w;
		hButton = h;
	}
	void change() {
		press = !press;
	}
	void off() {
		press = 0;
	}
	void on() {
		press = 1;
	}
	string getName() {
		return text;
	}
	Vector2f getSize() {
		return Vector2f(button.getLocalBounds().getSize().x, button.getLocalBounds().getSize().y);
	}
};

std::vector<Button*> Button::ALLBUTTONS;

