#pragma once

#include <iostream>
#include <vector>



class Vector2{
	
	public:
	
	float x;
	float y;
	
	Vector2(float xx, float yy);
	Vector2(const Vector2& other);
	Vector2(const std::vector<float>& other);
	Vector2(float xyz);
	Vector2(void);

	void getRaw(float* data) const;
	
	friend Vector2 operator +(const Vector2& a, const Vector2& b);
	friend Vector2 operator -(const Vector2& a, const Vector2& b);
	friend float operator *(const Vector2& a, const Vector2& b);	
	
	friend Vector2 operator *(const Vector2& a, float c);
	inline friend Vector2 operator *(float c, const Vector2& a) { return (a * c); }
	
	friend Vector2 operator /(const Vector2& a, float c);
	
	friend float operator ^(const Vector2& a, const Vector2& b);
	friend bool operator ==(const Vector2& a, const Vector2& b);	
	friend Vector2 operator %(const Vector2& a, const Vector2& b);
	float& operator [](const int indx);			
	
	void operator =(const Vector2& a);

	void operator +=(const Vector2 &a);
	void operator -=(const Vector2 &b);

	void operator *=(float c);

	void operator /=(float c);

	friend std::ostream& operator <<(std::ostream& os, const Vector2& a);
	
	float norm(void) const;
	friend float norm(Vector2& a);
	friend float norm2(const Vector2& a);

	friend Vector2 abs(const Vector2& a);
	
	void normalize(void);
	friend Vector2 normalize(Vector2& a);

	friend float distance(const Vector2& a, const Vector2& b);

	friend bool nonNegative(const Vector2& a);
};


