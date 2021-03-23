#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>


using namespace std;

ifstream f("date.in");

int main()
{
    int nodes, transitions, this_node, next_node, i, j, initiala, nr_finale, nr_cuv, x=0;
    char litera_crt;

    bool st_finala;

    vector <int> finale;

    vector <string> cuv1;

    vector <int> traseu;

    string cuvinte;

    stack <int> st;

    f >> nodes >> transitions;

    char dfa[nodes][nodes];

    for(i = 0;i <= transitions; i++)
    {
        f >> this_node >> next_node;
        f >> dfa[this_node][next_node];             ///punem tranzitiile in matricea de adiacenta
    }

    for(i = 0; i < nodes; i++)
        for(j = 0;j < nodes; j++)
    {
        if(dfa[i][j] != 'a' && dfa[i][j] != 'b' && dfa[i][j] != 'c')        ///marcam si nodurile care nu sunt vecine
            dfa[i][j] = '#';
    }

    f>>initiala;

    f>>nr_finale;

    for(i=0;i<nr_finale;i++)
    {
        f>>j;
        finale.push_back(j);            ///retinem toate starile finale intr-un vector
    }


    f>>nr_cuv;
    while(nr_cuv!=0)
    {
        f>>cuvinte;
        cuv1.push_back(cuvinte);                   ///stocam cuvintele intr-un vector
        nr_cuv--;
    }

    while (x < cuv1.size())                ///repetitiva pt a verifica toate cuvintele din input
    {
        while( !st.empty() )               ///pregatim stiva pentru a verifica inputurile
            st.pop();

        st_finala = false;

        cuvinte = cuv1[x];

        litera_crt = cuvinte[0];            ///retinem prima litera din cuvant

        st.push(initiala);

        this_node = st.top();               ///initializam nodul curent cu varful stivei(starea initiala)

        traseu.clear();

        traseu.push_back(initiala);

        i=0;
        while(i<nodes)
        {
            if(dfa[this_node][i] != '#' && litera_crt == dfa[this_node][i])         ///daca gasim o tranzitie favorabila, trecem nodul urmator in stiva,
            {                                                                       ///stergem prima litera din cuvant(cea de care aveam nevoie),
                st.push(i);                                                         ///actualizam litera curenta, actualizam nodul curent si actualizam traseul
                for(j = 0;j < cuvinte.length(); j++)
                        cuvinte[j] = cuvinte[j+1];
                litera_crt = cuvinte[0];
                this_node = i;
                traseu.push_back(i);

            }
            else i++;
        }

        for(j = 0;j < finale.size(); j++)                                  ///ultimul nod favorabil va ramane memorat in this_node si verificam daca este stare finala
            if(finale[j] == this_node)
                st_finala = true;

        if(cuvinte[0] == NULL && st_finala == true)                        ///daca ultimul nod vizitat este stare finala iar cuvantul a ajuns nul => inputul este acceptat
            {
                cout<<"DA"<<endl;
                cout<<"TRASEU: ";
                for(int k = 0;k < traseu.size(); k++)                      ///afisarea traseului daca inputul este acceptat
                    cout<<traseu[k]<<" ";
                cout<<endl;
            }
        else cout<<"NU"<<endl;

        x++;
    }


    return 0;
}
