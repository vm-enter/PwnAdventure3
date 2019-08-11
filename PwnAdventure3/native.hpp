#pragma once

#ifndef Padding
#define Padding(x) struct { unsigned char __padding##x[(x)]; };
#endif

#ifndef Padding_add
#define Padding_add(x, y) struct { unsigned char __padding##x[(x) + (y)]; };
#endif

#ifndef Padding_sub
#define Padding_sub(x, y) struct { unsigned char __padding##x[(x) - (y)]; };
#endif

#ifndef static_assert_size
#define static_assert_size(actual, expected) \
	static_assert((actual) == (expected), "Size assertion failed: " #actual " != " #expected ".");
#endif

#ifndef static_assert_offset
#define static_assert_offset(type, member, expected) \
	static_assert((offsetof(type, member)) == (expected), "Offset assertion failed .");
#endif