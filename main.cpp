#include "vec3.hpp"

int main() {
	water::vec3 u{ 1,0,0 }, v{ 0,1,0 };
	std::cout << "u = " << u << ", v = " << v << std::endl;
	std::cout << "u + v = " << u + v << std::endl;
	std::cout << "dot(u,v) = " << dot(u, v) << std::endl;
	std::cout << "cross(u,v) = " << cross(u, v) << std::endl;
	auto& [u_x, u_y, u_z] = u;
	u_x = 0.9; u_y = 0.7; u_z = 0.6;
	std::cout << u << std::endl;
	return 0;
}