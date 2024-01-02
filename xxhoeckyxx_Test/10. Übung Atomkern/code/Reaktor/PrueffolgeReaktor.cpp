/**
 * OPR-Praktikum SS 2012
 * Aufgabe 9
 * @author Thomas Mahr
 */

#include "PrueffolgeReaktor.h"
#include "Atomkern.h"
#include "Reaktor.h"
using namespace std;

const Atomkern PrueffolgeReaktor::DEUTERIUM("D",2,1);
const Atomkern PrueffolgeReaktor::TRITIUM("T",3,1);
const Atomkern PrueffolgeReaktor::HELIUM4("He",4,2);	

PrueffolgeReaktor::PrueffolgeReaktor()
{
	anmelden("Reaktor erstellen", &pruefungReaktorErstellen);
	anmelden("Reaktor befuellen und komplett entleeren", &pruefungReaktorBetrieb1);
	anmelden("Kernfusion mit Wasserstoff", &pruefungReaktorBetrieb2);
	anmelden("Kernspaltung mit Plutonium", &pruefungReaktorBetrieb3);
}

void PrueffolgeReaktor::pruefungReaktorErstellen() 
{
	Reaktor reaktor;
	// Ein gerade erstellter Reaktor enthält kein Kernmaterial
	SICHERSTELLEN(*reaktor==Atomkern(0,0));
}

void PrueffolgeReaktor::pruefungReaktorBetrieb1() 
{
	Reaktor reaktor;	
	// Reaktor mit Deuterium füllen
	reaktor < DEUTERIUM;
	SICHERSTELLEN(*reaktor==DEUTERIUM);
	// Reaktor mit Tritium füllen
	reaktor < TRITIUM;
	// Auf (instabiles) Fusionsprodukt prüfen
	SICHERSTELLEN(*reaktor==Atomkern(5,2));
	// Reaktor komplett entleeren
	~reaktor;
	SICHERSTELLEN(*reaktor==Atomkern(0,0));
}

void PrueffolgeReaktor::pruefungReaktorBetrieb2() 
{
	Reaktor reaktor;	
	// Bei der Verschmelzung von Deuterium mit Tritium wird ein Neutron frei. 
	reaktor < DEUTERIUM < TRITIUM > Atomkern::NEUTRON;
	// Zurück bleibt Helium.
	SICHERSTELLEN(*reaktor==HELIUM4);
}

void PrueffolgeReaktor::pruefungReaktorBetrieb3() 
{
	Reaktor reaktor;	
	const Atomkern PLUTONIUM("Pu",239,94);
	const Atomkern BARIUM("Ba",144,56);
	const Atomkern STRONTIUM("Sr",94,38);

	// Plutonium spaltet sich bei Wechselwirkung mit einem Neutron in Barium und Strontium und gibt dabei zwei Neutronen frei.
	reaktor < PLUTONIUM < Atomkern::NEUTRON;
	SICHERSTELLEN(*reaktor==Atomkern(240,94));
	reaktor > BARIUM > STRONTIUM > 2*Atomkern::NEUTRON;
	SICHERSTELLEN(*reaktor==Atomkern(0,0));
	
	// Komplette Reaktion in einem Aufruf:
	reaktor < PLUTONIUM < Atomkern::NEUTRON > BARIUM > STRONTIUM > 2*Atomkern::NEUTRON;
	SICHERSTELLEN(*reaktor==Atomkern(0,0));
}
