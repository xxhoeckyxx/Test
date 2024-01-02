/**
 * OPR-Praktikum SS 2012
 * Aufgabe 9
 * @author Thomas Mahr
 */

#pragma once
#include "Prueffolge.h"
class Atomkern;

class PrueffolgeReaktor : public Prueffolge
{
public:

	PrueffolgeReaktor();

private:

	static const Atomkern DEUTERIUM;
	static const Atomkern TRITIUM;
	static const Atomkern HELIUM4;	

	static void pruefungReaktorErstellen();
	static void pruefungReaktorBetrieb1();
	static void pruefungReaktorBetrieb2();
	static void pruefungReaktorBetrieb3();
};

