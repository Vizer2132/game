#pragma once


class Slider : public Drawable, public Transformable {
private:
	RectangleShape line;
	RectangleShape jost;

	string name;

	float lineLen = 100;
	float jostPos;

	int LBM_press() const { return mouse.isButtonPressed(mouse.Left); }
	int RBM_press() const { return mouse.isButtonPressed(mouse.Right); }


	float w, h;

	float mousex, mousey;
	bool press = 0;
	float value;

	float per = 1;
	float max = 10, min = 0;

public:
	Slider(string n, float x, float y, float mn = 0, float mx = 10, float stPos = 0) { // stPos в процентах
		setPosition(x, y);
		//if (stPos <= 0) stPos = mn;
		//if (stPos >= 100) stPos = mx;

		//value = (stPos / 100) * (mx - mn)+mn;

		name = n;

		min = mn;
		max = mx;

		line.setPosition(getPosition());
		line.setSize(Vector2f(lineLen, 5));
		
		jost.setOrigin(4, (15 - 5) / 2.0);
		jost.setFillColor(Color(100, 100, 100));
		jost.setPosition(getPosition());
		jost.setSize(Vector2f(8, 15));
	}

	virtual void draw(RenderTarget& target, RenderStates states) const {
		target.draw(line, states);
		target.draw(jost, states);
	}

	float getValue() {
		mousey = mouse.getPosition().y - windowPos.y;
		mousex = mouse.getPosition().x - windowPos.x;

		w = jost.getLocalBounds().width;
		h = jost.getLocalBounds().height;

		if (!LBM_press()) {
			press = 0;
		}

		if (press || mousex > getPosition().x + value && mousex < getPosition().x + w + value && mousey > getPosition().y && mousey < getPosition().y + h && LBM_press()) {
			press = 1;

			if (mousex > getPosition().x && mousex < getPosition().x + lineLen) {
				value = mousex - getPosition().x;
				jost.setPosition(mousex, getPosition().y);
			}
			else if (mousex < getPosition().x + lineLen) {
				value = 0;
				jost.setPosition(getPosition());
			}
			else {
				value = lineLen;
				jost.setPosition(getPosition().x + lineLen, getPosition().y);
			}
		}

		return value * (max / lineLen) + min;
	}
	string getName() {
		return name;
	}


};
