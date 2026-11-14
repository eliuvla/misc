#pragma once

#include "raylib.h"

Vector2 curve_parametrization(float t);


Vector2 test_curve(float t){
	return {t,2*t};
}