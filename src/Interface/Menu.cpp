#include <Interface/Menu.hpp>
#include <Misc/Utils.hpp>
#include <Config/Globals.hpp>

Menu::Menu(int x, int y, int width, int height):
	current(nullptr),
	currentIndex(0),
	first(nullptr),
	last(nullptr),
	x(x),
	y(y),
	width(width),
	height(height),
	selected(false),
	selectedItem(nullptr)
{ }
Menu::~Menu()
{
	for (unsigned int i = 0; i < (this->item.size()); i++)
		SAFE_DELETE(this->item[i]);

	this->item.clear();
}
void Menu::add(MenuItem* item)
{
	this->item.push_back(item);

	// Means we're the first item being added!
	if (this->item.size() == 1)
	{
		this->current      = this->item.back();
		this->currentIndex = this->item.size() - 1;
	}

	// Means we're the first non-nil item being added!
	unsigned int i = 0;
	for (i = 0; i < (this->item.size()); i++)
		if (this->item[i])
			break;

	this->current      = this->item[i];
	this->currentIndex = i;
}
void Menu::addBlank()
{
	this->item.push_back(nullptr);
}
void Menu::removeByID(int id)
{
	auto it = this->item.begin();

	while (it != this->item.end())
	{
		if (!(*it))
			++it;

		if ((*it)->id == id)
		{
			if (this->current == *it)
			{
				this->goNext();
				this->currentIndex--;
			}

			this->item.erase(it);
			return;
		}
		else
			++it;
	}
}
void Menu::removeByLabel(std::string label)
{
	auto it = this->item.begin();

	while (it != this->item.end())
	{
		if (!(*it))
			++it;

		if ((*it)->label == label)
		{
			if (this->current == *it)
			{
				this->goNext();
				this->currentIndex--;
			}

			this->item.erase(it);
			return;
		}
		else
			++it;
	}
}
void Menu::draw(Window* window)
{
	for (unsigned int i = 0; i < (this->item.size()); i++)
	{
		// <rant>
		// THIS IS VERY UGLY
		// HOW CAN I LAY DOWN A CLASS HIERARCHY
		// AND OVERRIDE PARENT FUNCTIONS ON CHILD CLASSES
		// IF WHEN I HAVE A PARENT POINTER I CANT LET THE
		// COMPILER DECIDE WETHER TO CALL PARENT OR CHILD
		// FUNCTIONS?
		// </rant>

//		MenuItemCheckbox* pCheckbox = dynamic_cast<MenuItemCheckbox*>a

		// Blank Menu Item, will show horizontal line
		if (! this->item[i])
		{
			for (int j = 0; j < (this->width); j++)
				window->printChar(((Globals::Profiles::current->settings.screen.fancy_borders) ?
				                   ACS_HLINE :
				                   '-'),
				                  this->x + j,
				                  this->y + i,
				                  Colors::pair(COLOR_WHITE, COLOR_DEFAULT));


		}
		else
		{
			this->item[i]->draw(window,
			                    this->x,
			                    this->y + i,
			                    this->width,

			                    // Highlighting current item if
			                    // it's the current.
			                    (this->item[i] == this->current));
		}
	}
}
void Menu::handleInput(int input)
{
	if (input == ERR)
		return;

	switch(input)
	{
	case KEY_DOWN:
	case '\t':
		this->goNext();
		break;

	case KEY_UP:
	case KEY_BTAB:
		this->goPrevious();
		break;

	case KEY_HOME:
	case KEY_PPAGE:
		this->goFirst();
		break;

	case KEY_END:
	case KEY_NPAGE:
		this->goLast();
		break;

	case KEY_ENTER:
	case '\n':

		// Will only quit if the selected item is a simple
		// item - more complex ones doesn't quit.
		if (this->current->type == MenuItem::ITEM)
		{
			this->selected = true;
			this->selectedItem = this->current;
		}
		else
			this->current->handleInput(input);
		break;

	default:
		if (this->current)
			this->current->handleInput(input);
		break;
	}
}
void Menu::goNext()
{
	// Empty element, piece of cake
	if (this->item.size() == 0)
		return;

	// Empty element, also piece of cake
	if (this->item.size() == 1)
	{
		this->current = this->item.front();
		this->currentIndex = 0;
		return;
	}

	// Last element...
	// Well, if the last element is nil then we have
	// a problem.
	if (this->current == this->item.back())
	{
		// Assuming we're not nil, things will go smooth
		if (this->currentIndex == (this->item.size() - 1))
		{
			this->goFirst();
			return;
		}
	}

	this->currentIndex++;
	this->current = this->item[this->currentIndex];

	if (! this->current)
		this->goNext();
}
void Menu::goPrevious()
{
	if (this->item.size() == 0)
		return;

	if (this->item.size() == 1)
	{
		this->current = this->item.front();
		this->currentIndex = 0;
		return;
	}

	if (this->current == this->item.front())
	{
		if (this->currentIndex == 0)
		{
			this->goLast();
			return;
		}
	}

	this->currentIndex--;
	this->current = this->item[this->currentIndex];

	if (! this->current)
		this->goPrevious();
}
void Menu::goFirst()
{
	if (this->item.size() == 0)
		return;

	if (this->item.size() == 1)
	{
		this->current = this->item.front();
		this->currentIndex = 0;
		return;
	}

	this->current = this->item.front();
	this->currentIndex = 0;

	if (! this->current)
		this->goNext();
}
void Menu::goLast()
{
	if (this->item.size() == 0)
		return;

	if (this->item.size() == 1)
	{
		this->current = this->item.front();
		this->currentIndex = 0;
		return;
	}

	this->current = this->item.back();
	this->currentIndex = (this->item.size() - 1);

	if (! this->current)
		this->goPrevious();
}
bool Menu::willQuit()
{
	// Will only quit if the user selected an item
	// and the item selected is valid.
	return (this->selected && this->selectedItem);
}
std::string Menu::currentLabel()
{
	if (! this->current)
		this->goNext();

	return (this->current->label);
}
int Menu::currentID()
{
	if (! this->current)
		this->goNext();

	return (this->current->id);
}
bool Menu::getBool(int id)
{
	for (unsigned int i = 0; i < (this->item.size()); i++)
	{
		if (! this->item[i])
			continue;

		if (this->item[i]->id == id)
		{
			// Either the type got messed up or we have
			// two items with the same id.
			if (this->item[i]->type != MenuItem::CHECKBOX)
				return false;

			// This cast may be dangerous if the type was
			// somehow changed.
			MenuItemCheckbox* c = (MenuItemCheckbox*)this->item[i];
			return c->isChecked();
		}
	}
	return false;
}
int Menu::getInt(int id)
{
	for (unsigned int i = 0; i < (this->item.size()); i++)
	{
		if (! this->item[i])
			continue;

		if (this->item[i]->id == id)
		{
			// Either the type got messed up or we have
			// two items with the same id.
			if (this->item[i]->type != MenuItem::NUMBERBOX)
				return -1;

			// This cast may be dangerous if the type was
			// somehow changed.
			MenuItemNumberbox* c = (MenuItemNumberbox*)this->item[i];
			return c->current;
		}
	}
	return -1;
}
std::string Menu::getString(int id)
{
	for (unsigned int i = 0; i < (this->item.size()); i++)
	{
		if (! this->item[i])
			continue;

		if (this->item[i]->id == id)
		{
			// Either the type got messed up or we have
			// two items with the same id.
			if (this->item[i]->type == MenuItem::TEXTBOX)
			{
				MenuItemTextbox* c = (MenuItemTextbox*)this->item[i];
				return c->currentText;
			}
			else if (this->item[i]->type == MenuItem::TEXTLIST)
			{
				MenuItemTextlist* c = (MenuItemTextlist*)this->item[i];
				return c->currentText();
			}
			else
				return "";

			// This cast may be dangerous if the type was
			// somehow changed.
		}
	}
	return "";
}
void Menu::reset()
{
	this->selected = false;
	this->selectedItem = nullptr;
}


