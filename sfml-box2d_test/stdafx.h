// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <memory>
#include <functional>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

using namespace sf;

#include"coords_convert.h"

extern sf::Font g_font;

#define LENGTH_OF(x) sizeof(x) / sizeof(x[0])

// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
