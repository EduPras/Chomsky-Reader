#include<iostream>
#include<queue>
#include<map>
#include<vector>
#include<sstream>

using namespace std;

void add(string* k, string *v, map<string, string> *m, map<string, string> *r){ 
  // Verificar se já existe uma produção
  string value = *v, key = *k;
  if(!m->count(key)){
    // Caso não, por exemplo X -> AS, insere {"AS", "X"}
    m->insert({key, value});
  }else{
    // O map replace guarda produções que podem ser
    // simplificadas em outras, caso ao final das 
    // declarações possuem a mesma função.
    r->insert({value, (*m)[key]});
  }
}

map<string, string> rm_redundancies(map<string, string> *m, map<string, string> *r){
  // Substituindo as redundancias
  // Como R = S dos exemplos
  map<string, string> mfinal;
  for (const auto x:  *m) {
    for (const auto y: *r){
      // [RR] = X
      if(x.first[0] == y.first[0] and x.first[1] == y.first[0]){
        mfinal.insert({y.second+y.second, x.second});
      }
      // [RY] = X
      else if(x.first[0] == y.first[0] ) {
        mfinal.insert({y.second + x.first[1], x.second});
      }
      // [YR] = X
      else if(x.first[1] == y.first[0] ) {
        mfinal.insert({x.first[0] + y.second, x.second});
      }else{
        mfinal.insert({x.first, x.second});
      }
    }
  }
  return mfinal;
}

// Divide a string em pares, ex: AA|AB|AA
// caso não encontre nenhuma produção, os pares mudam
// ex: A|AA|BA|A
bool reduce(string str, map<string, string> m, queue<string> *dt){
  //cout << str << endl;
  if(str == "S"){
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
      result = reduce(ss.str(), m, dt);
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
      result = reduce(ss.str(), m, dt);
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
  string input, aux;
  int P;
  cin >> P;
  // Lendo produções
  while(P--){
    string a,arrow,c;
    cin >> a >> arrow >> c;
    add(&c, &a, &m, &replace);
  }
  // Removendo redundancias das produções
  m = rm_redundancies(&m, &replace);
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
    if(reduce(input, m, &derivation_tree)){
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
