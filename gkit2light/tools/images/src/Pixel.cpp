#include <iostream>
#include "Pixel.h"

Pixel::Pixel()
{
	r=0;
	g=0;
	b=0;
}

Pixel::Pixel(const unsigned char nr,const unsigned char ng,const unsigned char nb)
{
	r=nr;
	g=ng;
	b=nb;
}

const unsigned char Pixel::getRouge() const
{
	return r;
}

const unsigned char Pixel::getVert() const
{
	return g;
}

const unsigned char Pixel::getBleu() const
{
	return b;
}

void Pixel::setRouge(const unsigned char nr)
{
	r=nr;
}

void Pixel::setVert(const unsigned char ng)
{
	g=ng;
}

void Pixel::setBleu(const unsigned char nb)
{
	b=nb;
}
