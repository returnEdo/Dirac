#pragma once

#include <GL/glew.h>
#include <iostream>

// PRINTING MACROS

// base print
#define PRINT(x) \
	std::cout << x << std::endl;

// deduce tag
#define PRINT_AUTO(x) \
	std::cout << "\t" << #x << ":\t" << x << std::endl;

// impose tag
#define PRINT_TAG(tTag, x) \
	std::cout << "\t" << tTag << ":\t" << x << std::endl;

// array with index
#define PRINT_ARRAY(x) \
	for (int i = 0; i < x.size(); i++) \
	{ \
		PRINT_TAG(i, x[i]); \
	}


// CLASS MACROS

// add member (uppercase name)
#define ADD_MEMBER(tAccess, type, name) \
	tAccess: type m ## name

// getter
#define GETTER(type, name) \
	public: inline type get_ ## m ## name(void)	{ return m ## name; }

// getter ref
#define GETTER_REF(type, name) \
	public: inline const type ## & get_ ## m ## name(void) const { return m ## name; }

// setter
#define SETTER(type, name) \
	public: inline void set_ ## m ## name(type tName) { m ## name = tName; } 

// setter ref
#define SETTER_REF(type, name) \
	public: inline void set_ ## m ## name(const type ## & tName) { m ## name = tName; } 

// add field
#define ADD_FIELD(tAccess, type, name) \
	ADD_MEMBER(tAccess, type, name); \
	GETTER(type, name) \
	SETTER(type, name)

// add ref field
#define ADD_FIELD_REF(tAccess, type, name) \
	ADD_MEMBER(tAccess, type, name); \
	GETTER(type, name) \
	SETTER(type, name)


// ASSERTION
#define DIRAC_ASSERT(tCondition, tMessage) \
	if (not (tCondition)) \
	{ \
		std::cout << "\n\t- - - - - - - - - - - - - - - - - - - - - - " << std::endl; \
		std::cout << "\n\tDIRAC ASSERTION failed ..." << std::endl; \
		std::cout << "\tin FILE:\t" << __FILE__ << std::endl; \
		std::cout << "\tin FUNCTION:\t" << __func__ << std::endl; \
		std::cout << "\tat LINE:\t" << __LINE__ << std::endl; \
		std::cout << "\tDIRAC ASSERTION message: " << std::endl; \
		std::cout << "\t" << tMessage << std::endl; \
		std::cout << "\n\t- - - - - - - - - - - - - - - - - - - - - - " << std::endl; \
		exit(1); \
	}

// DEBUG
#define DBG PRINT("\t@ line:\t" << __LINE__)

// ARRAY
#define DIRAC_COUNT(x, tType)	sizeof(x) / sizeof(tType)
