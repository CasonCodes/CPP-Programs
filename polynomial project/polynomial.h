// HEADER FILE FOR CLIENT | DECLARATIONS

#pragma once

// ==================================
// What does a polynomial consist of?
// ==================================

struct Term {
	Term* nextTerm;
	double coefficient;
	int exponent;
};

struct Polynomial {
	Term* Head;
};

// =========================
// What can a polynomial do?
// =========================

bool initialize(Polynomial*);

bool addTerm(Polynomial, Term);

bool addPolynomial(Polynomial, Polynomial);
 
int  getDegree(Polynomial);

bool compare(Polynomial, Polynomial);

bool print(Polynomial);

bool releaseMemory(Polynomial);

// ======================================
// How does a polynomial do those things?
// --> polynomial.cpp <--
// ======================================