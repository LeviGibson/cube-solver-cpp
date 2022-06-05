//
//Created by 0x0015 on 06-05-2022 :)
//

#pragma once
#include "Cube.h"
#include <iostream>
#include <vector>

namespace CubeUtil{
	namespace Search{
		inline std::vector<int> moves;
		void solve_recur(Cube& cube, bool extended, unsigned int depth);
		void solve(Cube& cube, unsigned int depth);
	}
}
