#include <iostream>
#include<cstring>
using namespace std;
void paranteze(char s[],char r,int i)
{
    char aux[50];
    strcpy(aux,s + i);
    //strcpy(s+x,"(");
    strcpy(s+i+1,aux);
    s[i] = '(';
    int x=i+2;//sar peste paranteza si negatie
    int pz=0;//parantezele deja puse
    int ok=0;//inca nu am pus ')'
    while(ok==0)
    {
        if(s[x]=='(')
            pz++;
        if(s[x]==')')
            pz--;
        if(pz == 0 && strchr("QWERTYUIOPLKJHGFDSAZXCVBNM)",s[x]) && s[x+1] != '(')
        {
            strcpy(aux,s+x+1);
            strcpy(s+x+2,aux);
            s[x+1]=')';
            ok=1;
        }
        x++;
    }
    if ( r == 'd' )
        cout<<s<<endl;
}
void rbinara(char s[],char r,int i)
{
    char aux[50];
    //pun paranteza '(' in stanga
    int ok=0;//inca nu am pus '('
    int pz=0;//parantezele deja puse
    int x=i-1;
    while ( ok == 0  )
    {
        if(s[x]==')')
            pz++;
        if(s[x]=='(')
            pz--;
        if(pz==0 && strchr("QWERTYUIOPLKJHGFDSAZXCVBNM(",s[x]) )
        {
            if( s[x-1] == '(')
                ok=1;
            else{
            strcpy(aux,s+x);
            strcpy(s+x+1,aux);
            s[x]='(';
            ok=1;
            }
        }
        x--;
    }
    //pun ')' in dreapta
    x = i+1;
    ok=0;//inca nu am pus ')'

    while(ok==0 )
    {
        if(s[x]=='(')
            pz++;
        if(s[x]==')')
            pz--;
        if(pz == 0 && strchr("QWERTYUIOPLKJHGFDSAZXCVBNM)",s[x]) )
        {
            if(s[x+1] == ')')
                ok=1;
            else{
            strcpy(aux,s+x+1);
            strcpy(s+x+2,aux);
            s[x+1]=')';
            ok=1;
            }
        }
        x++;
    }
    if ( r == 'd' )
        cout<<s<<endl;
}
struct Nod
{
    char valoare;
    struct Nod *st, *dr, *prec;
};
Nod *prim=NULL,*p=NULL;
// prim retine primul nod din lista
// p retine pozitia curenta
int k=0,k1=1,a=1;
void inserareNod(Nod* &prim, char caracter,Nod *&p)
{
    //Creeam noul nod
    Nod *nodnou = new Nod;
    nodnou->st = NULL;
    nodnou->dr = NULL;
    nodnou->prec = NULL;
    nodnou->valoare = NULL;
    if (prim == NULL) // In cazul in care lista noastra este vida, punem elementul in lista
        {prim = nodnou;
        p = prim;
        }
        else //pun nodul in lista
            if ( p->st == NULL )
            {
                nodnou->prec = p;
                p->st = nodnou;
                p = nodnou;
            }
            else
                if ( p->dr == NULL && strchr("^vid",p->valoare) )
                {
                    nodnou->prec = p;
                    p->dr = nodnou;
                    p = nodnou;
                }
                else
                   a = 0;
//Daca valoarea nu e litera mare,negatie sau paranteza nodul trebuie sters
    if (!(strchr("QWERTYUIOPLKJHGFDSAZXCVBNM(",caracter)))
            {
                if( nodnou->prec != NULL )
                    if ( p->prec->dr != NULL )
                    {
                        Nod *nodscos = p;
                        p = p->prec;
                        p->dr = NULL;
                        delete nodscos;
                    }
                    else
                    {
                        Nod *nodscos=p;
                        p = p->prec;
                        p->st = NULL;
                        delete nodscos;
                    }
                    else
                        {delete nodnou;
                        a = 1;
                        }
            }
        if ( strchr("(",caracter) && a == 1)//valoarea nodului devine c (astept un operator)
            {p->valoare='c';}
        else
            if ( (caracter == '^' || caracter == 'd' || caracter == 'i' || caracter=='v') && p->valoare == 'c')//pun operatorul
                {
                    p->valoare = caracter;
                }
            else
                if ( strchr(")",caracter) && strchr("QWERTYUIOPLKJHGFDSAZXCVBNMndiv^",p->valoare))//urc o pozitie
                        {
                            if ( p->prec != NULL)
                                p = p->prec;
                            else
                            k++;//daca iese cu 1 -> arborele este complet
                        }
                else
                    if ( strchr("n",caracter) && p->valoare == 'c' && p->st == NULL ) //pun negatia
                        {p->valoare = caracter; }
                        else
                            if ( p != prim )
                            {
                                if ( strchr("QWERTYUIOPLKJHGFDSAZXCVBNM",caracter) && strchr("^vidnc",p->prec->valoare) )//pun propozitia
                                    {
                                    p->valoare = caracter;
                                    p = p->prec;
                                    }
                                else
                                {
                                    a = 0;
                                }
                            }
                            else
                                {
                                    a = 0;
                                }
}
void afisarei(Nod *nod_curent)
{
    if ( nod_curent )
    {   afisarei(nod_curent->st);
        cout<<nod_curent->valoare<<" ";
        afisarei(nod_curent->dr);
    }
}
int main()
{
    char s[50],r,x=-1;
    int ok=1,j=1;
    cout<<"ATENTIE"<<endl;
    cout<<"Pentru ca programul sa functioneze corect tine-ti cont de urmatoarele notatii:"<<endl;
    cout<<"^ -> pentru conjunctie"<<endl<<"v -> pentru disjunctie"<<endl<<"i -> pentru incluziune"<<endl<<"d -> pentru dubla incluziune"<<endl<<"n -> pentru negatie"<<endl;
    cout<<"Introduceti propozitia:"<<endl;
    cin.getline(s,50);
    cout<<"Doriti sa vedeti pasii? (d/n):"<<endl;
    cin>>r;
    if (strlen(s)==1){
        if (strchr("QWERTYUIOPLKJHGFDSAZXCVBNM",s[0]))//verific daca e propozitie atomica si creez arborele
                {k = 1;
                Nod *nodnou = new Nod;
                nodnou->st = NULL;
                nodnou->dr = NULL;
                nodnou->prec = NULL;
                nodnou->valoare = s[0];
                prim = nodnou;
                }}
    else
    {
        for(int i=0;i<strlen(s);i++)//verific caracterele
        {
            if ( !strchr("QWERTYUIOPLKJHGFDSAZXCVBNM^divn() ",s[i]))
                {
                    j=0;//am un caracter necunoscut
                    ok=i;
                    if ( s[i]==' ')//sterg spatiile
                    {
                        char aux[50];
                        strcpy(aux,s+i+1);
                        strcpy(s+i,aux);
                    }
                }
        }
        if( j == 1 )
        {
            if ( r == 'd' )
                cout<<"Aduc propozitia in sintaxa stricta"<<endl;
            for ( int i = strlen(s)-1; i >= 0; i--)
                if (s[i] == 'n' && s[i-1]!='(')
                    paranteze(s,r,i);
            for ( int i = strlen(s)-1; i >= 0; i--)
                if (strchr("^v",s[i]) && s[i-2]!='(')
                    rbinara(s,r,i);
            for ( int i = strlen(s)-1; i >= 0; i--)
                if (s[i] == 'i' && s[i-2]!='(')
                    rbinara(s,r,i);
            for ( int i = strlen(s)-1; i >= 0; i--)
                if (s[i] == 'd' && s[i-2]!='(')
                    rbinara(s,r,i);
            if ( r == 'd' )
                cout<<"Verific daca propozitia este bine formata"<<endl;
            for(int i=0;i<strlen(s);i++)
            {
                if ( a == 1 && k != 1 )
                    inserareNod(prim,s[i],p);
                else
                {
                    ok=0;
                    break;
                }
            }
            if ( ok == 1 && k == 1 && a == 1)//verific daca am un arbore complet
                {
                    if ( r == 'd' )
                        cout<<"Propozitia e bine formata"<<endl;
                }
            else
                {
                    if( k == 1 && ok == 0)
                        {
                            if( r == 'd')
                                cout<<"Nu am terminat de citit sirul"<<endl;
                            cout<<"Propozitia nu este bine formata"<<endl;
                        }
                    else
                        cout<<"Propozitia nu este bine formata"<<endl;
                }
        }
        else
            cout<<s[ok]<<" ->caracter necunoscut";
    }
        if ( ok == 1 && k == 1 && a == 1)
        afisarei(prim);
}
