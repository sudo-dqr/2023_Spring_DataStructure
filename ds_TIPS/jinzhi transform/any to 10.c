#include <stdio.h>
int main(){
	int x,p;   //x输入数字  p该数的进制数  
	scanf("%d",&x);
	scanf("%d",&p);
	int y=0,product=1;
	while(x!=0){
		y=y+(x%10)*product;
		x=x/10;
		product=product*p;
	}
	printf("%d",y);
	return 0;
} 