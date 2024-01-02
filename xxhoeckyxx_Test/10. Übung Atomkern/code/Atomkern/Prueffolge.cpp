/**
 * OPR-Praktikum SS 2012
 * Aufgabe 9
 * @author Thomas Mahr
 */

#include "Prueffolge.h"
#include <iostream>
#include <sstream>
using namespace std;

Prueffolge::Prueffolge()
{
}
	
Prueffolge::~Prueffolge()
{
	for(list<Prueffall*>::iterator it=prueffaelle.begin(); it!=prueffaelle.end(); it++)	
	{ 
		delete *it;
	}
}

void Prueffolge::anmelden(std::string bezeichnung, Prueffunktion test)
{
	Prueffall* tf = new Prueffall(bezeichnung,test);
	tf->funktion = test;
	prueffaelle.push_back(tf);
}	


void Prueffolge::ausfuehren()
{
	int zaehlerTestBestanden = 0;
	for(list<Prueffall*>::iterator it=prueffaelle.begin(); it!=prueffaelle.end(); it++)	
	{ 
		cout << "PRUEFUNG " << (*it)->bezeichnung << ": ";
		try
		{
			(*it)->funktion(); 
			zaehlerTestBestanden++;
			cout << "ERFOLGREICH\n";
		}
		catch(Fehler f)
		{
			cout << f.beschreibung() << endl;
		}
	}
	
	cout << zaehlerTestBestanden << " von " << prueffaelle.size() << " Pruefungen erfolgreich\n";
}

void Prueffolge::sicherstellen(bool b, std::string dateiName, int zeile)
{
	if(!b)
	{
		throw Fehler(dateiName, zeile);
	}
}


string Prueffolge::Fehler::beschreibung()
{
	stringstream s;
	s << "FEHLER in " << dateiName << " Zeile " << zeile;
	return s.str();
}

