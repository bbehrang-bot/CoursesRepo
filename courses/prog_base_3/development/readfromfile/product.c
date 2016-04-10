#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#define PRODUCT_NAME_MAX_LENGTH 500
#define PRODUCT_IMAGE_ADDR_LENGTH 500
PRODUCT_STATUS product_status = PRODUCT_OK;
struct product_s
{
    char name[PRODUCT_NAME_MAX_LENGTH];
    char group[PRODUCT_NAME_MAX_LENGTH];
    char imageAddr[PRODUCT_IMAGE_ADDR_LENGTH];
    int id;
    int price;
    int inStock;
    int ordersDone;

};
product_t * product_new()
{
    product_t * product = malloc(sizeof(struct product_s));
    if(product == NULL)
    {
        product_status = PRODUCT_ERROR_NO_MEMORY;
        return NULL;
    }
    strcpy(product->name,"");
    strcpy(product->group,"");
    strcpy(product->imageAddr,"");
    product->id=0;
    product->inStock=0;
    product->price=0;
    product->ordersDone=0;
    product_status = PRODUCT_OK;
    return product;
}
void product_read_from_file(size_t size,product_t* product[size],char * file_name)
{
    FILE * file_pointer;
    file_pointer = fopen(file_name,"r");
    if(file_pointer == NULL)
    {
        product_status = PRODUCT_ERROR_FILE_NULL_PTR;
        return NULL;
    }
    char buffer[500];
    fgets(buffer,500,file_pointer);
    fgets(buffer,500,file_pointer);
    int i=0;
    while(!feof(file_pointer))
    {
        char tm[200];
        char * token = strtok(buffer,",");
        int field=0;
        while(token!=NULL)
        {
            switch(field)
            {
            case 0:
            {
                strcpy(product[i]->name,token);
                field++;

            }
            break;
            case 1:
            {
                strcpy(product[i]->group,token);
                field++;
            }


            break;
            case 2:
            {
                sscanf(token,"%i",&(product[i]->id));
                field++;
            }
            break;
            case 3:
            {
                sscanf(token,"%i",&(product[i]->price));
                field++;
            }
            break;
            case 4:
            {
                sscanf(token,"%i",&(product[i]->inStock));
                field++;
            }
            break;
            case 5:
            {
                sscanf(token,"%i",&(product[i]->ordersDone));
                field++;
            }
            break;
            case 6:
            {
                strcpy(product[i]->imageAddr,token);
                field++;
            }
            break;

            }
            token = strtok(NULL,",");
        }
        // strcpy(tm,product[i]->name);
        //int v = product[i]->price;
        //printf("%i\n",product[i]->price);
        fgets(buffer,500,file_pointer);
        i++;
    }
}
void product_print_list(size_t size,product_t *product[size])
{
    for(int i=0; i<size; i++)
    {
        if(strcmp(product[i]->name,"")!=0)
        {
            printf("Name : %s  ,Group : %s, id: %d, price : %d, inStock : %d, ordersdone: %d, imageaddress : %s\n",(product[i]->name)
                   ,(product[i]->group),(product[i]->id)
                   ,(product[i]->price),(product[i]->inStock),(product[i]->ordersDone),(product[i]->imageAddr)
                  );

       }

    }
}
