FILE *fptr;
    char *ptr;
    int i = 0;
    char line[80];
    fptr = fopen("bar2.txt","r");
    sz = sizeOfFile(sz,fptr);
    ptr = fileToArray(fptr);
    for (i = 0; i < 30; i++)
    {
        printf("%s\n",lables[i]);
    }
    fclose(fptr);