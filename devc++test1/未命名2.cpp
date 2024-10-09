#include <iostream>
using namespace std;
#include <cmath>
#include <vector>
long long n;
vector<int> v;
int ans;
bool isprime(int x){
  for(int i=2;i<=sqrt(x);i++){
    if(x%i==0)
      return false;
  }
  return true;
}

int main()
{
  n=sqrtl(23333333333333);
  n=sqrtl(n);
  for(int i=2;i<=n;i++){
    if(isprime(i))
      v.push_back(i);
  }
  for(long long i = 2333; i <= 23333333333333; i++){
    n=sqrtl(i);
    if(n*n!=i)continue;
    if(n%2==0 && isprime(n/2)==true)
      ans++;
    if(n%2!=0){
      for(int j=0;v[j]<=sqrtl(n);j++){
        if(n%j!=0)continue;
        if(isprime(n/j)==true){
          ans++;
          break;
        }
      }
    }
  }
  cout<<ans;
  return 0;
}
