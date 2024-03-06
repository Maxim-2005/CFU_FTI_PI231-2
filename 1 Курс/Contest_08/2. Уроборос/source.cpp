// обьявление класса вектор для доступности в поинте
class Vector;

// инициализация класса поинт с использованием вектора
class Point {
public:
    int x;
    int y;
	
	// конструктор который возвращает х и у
    Point(int x, int y) : x(x), y(y) {}
	
	// обьявление метода мув
    void move(const Vector& v);
};

// инициализация ранее обьявленного класса вектор
class Vector {
public:
    int x;
    int y;
	
	// конструктор
    Vector(const Point& p1, const Point& p2) {
        x = p2.x - p1.x;
        y = p2.y - p1.y;
    }
};

// реализация метода мув с использованием класса вектор
void Point::move(const Vector& v) {
    x += v.x;
    y += v.y;
};
