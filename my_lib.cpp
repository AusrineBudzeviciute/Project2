#include "my_lib.h"

void studentas::setVardas(string vardas){
    vardas_ = vardas;
}
void studentas::setPavarde(string pavarde){
    pavarde_ = pavarde;
}
void studentas::setEgz(int egz) {
    egz_ = egz;
}
void studentas::setRez(float rez) {
    rez_ = rez;
}
void studentas::setMediana(float mediana){
    mediana_ = mediana;
}
void studentas::setPazymiai(int paz)
{
    pazymiai.push_back(paz);
}
void studentas::clearPazymiai(){
    pazymiai.clear();
}

float median(vector<int> pazymiai)
{
    float mediana;
    sort(pazymiai.begin(), pazymiai.end());
    if (pazymiai.size()%2 == 0)
        mediana = (pazymiai[pazymiai.size()/2] + pazymiai[(pazymiai.size()/2)-1])/2.0;
    else
        mediana = pazymiai[(pazymiai.size()/2)];
    return mediana;
}

float mean(vector<int> pazymiai, int egzaminas)
{
    float suma=0, rezultatas;
    for (auto &a: pazymiai)
        suma = suma + a;
    rezultatas = (suma/pazymiai.size())*0.4 + egzaminas*0.6;
    return rezultatas;
}

bool pagalVarda(const studentas& s1, const studentas& s2){
    return s1.getVardas() < s2.getVardas();
}
bool pagalPavarde(const studentas& s1, const studentas& s2){
    return s1.getPavarde() < s2.getPavarde();
}
bool pagalRezultata(const studentas& s1, const studentas& s2){
    return s1.getRez() < s2.getRez();
}


int generate_random()
{
    static std::mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(1, 10);
    return dist(mt);
}

int rusiavimui()
{
    int pasirinkimas;
    cout<<"Iveskite parametra, pagal kuri rusiuojamas failas (1- vardas, 2 - pavarde, 3 - rezultatas): ";
    cin>>pasirinkimas;
    return pasirinkimas;
}

void tikrinimas(int& x)
{
    try{
        if (cin.fail() || x <= 0)
            throw invalid_argument("Pateiktas netinkamas skaicius.");}
    catch (const invalid_argument& e)
    {
        cerr<< e.what()<<endl;
        cin.clear();
        cin.ignore(256, '\n');
        cout<<"Iveskite is naujo: ";
        cin>>x;
        tikrinimas(x);
    }
}

void print_mean(vector<studentas> grupe)
{
    cout<<"Pavarde             "<<"Vardas              "<<"Galutinis (Vid.)"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for (auto &a: grupe)
        cout<<left<<setw(20)<<a.getPavarde()<<setw(20)<<a.getVardas()<<setw(5)<<fixed<<setprecision(2)<<a.getRez()<<endl;
}

void print_median(vector<studentas> grupe)
{
    cout<<"Pavarde             "<<"Vardas              "<<"Galutinis (Med.)"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for (auto &a: grupe)
        cout<<left<<setw(20)<<a.getPavarde()<<setw(20)<<a.getVardas()<<setw(5)<<fixed<<setprecision(2)<<a.getMediana()<<endl;
}

void print_mean_median (vector<studentas> grupe)
{
    cout<<"Pavarde             Vardas              Galutinis (Vid.)    Galutinis (Med.)"<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;
    for (auto &a: grupe)
        cout<<left<<setw(20)<<a.getPavarde()<<setw(20)<<a.getVardas()<<setw(20)<<fixed<<setprecision(2)<<a.getRez()<<setw(5)<<a.getMediana()<<endl;
}

void Failo_nuskaitymas (string pavadinimas, studentas stud, vector <studentas> &grupe)
{
    auto start = std::chrono::high_resolution_clock::now();
    ifstream failas(pavadinimas);
    if(failas.fail()) cout<<"Failo atidarymo klaida."<<endl;

    string antraste;
    for (int i = 0; i<1; i++) getline(failas,antraste);

    istringstream iss(antraste);
    string namudarbas, vardas, pavarde;
    int sk = 0, egz;

    while (iss >> namudarbas)
    {
        if (namudarbas.substr(0, 2) == "ND") sk++;
    }

    while(failas >> vardas >> pavarde)
    {
        stud.setVardas(vardas);
        stud.setPavarde(pavarde);
        for(int i=0; i<sk; i++)
        {
            int paz;
            if(!(failas>>paz)) throw invalid_argument("Netinkamas pazymys faile.");
            if (paz<=0 || paz>10) throw invalid_argument("Netinkamas pazymys faile.");
            stud.setPazymiai(paz);
        }
        failas >> egz;
        stud.setEgz(egz);
        stud.setRez(mean(stud.getPazymiai(), stud.getEgz()));
        stud.setMediana(median(stud.getPazymiai()));
        grupe.push_back(stud);
        stud.clearPazymiai();
    }
    failas.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << "Failo nuskaitymas uztruko: "<< diff.count() << " s\n";
}

void Failo_rusiavimas (vector<studentas> grupe)
{
    vector<studentas> neismaneliai, gudruciai;

    auto start = std::chrono::high_resolution_clock::now();

    auto partitionPoint = std::partition(grupe.begin(), grupe.end(), [](const auto& a) {
    return a.getRez() < 5;});
    gudruciai.insert(gudruciai.end(), partitionPoint, grupe.end());
    neismaneliai.insert(neismaneliai.end(), grupe.begin(), partitionPoint);
    grupe.erase(partitionPoint, grupe.end());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << "Failo rusiavimas uztruko: "<< diff.count() << " s\n";

    int pasirinkimas = rusiavimui();
    if (pasirinkimas == 1){
        sort(gudruciai.begin(), gudruciai.end(), pagalVarda);
        sort(neismaneliai.begin(), neismaneliai.end(), pagalVarda);
    }
    else if (pasirinkimas == 2){
        sort(gudruciai.begin(), gudruciai.end(), pagalPavarde);
        sort(neismaneliai.begin(), neismaneliai.end(), pagalPavarde);
    }
    else if (pasirinkimas == 3){
        sort(gudruciai.begin(), gudruciai.end(), pagalRezultata);
        sort(neismaneliai.begin(), neismaneliai.end(), pagalRezultata);
    }

    auto start2 = std::chrono::high_resolution_clock::now();
    print_file("gudruciai.txt", gudruciai);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff2 = end2-start2;
    std::cout << "Gudruciu failo kurimas uztruko: "<< diff2.count() << " s\n";

    auto start3 = std::chrono::high_resolution_clock::now();
    print_file("neismaneliai.txt", neismaneliai);
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff3 = end3-start3;
    std::cout << "Neismaneliu failo kurimas uztruko: "<< diff3.count() << " s\n";
}

void print_file(string pavadinimas, vector<studentas> studentai)
{
    ofstream g(pavadinimas);
    g<<"Pavarde             Vardas              Galutinis (Vid.)"<<endl;
    for (auto &a: studentai)
        g<<left<<setw(20)<<a.getPavarde()<<setw(20)<<a.getVardas()<<setw(5)<<fixed<<setprecision(2)<<a.getRez()<<endl;
}





