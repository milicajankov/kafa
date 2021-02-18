#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Kafa {
protected:
    char tip;
    double osnovna_cena;
public:
    Kafa(char t, double os): tip(t), osnovna_cena(os) { }

    virtual string ispis()const{
        return string("(") + tip + " , " + "$" + to_string(osnovna_cena);
    }
    virtual bool poredjenje(const Kafa &k)const{
        return (k.tip==tip)&&(k.osnovna_cena==osnovna_cena);
    }
    virtual double prava_cena()const=0;
    double getOsnovna_cena(){
        return osnovna_cena;
    }
    friend ostream& operator<<(ostream& out, const Kafa &c){
        out << c.ispis();
        return out;
    }
    friend bool operator == (const Kafa &p1, const Kafa &p2){
        return p1.poredjenje(p2);
    }
    friend bool operator != (const Kafa &p1, const Kafa &p2){
        return !(p1.poredjenje(p2));
    }
};
class Espresso : public Kafa {
    bool produzena;
    bool mleko;
public:
    Espresso(bool p, bool m) : produzena(p), mleko(m), Kafa('E', 70) { }
    string ispis()const{
        return string("[") + string("P:") + to_string(produzena) + string(" , M: ") + to_string(mleko) + string(" ;  ( ") + Kafa::ispis() + "]";
    }
    double prava_cena()const{
        int dodatak;
        if(produzena)dodatak=50;
        if(mleko)dodatak=50;
        if(mleko&&produzena)dodatak=70;
        return dodatak + Kafa::osnovna_cena;
    }
    bool poredjenje(const Espresso &e)const{
        return Espresso::poredjenje(e) && (e.produzena==produzena) || (e.mleko == mleko);

    }
};
class Capuchino : public Kafa {
    string ukus=" ";
public:
    Capuchino(string u = " " ): ukus(u), Kafa('C',70) { }
    double prava_cena()const{
        double dodatak;
        if(ukus!=" ")
            return Kafa::osnovna_cena + 100;
            else
            return Kafa::osnovna_cena;
    }
    string ispis()const{
        return string("[") + ukus + string("(") + Kafa::ispis() + "]";

    }
    bool poredjenje(const Capuchino &c)const{
        return Kafa::poredjenje(c) && (c.ukus==ukus);
    }

};
class CoffeShop{
    vector<Kafa*> spisak;
    double zarada;
public:

    CoffeShop() = default;
    void dodaj(Kafa *k){
        spisak.push_back(k);
    }
    void izbaci(const Kafa *k){
        size_t i = 0;
        for(i=0; i<spisak.size(); ++i)
            if(*spisak[i] == *k)
             //   break;
            spisak.erase(spisak.begin() + i);
            }
    /*void ukloni(Kafa *k){
        int poc=1;
            for(auto i=0;i<spisak.size();++i){
                if(spisak[i]->poredjenje(*k)){
                    poc=i;
                    break;
                }
            if(poc!=1)
                spisak.erase(spisak.begin() + poc);
            }

    */
    void naplati(){
        for(auto a:spisak)
            zarada+=a->prava_cena();
            spisak.resize(0);
    }

    string ispis()const{
        string res = " ";
        res+= "Zarada: " + to_string(zarada) + "\n";
        for(auto a: spisak)
            res+=a->ispis() + "\n";
        return res;friend Complex operator += (Complex &a, const Complex &b);
    }
    friend ostream& operator<<(ostream& out, const CoffeShop &c){
        out << c.ispis();
        return out;
    }
};
int main()
{
    CoffeShop c;
    cout << c <<endl;
    c.dodaj(new Espresso(true, true));
    c.dodaj(new Capuchino("vanila"));
    cout << c <<endl;
    c.naplati();
    cout << c <<endl;
    c.dodaj(new Capuchino("cokolada"));
    c.izbaci(new Capuchino("cokolada"));
    cout << c << endl;
    return 0;
}
