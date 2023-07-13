//≤Â»Î≈≈–Ú
 void insertSort(int x[],int n)
 {
 	int i,j,temp;
 	for(i=1;i<n;i++)
 	{
 		temp=x[i];
 		for(j=i-1;j>=0;j--)
 		{
 			if(x[j]>temp)
 			x[j+1]=x[j];
 			else
 			break;
		 }
		 x[j+1]=temp;
	 }
 }
