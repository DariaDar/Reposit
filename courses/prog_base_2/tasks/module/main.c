#include <stdio.h>
#include <stdlib.h>
#include "text.h"

int main()
{
    int n;
    int index, format;
    int cntMax;
    char str[200];

    printf("Make your new text.\nEnter Max count of sentences:");
    scanf("%i", &cntMax);
    printf("\nEnter your first sentence.\n");
    scanf("%s", str);
    text_t pStruct = text_new(cntMax,str);


    printf("1. Add sentence.\n2. Delete sentence\n3.Set format\n");
    printf("4.Get list of your sentences with special format.\n5.Get count of your sentences.\n6.Exit\n\n ");
    for(;;)
    {
        text_getList(pStruct);
        printf("\n\nEnter number of command: ");
        fflush(stdin);
        scanf("%i", &n);
        switch(n)
        {
            case 1:
            printf("Write INDEX and then your string.\n");
            scanf("%i %s", &index, str);
            text_Insert(pStruct,index,str);
            break;
        case 2:
            printf("Write index: ");
            scanf("%i", &index);
            text_deleteStr(pStruct, index);
            break;
        case 3:
            printf("Write INDEX (0...%i) and then your format (0..3):\n", (text_getRealCntStr(pStruct) - 1));
            scanf("%i %i", &index, &format);
            text_setFormat(index, format,pStruct);
            break;
        case 4:
            printf("Write number of format (0..3):\n");
            scanf("%i", &format);
            text_getListForm(pStruct,format);
            break;
        case 5:
            printf("%i", text_getRealCntStr(pStruct));
            break;
        default:
            text_delete(pStruct);
            return 0;
            break;
        }
    }

}

