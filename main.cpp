#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int generujLiczbeRat(int lata) {

  int iloscRat = 0;

  for (int i = 1; i <= lata * 12; i++) {

    iloscRat++;
  }

  return iloscRat;
}

double generujRate(int lata, int kapital, double oprocentowanie) {

  double miesiecznaStopaProcentowa = oprocentowanie / 12;
  const int ileLat = generujLiczbeRat(lata);
  double wartoscRaty = (kapital * miesiecznaStopaProcentowa) /
                       (1 - pow(1 + miesiecznaStopaProcentowa, ileLat * (-1)));

  return wartoscRaty;
}

void generujTabele() {

  cout << "Rok	Miesiac    Czesc kapitalowa    Czesc odsetkowa    Pozostaly "
          "kapital do splaty    Biezaca kwota splaconych rat"
       << "\n";
}

void generujHarmonogramRatStalych(int lata, int kapital, double oprocentowanie) {

  const int ileRat = generujLiczbeRat(lata);
  double biezacaKwotaSplaconychRat = 0;
  double pozostalyKapitalDoSplaty = kapital;
  double miesiecznaStopaProcentowa = oprocentowanie / 12;
  const double rata = generujRate(lata, kapital, oprocentowanie);
  int rok = 1;

  generujTabele();

  for (int miesiac = 1; miesiac <= ileRat; miesiac++) {

    double czescOdsetkowa =
        pozostalyKapitalDoSplaty * miesiecznaStopaProcentowa;
    double czescKapitalowa = rata - czescOdsetkowa;

    pozostalyKapitalDoSplaty -= czescKapitalowa;
    biezacaKwotaSplaconychRat += rata;

    if (miesiac > 0 && miesiac % 12 == 0) {
      rok++;
    }

    cout << fixed;
    cout << rok << "     " << miesiac << "     " << setprecision(2)
         << czescKapitalowa << "     " << setprecision(2) << czescOdsetkowa
         << "     " << setprecision(2) << pozostalyKapitalDoSplaty << "     "
         << setprecision(2) << biezacaKwotaSplaconychRat << "\n";
  }
}

double generujRateMalejaca(int lata, int miesiac, int kapital, double oprocentowanie) {

  const int iloscRat = generujLiczbeRat(lata);
  const double miesieczneOprocentowanie = oprocentowanie/12;

  double rataMalejaca = kapital/iloscRat * (1 + (iloscRat - miesiac + 1) * miesieczneOprocentowanie);

  return rataMalejaca;

}

void generujHarmonogramRatMalejacych(int lata, int kapital, double oprocentowanie) {
    const int ileRat = generujLiczbeRat(lata);
    double miesiecznaStopaProcentowa = oprocentowanie / 12;
    double biezacaKwotaSplaconychRat = 0;
    double pozostalyKapitalDoSplaty = kapital;
    int rok = 1;

    double rataMalejaca = generujRateMalejaca(lata, 1, kapital, oprocentowanie);
    double czescKapitalowa = rataMalejaca - (pozostalyKapitalDoSplaty * miesiecznaStopaProcentowa);

    generujTabele();

    for (int miesiac = 1; miesiac <= ileRat; miesiac++) {
        double czescOdsetkowa = pozostalyKapitalDoSplaty * miesiecznaStopaProcentowa;

        double czescKapitalowaStala = czescKapitalowa;

        if (miesiac < ileRat) {
            pozostalyKapitalDoSplaty -= czescKapitalowaStala;
        } else {

            czescKapitalowaStala = pozostalyKapitalDoSplaty;
            pozostalyKapitalDoSplaty = 0;
        }

        biezacaKwotaSplaconychRat += (czescKapitalowaStala + czescOdsetkowa);

        if (miesiac > 0 && miesiac % 12 == 0) {
            rok++;
        }

        cout << fixed;
        cout << rok << "     " << miesiac << "     " << setprecision(2)
             << czescKapitalowaStala << "     " << setprecision(2) << czescOdsetkowa
             << "     " << setprecision(2) << pozostalyKapitalDoSplaty << "     "
             << setprecision(2) << biezacaKwotaSplaconychRat << "\n";
    }
}






void generujWybor() {

  cout << "**Harmonogram rat kredytu hipotecznego**"
       << "\n";
  cout << "Aby wybrac platnosc w ratach stalych, wybierz 1."
       << "\n";
  cout << "Aby wybrac platnosc w ratach malejacych, wybierz 2."
       << "\n";
  cout << "Aby zakonczyc, wybierz 0."
       << "\n";
}

void panel(int lata, int kapital, double oprocentowanie, int k) {

  do {

    generujWybor();

    cin >> k;

    if (k == 1) {

      cout << "Na ile lat chcesz wziac kredyt? ";
      cin >> lata;
      cout << "\n";

      cout << "Na jaka kwote chcesz wziac kredyt? ";
      cin >> kapital;
      cout << "\n";

      cout << "Z jakim oprocentowaniem chcesz wziac kredyt? *UWAGA: Wpisz "
              "liczbe zmiennoprzecinkowa np. 0.05* ";
      cin >> oprocentowanie;
      cout << "\n";

      generujHarmonogramRatStalych(lata, kapital, oprocentowanie);
    }

    if (k == 2) {

      cout << "Na ile lat chcesz wziac kredyt? ";
      cin >> lata;
      cout << "\n";

      cout << "Na jaka kwote chcesz wziac kredyt? ";
      cin >> kapital;
      cout << "\n";

      cout << "Z jakim oprocentowaniem chcesz wziac kredyt? *UWAGA: Wpisz "
              "liczbe zmiennoprzecinkowa np. 0.05* ";
      cin >> oprocentowanie;
      cout << "\n";

      generujHarmonogramRatMalejacych(lata, kapital, oprocentowanie);
    }

  } while (k != 0);
}

int main() {

  int lata = 0;
  int kapital = 0;
  double oprocentowanie = 0.0;
  int k = 0;

  panel(lata, kapital, oprocentowanie, k);
}

