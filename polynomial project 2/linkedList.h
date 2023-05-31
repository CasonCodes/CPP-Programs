#pragma once

// ==========================
// What can a linked list do?
// ==========================

bool insert(Polynomial*, Term*);

bool isEmpty(Polynomial*);

bool remove();

bool sort();

bool edit(Term*, double, unsigned int);

// =========================================
// How does the linked list do those things?
// --> polynomial.cpp <--
// =========================================