#include <stdio.h>



int main(){
  int C,N,K;
  int ans;

  scanf("%d %d %d",&C,&N,&K);
  

/////////start and end for N children//////
  int s[N];
  int e[N];
  int Array[N][2];
  
  for(int i=0;i<N;i++){
      scanf("%d %d",&s[i],&e[i]);
   
      Array[i][0] = s[i];
      Array[i][1] = e[i]; 
    
    if(s[i] > C || e[i] > C || s[i] < 0 || e[i] < 0){
    
    	printf("Bad\n");
      	return 0;
        }
  }
  

  
/*
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
        printf("\nArray[%d][%d] = %d",i,j,Array[i][j]);
    }
}
*/
  
  
  int temp = 0;
for(int i = 0; i < N; i++){
  for(int j = i+1; j< N; j++){
      if(Array[j][0] < Array[i][0]){
        temp = Array[j][0];
        Array[j][0] = Array[i][0];
        Array[i][0] = temp;
      
        temp = Array[j][1];
        Array[j][1] = Array[i][1];
        Array[i][1] = temp;
      }

      if(Array[j][0] == Array[i][0]){
          if(Array[j][1] < Array[i][1]){
            temp = Array[j][0];
            Array[j][0] = Array[i][0];
            Array[i][0] = temp;
          
            temp = Array[j][1];
            Array[j][1] = Array[i][1];
            Array[i][1] = temp;

          }
        
      }
  
    }
}
  

 //MergeSort(Array,0,N-1);
  
/*
for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
        printf("\nArray[%d][%d] = %d",i,j,Array[i][j]);
    }
}
*/

int error = 0;
int remaining[N+1];
remaining[0] = Array[0][0] - 1;
for(int i=1;i<N;i++){
    remaining[i] = Array[i][0] - Array[i-1][1] - 1;

    if(remaining[i] < 0){
        ++error;
    }
}
remaining[N] = C - Array[N-1][1];
/*
for(int i=0; i<=N; i++){
    printf("\nrem[%d] = %d",i,remaining[i]);
}
*/
if(K == 0){
    if(error > 0 ){
        ans = 0;
    }

    else if(error == 0){
        ans = 1;
    }

}

if(K == 1){
    if(error > 2){
        ans = 0;
        
    }
  
  else if(error == 0){
        ans = 1;
    }

    else{
        for(int i=0;i<=N;i++){
            
                if(remaining[i] < 0 && remaining[i+1] >= 0){
                  
                  	if(error == 2){
                        ans = 0;
                        break;
                    }
                  
                    if(remaining[i-1] + remaining[i] + (Array[i-1][1] - Array[i-1][0] +1) >= (Array[i-1][1] - Array[i-1][0] +1)){
                        ans = 1;
                        break;
                    }
                    if(remaining[i] + remaining[i+1] + (Array[i][1] - Array[i][0] +1) >= (Array[i][1] - Array[i][0] +1)){
                        ans = 1;
                        break;
                    }
                  	
                  else{
                        for(int j = 0; j <= N; j++){
                            if(Array[i-1][1] - Array[i-1][0] +1 <= remaining[j]){
                                printf("Good\n");
                                return 0;
                            }
                        }
                    }
                    
                }
            
	      if(remaining[i] < 0  &&  remaining[i+1] < 0){
                    
                    if(Array[i+1][0] - Array[i-1][1] < 0){
                        printf("Bad\n");
                        return 0;
                    }

                    for(int j = 0; j <= N; j++){
                        if(Array[i][1] - Array[i][0] +1 <= remaining[j]){
                            printf("Good\n");
                            return 0;
                        }
                    }

                    
                }       
        }
    }

}


if(ans == 1){
    printf("Good\n");
}

else if(ans == 0){
    printf("Bad\n");
}
 return 0; 
}
