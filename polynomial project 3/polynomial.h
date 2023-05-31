#pragma once

// ==================================
// What does a polynomial consist of?
// ==================================

struct Node {
	double coeff;
	unsigned int exp;
	Node* next;
};

struct LinkedList {
	Node* head;
};

using Term = Node;
using Polynomial = LinkedList;

// =========================
// What can a polynomial do?
// =========================

void initPoly(Polynomial*);

void addTermWithPoly(Term, Polynomial*);

void addPolyWithPoly(Polynomial, Polynomial*);

void getDegFromPoly(Polynomial, unsigned int*);

void compareTwoPolys(Polynomial, Polynomial);

void printPoly(Polynomial);

void releasePoly(Polynomial*);

// ======================================
// How does a polynomial do those things?
// --> polynomial.cpp <--
// ======================================