//
//Created by 0x0015 on 06-05-2022 :)
//

#pragma once
#include "Cube.h"
#include "Algorithm.h"
#include <iostream>
#include <vector>

namespace CubeUtil{
	namespace Search{
		void solve_recur(Cube& cube, bool extended, float maxDepth);
		void solve(Cube& cube, unsigned int depth);
	}
}
