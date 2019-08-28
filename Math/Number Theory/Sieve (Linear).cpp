#include <bits/stdc++.h>
using namespace std;
const int MAX = 10000005;

int phi[MAX], dvc[MAX], sig[MAX];
int least[MAX], lstCnt[MAX], lstSum[MAX];
vector<int> primes;

void RunLinearSieve(int n) {
    n = max(n, 1);
    for(int i=0;i<=n;i++) least[i] = lstCnt[i] = lstSum[i] = 0;

    primes.clear();
    phi[1] = dvc[1] = sig[1] = 1;

    for(int i = 2; i <= n; i++){
        if(least[i] == 0){
            least[i] = i; lstCnt[i] = 1; lstSum[i] = 1 + i;
            phi[i] = i - 1; dvc[i] = 2; sig[i] = 1 + i;
            primes.push_back(i);
        }
        for(int x : primes){
            if(x > least[i] || i * x > n) break;
            least[i * x] = x;

            if(least[i] == x){
                lstCnt[i * x] = lstCnt[i] + 1;
                lstSum[i * x] = 1 + x * lstSum[i];

                phi[i * x] = phi[i] * x;
                dvc[i * x] = dvc[i] / (lstCnt[i] + 1) * (lstCnt[i * x] + 1);
                sig[i * x] = sig[i] / lstSum[i] * lstSum[i * x];
            }
            else{
                lstCnt[i * x] = 1;
                lstSum[i * x] = 1 + x;

                phi[i * x] = phi[i] * (x - 1);
                dvc[i * x] = dvc[i] * 2;
                sig[i * x] = sig[i] * (1 + x);
            }
        }
    }
}

int mob[MAX];
void Mobius(int n){
    RunLinearSieve(n);

    mob[1] = 1;
    for(int i = 2; i <= n; i++) {
        int j = i/least[i];
        if(least[j] == least[i]) mob[i] = 0;
        else mob[i] = -mob[j];
    }
}

int main(){
    int n = 100;
    RunLinearSieve(n);
    for(int i=1;i<=n;i++) cout<<i<<" "<<phi[i]<<" "<<dvc[i]<<" "<<sig[i]<<endl;
}
