#include <iostream>
#include <cstring>
#include <cmath>
#include <stdexcept>

using namespace std;

#define Kol_2


#ifdef Kol_2

class Wlasciciel 
{};

class Samochod 
{
protected:
	char numerRejestracyjny[10];
	int stanLicznika;
	bool czyDopuszczony;
	Wlasciciel wlasciciel;
	static const double warPocz;
	static Samochod* wzorzec;
public:

	void setStanLicznika(int licznik)
	{
		if (licznik < 0)
		{
			throw invalid_argument("Stan musi byc wiekszy od zera");
		}
		else
		{
			stanLicznika = licznik;
		}
	}

	static void setWzorzec(Samochod* wzor) {
		wzorzec = wzor;
	}

	const char* getRejestracja() { return numerRejestracyjny; }

	int getStanLicznika() { return stanLicznika; }

	bool getCzyDopuszczony() { return czyDopuszczony; }

	Samochod(const char* rejestracja,int licznik,bool wartosc, const Wlasciciel& m_wlasciciel):
		wlasciciel(m_wlasciciel),czyDopuszczony(wartosc)
	{
		setStanLicznika(licznik);
		strncpy_s(numerRejestracyjny, rejestracja, sizeof(numerRejestracyjny));
		numerRejestracyjny[sizeof(numerRejestracyjny) - 1] = '\0';
	}

	Samochod() 
	{
		if (wzorzec == nullptr) {
			throw runtime_error("Nie zdefiniowano wzorca ");
		}
		*this = *wzorzec;
	};



	virtual int obliczZasieg() 
	{
		if (czyDopuszczony != true)
		{
			throw invalid_argument("Samochod musi byc dopuszczony do ruchu");
		}
		else
		{
			return 800;
		}
	}
	
	virtual double obliczWartosc() 
	{
		double wspSpraw = (czyDopuszczony) ? 1.0 : 0.2;
		double wartosc = (warPocz - 0.2 * stanLicznika) * wspSpraw;
		if (wartosc < 400.0) {
			wartosc = 400.0;
		}

		return wartosc;
	}

	explicit operator double() {
		return obliczWartosc();
	}

	bool operator!=(const Samochod& other) 
	{
		if (czyDopuszczony!=other.czyDopuszczony) 
		{
			return false;
		}
		else if (abs(stanLicznika - other.stanLicznika) > 20) 
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	friend ostream& operator<<(ostream& os, Samochod& samochod) 
	{
		os << "Samochod: " << samochod.getRejestracja()
			<< ", Licznik: " << samochod.getStanLicznika()
			<< ", Dopuszczenie: " << (samochod.getCzyDopuszczony() ? "dopuszczony" : "niedopuszczony")
			<< ",Wartosc: " << (samochod.obliczWartosc());
		return os;
	}

};
const double Samochod::warPocz = 20000.0;
Samochod* Samochod::wzorzec = nullptr;


class SamochodElektryczny : public Samochod
{
private:
	int stanBaterii;

public:
	SamochodElektryczny(const char* rejestracja, int licznik, bool wartosc, const Wlasciciel& m_wlasciciel, int stanBaterii)
		: Samochod(rejestracja, stanLicznika, czyDopuszczony, wlasciciel), stanBaterii(stanBaterii)
	{
		if (stanBaterii < 0 || stanBaterii > 100) 
		{
			throw invalid_argument("Zakres bateri musi wynosic od 0 do 100%");
		}
	}

	int obliczZasieg() override 
	{
		if (czyDopuszczony!=true)
		{
			throw invalid_argument("Samochod musi byc dopuszczony do ruchu");
		}
		else
		{
			return 2.5 * stanBaterii;
		}
	}

	int getStanBaterii() {return stanBaterii;}

	double obliczWartosc() override 
	{
		double wartosc = Samochod::obliczWartosc();
		double wartoscElektryka = wartosc * 0.7;
		return wartoscElektryka;
	}
};

int main()
{
	Wlasciciel wlasciciel1;
	Wlasciciel wlasciciel2;
	Wlasciciel wlasciciel3;

	Samochod samochod1("ABC", 1000, true, wlasciciel1);

	SamochodElektryczny samochodElektryczny1("ELE", 800, true, wlasciciel2, 50);

	if (samochod1 != samochodElektryczny1) {
		cout << "Samochody sa identyczne." << endl;
	}
	else {
		cout << "Samochody nie sa identyczne." << endl;
	}

	cout << "Informacje o samochodzie 1: " << endl;
	cout << samochod1 << endl;

	cout << "Informacje o samochodzie elektrycznym 1: " << endl;
	cout << samochodElektryczny1 << endl;

	cout << "Zasięg samochodu 1: " << samochod1.obliczZasieg() << " km" << endl;
	cout << "Zasięg samochodu elektrycznego 1: " << samochodElektryczny1.obliczZasieg() << " km" << endl;
}

#endif