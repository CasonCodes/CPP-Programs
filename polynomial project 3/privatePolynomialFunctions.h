#pragma once
#include "privatePolynomialFunctions.h"
#include "polynomial.h"

bool empty(Polynomial);

int getPolySize(Polynomial*);

void insertTerm(Term*, Polynomial*);