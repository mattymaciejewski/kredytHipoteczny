#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


int generujLiczbeRat (int lata) {

  int iloscRat = 0;

  for(int i = 0; i <= lata*12; i++) {

    iloscRat++;
  }

  return iloscRat;
}


double generujRate(int lata, int kapital, double oprocentowanie) {

  double miesiecznaStopaProcentowa = oprocentowanie/12;
  const int ileLat = generujLiczbeRat(lata);
  double wartoscRaty = (kapital*miesiecznaStopaProcentowa)/(1-pow(1+miesiecznaStopaProcentowa,ileLat*(-1)));

  return wartoscRaty;
}


void generujTabele() {

  cout << "Rok	Miesiac    Czesc kapitalowa    Czesc odsetkowa    Pozostaly kapital do splaty    Biezaca kwota splaconych rat" << "\n";
}


void generujHarmonogramRatStalych(int lata, int kapital, double oprocentowanie) {

  const int ileRat = generujLiczbeRat(lata); 
  double biezacaKwotaSplaconychRat = 0;
  double pozostalyKapitalDoSplaty = kapital;
  double miesiecznaStopaProcentowa = oprocentowanie/12;
  const double rata = generujRate(lata, kapital, oprocentowanie);
  int rok = 1;

  generujTabele();

  for(int miesiac = 0; miesiac < ileRat; miesiac++) {

    double czescOdsetkowa = pozostalyKapitalDoSplaty * miesiecznaStopaProcentowa;
    double czescKapitalowa = rata - czescOdsetkowa;

    pozostalyKapitalDoSplaty -= czescKapitalowa;
    biezacaKwotaSplaconychRat += rata;

    if(miesiac > 0 && miesiac % 12 == 0) {
      rok++;
    }

    cout << fixed;
    cout << rok << "     " << miesiac << "     " << setprecision(2) << czescKapitalowa << "     " << setprecision(2) << czescOdsetkowa << "     " << setprecision(2) << pozostalyKapitalDoSplaty << "     " << setprecision(2) << biezacaKwotaSplaconychRat << "\n";
  } 
}


double generujRateMalejaca(int lata, int kapital, double oprocentowanie, int miesiac) {
    const int ileRat = generujLiczbeRat(lata);
    int wybranaRata = ileRat - miesiac + 1;
    double miesiecznaStopaProcentowa = oprocentowanie / 12;
    double rataMalejaca = (kapital/ileRat) * (1+(wybranaRata * miesiecznaStopaProcentowa));
    return rataMalejaca;
}

void generujHarmonogramRatMalejacych(int lata, int kapital, double oprocentowanie) {
    const int ileRat = generujLiczbeRat(lata);
    double biezacaKwotaSplaconychRat = 0;
    double pozostalyKapitalDoSplaty = kapital;
    double miesiecznaStopaProcentowa = oprocentowanie / 12; 
    int rok = 1;

    generujTabele();

    for (int miesiac = 0; miesiac < ileRat; miesiac++) {
        double rataMalejaca = generujRateMalejaca(lata, kapital, oprocentowanie, miesiac);
        double czescOdsetkowa = pozostalyKapitalDoSplaty * miesiecznaStopaProcentowa;
        double czescKapitalowa = rataMalejaca - czescOdsetkowa;

        pozostalyKapitalDoSplaty = kapital - biezacaKwotaSplaconychRat;
        biezacaKwotaSplaconychRat += rataMalejaca;

        if (miesiac > 0 && miesiac % 12 == 0) {
            rok++;
        }

        cout << fixed;
        cout << rok << "     " << miesiac << "     " << setprecision(2) << czescKapitalowa << "     " << setprecision(2) << czescOdsetkowa << "     " << setprecision(2) << pozostalyKapitalDoSplaty << "     " << setprecision(2) << biezacaKwotaSplaconychRat << "\n";
    }
}


void generujWybor() {

  cout << "**Harmonogram rat kredytu hipotecznego**" << "\n";
  cout << "Aby wybrac platnosc w ratach stalych, wybierz 1." << "\n";
  cout << "Aby wybrac platnosc w ratach malejacych, wybierz 2." << "\n";
  cout << "Aby zakonczyc, wybierz 0." << "\n";

}


void panel(int lata, int kapital, double oprocentowanie, int k) {

do {

generujWybor();

cin >> k;

if(k == 1) {

  cout << "Na ile lat chcesz wziac kredyt? ";
  cin >> lata;
  cout << "\n";

  cout << "Na jaka kwote chcesz wziac kredyt? ";
  cin >> kapital;
  cout << "\n";

  cout << "Z jakim oprocentowaniem chcesz wziac kredyt? *UWAGA: Wpisz liczbe zmiennoprzecinkowa np. 0.05* ";
  cin >> oprocentowanie;
  cout << "\n";

generujHarmonogramRatStalych(lata, kapital, oprocentowanie);

}

if(k == 2) {

  cout << "Na ile lat chcesz wziac kredyt? ";
  cin >> lata;
  cout << "\n";

  cout << "Na jaka kwote chcesz wziac kredyt? ";
  cin >> kapital;
  cout << "\n";

  cout << "Z jakim oprocentowaniem chcesz wziac kredyt? *UWAGA: Wpisz liczbe zmiennoprzecinkowa np. 0.05* ";
  cin >> oprocentowanie;
  cout << "\n";

  generujHarmonogramRatMalejacych(lata, kapital, oprocentowanie);

}


} while(k!=0);



}


int main() {

  int lata = 0;
  int kapital = 0;
  double oprocentowanie = 0.0;
  int k = 0;

  panel(lata, kapital, oprocentowanie, k);

}
