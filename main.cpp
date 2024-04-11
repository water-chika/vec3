#include "vec3.hpp"

int main() {
	water::vec3 u{ 1,0,0 }, v{ 0,1,0 };
	std::cout << "u = " << u << ", v = " << v << std::endl;
	std::cout << "u + v = " << u + v << std::endl;
	std::cout << "dot(u,v) = " << dot(u, v) << std::endl;
	std::cout << "cross(u,v) = " << cross(u, v) << std::endl;
	return 0;
}