#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct geotermalLine {
private:
	int x1;
	int y1;
	int x2;
	int y2;

public:

	int getX1()
	{
		return x1;
	}

	int getX2()
	{
		return x2;
	}

	int getY1()
	{
		return y1;
	}

	int getY2()
	{
		return y2;
	}

	geotermalLine(int set_x1, int set_y1, int set_x2, int set_y2)
		: x1(set_x1), y1(set_y1), x2(set_x2), y2(set_y2) {}
};

int copyUp(std::string str, int& iter, char ch) {
	std::string value;
	while (str[iter] != ch) {
		value += str[iter];
		iter++;
	}
	iter++;
	return stoi(value);
}

geotermalLine splitString(std::string str) {
	int iter = 0;
	int x1 = copyUp(str, iter, ',');
	int y1 = copyUp(str, iter, ' ');
	iter += 3;
	int x2 = copyUp(str, iter, ',');
	int y2 = copyUp(str, iter, '\0');
	return geotermalLine(x1, y1, x2, y2);
}

int maxX(std::vector<geotermalLine> vector_values) {
	int max_x = 0;
	for (auto value : vector_values)
	{
		int x1 = value.getX1();
		if (x1 > max_x) {
			max_x = x1;
		}
		int x2 = value.getX2();
		if (x2 > max_x) {
			max_x = x2;
		}
	}
	return max_x;
}

int maxY(std::vector<geotermalLine> vector_values) {
	int max_y = 0;
	for (auto value : vector_values)
	{
		int y1 = value.getY1();
		if (y1 > max_y) {
			max_y = y1;
		}
		int y2 = value.getY2();
		if (y2 > max_y) {
			max_y = y2;
		}
	}
	return max_y;
}

void invertLine(int& value_1, int& value_2) {
	int value;
	if (value_1 > value_2)
	{
		value = value_1;
		value_1 = value_2;
		value_2 = value;
	}
}

void invertLine(int& x_1, int& y_1, int& x_2, int& y_2) {
	int x;
	int y;
	if (x_1 > x_2)
	{
		x = x_1;
		x_1 = x_2;
		x_2 = x;
		y = y_1;
		y_1 = y_2;
		y_2 = y;
	}
}

//void setLine(std::vector< std::vector<__int8>>& bottom,
//	geotermalLine coordinateLine) {
//	int x1 = coordinateLine.getX1();
//	int y1 = coordinateLine.getY1();
//	int x2 = coordinateLine.getX2();
//	int y2 = coordinateLine.getY2();
//
//	invertLine(x1, x2);
//	invertLine(y1, y2);
//	int y = y1;
//
//	if (x1 == x2 || y1 == y2) {
//		for (x1; x1 < x2 + 1; x1++)
//		{
//			y1 = y;
//			for (y1; y1 < y2 + 1; y1++)
//			{
//				bottom[x1][y1]++;
//			}
//		}
//	}
//}

void setLine(std::vector< std::vector<__int8>>& bottom,
	geotermalLine coordinateLine) {
	int x1 = coordinateLine.getX1();
	int y1 = coordinateLine.getY1();
	int x2 = coordinateLine.getX2();
	int y2 = coordinateLine.getY2();



	if (x1 == x2 || y1 == y2) {
			invertLine(x1, x2);
		invertLine(y1, y2);
		int y = y1;
		for (x1; x1 < x2 + 1; x1++)
		{
			y1 = y;
			for (y1; y1 < y2 + 1; y1++)
			{
				bottom[x1][y1]++;
			}
		}
	}
	else if ((x1 > x2 && y1 > y2) || (x1 < x2 && y1 < y2))
	{
		invertLine(x1, x2);
		invertLine(y1, y2);
		for (x1; x1 < x2 + 1; x1++)
		{
			for (y1;  (y1 < y2 + 1);)
			{
				bottom[x1][y1]++;
				y1++;
				break;
			}
		}
	}
	else {
		invertLine(x1, y1, x2, y2);
		for (x1; x1 < x2 + 1; x1++)
		{
			for (y1; (y1 > y2 - 1);)
			{
				bottom[x1][y1]++;
				y1--;
				break;
			}
		}
	}

}

int searchForIntersection(std::vector< std::vector<__int8>> bottom) {
	int count = 0;
	for (auto values : bottom)
	{
		for (auto value : values) {
			if (value > 1)
				count++;
		}
	}
	return count;
}

int main()
{
	std::string path("inputFive.txt");

	std::ifstream in(path); 
	std::string line;
	std::vector<geotermalLine> line_list;
	int width;
	int height;

	if (in.is_open())
	{
		while (getline(in, line))
		{
			line_list.push_back(splitString(line));
		}
	}
	else std::cout << "File not found";
	in.close();     

	width = maxX(line_list) + 1;
	height = maxY(line_list) + 1;
	std::vector< std::vector<__int8>> bottom(width, std::vector<__int8>(height, 0));

	for (auto value : line_list)
	{
		setLine(bottom, value);
	}

	std::cout << searchForIntersection(bottom) << "\n";

	system("pause");
	return 0;
}