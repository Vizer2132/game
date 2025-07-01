#pragma once

class Objects : public Drawable, public Transformable {
private:
	Vector2f rSize = Vector2f(10, 10);
	Vector2f r2size = Vector2f(rSize.x / 2, rSize.x / 2);
	RectangleShape lv{ rSize }, rv{ rSize }, ln{ rSize }, rn{ rSize };
	RectangleShape ls{ rSize }, rs{ rSize }, ws{ rSize }, ns{ rSize };


	string path = "";
	Sprite s;
	Texture t;
	bool dragPress = 0;

	bool LBM_press() { return mouse.isButtonPressed(mouse.Left); }
	bool RBM_press() { return mouse.isButtonPressed(mouse.Right); }

	float obW = 0;
	float obH = 0;

	int mousey;
	int mousex;

	float indentx = 0;
	float indenty = 0;
		
	Area area;

public:
	//bool is_select = 0;
	bool press = 0;

	Area* getArea() {
		return &area;
	}

	Objects(string p = "C:/Users/vi/Desktop/gameD - gameMakerV1/gameD - gameMakerV1/no_image.jpg") {
		path = p;
		t.loadFromFile(p);
		Sprite sp;

		sp.setTexture(t);
		// sp.setScale(SIZE_WINDOW_W / (3 * sp.getLocalBounds().width), SIZE_WINDOW_H / (3 * sp.getLocalBounds().height));
		sp.setScale(300 / sp.getLocalBounds().width, 300 / sp.getLocalBounds().height);



		sp.setPosition(0, 0);
		s = sp;
		setPosition(SIZE_WINDOW_W / 2.0 - sp.getLocalBounds().width * sp.getScale().x / 2, SIZE_WINDOW_H / 2.0 - sp.getLocalBounds().height * sp.getScale().y / 2);

		//is_select = 1;
	}
	~Objects() {
		//if (area != NULL) delete& area
	}
	void setPath(string p) {
		path = p;
		t.loadFromFile(p);
		Sprite sp;

		sp.setTexture(t);
		sp.setScale(SIZE_WINDOW_W / (3 * sp.getLocalBounds().width), SIZE_WINDOW_H / (3 * sp.getLocalBounds().height));

		sp.setPosition(0, 0);

		s = sp;
	}

	//virtual Vector2f getSize() {
	//	return Vector2f(s.getLocalBounds().width, s.getLocalBounds().height);
	//}

	virtual void draw(RenderTarget& target, RenderStates states) const {
		states.transform *= getTransform();
		target.draw(s, states);
		target.draw(area, states);


		/*if (is_select) {
			target.draw(lv);
			target.draw(rv);
			target.draw(ln);
			target.draw(rn);
		}*/
	}

	bool touch() {
		//setPosition(getPosition());
		obW = s.getLocalBounds().width * s.getScale().x;
		obH = s.getLocalBounds().height * s.getScale().y;

		mousex = mouse.getPosition().x - windowPos.x;
		mousey = mouse.getPosition().y - windowPos.y;

		if (mousex > getPosition().x && mousex < getPosition().x + obW && mousey > getPosition().y && mousey < getPosition().y + obH && LBM_press()) {
			press = 1;
			return 1;
		}
		else {
			press = 0;
			return 0;
		}
	}

	void drag() {
		mousey = mouse.getPosition().y - windowPos.y;
		mousex = mouse.getPosition().x - windowPos.x;

		if (touch() || dragPress == 1) {
			obW = s.getLocalBounds().width * s.getScale().x;
			obH = s.getLocalBounds().height * s.getScale().y;

			lv.setPosition(getPosition() - r2size);
			rv.setPosition(getPosition() + Vector2f(obW, 0) - r2size);
			ln.setPosition(getPosition() + Vector2f(0, obH) - r2size);
			rn.setPosition(getPosition() + Vector2f(obW, obH) - r2size);

			if (LBM_press()) dragPress = 1;
			else dragPress = 0;

			setPosition(mousex - indentx, mousey - indenty);
		}
		else {
			indentx = mousex - getPosition().x;
			indenty = mousey - getPosition().y;
		}
	}
	Vector2f getSize() { //  Object->getScale().x   не тоже самое что    s.getScale().x
		return Vector2f(s.getLocalBounds().width * s.getScale().x, s.getLocalBounds().height * s.getScale().y);
	}
};

