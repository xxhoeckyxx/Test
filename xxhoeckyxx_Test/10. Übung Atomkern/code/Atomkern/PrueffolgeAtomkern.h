/**
 * OPR-Praktikum SS 2012
 * Aufgabe 9
 * @author Thomas Mahr
 */

#pragma once
#include "Prueffolge.h"

class PrueffolgeAtomkern : public Prueffolge
{
public:

	PrueffolgeAtomkern();

private:

	static void pruefungAtomkernErstellen();
	static void pruefungAusgabe();
	static void pruefungProton();
	static void pruefungNeutron();
	static void pruefungOperatorPlusGleich();
	static void pruefungOperatorMinusGleich();
	static void pruefungKernfusion();
	static void pruefungKernspaltung();
};
