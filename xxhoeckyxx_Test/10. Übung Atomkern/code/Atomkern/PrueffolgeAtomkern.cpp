/**
 * OPR-Praktikum SS 2012
 * Aufgabe 9
 * @author Thomas Mahr
 */

#include "PrueffolgeAtomkern.h"
#include "Atomkern.h"
#include <sstream>
using namespace std;

PrueffolgeAtomkern::PrueffolgeAtomkern()
{
	anmelden("Atomkern erstellen", &pruefungAtomkernErstellen);
	anmelden("Atomkern ausgeben", &pruefungAusgabe);
	anmelden("Proton", &pruefungProton);
	anmelden("Neutron", &pruefungNeutron);
	anmelden("operator+=", &pruefungOperatorPlusGleich);
	anmelden("operator-=", &pruefungOperatorMinusGleich);
	anmelden("Kernfusion", &pruefungKernfusion);
	anmelden("Kernspaltung", &pruefungKernspaltung);	
}

void PrueffolgeAtomkern::pruefungAtomkernErstellen() 
{
	Atomkern kern("Pu",239,94);
	SICHERSTELLEN(kern.symbol()=="Pu");
	SICHERSTELLEN(kern.ordnungszahl()==94);	
	SICHERSTELLEN(kern.massenzahl()==239);	
}

void PrueffolgeAtomkern::pruefungAusgabe() 
{
	Atomkern kern("C",12,6);	
	stringstream s;
	s << "Atomkern = " << kern << ".";
	SICHERSTELLEN(s.str()=="Atomkern = C(12,6).");
}

void PrueffolgeAtomkern::pruefungProton() 
{
	SICHERSTELLEN(Atomkern::PROTON.ordnungszahl()==1);
	SICHERSTELLEN(Atomkern::PROTON.massenzahl()==1);
}

void PrueffolgeAtomkern::pruefungNeutron() 
{
	SICHERSTELLEN(Atomkern::NEUTRON.ordnungszahl()==0);
	SICHERSTELLEN(Atomkern::NEUTRON.massenzahl()==1);
}

void PrueffolgeAtomkern::pruefungOperatorPlusGleich() 
{
	Atomkern kern("C",12,6);	
	kern += Atomkern::NEUTRON;
	SICHERSTELLEN(kern.ordnungszahl()==6);
	SICHERSTELLEN(kern.massenzahl()==13);
	kern += Atomkern::PROTON;
	SICHERSTELLEN(kern.ordnungszahl()==7);
	SICHERSTELLEN(kern.massenzahl()==14);
}

void PrueffolgeAtomkern::pruefungOperatorMinusGleich() 
{
	Atomkern kern("C",12,6);	
	kern -= Atomkern::NEUTRON;
	SICHERSTELLEN(kern.ordnungszahl()==6);
	SICHERSTELLEN(kern.massenzahl()==11);
	kern -= Atomkern::PROTON;
	SICHERSTELLEN(kern.ordnungszahl()==5);
	SICHERSTELLEN(kern.massenzahl()==10);
}

void PrueffolgeAtomkern::pruefungKernfusion()
{
	const Atomkern DEUTERIUM("D",2,1);
	const Atomkern TRITIUM("T",3,1);
	const Atomkern HELIUM("He",4,2);	
	Atomkern ergebnis = DEUTERIUM + TRITIUM - Atomkern::NEUTRON;
	SICHERSTELLEN(ergebnis.ordnungszahl()==2);
	SICHERSTELLEN(ergebnis.massenzahl()==4);	
	SICHERSTELLEN(ergebnis==HELIUM);
}

void PrueffolgeAtomkern::pruefungKernspaltung()
{
	const Atomkern PLUTONIUM("Pu",239,94);
	const Atomkern BARIUM("Ba",144,56);
	const Atomkern STRONTIUM("Sr",94,38);
	SICHERSTELLEN(PLUTONIUM + Atomkern::NEUTRON == BARIUM + STRONTIUM + Atomkern::NEUTRON * 2);
}

