/*证明放在这里，说不定以后有用

设第j天结束的概率为 Tj

Tj=C(j-1,k-1)*p^k*(1-p）^（j-k） (j-1<k-1时C(j-1,k-1)=0）

∑Tj=1 即 p^k/(1-p）^k ∑C(j-1,k-1)*(1-p）^j=1

我们可以得∑C(j-1,k-1)*(1-p）^j=(1-p)^k/p^k         (1)

the expected number of days:

∑j*Tj=p^k/(1-p)^k *∑j*C(j-1,k-1)*(1-p）^j      

	  =k*p^k/(1-p)^k *∑C(j,k)*(1-p)^j     //j*C(j-1,k-1)=k*C(j,k) 
	  
	  =k*p^k/(1-p)^(k+1) *∑C(j,k)*(1-p)^(j+1)     
	  
	  =k*p^k/(1-p)^(k+1) * (1-p)^(k+1)/p^(k+1)  //由（1）得   
	  
	  =k/pthe expected number of coins∑j*j*Tj

	  =p^k/(1-p)^k *∑(j*(j+1)-j)*C(j-1,k-1)*(1-p）^j  
      
	  =p^k/(1-p)^k *∑j*(j+1)*C(j-1,k-1)*(1-p）^j - ∑j*Tj 
	  
	  =k*(k+1)*p^k/(1-p)^k *∑C(j+1,k+1)*(1-p)^j  - ∑j*Tj  //j*C(j-1,k-1)=k*C(j,k)   
	  
	  =k*(k+1)*p^k/(1-p)^(k+2) *∑C(j+1,k+1)*(1-p)^(j+2) -∑j*Tj        

	  =k*(k+1)*p^k/(1-p)^(k+2) * (1-p)^(k+2)/p^(k+2)  -∑j*Tj  //由（1）得     
	  
	  =k*(k+1)/p^2 - ∑j*Tj   

	  =k*(k+1)/p^2 - k/p
*/
#include "cstdio"
long double k, p;
int main() {
	while(scanf("%lf", &k), k) {
		scanf("%lf", &p);
		printf("%.3f %.3f\n", k / p, k * ( k + 1 ) / p / p - k / p);
	}
	return 0;
}