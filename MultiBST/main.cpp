#include <iostream>

using namespace std;

class MultiBST{
public:
    virtual MultiBST* ins(int x)=0;
    virtual void Inorder()=0;
    virtual int Multiplicity(int x)=0;
};

class Nodo{
private:
    Nodo* padre, *left, *right;
    int chiave;
    int molt;
public:
    Nodo(int val){
    chiave=val;
    padre=left=right=NULL;
    molt=1;
    }
    int getChiave(){return chiave;}
    void setChiave(int p){chiave=p;}
    int getMult(){return molt;}
    void setMult(int p){molt=p;}
    Nodo* getPadre(){return padre;}
    void setPadre(Nodo* p){padre=p;}
    Nodo* getDestro(){return right;}
    void setDestro(Nodo* p){right=p;}
    Nodo* getSinistro(){return left;}
    void setSinistro(Nodo* p){left=p;}
};

class MyMultiBST : public MultiBST {
private:
    Nodo* radice;
    void visita_Inorder(Nodo* p);
    void Trapianta(Nodo* , Nodo*);

public:
    MyMultiBST(){radice=NULL;}
    Nodo* getRoot(){return radice;}
    void setRoot(Nodo* p){radice=p;}
    MultiBST* ins(int);
    int Multiplicity(int x);
    Nodo* search_ (int p);
    void Inorder();
    MultiBST* del(int);
    Nodo* Minimo(Nodo*);
    int rank_(int x);
    Nodo* successore(Nodo* x);
    };

Nodo* MyMultiBST ::search_(int p){
    Nodo* nuovo=radice;

    while(nuovo!=NULL && nuovo->getChiave()!=p){
        if(nuovo->getChiave()>p)
            nuovo=nuovo->getSinistro();
        else nuovo=nuovo->getDestro();
    }

    return nuovo;
}

MultiBST* MyMultiBST :: ins(int key){
    Nodo* x=radice, *y=NULL;

    Nodo* temp=search_(key);

    if(temp){
        temp->setMult(temp->getMult()+1);
        return this;
        }
    else{
        while(x!=NULL){
            y=x;
            if(key<x->getChiave()) x=x->getSinistro();
            else x=x->getDestro();
        }
        Nodo* nuovo= new Nodo(key);
        nuovo->setPadre(y);
        if(y==NULL) radice=nuovo;
        else if(key <(y->getChiave())) y->setSinistro(nuovo);
        else y->setDestro(nuovo);
        return this;
        }

}

void MyMultiBST ::visita_Inorder(Nodo* p){
    if(p!=NULL) {
        visita_Inorder(p->getSinistro());
        for(int i=0; i<(p->getMult());i++)
            cout << p->getChiave() << "\t" ;
        visita_Inorder(p->getDestro());
    }
}

void MyMultiBST::Inorder(){
    cout <<endl;
    visita_Inorder(radice);
    cout <<endl;
}

int MyMultiBST::Multiplicity(int x){
    Nodo* temp=search_(x);
    if(temp) return temp->getMult();
    else return 0;
}

//ESERCIZIO 2

void MyMultiBST::Trapianta(Nodo* u, Nodo*v){
    if(u->getPadre()==NULL) radice=v;
    else if(u==u->getPadre()->getSinistro())
        u->getPadre()->setSinistro(v);
    else u->getPadre()->setDestro(v);
    if(v!=NULL)
        v->setPadre(u->getPadre());
}

Nodo* MyMultiBST::Minimo(Nodo* p){
    Nodo* minimo_=p;

    while(minimo_->getSinistro()!=NULL) minimo_=minimo_->getSinistro();
    return minimo_;
}

MultiBST* MyMultiBST ::del(int x){
    Nodo* y;

    Nodo* z=search_(x);

    if(z){
        if(z->getMult()>1){
            z->setMult(z->getMult()-1);
        }
        else {
           if(z->getSinistro()==NULL) Trapianta(z,z->getDestro());
           else if(z->getDestro()==NULL) Trapianta(z, z->getSinistro());
           else {
            y=Minimo(z->getDestro());
            if(y->getPadre()!=z){
                Trapianta(y,y->getDestro());
                y->setDestro(z->getDestro());
                y->getDestro()->setPadre(y);
            }
            Trapianta(z,y);
            y->setSinistro(z->getSinistro());
            y->getSinistro()->setPadre(y);
           }
           }
        }
        else cout << "Elemento non presente nell'albero. \n";
        return this;
}

// ESERCIZIO 3
 int MyMultiBST::rank_(int x){
    Nodo* p= search_(x);
    int rango=1;
    if(p){
            p=Minimo(radice);
            while(p->getChiave()<x){
                rango+=(p->getMult());
                p=successore(p);
                }
            return rango;
       }
    else return 0;
 }

 Nodo* MyMultiBST ::successore(Nodo* x) {
    if(x==NULL) return NULL;
    if(x->getDestro()) return Minimo(x->getDestro());
    Nodo* y=x->getPadre();
    while(y!=NULL && (y->getChiave() < x->getChiave()))
        y=y->getPadre();
    return y;
    }

int main()
{
    MyMultiBST Tree;
    int input[]={10,7,7,23,30,4,1,5,9,5,1,7,1,9};
    cout << "Vettore inserito: \n" ;
    for(int i=0; i<14; i++){
        cout << input[i] << "\t";
    }
    cout <<endl;
    for(int i=0; i< 14; i++) Tree.ins(input[i]);
    Tree.Inorder();
    cout << "\nMolteplicita' di 5: " << Tree.Multiplicity(5);
    cout << "\nMolteplicita' di 7: " <<Tree.Multiplicity(7);
    cout << "\nMolteplicita' di 17: " << Tree.Multiplicity(17) <<endl;
    Tree.del(7);
    Tree.del(4);
    Tree.del(23);
    Tree.del(7);
    Tree.del(7);
    Tree.Inorder();
    Tree.del(7);
    cout << "\nMolteplicita' di 7: " <<Tree.Multiplicity(7) <<endl;
    cout << "Rank di 5: " << Tree.rank_(5) <<endl;
    cout << "Rank di 9: " << Tree.rank_(9) <<endl;
    cout << "Rank di 30: " << Tree.rank_(30) <<endl;
    return 0;
}
