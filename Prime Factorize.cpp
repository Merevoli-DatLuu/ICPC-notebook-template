#include <bits/stdc++.h>

using namespace std;
const int LIMIT = 1e7 + 7;
bool sieve[LIMIT];
int prime_factor[LIMIT];

void sieve_of_eratosthene(){
    memset(sieve, true, sizeof(sieve));

    for (long long i=2; i<=sqrt(LIMIT); i++){
        if (sieve[i]){
            for (long long j=i*i; j<=LIMIT; j+=i){
                sieve[j] = false;
                prime_factor[j] = i;
            }
        }
    }

    for (int i=2; i<LIMIT; i++){
        if (sieve[i]){
            prime_factor[i] = i;
        }
    }
}

vector <int> factorize(int k){
    vector <int> fres;

    while (k > 1){
        fres.push_back(prime_factor[k]);
        k /= prime_factor[k];
    }

    return fres;
}

int main(){
    sieve_of_eratosthene();

    int n;
    cin >> n;

    vector <int> res = factorize(n);

    for (int i=0; i<res.size(); i++){
        cout << res[i] << ' ';
    }
}
