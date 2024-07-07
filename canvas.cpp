#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
class Canvas
{
protected:
    int width, height;
    char **canvas;

public:
    Canvas(int width, int height, char empty_symbol) : width(width), height(height)
    {
        canvas = new char *[height];
        for (int i = 0; i < height; i++)
        {
            canvas[i] = new char[width];
            for (int j = 0; j < width; j++)
            {
                canvas[i][j] = empty_symbol;
            }
        }
    }
    ~Canvas()
    {
        for (int i = 0; i < height; i++)
        {
            delete[] canvas[i];
        }
        delete[] canvas;
    }
    virtual void draw_to_file(const std::string &filename) = 0;
    virtual void coordinates(int x, int y, char symbol) = 0;
};

class Figure
{
protected:
    int x, y;
    char symbol;

public:
    Figure(int x, int y, char symbol) : x(x), y(y), symbol(symbol) {}
    virtual ~Figure() = default;
    virtual void draw(Canvas &c) = 0;
};

class ASCIICanvas : public Canvas
{
public:
    ASCIICanvas(int width, int height, char empty_symbol) : Canvas(width, height, empty_symbol) {}

    void draw_to_file(const std::string &filename) override
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    file << canvas[i][j];
                }
                file << std::endl;
            }
            file.close();
        }
        else
        {
            std::cerr << "file open error!" << std::endl;
        }
    }

    void coordinates(int x, int y, char symbol) override
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            canvas[y][x] = symbol;
        }
    }
};

class Rectangle : public Figure
{
protected:
    int a, b;

public:
    Rectangle(int a, int b, int x, int y, char symbol) : Figure(x, y, symbol), a(a), b(b) {}

    void draw(Canvas &c) override
    {
        for (int i = 0; i < a; i++)
        {
            for (int j = 0; j < b; j++)
            {
                c.coordinates(x + i, y + j, symbol);
            }
        }
    }
};

class Triangle : public Figure
{
private:
    int a, h;

public:
    Triangle(int a, int h, int x, int y, char symbol) : Figure(x, y, symbol), a(a), h(h) {}
    ~Triangle() {}
    void draw(Canvas &c) override
    {
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < a; j++)
            {
                if (j <= i)
                {
                    c.coordinates(x + j, y + i, symbol);
                }
            }
        }
    }
};

class Square : public Rectangle
{
public:
    Square(int a, int x, int y, char symbol) : Rectangle(a, a, x, y, symbol) {}
};

class Circle : public Figure
{
private:
    int r;

public:
    Circle(int r, int x, int y, char symbol) : Figure(x, y, symbol), r(r) {}
    void draw(Canvas &c) override
    {
        for (int i = -r; i <= r; i++)
        {
            for (int j = -r; j <= r; j++)
            {
                if (std::pow(i, 2) + std::pow(j, 2) <= std::pow(r, 2))
                {
                    c.coordinates(x + i, y + j, symbol);
                }
            }
        }
    }
};

int main()
{
    std::ifstream data_file("data.txt");
    if (!data_file.is_open())
    {
        std::cerr << "file open error!" << std::endl;
        return 1;
    }

    int canvas_width, canvas_height;
    char empty_symbol;
    std::string filename;
    std::vector<Figure *> shapes; // vektor wskanikow pozwala na przechowywanie obiektow roznych klas dziedziczacych po Figure
    std::string my_shape;
    data_file >> canvas_width >> canvas_height >> filename >> empty_symbol;

    ASCIICanvas canvas(canvas_width, canvas_height, empty_symbol);

    while (data_file >> my_shape)
    {
        if (my_shape == "Rectangle")
        {
            int a, b, x, y;
            char symbol;
            data_file >> a >> b >> x >> y >> symbol;
            shapes.push_back(new Rectangle(a, b, x, y, symbol));
        }
        else if (my_shape == "Square")
        {
            int a, x, y;
            char symbol;
            data_file >> a >> x >> y >> symbol;
            shapes.push_back(new Square(a, x, y, symbol));
        }
        else if (my_shape == "Triangle")
        {
            int a, h, x, y;
            char symbol;
            data_file >> a >> h >> x >> y >> symbol;
            shapes.push_back(new Triangle(a, h, x, y, symbol));
        }
        else if (my_shape == "Circle")
        {
            int r, x, y;
            char symbol;
            data_file >> r >> x >> y >> symbol;
            shapes.push_back(new Circle(r, x, y, symbol));
        }
    }

    for (auto &element : shapes)
    {
        element->draw(canvas);
    }

    canvas.draw_to_file(filename);

    return 0;
}