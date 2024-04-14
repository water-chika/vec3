#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <tuple>
#include <random>

namespace water {
	class vec3 {
	public:
		vec3() : m_e{} {}
		vec3(double e0, double e1, double e2) : m_e{ e0, e1, e2 } {}
		double operator[](int i) const {
			return m_e[i];
		}
		double& operator[](int i) {
			return m_e[i];
		}
		template<std::size_t I>
		double& get() {
			return m_e[I];
		}
		vec3& operator+=(const vec3& v) {
			m_e[0] += v.m_e[0];
			m_e[1] += v.m_e[1];
			m_e[2] += v.m_e[2];
			return *this;
		}
		vec3& operator-=(const vec3& v) {
			m_e[0] -= v.m_e[0];
			m_e[1] -= v.m_e[1];
			m_e[2] -= v.m_e[2];
			return *this;
		}
		vec3& operator*=(double t) {
			m_e[0] *= t;
			m_e[1] *= t;
			m_e[2] *= t;
			return *this;
		}
		vec3& operator/=(double t) {
			return *this *= 1 / t;
		}
		double length() const {
			return std::hypot(m_e[0], m_e[1], m_e[2]);
		}
		double length_squared() const {
			return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
		}
		vec3 unit() {
			vec3 u = *this;
			u /= this->length();
			return u;
		}
	private:
		std::array<double, 3> m_e;
	};
	inline vec3 operator+(const vec3& u, const vec3& v) {
		return vec3{ u[0] + v[0], u[1] + v[1], u[2] + v[2] };
	}
	inline vec3 operator-(const vec3& u) {
		return vec3{ -u[0], -u[1], -u[2] };
	}
	inline vec3 operator-(const vec3& u, const vec3& v) {
		return vec3{ u[0] - v[0], u[1] - v[1], u[2] - v[2] };
	}
	inline vec3 operator*(double t, const vec3& v) {
		return vec3{ t * v[0], t * v[1], t * v[2] };
	}
	inline vec3 operator*(const vec3& v, double t) {
		return vec3{ v[0] * t, v[1] * t, v[2] * t };
	}
	inline vec3 operator/(const vec3& v, double t) {
		return vec3{ v[0] / t, v[1] / t, v[2] / t };
	}
	inline double dot(const vec3& u, const vec3& v) {
		return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
	}
	inline vec3 cross(const vec3& u, const vec3& v) {
		return vec3{ 
			u[1] * v[2] - u[2] * v[1],
			u[2] * v[0] - u[0] * v[2],
			u[0] * v[1] - u[1] * v[0]
		};
	}
	inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
		out << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
		return out;
	}
	// This would distribute random vec3 on [a, b).
	class uniform_vec3_distribution {
	public:
		uniform_vec3_distribution() : uniform_vec3_distribution{ vec3{} } {}
		uniform_vec3_distribution(const vec3& a, const vec3& b = vec3{ 1,1,1 })
			:
			m_a{ a },
			m_b{ b },
			m_real_distribution{ 0, 1 }
		{}
		void reset() {
			m_real_distribution.reset();
		}
		vec3 operator()(auto& generator) {
			return m_a + (m_b - m_a) * m_real_distribution(generator);
		}
		vec3 a() const {
			return m_a;
		}
		vec3 b() const {
			return m_b;
		}
	private:
		vec3 m_a;
		vec3 m_b;
		std::uniform_real_distribution<double> m_real_distribution;
	};
	class uniform_sphere_distribution {
	public:
		uniform_sphere_distribution(double m_radius) : m_real_distribution{ -m_radius, +m_radius } {}
		void reset() {
			m_real_distribution.reset();
		}
		vec3 operator()(auto& generator) {
			while (true) {
				vec3 p{ m_real_distribution(generator), m_real_distribution(generator), m_real_distribution(generator) };
				if (p.length_squared() < 1) {
					return p;
				}
			}
		}
	private:
		std::uniform_real_distribution<double> m_real_distribution;
	};
	class uniform_unit_vec3_distribution {
	public:
		uniform_unit_vec3_distribution() : m_sphere_distribution{ 1.0 } {}
		void reset() {
			m_sphere_distribution.reset();
		}
		vec3 operator()(auto& generator) {
			return m_sphere_distribution(generator).unit();
		}
	private:
		uniform_sphere_distribution m_sphere_distribution;
	};
	template<bool On = true>
	class uniform_hemisphere_distribution {
		static_assert(On == true);
	public:
		uniform_hemisphere_distribution(const vec3& normal) : m_normal{ normal } {}
		void reset() {
			m_unit_distribution.reset();
		}
		vec3 operator()(auto& generator) {
			vec3 v = m_unit_distribution(generator);
			if (dot(v, m_normal) > 0.0) {
				return v;
			}
			else {
				return -v;
			}
		}
	private:
		vec3 m_normal;
		uniform_unit_vec3_distribution m_unit_distribution;
	};
}
namespace std {
	template<>
	class tuple_size<water::vec3> {
	public:
		static constexpr int value = 3;
	};
	template<>
	class tuple_element<0, water::vec3> {
		using type = double;
	};
	template<>
	class tuple_element<1, water::vec3> {
		using type = double;
	};
	template<>
	class tuple_element<2, water::vec3> {
		using type = double;
	};
}
