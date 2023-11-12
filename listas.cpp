#include "my_lib.h"

int listas()
{
try{

    stipendininkas stip;
    list <stipendininkas> kursas;
    int ivedimas1;
    cout<<"Iveskite: '1' - failo nuskaitymui; '2' - duomenu ivedimui; '3' - failo generavimui: ";
    cin>>ivedimas1;

    if(ivedimas1 == 1)
    {
        string pav;
        cout<<"Iveskite failo pavadinima: ";
        cin>>pav;
        Failo_nuskaitymas_l(pav, stip, kursas);
        int strategija;
        cout<<"Iveskite, kuri strategija bus tikrinama (1, 2, 3): ";
        cin>>strategija;
        if (strategija == 1)
        {
            int pasirinkimas = rusiavimui();
            for (auto &a: kursas)
                a.x = pasirinkimas;
            kursas.sort();
            Failo_rusiavimas1_l(kursas);
        }
        else if (strategija == 2)
            Failo_rusiavimas2_l(kursas);
        else if (strategija == 3)
            Failo_rusiavimas3_l(kursas);
    }

    else if (ivedimas1 == 2)
    {
        int n;
        cout<<"Iveskite, kiek studentu yra sarase:"<<endl;
        cin>>n;
        tikrinimas(n);

        for (int i=0; i<n; i++)
        {
            cout<<"Iveskite varda ir pavarde: "<<endl;
            cin>>stip.vardas>>stip.pavarde;

            char ivedimas2;
            cout<<"Iveskite: '+' - duomenu generavimui; '-' - duomenu ivedimui: ";
            cin>>ivedimas2;
            if (ivedimas2 == '+')
            {
                int skaicius;
                cout<<"Iveskite, kiek pazymiu generuojama: ";
                cin>>skaicius;
                tikrinimas(skaicius);

                for(int j=0; j<skaicius; j++) stip.pazymiai.push_back(generate_random());
                stip.egz = generate_random();
                stip.mediana = median_l(stip.pazymiai);
                stip.rez = mean_l(stip.pazymiai, stip.egz);
                kursas.push_back(stip);
                stip.pazymiai.clear();
            }

            else if (ivedimas2 == '-')
            {
                int p;
                cout<<"Iveskite pazymi (0 zymi pazymiu ivedimo pabaiga): ";
                cin>>p;

                if (cin.fail() || p < 0 || p > 10) throw invalid_argument("Pateiktas netinkamas skaicius.");

                while (p != 0)
                {
                    stip.pazymiai.push_back(p);
                    cout<<"Iveskite pazymi (0 zymi pazymiu ivedimo pabaiga): ";
                    cin>>p;
                    if (cin.fail() || p < 0 || p > 10) throw invalid_argument("Pateiktas netinkamas skaicius.");
                }

                cout<<"Iveskite egzamino rezultata: "<<endl;
                cin>>stip.egz;

                stip.mediana = median_l(stip.pazymiai);
                stip.rez = mean_l(stip.pazymiai, stip.egz);
                kursas.push_back(stip);
                stip.pazymiai.clear();
            }
        }
        kursas.sort();
        char ivedimas3;
        cout<<"Iveskite: 'V' - vidurkio isvedimui; 'M' - medianos isvedimui: ";
        cin>>ivedimas3;
        if (ivedimas3 == 'V') print_mean_l(kursas);
        else print_median_l(kursas);
        cout<<"Grupes objekto saugojimo atmintyje adresas: "<<&kursas<<endl;
        for(auto &stip: kursas) {cout<<"Studento objekto saugojimo atmintyje adresas: "<<&stip<<endl;}
    }

    else if (ivedimas1 == 3)
    {
        int studentusk;
        cout<<"Iveskite, kiek studentu generuojama: ";
        cin>>studentusk;
        Failo_kurimas(studentusk);
    }
}

catch (const exception& e) {
    cerr << "Klaida: " << e.what() << endl;
    return 1;}

    system("pause");
    return 0;

}






