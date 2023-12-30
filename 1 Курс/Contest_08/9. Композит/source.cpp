class Label : public Leaf {
    std::string text;
public:
    Label(const std::string& text) :text(text) {
    }

    Canvas render() override {
        Canvas c;

        c.draw(text);

        return c;
    }

    std::string click(int x, int y) override {
        return "Label(" + text + ")";
    }
}; 

// реализация класса чек бокс
class CheckBox : public Leaf {
    std::string text;
    bool check;
public:

	// конструктор
    CheckBox(const std::string& text, const bool check) :text(text) {
        this->check = check;
    }
	
	// переопределение отрисовки
    Canvas render() override {
        Canvas c;

        if (check)
            c.draw("[x] " + text);
        else
            c.draw("[ ] " + text);

        return c;
    }

	// клик
    std::string click(int x, int y) override {
        return "CheckBox(" + text + ")";
    }
}; 

// вертикальное размещение
class VLayout : public Composite {
public:
	
	// переопределение отрисовки
    Canvas render() override {
        Canvas c;

        for (auto i : components) {
            Canvas t = i->render();
            c.draw(t, 0, c.height() == 0 ? 0 : c.height() + 1);
        }

        return c;
    }
	
	// клик
    std::string click(int x, int y) override {
        int curX = 0;
        int curY = 0;

        for (auto i : components) {
            Canvas t = i->render();
            curX = t.width();
            curY += t.height();

            if (curY > y) {
                if (curX > x)
                    return i->click(x, y - (curY - t.height()));
                else
                    return "Empty";
            }

            curY += 1;
            if (curY > y)
                return "Empty";
        }
        return "Empty";
    }
};
