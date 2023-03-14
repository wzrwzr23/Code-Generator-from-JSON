#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define lenrow 2000


int main() {
	FILE*inputCsv;
	char filepath[1000];
	printf("Enter path:");
	scanf("%s", filepath);//asks user to input filepath, opens intended file

	inputCsv=fopen(filepath, "r");
        FILE*output=fopen("C:\\Users\\Josiah\\Documents\\tnJSON.json", "w");//path to store json file
	if (inputCsv == NULL) 
	
	{
        printf("Error: Unable to open CSV file.");//throw error if path does not exist
        return 1;
        }

        char row[lenrow];
        char *column;
        char *columns[100];
        int i, num_columns, lenColumn;

        char *column_names[lenrow];
    
    
        if (fgets(row, lenrow, inputCsv))
		
	{
		// Get the column names from the first row
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
        
	for (i = 0; i < lenColumn; i++) 
	{
			
            printf("    \"%s\": \"%s\"", column_names[i+1], columns[i]);//print header:value
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
        
        printf("  }\n");
        fputs("\n  }", output);
        
        if (!feof(inputCsv))
	{
            printf(",");//adds comma if end of file not reached
        }
        printf("\n");
    }
    
    
    printf("]\n");
    fputs("\n]\n", output);

    fclose(inputCsv);
    return 0;
}

