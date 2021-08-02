#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
#define TAM 50

struct Dados {
    int aux;
	string rg;
	string nome;
	Dados* proximo;

}typedef Dados;

struct SetLista{
	Dados* primeiro;
	Dados* ultimo;
	int tamanho;
	int tipo;
}typedef SetLista;

Dados* listaEncadeada(SetLista* a);
Dados* listaSequencial(SetLista* a);
void escreveArquivo(Dados* lista, SetLista* a);
void removeElemento(Dados* lista, SetLista* a);
void adicionaElemento(Dados* lista,SetLista* a);
void imprimeLista(Dados* lista, SetLista* a);
void procuraElemeto(Dados* lista, SetLista* a);

int m, c;

int main(){

	clock_t start_time, end_time;

    int aux, aux2, *a;
    SetLista* setlista = new SetLista;
    Dados* primeiro, *lista;

    cout << "Digite 1 para encadeada e 2 para sequencial:\n";
    cin >> aux;
    setlista->tipo = aux;

    start_time = clock();
    if(aux == 1){
        setlista->primeiro = listaEncadeada(setlista);
        setlista->ultimo->proximo = NULL;
    }else{
        lista = listaSequencial(setlista);
        lista[setlista->tamanho-1].proximo = NULL;
    }
    end_time = clock();

    cout << "\nExecution time was  " << (end_time - start_time) / CLOCKS_PER_SEC  << "  seconds\n";
    cout << "C: " << c << "M: " << m << "\n";




    while(aux!=6){

        cout << "\n1-Adicionar elemento.\n2-Remover elemento.\n3-Imprimir lista.\n4-Procurar elemento.\n5-Escrever em arquivo.\n6-Sair.\n";
        cin >> aux;

        start_time = clock();
        c++;
        switch (aux){
            case 1:
                adicionaElemento(lista, setlista);
                cout << "C: " << c << "M: " << m << "\n";
                imprimeLista(lista, setlista);
                break;
            case 2:
                removeElemento(lista, setlista);
                cout << "C: " << c << "M: " << m << "\n";
                imprimeLista(lista, setlista);
                break;
            case 3:
                imprimeLista(lista, setlista);
                break;
            case 4:
                procuraElemeto(lista, setlista);
                break;
            case 5:
                escreveArquivo(lista, setlista);
                break;
            default:
                c=0;
                m=0;
                break;
        }
        end_time = clock();
        cout << "Execution time was " << (end_time - start_time) / CLOCKS_PER_SEC  << " seconds\n\n";
        cout << "C: " << c << "M: " << m << "\n";

    }

    	cout << "____END____";

    return 0;
}
Dados* listaEncadeada(SetLista* a){

    m = 0;
    c = 0;
    int i = 0, j, aux;
	string line, nomef, nome, rg;
	Dados* atual;

	cout << "Qual o nome do arquivo? ";
	cin >> nomef;
	ifstream myfile(nomef.c_str());

	Dados* primeiro = new Dados;
	atual = primeiro;


	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			for (j = 0; j < line.size(); j++) {
				if (line[j] == ',')
					aux = j;
			}
			string nome = line.substr(0, aux);
			string rg = line.substr(aux + 1, line.size());

			Dados* proximo = new Dados;

			atual->nome = nome;
			atual->rg = rg;
			atual->proximo = proximo;

			atual = proximo;
			i++;

		}
		a->ultimo = atual;
		myfile.close();

		cout << "\n";
		a->tamanho = i;
	}
	else
		cout << "Unable to open file";

	return primeiro;
}

Dados* listaSequencial(SetLista* a){

    int i = 0, j, aux, n;
	string line, nome;
	Dados* lista;

	c=0;
	m=0;

	cout << "Quantas pessoas? ";
	cin >> n;

	lista = (Dados*) malloc((n+20)*sizeof(Dados));

	cout << "\nQual o nome do arquivo? ";
	cin >> nome;
	ifstream myfile("NomeRG10.txt");


	if (myfile.is_open()) {

		while (getline(myfile, line)) {
			for (j = 0; j < line.size(); j++) {
				if (line[j] == ',')
					aux = j;

			}
			string nome = line.substr(0, aux);
			string rg = line.substr(aux + 1, line.size());

			lista[i].nome = nome;
			lista[i].rg = rg;

			i++;
		}
		myfile.close();
		cout << i << "\n\n__________\n\n";
		a->tamanho = i;
	}
	else
		cout << "\nUnable to open file";

	return lista;
}

void imprimeLista(Dados* lista, SetLista* a){

    int i, j;
    m = 0;
    c = 0;
    Dados* atual = a->primeiro;
    i = a->tamanho;

    if (a->tipo == 2){
        for (j = 0; j < i; j++){
			cout << "Nome:   " << lista[j].nome << "    RG:    " << lista[j].rg << '\n';
			cout << "____________________________________\n";
		}
    }else{
        for(j = 0; j < i; j++){
			cout << "Nome:   " << atual->nome << "    RG:    " << atual->rg << '\n';
			cout << "____________________________________\n";
			atual = atual->proximo;
		}
    }

}


void adicionaElemento(Dados* lista, SetLista* a){


	int aux=0, pos, tam, i;
	Dados* paux1, paux;
	string nome, rg;

	m = 0;
    c = 0;

    tam = a->tamanho;
	a->tamanho = tam+ 1;
	tam++;

	cout << "Digite o nome e o RG:  \n";
    cin >> nome;
    cin >> rg;

	cout << "1-Adicionar elemento no final. \n2-Adicionar elemento no começo. \n3-Adicionar elemento no meio. \n";
	cin >> aux;


	if(a->tipo == 1){

        Dados* atual = new Dados;
        atual->nome = nome;
        atual->rg = rg;
		switch (aux){
			case 1:
				//Dados* atual = new Dados;
				paux1 = a->primeiro;
				for(i=0 ;i < tam-1 ;i++){
					paux1 = paux1->proximo;
                    m++;
                }
                paux1->proximo = atual;
				a->ultimo->proximo = atual;
				a->ultimo = atual;
				m=m+2;
				c++;
				break;
			case 2:
				atual->proximo = a->primeiro;
				a->primeiro = atual;
				m=m+2;
				c++;
				break;
			case 3:
				cout << "Qual posição? \n";
				cin >> pos;
				paux1 = a->primeiro;
				for(i=0 ;i < pos-1 ;i++){
					paux1 = paux1->proximo;
                    m++;
                }
				//Dados* atual = new Dados;
				atual->proximo = paux1->proximo;
				paux1->proximo = atual;
				m=m+2;
				c++;
				break;
			default:
				cout << "Valor invalido";
				c++;
				break;

		}
	}else{
        //lista = (Dados*) realloc(lista, tam*sizeof(Dados));
        //cout << "CHEGOU \n\n\n";
		switch (aux){
			case 1:
				lista[tam-1].nome = nome;
				lista[tam-1].rg = rg;
				m=m+2;
				c++;
				break;
			case 2:
				for(i=tam-1;i>0;i--){
					lista[i].nome = lista[i-1].nome;
					lista[i].rg = lista[i-1].rg;
					m=m+2;
					c++;
				}
				lista[0].nome = nome;
				lista[0].rg = rg;
				m=m+2;
				c++;
				break;
			case 3:
				cout << "Qual posição? \n";
				cin >> pos;

				for(i=tam-1;i>pos-1;i--){
					lista[i].nome = lista[i-1].nome;
					lista[i].rg = lista[i-1].rg;
					m=m+2;
					c++;
				}

				lista[pos-1].nome = nome;
                lista[pos-1].rg = rg;
				m=m+2;
				c++;
                break;
			default:
				cout << "Valor invalido";
				c++;
				break;
        }
    }
}
void removeElemento(Dados* lista, SetLista* a){

	int aux, j, pos, i, tam;
	Dados* atual, *paux;
	m = 0;
    c = 0;

    atual = a->primeiro;
    a->tamanho = a->tamanho -1;
    tam = a->tamanho;

	cout << "1-Remover elemento no final. \n2-Remover elemento no começo. \n3-Remover elemento no meio. \n";
	cin >> aux;
	if(a->tipo == 1){
		switch (aux){
			case 1:
				for(j=0 ; j<a->tamanho-1 ; j++){
					atual = atual->proximo;
					m++;
					c++;
                }
				paux = atual->proximo;
				delete paux;
				//atual->proximo = NULL;
				m=m+2;
                c++;
				break;
			case 2:
				a->primeiro = a->primeiro->proximo;
				delete atual;
                m=m+2;
                c++;
				break;
			case 3:
				cout << "Qual posição? \n";
				cin >> pos;
				for(j=0 ;j < pos-1 ;j++){
					atual = atual->proximo;
                    c++;
                    m++;
                }
				paux = atual->proximo;
				atual->proximo = paux->proximo;
				delete paux;
                c++;
                m=m+2;
				break;
			default:
				cout << "Valor invalido";
				c++;
				break;

		}
	}else{
		switch (aux){
			case 1:
				//lista = (Dados*) realloc(lista, tam*sizeof(Dados));
                c++;
				break;
			case 2:
				for(i=0;i<tam;i++){
					lista[i].nome = lista[i+1].nome;
					lista[i].rg = lista[i+1].rg;
					m=m+2;
					c++;
				}
				//lista = (Dados*) realloc(lista, tam*sizeof(Dados));
				c++;
				break;
			case 3:
				cout << "Qual posição? \n";
				cin >> pos;
				for(i=pos-1;i<tam;i++){
					lista[i].nome = lista[i+1].nome;
					lista[i].rg = lista[i+1].rg;
					m=m+2;
					c++;
				}
				//lista = (Dados*) realloc(lista, tam*sizeof(Dados));
				c++;
				break;
			default:
				cout << "Valor invalido";
				c++;
				break;
		}
    }
}

void procuraElemeto(Dados* lista, SetLista* a){

	string rg;
	Dados* atual;
	int i, tam =a->tamanho;
	m = 0;
    c = 0;
	cout << "Insira o RG:\n";
    cin >> rg;

    atual = a->primeiro;

    if(a->tipo == 1){
    	for(i = 0; i < tam; i++){
    		if(atual->rg == rg)
    			break;
    		atual = atual->proximo;
        }

		cout << "Nome:   " << atual->nome << "    RG:    " << atual->rg << "   Posição : " << i+1 << '\n';
		cout << "____________________________________\n";
		m++;
        c++;

    }else{
    	for(i = 0; i < a->tamanho; i++){
    		if(lista[i].rg == rg)
    			break;
    	}

    	cout << "Nome:   " << lista[i].nome << "    RG:    " << lista[i].rg << "   Posição : " << i+1 << '\n';
		cout << "____________________________________\n";
        m++;
        c++;
    }
}

void escreveArquivo(Dados* lista, SetLista* a){

	Dados* atual;
	int i, tam = a->tamanho;

	m = 1;
    c = 0;

	ofstream myfile ("arq.txt");
    if (myfile.is_open()){
    	if(a->tipo == 1){
    		atual = a->primeiro;
    		for(i=0;i<tam;i++){
    			myfile << atual->nome << "," << atual->rg << "\n";
    			atual=atual->proximo;
    			m++;
                c++;
    		}
    	}else{
    		for(i=0;i<tam;i++){
    			myfile << lista[i].nome << "," << lista[i].rg << "\n";
    			c++;
    		}
    	}

      myfile.close();
    }
    else
        cout << "Unable to open file";
}

