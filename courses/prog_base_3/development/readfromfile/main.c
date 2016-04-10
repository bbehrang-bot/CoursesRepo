#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
int main()
{
    product_t * product[5]={product_new(),product_new(),product_new(),product_new(),product_new()};
    product_read_from_file(5,product,"product1.csv");
    product_print_list(5,product);
    return 0;
}
