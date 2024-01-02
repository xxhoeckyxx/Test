/**
 * OPR-Praktikum SS 2012
 * Aufgabe 9
 * @author Thomas Mahr
 */

#pragma once
#include <list>
#include <string>

#define SICHERSTELLEN(exp) ( sicherstellen(exp, __FILE__, __LINE__) )

class Prueffolge
{
public:

	Prueffolge();
	virtual ~Prueffolge();
	void ausfuehren();

protected:

	typedef void (*Prueffunktion)();

	struct Fehler
	{
		std::string dateiName;
		int zeile;
		Fehler(std::string dateiName, int zeile) : dateiName(dateiName), zeile(zeile) {}		
		std::string beschreibung();
	};
	
	struct Prueffall
	{
		std::string bezeichnung;
		Prueffunktion funktion;
		Prueffall(std::string bezeichnung, Prueffunktion funktion) : bezeichnung(bezeichnung), funktion(funktion) {}
	};

	void anmelden(std::string bezeichnung, Prueffunktion test);
	
	static void sicherstellen(bool b, std::string dateiName, int zeile);

private:

	std::list<Prueffall*> prueffaelle;
};
