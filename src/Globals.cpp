#include "Globals.hpp"
#include "Block.hpp"
#include <ncurses.h>

int Globals::version[3] = { 0, 0, 1 };

//  __   __    ___   ____  ____  _
// ( (` / /`  | |_) | |_  | |_  | |\ |
// _)_) \_\_, |_| \ |_|__ |_|__ |_| \|

bool Globals::Screen::center_horizontally = true;
bool Globals::Screen::center_vertically   = true;

bool Globals::Screen::show_borders  = true;
bool Globals::Screen::fancy_borders = true;
bool Globals::Screen::outer_border  = true;

bool Globals::Screen::use_colors = true;

//  __     __    _      ____
// / /`_  / /\  | |\/| | |_
// \_\_/ /_/--\ |_|  | |_|__

int Globals::Game::next_pieces   = 5;
int Globals::Game::initial_noise = 0;

bool Globals::Game::has_ghost = true;
bool Globals::Game::can_hold  = true;

bool Globals::Game::has_statistics      = true;
bool Globals::Game::has_line_statistics = true;

short Globals::Game::random_algorithm = 0;

bool Globals::Game::has_game_over_animation = true;
int  Globals::Game::line_clear_timeout_us   = 200000; // microseconds

bool Globals::Game::slide_left  = false;
bool Globals::Game::slide_right = false;

// _____  _     ____  _      ____
//  | |  | |_| | |_  | |\/| | |_
//  |_|  |_| | |_|__ |_|  | |_|__

bool Globals::Theme::piece_has_colors = true;
bool Globals::Theme::ghost_has_colors = true;
bool Globals::Theme::show_pivot_block = false;
bool Globals::Theme::lock_piece_color = false;

Block* Globals::Theme::clear_line      = NULL;
Block* Globals::Theme::piece_colorless = NULL;
Block* Globals::Theme::piece           = NULL;
Block* Globals::Theme::ghost           = NULL;
Block* Globals::Theme::locked          = NULL;

Block* Globals::Theme::piece_S = NULL;
Block* Globals::Theme::piece_Z = NULL;
Block* Globals::Theme::piece_O = NULL;
Block* Globals::Theme::piece_I = NULL;
Block* Globals::Theme::piece_L = NULL;
Block* Globals::Theme::piece_J = NULL;
Block* Globals::Theme::piece_T = NULL;

//  __    ___   _      ____  _   __
// / /`  / / \ | |\ | | |_  | | / /`_
// \_\_, \_\_/ |_| \| |_|   |_| \_\_/

std::string Globals::Config::config_filename = "";
std::string Globals::Config::hscore_filename = "";

//  _   _      ___   _    _____
// | | | |\ | | |_) | | |  | |
// |_| |_| \| |_|   \_\_/  |_|

int Globals::Input::left                    = KEY_LEFT;
int Globals::Input::right                   = KEY_RIGHT;
int Globals::Input::up                      = KEY_UP;
int Globals::Input::down                    = KEY_DOWN;
int Globals::Input::drop                    = ' ';
int Globals::Input::rotate_clockwise        = 'x';
int Globals::Input::rotate_counterclockwise = 'z';
int Globals::Input::pause                   = 'p';
int Globals::Input::hold                    = 'c';
int Globals::Input::toggle_statistics       = '2';
int Globals::Input::help                    = 'h';
int Globals::Input::high_scores             = '1';
int Globals::Input::quit                    = 'q';

//  _   _      _  _____
// | | | |\ | | |  | |
// |_| |_| \| |_|  |_|

void Globals::init()
{
	Globals::Theme::clear_line = new Block(Colors::pair(COLOR_WHITE, COLOR_DEFAULT, false),
	                ':', ':');

	Globals::Theme::piece_colorless = new Block(Colors::pair(COLOR_BLACK, COLOR_WHITE, false),
	                ' ', ' ');

	Globals::Theme::piece = new Block(Colors::pair(COLOR_BLACK, COLOR_WHITE, false),
	                ' ', ' ');

	Globals::Theme::ghost = new Block(Colors::pair(COLOR_BLACK, COLOR_WHITE, true),
	                '[', ']');

	Globals::Theme::locked = new Block(Colors::pair(COLOR_WHITE, COLOR_WHITE, false),
	                ' ', ' ');

	Globals::Theme::piece_S = new Block(Colors::pair(COLOR_WHITE, COLOR_GREEN, false),
	                ' ', ' ');

	Globals::Theme::piece_Z = new Block(Colors::pair(COLOR_WHITE, COLOR_RED, false),
	                ' ', ' ');

	Globals::Theme::piece_O = new Block(Colors::pair(COLOR_WHITE, COLOR_YELLOW, false),
	                ' ', ' ');

	Globals::Theme::piece_I = new Block(Colors::pair(COLOR_WHITE, COLOR_CYAN, true),
	                ' ', ' ');

	Globals::Theme::piece_L = new Block(Colors::pair(COLOR_WHITE, COLOR_YELLOW, true),
	                ' ', ' ');

	Globals::Theme::piece_J = new Block(Colors::pair(COLOR_WHITE, COLOR_BLUE, false),
	                ' ', ' ');

	Globals::Theme::piece_T = new Block(Colors::pair(COLOR_WHITE, COLOR_MAGENTA, false),
	                ' ', ' ');

}
