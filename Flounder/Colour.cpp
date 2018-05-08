#include "Colour.hpp"

#include <cassert>
#include <sstream>
#include "Maths.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace fl
{
	const Colour Colour::CLEAR = Colour(0.0f, 0.0f, 0.0f, 0.0f);
	const Colour Colour::WHITE = Colour("#ffffff");
	const Colour Colour::BLACK = Colour("#000000");

	Colour::Colour() :
		m_r(0.0f),
		m_g(0.0f),
		m_b(0.0f),
		m_a(1.0f)
	{
	}

	Colour::Colour(const float &r, const float &g, const float &b, const float &a) :
		m_r(r),
		m_g(g),
		m_b(b),
		m_a(a)
	{
	}

	Colour::Colour(const std::string &hex, const float &a) :
		m_r(0.0f),
		m_g(0.0f),
		m_b(0.0f),
		m_a(a)
	{
		*this = hex;
	}

	Colour::Colour(const Colour &source) :
		m_r(source.m_r),
		m_g(source.m_g),
		m_b(source.m_b),
		m_a(source.m_a)
	{
	}

	Colour::Colour(const Vector3 &source) :
		m_r(source.m_x),
		m_g(source.m_y),
		m_b(source.m_z),
		m_a(1.0f)
	{
	}

	Colour::Colour(const Vector4 &source) :
		m_r(source.m_x),
		m_g(source.m_y),
		m_b(source.m_z),
		m_a(source.m_w)
	{
	}

	Colour::~Colour()
	{
	}

	Colour Colour::Add(const Colour &other) const
	{
		return Colour(m_r + other.m_r, m_g + other.m_g, m_b + other.m_b, m_a + other.m_a);
	}

	Colour Colour::Subtract(const Colour &other) const
	{
		return Colour(m_r - other.m_r, m_g - other.m_g, m_b - other.m_b, m_a - other.m_a);
	}

	Colour Colour::Multiply(const Colour &other) const
	{
		return Colour(m_r * other.m_r, m_g * other.m_g, m_b * other.m_b, m_a * other.m_a);
	}

	Colour Colour::Divide(const Colour &other) const
	{
		return Colour(m_r / other.m_r, m_g / other.m_g, m_b / other.m_b, m_a / other.m_a);
	}

	Colour Colour::Scale(const float &scalar) const
	{
		return Colour(m_r * scalar, m_g * scalar, m_b * scalar, m_a * scalar);
	}

	Colour Colour::Normalize() const
	{
		float l = Length();
		assert(l != 0.0f && "Zero length vector!");
		return Colour(m_r / l, m_g / l, m_b / l, m_a / l);
	}

	float Colour::LengthSquared() const
	{
		return m_r * m_r + m_g * m_g + m_b * m_b + m_a * m_a;
	}

	float Colour::Length() const
	{
		return std::sqrt(LengthSquared());
	}

	Colour Colour::Interpolate(const Colour &other, const float blend) const
	{
		float r = Maths::Interpolate(m_r, other.m_r, blend);
		float g = Maths::Interpolate(m_g, other.m_g, blend);
		float b = Maths::Interpolate(m_b, other.m_b, blend);
		float a = Maths::Interpolate(m_a, other.m_a, blend);
		return Colour(r, g, b, a);
	}

	Colour Colour::SmoothDamp(const Colour &target, const Colour &rate) const
	{
		return Colour(Maths::SmoothDamp(m_r, target.m_r, rate.m_r), Maths::SmoothDamp(m_g, target.m_g, rate.m_g), Maths::SmoothDamp(m_b, target.m_b, rate.m_b), Maths::SmoothDamp(m_a, target.m_a, rate.m_a));
	}

	Colour Colour::GetUnit()
	{
		float l = Length();
		return Colour(m_r / l, m_g / l, m_b / l, m_a / l);
	}

	std::string Colour::GetHex()
	{
		std::string result = "#";

		char r[255];
		snprintf(r, 255, "%.2X", static_cast<int>(m_r * 255.0f));
		result.append(r);

		char g[255];
		snprintf(g, 255, "%.2X", static_cast<int>(m_g * 255.0f));
		result.append(g);

		char b[255];
		snprintf(b, 255, "%.2X", static_cast<int>(m_b * 255.0f));
		result.append(b);

		return result;
	}

	Colour &Colour::operator=(const Colour &other)
	{
		m_r = other.m_r;
		m_g = other.m_g;
		m_b = other.m_b;
		m_a = other.m_a;
		return *this;
	}

	Colour &Colour::operator=(const std::string &hex)
	{
		int r, g, b;
		sscanf(hex.c_str() + (hex[0] == '#' ? 1 : 0), "%2x%2x%2x", &r, &g, &b);
		m_r = static_cast<float>(r) / 255.0f;
		m_g = static_cast<float>(g) / 255.0f;
		m_b = static_cast<float>(b) / 255.0f;
		return *this;
	}

	bool Colour::operator==(const Colour &other) const
	{
		return m_r == other.m_r && m_g == other.m_r && m_b == other.m_b && m_a == other.m_a;
	}

	bool Colour::operator!=(const Colour &other) const
	{
		return !(*this == other);
	}

	bool Colour::operator<(const Colour &other) const
	{
		return m_r < other.m_r && m_g < other.m_g && m_b < other.m_b && m_a < other.m_a;
	}

	bool Colour::operator<=(const Colour &other) const
	{
		return m_r <= other.m_r && m_g <= other.m_g && m_b <= other.m_b && m_a <= other.m_a;
	}

	bool Colour::operator>(const Colour &other) const
	{
		return m_r > other.m_r && m_g > other.m_g && m_b > other.m_b && m_a > other.m_a;
	}

	bool Colour::operator>=(const Colour &other) const
	{
		return m_r >= other.m_r && m_g >= other.m_g && m_b >= other.m_b && m_a >= other.m_a;
	}

	bool Colour::operator==(const float &value) const
	{
		return m_r == value && m_g == value && m_b == value && m_a == value;
	}

	bool Colour::operator!=(const float &value) const
	{
		return !(*this == value);
	}

	Colour operator+(Colour left, const Colour &right)
	{
		return left.Add(right);
	}

	Colour operator-(Colour left, const Colour &right)
	{
		return left.Subtract(right);
	}

	Colour operator*(Colour left, const Colour &right)
	{
		return left.Multiply(right);
	}

	Colour operator/(Colour left, const Colour &right)
	{
		return left.Divide(right);
	}

	Colour operator+(Colour left, float value)
	{
		return left.Add(Colour(value, value, value, value));
	}

	Colour operator-(Colour left, float value)
	{
		return left.Subtract(Colour(value, value, value, value));
	}

	Colour operator*(Colour left, float value)
	{
		return left.Multiply(Colour(value, value, value, value));
	}

	Colour operator/(Colour left, float value)
	{
		return left.Divide(Colour(value, value, value, value));
	}

	Colour operator+(float value, Colour left)
	{
		return Colour(value, value, value, value).Add(left);
	}

	Colour operator-(float value, Colour left)
	{
		return Colour(value, value, value, value).Subtract(left);
	}

	Colour operator*(float value, Colour left)
	{
		return Colour(value, value, value, value).Multiply(left);
	}

	Colour operator/(float value, Colour left)
	{
		return Colour(value, value, value, value).Divide(left);
	}

	Colour &Colour::operator+=(const Colour &other)
	{
		return *this = Add(other);
	}

	Colour &Colour::operator-=(const Colour &other)
	{
		return *this = Subtract(other);
	}

	Colour &Colour::operator*=(const Colour &other)
	{
		return *this = Multiply(other);
	}

	Colour &Colour::operator/=(const Colour &other)
	{
		return *this = Divide(other);
	}

	Colour &Colour::operator+=(float value)
	{
		return *this = Add(Colour(value, value, value, value));
	}

	Colour &Colour::operator-=(float value)
	{
		return *this = Subtract(Colour(value, value, value, value));
	}

	Colour &Colour::operator*=(float value)
	{
		return *this = Multiply(Colour(value, value, value, value));
	}

	Colour &Colour::operator/=(float value)
	{
		return *this = Divide(Colour(value, value, value, value));
	}

	std::ostream &operator<<(std::ostream &stream, const Colour &vector)
	{
		stream << vector.ToString();
		return stream;
	}

	std::string Colour::ToString() const
	{
		std::stringstream result;
		result << "Colour(" << m_r << ", " << m_g << ", " << m_b << ", " << m_a << ")";
		return result.str();
	}
}
