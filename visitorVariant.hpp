// Проблема циклического посетителя состоит в его очень медленной работе
// В связи с этим на помощь приходит более современнй подход к его реализации
// А именно использование функциональных объектов, std::variant и std::visit
// Пример взят из книги "Проектирование программ на С++"

#include <vector>
#include <iostream>
#include <variant>

class Circle;
class Square;

// используем std::variant для храненения фигур
using Shape = std::variant<Circle, Square>;

// используем std::vector<std::variant<Circle, Square>> для хранения фигур
using Shapes = std::vector<Shape>;

class Draw
{
public:
	void operator()(const Circle&) const
	{
		std::cout << "Draw Circle" << std::endl;
	}
	void operator()(const Square&) const
	{
		std::cout << "Draw Square" << std::endl;
	}
};

class Rotate
{
public:
	void operator()(const Circle&) const
	{
		std::cout << "Rotate Circle" << std::endl;
	}
	void operator()(const Square&) const
	{
		std::cout << "Rotate Square" << std::endl;
	}
};

// пример функции для отрисовки всех фигур
void drawShapes(const Shapes& shapes)
{
	for (const auto& shape: shapes) {
		// передаем в std::visit функтор Draw{}
		std::visit(Draw{}, shape);
	}
}

// пример фунции для поворота всех фигур
void rotateShapes(const Shapes& shapes)
{
	for (const auto& shape: shapes) {
		// передаем в std::visit функтор Rotate{}
		std::visit(Rotate{}, shape);
	}
}