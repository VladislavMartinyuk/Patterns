// �������� ������������ ���������� ������� � ��� ����� ��������� ������
// � ����� � ���� �� ������ �������� ����� ���������� ������ � ��� ����������
// � ������ ������������� �������������� ��������, std::variant � std::visit
// ������ ���� �� ����� "�������������� �������� �� �++"

#include <vector>
#include <iostream>
#include <variant>

class Circle;
class Square;

// ���������� std::variant ��� ���������� �����
using Shape = std::variant<Circle, Square>;

// ���������� std::vector<std::variant<Circle, Square>> ��� �������� �����
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

// ������ ������� ��� ��������� ���� �����
void drawShapes(const Shapes& shapes)
{
	for (const auto& shape: shapes) {
		// �������� � std::visit ������� Draw{}
		std::visit(Draw{}, shape);
	}
}

// ������ ������ ��� �������� ���� �����
void rotateShapes(const Shapes& shapes)
{
	for (const auto& shape: shapes) {
		// �������� � std::visit ������� Rotate{}
		std::visit(Rotate{}, shape);
	}
}