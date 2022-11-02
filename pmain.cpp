#include<iostream>
#include<map>
#include<vector>

using namespace std;

void add(string* k, string *v, map<string, string> *m, map<string, string> *r){ 
  // Verificar se já existe uma produção
  string value = *v, key = *k;
  if(!m->count(key)){
    cout <<  "Adicionando chave [ " << 
      key << ", " << value << " ]" << endl;
    m->insert({key, value});
  }else{
    // O map replace guarda produções que podem ser
    // simplificadas em outras, caso ao final das 
    // declarações possuem a mesma função.
    cout << "Chave " << key << " já existe com o valor "
      << (*m)[key] << endl;
    r->insert({value, (*m)[key]});
  }
}

map<string, string> rm_redundancies(map<string, string> *m, map<string, string> *r){
  cout << endl;
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

int main(){
  map<string, string> m, replace; 
  string input;
  int P;
  cin >> P;
  while(P--){
    string a,arrow,c;
    cin >> a >> arrow >> c;
    add(&c, &a, &m, &replace);
  }
  m = rm_redundancies(&m, &replace);
  cout << endl << "Final\n";
    for (const auto x:  m) {
      std::cout << '[' << x.first << "] = " << x.second << ";\n";
    }
}
