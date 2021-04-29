#pragma once




namespace Dirac
{

namespace Graphics
{

struct Attribute
{
	unsigned int mCount;
	unsigned int mGLType;
	unsigned int mStride;
	unsigned int mOffset;
};

class VertexArray
{	
	private:

	unsigned int mID { 0 };
	unsigned int mCurrentAttribute { 0 };

	public:
	
	VertexArray(void);
	~VertexArray(void);

	void bind(bool Bind = true);

	void addAttribute(Attribute tAttribute);
};

};


};
