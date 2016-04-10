#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED
typedef enum PRODUCT_STATUS
{PRODUCT_OK, PRODUCT_ERROR_NULL_PTR, PRODUCT_ERROR_NO_MEMORY,PRODUCT_ERROR_NAME_OVERFLOW,PRODUCT_ERROR_FILE_NULL_PTR} PRODUCT_STATUS;
typedef struct product_s product_t;
product_t * product_new();
void product_read_from_ile(size_t size,product_t *product[size] , char * fileName);
void product_print_list(size_t size,product_t *product[size]);

#endif // PRODUCT_H_INCLUDED
