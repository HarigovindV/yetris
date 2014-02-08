#include <Interface/MenuItem.hpp>
#include <Config/Globals.hpp>
#include <Misc/Utils.hpp>

MenuItem::MenuItem(std::string label, int value):
	type(MenuItem::ITEM),
	label(label),
	value(value)
{ }

void MenuItem::draw(Window* window, int x, int y, int width, bool hilite)
{
	window->print(this->label.substr(0, width), x, y,
	              ((hilite) ?
	               Globals::Theme::hilite_text:
	               Globals::Theme::text));
}
void MenuItem::handleInput(int input)
{
	UNUSED(input);
}

