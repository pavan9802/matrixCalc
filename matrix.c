#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
/* multiplies 2 matricies*/ 
void Multiply(double** mult, double **x, double **y, int rowl1, int coll1, int rowl2, int coll2 ){

    
     for (int row = 0; row < rowl1; row++)
        {
            for (int col = 0; col < coll2; col++)
            {
                mult[row][col] = 0.0;
                for(int i = 0; i< rowl2; i++)
                {
                    mult[row][col] += x[row][i] * y[i][col];
                }
            }
        }

}
/* transposes a matrix*/ 
void transpose(double **x, double **trans, int rowl, int coll)
{
    for (int i = 0; i < rowl; i++)
    {
        for (int j = 0; j < coll; j++) 
        {
             double temp = x[i][j];
             trans[j][i] = temp;
        }
    }

}
/* finds the inverse of a square matrix*/
void inverse(double ** inverseMatrix,double ** mult, int size)
{
   for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if(row == col)
            {
                inverseMatrix[row][col] = 1;
            }
            else
            {
                inverseMatrix[row][col] = 0;
            }
        }
    }


    for(int p = 0; p< size; p++){
        double temp = mult[p][p];  
        for(int col = 0 ;col < size; col ++){
            mult [p][col] = mult[p][col]/temp;
           inverseMatrix[p][col] =  inverseMatrix[p][col]/temp;
    
        }  
        for(int i = p+1 ;i < size; i++){
            temp = mult[i][p];
            for(int col= 0 ;col < size; col ++){
                
                 mult[i][col] =     mult[i][col] - mult[p][col]*temp   ; 
                 inverseMatrix[i][col] =  inverseMatrix[i][col]  -inverseMatrix[p][col] * temp  ; 
                     
            }    
        } 

    }

    for(int p = size-1 ; p>=0; p--)
    {
        for(int i = p-1 ;i >=0; i--)
        {
            double temp = mult[i][p];
            for(int col= 0 ;col < size; col ++)
            {
                mult[i][col] =     mult[i][col] - mult[p][col]*temp   ; 
                inverseMatrix[i][col] =   inverseMatrix[i][col]  -inverseMatrix[p][col] * temp  ; 
            }
            
        }
    }
    

}
void printx(double **x, int rowl, int coll){
          /*Print matrix*/
    for (int i = 0; i < rowl; i++){
        for (int j = 0; j < coll; j++)
        {
            if(j+1== coll)
            {
                printf("%.0f", x[i][j]);
                printf("\n");
            }else
            {
                printf("%.0f", x[i][j]);
            }
        }
    }
   
}
void freeMem(double ** array, int len){
    for(int i = 0; i < len; i ++){
        free(array[i]);
    }
    free(array);

}
int main(int argc, char *argv[])
{
    
    if (argc == 1 || argc > 3 ) 
    {
        printf("Error: Enter 1 or 2 file names\n");
        return 1 ;
     }
    //else if(0 == 0){
    //     printf("%d", argc);
    // }
    else if (argc == 2)
    {
        printf("argc");
        FILE *file = fopen(argv[1], "r");
        char str1[5];
        
        fscanf(file, "%5s", str1);
        int coll;
        fscanf(file, "%d", &coll);
        int rowl;
        fscanf(file, "%d", &rowl);

        double** arr = (double**)malloc(rowl * sizeof(int*));
        
        for (int i = 0; i < rowl; i++)
        {
            arr[i] = (double*)malloc(coll * sizeof(int));        
        }

        for (int row = 0; row < rowl; row++)
        {
            for (int col = 0; col < coll; col++)
            {
                int temp;
                fscanf(file, "%d",&temp);
                arr[row][col] =temp;
           
            }
        }

        if (str1[0] == 't')
        {
            double** result = (double**)malloc(coll * sizeof(int*));
            for (int i = 0; i < coll; i++)
            {
                arr[i] = (double*)malloc(rowl * sizeof(int));
            }      
        
        transpose(arr, result,rowl, coll);
        printx(result, coll,rowl);
        freeMem(result, coll);
        freeMem(arr, rowl);
        }   
        else if(str1[0] == 'i') 
        {
            if(rowl != coll)
            {
                printf("Error: Matrix must be a square matrix\n");
                return 1;
            }
            double** result = (double**)malloc(rowl * sizeof(int*));
            for (int i = 0; i < rowl; i++)
            {
                result[i] = (double*)malloc(coll * sizeof(int));
            }
        inverse(result, arr, rowl);
        printx(result, coll,rowl);
        freeMem(result, rowl);
        freeMem(arr, rowl);
        }

    return 1;
    }
    else
    {
        FILE *file = fopen(argv[1], "r");
        char str1[6];
        
        fscanf(file, "%5s", str1);
        int coll;
        fscanf(file, "%d", &coll);

        int rowl;
        fscanf(file, "%d", &rowl);

        
        FILE *file2 = fopen(argv[2], "r");

        char str2[6];
        fscanf(file2, "%5s", str2);
        
        int coll2;
        fscanf(file2, "%d", &coll2);
    
        int rowl2;
        fscanf(file2, "%d", &rowl2);
        if(str1[0]!=str2[0])
        {
            printf("error: Files must be wanting to complete the same calculation");
            return 1;
        }
   
   
        /*Allocate mem for 3 2d arrays*/
        double** arr = (double**)malloc(rowl * sizeof(int*));
        double** arr2 = (double**)malloc(rowl2 * sizeof(int*));
    

        for (int i = 0; i < rowl; i++)
        {
            arr[i] = (double*)malloc(coll * sizeof(int));        
        }
        for (int i = 0; i < rowl2; i++)
        {
            arr2[i] = (double*)malloc(coll2 * sizeof(int));        
        }   
        
        /*Reads file and imputs data into arr and arr2. Sets result to a 0 array*/
        for (int row = 0; row < rowl; row++)
        {
            for (int col = 0; col < coll; col++)
            {
                int temp;
                fscanf(file, "%d",&temp);
                arr[row][col] =temp;
           
            }
        }
        for (int row = 0; row < rowl2; row++)
        {
            for (int col = 0; col < coll2; col++){
                int temp;
                fscanf(file2, "%d",&temp);
                arr2[row][col] =temp;
           
            }
        }
        if(str1[0] == 'm'){
            //allocate mem and call method
            if(coll != rowl2)
            {
                printf("Error: Matricies with invalid dimensions");
                return 1;
            }
            double** result = (double**)malloc(rowl * sizeof(int*));
            for (int i = 0; i < rowl; i++)
            {
                result[i] = (double*)malloc(coll2 * sizeof(int));        
            }
        
        Multiply(result, arr, arr2, rowl, coll, rowl2, coll2);
        printx(result, rowl, coll2);
        freeMem(arr, rowl);
        freeMem(arr2, rowl2);
        freeMem(result, rowl);

    }
    return 1;
  }
    
    
    
    
    

     
    
    
}