/*  File: 
    
    
    Programmer:  Mason Allain                    Date: oct 10
*/

#include <stdio.h>
int main (void){
	//open file
		FILE * fin = fopen("salesin.txt", "r");
		
	//veriables
		float cost, sale, total, tprofit=0 , tloss=0, n;
		int quantity;
		
	//loop
		while(fscanf(fin, "%f %f %d", &cost, &sale, &quantity) !=EOF){
				
			total = (sale-cost)*quantity;

			if(total>=0){
				tprofit = tprofit + total;
				
				printf("%.2f %.2f %d: profit = %.2f, total profit = %.2f\n", cost, sale, quantity, total, tprofit);
				
			}else{
				tloss = tloss + total;
				
				printf("%.2f %.2f %d: loss   = %.2f, total loss   = %.2f\n", cost, sale, quantity, -(total), -(tloss));
				
			}
		}

	//close
		fclose(fin);
		
	return 0;
}
