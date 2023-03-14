#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define lenrow 2000


int main() {
    extern char* strdup(const char*);
	FILE*inputCsv;
    FILE*output;
    char row[lenrow];
    char *column;
    char *columns[100];
    int i, num_columns, lenColumn;
    char *column_names[lenrow];
	char filepath[1000];
	printf("Enter path:");
	scanf("%s", filepath);

	inputCsv=fopen(filepath, "r");
    output = fopen("student.json", "w");
	if (inputCsv == NULL) 
	
	{
        printf("Error: Unable to open CSV file.");
        return 1;
    }


    
    
        if (fgets(row, lenrow, inputCsv))
		
		 {

        column = strtok(row, ",");
        while (column != NULL) 
		
		{   
            column_names[num_columns] = strdup(column);
            
            fputs(column_names[num_columns], output);
            num_columns++;
            column = strtok(NULL, ",");
        }
        lenColumn=num_columns-1;
        
    }
    
    
    
    printf("[\n");
    fputs("[", output);
    
    while (fgets(row, lenrow, inputCsv)) 
	
	{
        num_columns = 0;
        column = strtok(row, ",");
        fputs("\n", output);
		while (column != NULL) 
		
		{
            columns[num_columns++] = column;
            column = strtok(NULL, ",");
        }
        printf("  {\n");
        fputs("  {\n", output);
        
		for (i = 0; i < lenColumn-1; i++) 
		
		{
			
            printf("    \"%s\": \"%s\"", column_names[i+1], columns[i]);
            
            fputs("\n", output);
            fputs("    ", output);
            fputs(column_names[i+1], output);
            fputs(":", output);
            fputs(columns[i], output);
            
            if (i < num_columns - 1)
			
			 {
                printf(",");
            }
            
			printf("\n");
        }
        printf("    \"%s\": \"%s\"", column_names[lenColumn], columns[lenColumn]);
            
        fputs("\n", output);
        fputs("    ", output);
        fputs(column_names[lenColumn], output);
        fputs(":", output);
           fputs(columns[lenColumn-1], output);
        
        printf("  }\n");
        fputs("\n  }", output);
        
        if (!feof(inputCsv))
		
		 {
            printf(",");
        }

    }
    
    
    printf("]\n");
    fputs("\n]\n", output);


    
    fclose(inputCsv);
    return 0;
}
