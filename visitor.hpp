// ������ �������������� "����������" ������������ �����������, ������ ��������� ����� ��������. 
// ��� ��� � ������������ ����������� ���� ����������� ������ ��������� ����, �� �� �������� ��� ����
// ������ ���� �� ����� "�������������� �������� �� �++", ���������� 16 (���. 135)

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

// ������ ���� ������� ����� ShapeVisitor ����� ����� ��������� ����� �������� ��� ��������
class Draw : public ShapeVisitor
{
public:
	void visit(Circle c) const override
	{
		// ������ ��������� �����
	}
	void visit(Square s) const override
	{
		// ������ ��������� ��������
	}
};

class Rotate : public ShapeVisitor
{
public:
	void visit(Circle c) const override
	{
		// ������ �������� �����
	}
	void visit(Square) const override
	{
		// ������ �������� ��������
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

	// � ����������� �� ���� ������ ���������� �������� �����, ��������� �������� ��� ����� Circle
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

	// � ����������� �� ���� ������ ���������� �������� �����, ��������� �������� ��� ����� Square
	void accept(std::unique_ptr<ShapeVisitor> visitor) override
	{
		visitor->visit(*this);
	}

private:
	int a{ 0 };
};

// ������ ������� ������� ��������� ������ ���������� Shape � ������ ��
void drawShapes(std::vector<std::unique_ptr<Shape>> shapes)
{
	for (const auto& shape: shapes) {
		// �������� � ���� ���������� Draw, ������� �������� ������ ������� ����
		shape->accept(std::make_unique<Draw>());
	}
}

// ������ ������� ������� ��������� ������ ���������� Shape � ������������ ��
void rotateShapes(std::vector<std::unique_ptr<Shape>> shapes) 
{
	for (const auto& shape: shapes) {
		// �������� � ���� ���������� Rotate, ������� �������� ������ ������� ����
		shape->accept(std::make_unique<Rotate>());
	}
}