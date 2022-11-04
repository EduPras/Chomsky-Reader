#include<iostream>
#include<queue>
#include<map>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

void add(string* k, string *v, map<string, string> *m, map<string, string> *r){ 
  string value = *v, key = *k;
  m->insert({key, value});
}

// Divide a string em pares, ex: AA|AB|AA
// caso não encontre nenhuma produção, os pares mudam
// ex: A|AA|BA|A
bool reduce(string str, map<string, string> m, queue<string> *dt, vector<string> *S){
  vector<string>::iterator it;
  //cout << str << endl;
  it = find(S->begin(), S->end(), str);
  if(str.size() == 2 and it != S->end()){
    dt->push("S");
    dt->push(str);
    return true;
  }
  string s;
  stringstream ss;
  bool result;
  // Primeiro conjuntos de pares
  for(int i = 0; i < str.size()-1; i = i+2){
    ss << str[i] << str[i+1];
    s = ss.str();
    // Procura o par no map
    auto it = m.find(s);
    if(it != m.end()){
      // Limpa o buffer da stringstream
      ss.str("");
      // Insere todas as letras da palavra,
      // exceto pela dupla que foi trocada
      
      // Inserção das letras que precedem a produção
      for(int j = 0; j < i; j++)
        ss << str[j];
      // Inserção da produção
      ss << it->second;
      // Inserção das letras que sucedem a produção
      for(int j = i+2; j < str.size(); j++)
        ss << str[j];
      //cout << ss.str() << endl;
      result = reduce(ss.str(), m, dt, S);
      if(result) {
        dt->push(str);
        return result;
      }
    }
    // Limpando buffer 
    ss.str("");
  }
  // Divisão dos pares deslocado para o lado
  for(int i = 1; i < str.size(); i = i+2){
    ss << str[i] << str[i+1];
    s = ss.str();
    // Procura o par no map
    auto it = m.find(s);
    if(it != m.end()){
      // Limpa o buffer da stringstream
      ss.str("");
      // Insere todas as letras da palavra,
      // exceto pela dupla que foi trocada
      
      // Inserção das letras que precedem a produção
      for(int j = 0; j < i; j++)
        ss << str[j];
      // Inserção da produção
      ss << it->second;
      // Inserção das letras que sucedem a produção
      for(int j = i+2; j < str.size(); j++)
        ss << str[j];
      //cout << ss.str() << endl;
      result = reduce(ss.str(), m, dt, S);
      if(result) {
        dt->push(str);
        return result;
      }
    }
    // Limpando buffer 
    ss.str("");
  }
  return false;
}


int main(){
  map<string, string> m, replace; 
  queue<string> derivation_tree; 
  vector<string> S;
  string input, aux;
  int P;
  cin >> P;
  // Lendo produções
  while(P--){
    string a,arrow,c;
    cin >> a >> arrow >> c;
    if(a == "S") S.push_back(c);
    else add(&c, &a, &m, &replace);
  }
  // Removendo redundancias das produções
  while(cin >> input and input != "*"){
    aux = input;
    for(int i = 0; i < input.size(); i++)
    {
      // Transformando os terminais a -> A
      string s(1,input[i]);
      input[i] = m.find(s)->second[0];
    }
    // Verifica a partir do maps se é possível realizar
    // a decomposição
    cout << aux;
    if(reduce(input, m, &derivation_tree, &S)){
      derivation_tree.push(aux);
      cout << ": SIM\n";
      while(!derivation_tree.empty()){
        cout << derivation_tree.front() << endl;
        derivation_tree.pop();
      }
      cout << endl;
    }
    else cout <<": NAO\n";
    // Limpando a arvore 
    while(!derivation_tree.empty())
      derivation_tree.pop();
  

  }
}
