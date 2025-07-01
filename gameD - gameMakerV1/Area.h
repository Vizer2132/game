#pragma once


class Area : public Drawable, public Transformable{
private:
	vector<RectangleShape*> areaVector;
	string name;


public:
	Area() {
		
	}
	~Area() {
		clearPtrVector(areaVector);
	}
	void add(string n, float x, float y, float w, float h, Color c) {
		name = n;
		auto resh = new RectangleShape;
		resh->setPosition(x, y);
		resh->setSize(Vector2f(w, h));
		resh->setFillColor(c);

		areaVector.push_back(resh);
	}
	void add(string n, RectangleShape r) {
		name = n;
		auto resh = new RectangleShape;
		resh->setPosition(r.getPosition());
		resh->setSize(r.getSize());
		resh->setFillColor(r.getFillColor());

		areaVector.push_back(resh);
	}


	virtual void draw(RenderTarget& target, RenderStates states) const {
		for (auto av : areaVector) {
			target.draw(*av);
		}
	}

};

