// Simple
template<typename T>
void print(T t){
    for (const auto& e : t){
        cout << e << ' ';
    }
    cout << '\n';
}

// Any Container
template<typename T>
std::ostream& print(std::ostream &out, T const &val) {
  return (out << val << " ");
}

template<typename T1, typename T2>
std::ostream& print(std::ostream &out, std::pair<T1, T2> const &val) {
  return (out << "{" << val.first << " " << val.second << "} ");
}

template<template<typename, typename...> class TT, typename... Args>
std::ostream& operator<<(std::ostream &out, TT<Args...> const &cont) {
  for(auto&& elem : cont) print(out, elem);
  return out;
}
