#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <SFML/Graphics.hpp>

struct Object
{
	int GetPropertyInt(std::string name);//номер свойства объекта в нашем списке
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);
 
	std::string name;//объ€вили переменную name типа string
	std::string type;//а здесь переменную type типа string
	sf::Rect<float> rect;//тип Rect с нецелыми значени€ми
	std::map<std::string, std::string> properties;//создаЄм ассоциатиный массив. ключ - строковый тип, значение - строковый
 
	sf::Sprite sprite;//объ€вили спрайт
};
 
struct Layer//слои
{
	int opacity;//непрозрачность сло€
	std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
};

#endif 