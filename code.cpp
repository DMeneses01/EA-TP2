/* Duarte Emanuel Ramos Meneses - 2019216949
   Patricia Beatriz Silva Costa - 2019213995
   EA - Trabalho2 - 2021/2022 */

#include <iostream>
#include <string>
#include <sstream>  
#include <vector>
#include <map>

using namespace std;

struct member
{
    vector<int> recruited;
    int value;
    pair<int, int> put;
    pair<int, int> no_put;

};

int number_members;
map <int, member> tree;

int input(){
    string numbers;
    number_members = 0;

    while(getline(cin, numbers)){

        stringstream stream(numbers);

        vector<int> values;

        int n;
        stream >> n; //Buscar o primeiro numero da linha

        if(n != -1){ //Se for -1 acaba este grupo de teste
            values.emplace_back(n); //Caso contrario adicionamos

            number_members++; // Saber quantos membros tem este grupo

            while(stream >> n){ //buscar os resto de numeros daquela linha
                values.emplace_back(n);
            }

            member m = {}; 

            m.value = values.back(); //Valor e o último do vector


            //Buscar todos os membros que o recrutador recrutou    
            for(size_t i = 1; i < (values.size() - 1); i++){ 
                m.recruited.emplace_back(values[i]);
            }
            
            tree.insert(make_pair(values[0], m)); // --> Numero do no: suas informacoes
        
        }

        else { //Se chegarmos a -1 acaba este grupo de testes
            return 0;
        }

    }

    return 1; //Nao existem mais testes
}


int pyramid(int id) {

    if(tree[id].recruited.size() == 0){
        tree[id].put = {1, tree[id].value}; //Caso seja usado este no
        tree[id].no_put = {0, 0}; //Caso nao usemos o no -> Vai indicar depois que este nao tem filhos
        return 0;
    }
    for(size_t i = 0; i<tree[id].recruited.size(); i++){
        pyramid(tree[id].recruited[i]);
    }

    //Se eu colocar
    //Somar (1, valor) ao melhores casos dos filhos
    int f=1, s=tree[id].value;
    for(size_t i = 0; i<tree[id].recruited.size(); i++) {
        if (tree[tree[id].recruited[i]].no_put.first > tree[tree[id].recruited[i]].put.first) {
            f += tree[tree[id].recruited[i]].put.first;
            s += tree[tree[id].recruited[i]].put.second;
        }
        else if (tree[tree[id].recruited[i]].no_put.first < tree[tree[id].recruited[i]].put.first){
            f += tree[tree[id].recruited[i]].no_put.first;
            s += tree[tree[id].recruited[i]].no_put.second;
        }

        else{
            if (tree[tree[id].recruited[i]].no_put.second <= tree[tree[id].recruited[i]].put.second){
                f += tree[tree[id].recruited[i]].put.first;
                s += tree[tree[id].recruited[i]].put.second;
            }
            else{
                f += tree[tree[id].recruited[i]].no_put.first;
                s += tree[tree[id].recruited[i]].no_put.second;
            }
            
        }
    }
    tree[id].put = {f, s};

    //Se eu não colocar
    //Somar os casos de put dos filhos
    f=0, s=0;
    for(size_t i = 0; i<tree[id].recruited.size(); i++) {
        f += tree[tree[id].recruited[i]].put.first;
        s += tree[tree[id].recruited[i]].put.second;
    }
    tree[id].no_put = {f, s};

    return 0;
}


int main (){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int res = 0;

    while(res == 0){ //Enquanto nao retornar 1 significa que existem mais testes

        res = input(); //Input do grupo de teste
        if(res == 0){
            pyramid(0);

            if (tree[0].no_put.first > tree[0].put.first) 
                cout << tree[0].put.first << " " << tree[0].put.second << "\n";

            else if (tree[0].no_put.first < tree[0].put.first) 
                cout << tree[0].no_put.first << " " << tree[0].no_put.second << "\n";

            else{

                if (tree[0].no_put.second <= tree[0].put.second) 
                    cout << tree[0].put.first << " " << tree[0].put.second << "\n";

                else cout << tree[0].no_put.first << " " << tree[0].no_put.second << "\n";
                
            }
        }

        tree.clear();
        
    }

    return 0;
}