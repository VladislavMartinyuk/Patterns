// Патерн проектирования "Посетитель" обеспечивает возможность, удобно добавлять новые операции. 
// Ибо ООП и динамический полиморфизи дает возможность удобно создавать типы, но не операции над ними
// Пример взят из книги "Проектирование программ на С++", Рукводство 16 (стр. 135)

#include <memory>
#include <vector>

class Shape;
class Circle;
class Square;

class ShapeVisitor
{
public:
	virtual ~ShapeVisitor() = default;
	virtual void visit(Circle c) const = 0;
	virtual void visit(Square s) const = 0;
};

// Теперь имея базовый класс ShapeVisitor можно легко добавлять новые операции над фигурами
class Draw : public ShapeVisitor
{
public:
	void visit(Circle c) const override
	{
		// Логика рисования круга
	}
	void visit(Square s) const override
	{
		// Логика рисования квадрата
	}
};

class Rotate : public ShapeVisitor
{
public:
	void visit(Circle c) const override
	{
		// Логика поворота круга
	}
	void visit(Square) const override
	{
		// Логика поворота квадрата
	}
};

class Shape
{
public:
	virtual ~Shape() = default;
	virtual void accept(std::unique_ptr<ShapeVisitor> visitor) = 0;
};

class Circle : public Shape
{
public:
	Circle() = default;
	explicit Circle(int r) : radius{ r } {}

	// В зависимости от того какого посетителя передили метод, выполняем операцию над типом Circle
	void accept(std::unique_ptr<ShapeVisitor> visitor) override
	{
		visitor->visit(*this);
	}

private:
	int radius{ 0 };
};

class Square : public Shape
{
public:
	Square() = default;
	explicit Square(int a) : a{ a } {}

	// В зависимости от того какого посетителя передили метод, выполняем операцию над типом Square
	void accept(std::unique_ptr<ShapeVisitor> visitor) override
	{
		visitor->visit(*this);
	}

private:
	int a{ 0 };
};

// Пример функции которая принимает вектор указателей Shape и рисует их
void drawShapes(std::vector<std::unique_ptr<Shape>> shapes)
{
	for (const auto& shape: shapes) {
		// Передаем в него Посетителя Draw, который нарисует фигуру каждого типа
		shape->accept(std::make_unique<Draw>());
	}
}

// Пример функции которая принимает вектор указателей Shape и поворачивает их
void rotateShapes(std::vector<std::unique_ptr<Shape>> shapes) 
{
	for (const auto& shape: shapes) {
		// Передает в него Посетителя Rotate, который повернет фигуру каждого типа
		shape->accept(std::make_unique<Rotate>());
	}
}