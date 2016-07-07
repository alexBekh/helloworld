// sfml-box2d_test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "test1.h"
#include "revolute_joint.h"
#include "prismatic_joint.h"
#include "pulley_joint.h"
#include "test2.h"
#include "pong_box2d.h"
#include "gear_joint.h"
#include "wheel_joint.h"
#include "weld_joint.h"
#include "rope_joint.h"
#include "motor_joint.h"


static sf::Font g_font;


int main()
{
	if (!g_font.loadFromFile("../res/Bohemian typewriter.ttf"))
	{
		std::cout << "Error: can't load font" << std::endl;
		return 1;
	}
	//test1();
	//test2();
	////pong_box2d();
	//revolute_joint();
	//prismatic_joint();
	//pulley_joint();
	//gear_joint();
	//wheel_joint();
	//weld_joint();
	//rope_joint();
	motor_joint();

    return 0;
}

