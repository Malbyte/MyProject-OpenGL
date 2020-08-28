#include "Non_Defined_Functions.h"

#ifndef _INCLUDED_CLOCK_FUNCTION
//There is no official implementation of this in the program so this subsitutes
void Clock_10MS() {
	printf("10MilliSecond\n");
}
void Clock_S() {
	printf("1Second\n");
}
void Clock_M() {
	printf("1minute\n");
}
#endif // !_INCLUDED_CLOCK_FUNCTION