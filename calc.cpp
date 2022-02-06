#include "pch.h"

unsigned char arrayC(unsigned char TAM, unsigned char POS)
{
	return (POS % TAM);

}
unsigned char arrayL(unsigned char TAM, unsigned char POS)
{
	return (POS / TAM);

}
unsigned char arrayP(unsigned char TAM, unsigned char I, unsigned char J)
{
	return (TAM * I + J);
}

