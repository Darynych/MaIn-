#include "Physics.h"   //Препроцессор - это программа, которая принимает вашу программу, вносит некоторые изменения (например, включают 
//файлы (#include), расширение макросов (#define) и в основном все, что начинается с #), и дает "чистый" результат компилятору.
//Препроцессор работает так, когда видит #include: Содержимое physics.h почти буквально получает копию, вставленную в файл, включая его. 
#include "Graphics.h"

int main(int argc, char* args[]) // Эта строка — заголовок главной функции main(), в скобочках объявлены параметры argс и argv.Так вот,
//если программу запускать через командную строку, то существует возможность передать какую - либо информацию этой программе, для этого и 
//существуют параметры argc и argv[].Параметр argc имеет тип данных int, и содержит количество параметров, передаваемых в функцию main.
//Причем argc всегда не меньше 1, даже когда мы не передаем никакой информации, так как первым параметром считается имя функции.
//Параметр argv[] это  массив указателей на строки.Через командную строку  можно передать только данные строкового типа.
//Указатели и строки — это две большие темы, под которые созданы отдельные разделы.Так вот именно через параметр argv[] и передается какая - либо информация. /
{

	sf::Time Elapsed_Time = sf::seconds(0.f), RecentUpdateTime = sf::seconds(0.f);

	sf::Vector2u const window_size(Window_Width, Window_Height);//параметры окна?
	sf::Vector2u const graph_window_size(GraphWindowWidth, GraphWindowHeight);//параметры графичексие окна
	sf::Vector2f const x_axis_range(Window_Width*VesselSizeCoeff_x, Window_Width*(1 - VesselSizeCoeff_x));
	sf::Vector2f const y_axis_range(Window_Height*VesselSizeCoeff_y, Window_Height*(1 - VesselSizeCoeff_y));
	
	CMolecularGas Gas(x_axis_range, y_axis_range); //двумерная функция для молекул газа
	CDrawer Drawer(window_size); //информационные функции???? просрисовка графика
	// CGraph Graph;

	Gas.SetStartPosition(NumberOfMolecules);
	Drawer.Set(Gas);

	sf::Clock clock;
	size_t counter = 0;

	if (GraphIsActive) {
		// Graph.Create(graph_window_size);
		// Graph.Set();
	}

	while (Elapsed_Time.asSeconds() <= MaxTime) {

		if (Elapsed_Time.asMilliseconds() - RecentUpdateTime.asMilliseconds() >= 2000) {
			RecentUpdateTime = Elapsed_Time;
			Drawer.SetCounterMode(false);
		} //обработка времени, представляющее общее число миллисекунд
		else Drawer.SetCounterMode(true);

		Gas.MakeStep(Jump_Time);
		if (counter == 4) {
			Gas.UpdateSpeed(4 * Jump_Time);
			counter = 0;
		}
		else counter++;

		if (Drawer.DrawCurrent(Gas) == false) break;

		if (GraphIsActive && Drawer.ShowCounterMode() == false) {
			// Graph.ShowCondition(Drawer.ShowMediumEnergy(), Drawer.ShowMediumPressure());
		}

		// Graph.UpdateShow();
		Elapsed_Time += clock.restart();
	}

	return 0;
}
//самое мясо - это функции CMolecularGas::pair_collision и CMolecularGas::calculate_collision_time - здесь частицы отталкиваются от друг друга и со  стенками + время
//в файле Physics.h есть координаты, скорость и ускорение векторов
//Physics.cpp там лежат физические смещения частиц