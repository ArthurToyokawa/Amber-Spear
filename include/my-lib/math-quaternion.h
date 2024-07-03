#ifndef __MY_LIB_MATH_QUATERNION_HEADER_H__
#define __MY_LIB_MATH_QUATERNION_HEADER_H__

#include <concepts>
#include <type_traits>
#include <ostream>
#include <utility>

#include <cmath>

#include <my-lib/std.h>
#include <my-lib/math-vector.h>
#include <my-lib/math-matrix.h>

namespace Mylib
{
namespace Math
{

#ifdef MYLIB_MATH_BUILD_OPERATION
#error nooooooooooo
#endif

// ---------------------------------------------------

template <typename T>
class Quaternion
{
public:
	using Type = T;
	using Vector = Mylib::Math::Vector<T, 3>;

	consteval static Type fp (const auto v)
	{
		return static_cast<Type>(v);
	}

	// We store in this format (x, y, z, w), where x,y,z are the vector part,
	// and w is the scalar part, so that we can use the same memory layout
	// as in GLSL.
	union {
		struct {
			Vector v;
			T w__;
		};
		struct {
			T x;
			T y;
			T z;
			T w;
		};
		T data[4];
	};

	// ------------------------ Constructors

	Quaternion () noexcept = default;

	Quaternion (const Vector& v_, const T w_) noexcept
		: v(v_), w__(w_)
	{
	}

	Quaternion (const T x_, const T y_, const T z_, const T w_) noexcept
		: x(x_), y(y_), z(z_), w(w_)
	{
	}

	// Create a scalar (or real) quaternion.
	// The vector part is set to zero.

	Quaternion (const T w_) noexcept
		: x(0), y(0), z(0), w(w_)
	{
	}

	// Create a vector (or imaginary, or pure) quaternion.
	// The scalar part is set to zero.

	Quaternion (const Vector& v_) noexcept
		: v(v_), w__(0)
	{
	}

	// ------------------------ operator=

	// use default ones, so no need to define them

	// ------------------------ Other stuff

	constexpr Type& operator[] (const uint32_t i) noexcept
	{
		static_assert(sizeof(Quaternion) == (4 * sizeof(Type)));
		return this->data[i];
	}

	constexpr Type operator[] (const uint32_t i) const noexcept
	{
		static_assert(sizeof(Quaternion) == (4 * sizeof(Type)));
		return this->data[i];
	}

	#undef MYLIB_MATH_BUILD_OPERATION
	#define MYLIB_MATH_BUILD_OPERATION(OP) \
		constexpr Quaternion& operator OP (const Quaternion& other) noexcept \
		{ \
			for (uint32_t i = 0; i < 4; i++) \
				this->data[i] OP other[i]; \
			return *this; \
		}
	
	MYLIB_MATH_BUILD_OPERATION( += )
	MYLIB_MATH_BUILD_OPERATION( -= )

	#undef MYLIB_MATH_BUILD_OPERATION
	#define MYLIB_MATH_BUILD_OPERATION(OP) \
		constexpr Quaternion& operator OP (const Type s) noexcept \
		{ \
			for (uint32_t i = 0; i < 4; i++) \
				this->data[i] OP s; \
			return *this; \
		}
	
	MYLIB_MATH_BUILD_OPERATION( *= )
	MYLIB_MATH_BUILD_OPERATION( /= )

	// ---------------------------------------------------

	constexpr Quaternion& operator *= (const Quaternion& other) noexcept
	{
		*this = *this * other;
		return *this;
	}

	// ---------------------------------------------------

	constexpr T length_squared () const noexcept
	{
		Type value = 0;
		for (uint32_t i = 0; i < 4; i++)
			value += this->data[i] * this->data[i];
		return value;
	}

	constexpr T length () const noexcept
	{
		return std::sqrt(this->length_squared());
	}

	// ---------------------------------------------------

	/*
		Converts the quaternion to a pair of a normalized axis-vector and an angle.
		It considers the quaternion as a rotation quaternion (unit quaternion length=1).
	*/

	std::pair<Vector, T> to_axis_angle () const noexcept
	{
		std::pair<Vector, T> r;
		Vector& axis = r.first;
		T& angle = r.second;

		const T length = this->v.length();

		if (length == fp(0)) [[unlikely]]
			axis.set(1, 0, 0);
		else
			axis = this->v / length; // normalize
		
		angle = std::acos(this->w) * fp(2);

		return r;

/*		const T angle = std::acos(this->w) * 2;
		const T s = std::sqrt(1 - this->w * this->w);

		if (s < 0.001f)
			return std::make_pair(Vector(1, 0, 0), 0);

		return std::make_pair(this->v / s, angle);*/
	}

	// ---------------------------------------------------

	void set_rotation (const Vector& axis, const T angle) noexcept
	{
		const T half_angle = angle / fp(2);
		this->v = Mylib::Math::normalize(axis) * std::sin(half_angle);
		this->w = std::cos(half_angle);
	}

	// ---------------------------------------------------

	// normalize returns the length before normalization.
	// Got the idea from the MathFu library.

	constexpr Type normalize () noexcept
	{
		const Type len = this->length();
		for (uint32_t i = 0; i < 4; i++)
			this->data[i] /= len;
		return len;
	}

	constexpr void conjugate () noexcept
	{
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;
	}

	/*
		If the quaternion is normalized, then its inverse is equal to its conjugate.
	*/

	constexpr void invert_normalized () noexcept
	{
		this->conjugate();
	}

	constexpr void invert () noexcept
	{
		const Type len = this->length_squared();
		this->conjugate();
		for (uint32_t i = 0; i < 4; i++)
			this->data[i] /= len;
	}

	// ---------------------------------------------------

	constexpr void set_zero () noexcept
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	constexpr void set_identity () noexcept
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;
	}

	// ---------------------------------------------------

	static consteval Quaternion zero () noexcept
	{
		Quaternion q;
		q.set_zero();
		return q;
	}

	static consteval Quaternion identity () noexcept
	{
		Quaternion q;
		q.set_identity();
		return q;
	}

	static constexpr Quaternion rotation (const Vector& axis, const T angle) noexcept
	{
		Quaternion q;
		q.set_rotation(axis, angle);
		return q;
	}
};

// ---------------------------------------------------

using Quaternionf = Quaternion<float>;
using Quaterniond = Quaternion<double>;

static_assert(sizeof(Quaternionf) == (4 * sizeof(float)));
static_assert(sizeof(Quaterniond) == (4 * sizeof(double)));

// ---------------------------------------------------

#undef MYLIB_MATH_BUILD_OPERATION
#define MYLIB_MATH_BUILD_OPERATION(OP) \
	template <typename T> \
	constexpr Quaternion<T> operator OP (const Quaternion<T>& a, const Quaternion<T>& b) noexcept \
	{ \
		Quaternion<T> r; \
		for (uint32_t i = 0; i < 4; i++) \
			r[i] = a[i] OP b[i]; \
		return r; \
	}

MYLIB_MATH_BUILD_OPERATION( + )
MYLIB_MATH_BUILD_OPERATION( - )

#undef MYLIB_MATH_BUILD_OPERATION
#define MYLIB_MATH_BUILD_OPERATION(OP) \
	template <typename T> \
	constexpr Quaternion<T> operator OP (const Quaternion<T>& a, const T s) noexcept \
	{ \
		Quaternion<T> r; \
		for (uint32_t i = 0; i < 4; i++) \
			r[i] = a[i] OP s; \
		return r; \
	}

MYLIB_MATH_BUILD_OPERATION( * )
MYLIB_MATH_BUILD_OPERATION( / )

// ---------------------------------------------------

template <typename T>
constexpr Quaternion<T> operator- (const Quaternion<T>& q) noexcept
{
	Quaternion<T> r;
	for (uint32_t i = 0; i < 4; i++)
		r[i] = -q[i];
	return r;
}

// ---------------------------------------------------

template <typename T>
constexpr Quaternion<T> normalize (const Quaternion<T>& q) noexcept
{
	return q / q.length();
}

// ---------------------------------------------------

template <typename T>
constexpr Quaternion<T> conjugate (const Quaternion<T>& q) noexcept
{
	return Quaternion<T>(-q.x, -q.y, -q.z, q.w);
}

// ---------------------------------------------------

/*
	If the quaternion is normalized, then its inverse is equal to its conjugate.
*/

template <typename T>
constexpr Quaternion<T> invert_normalized (const Quaternion<T>& q) noexcept
{
	return conjugate(q);
}

template <typename T>
constexpr Quaternion<T> invert (const Quaternion<T>& q) noexcept
{
	return conjugate(q) / q.length_squared();
}

// ---------------------------------------------------

template <typename T>
constexpr Quaternion<T> operator* (const Quaternion<T>& q1, const Quaternion<T>& q2) noexcept
{
	Quaternion<T> r;

	// Hamilton product

	r.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
	r.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
	r.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
	r.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
	//r.v = (b.v * a.w) + (a.v * b.w) + cross_product(a.v, b.v);
	//r.w = a.w * b.w - dot_product(a.v, b.v);

	return r;
}

// ---------------------------------------------------

template <typename T>
constexpr Vector<T, 3> rotate (const Quaternion<T>& q, const Vector<T, 3>& v) noexcept
{
	const Quaternion<T> v_(v); // create a pure quaternion from the vector
	const Quaternion<T> r = (q * v_) * conjugate(q);
	return r.v;
}

// ---------------------------------------------------

template <typename T>
std::ostream& operator << (std::ostream& out, const Quaternion<T>& q)
{
	out << "[" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << "]";
	return out;
}

// ---------------------------------------------------

#undef MYLIB_MATH_BUILD_OPERATION

} // end namespace Math
} // end namespace Mylib

#endif