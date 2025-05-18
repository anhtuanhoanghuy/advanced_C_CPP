// Chương tình này sử dụng macro variadic để in ra một menu
#include <stdio.h>
#define print_menu(...)                                          \
    char *array[] = {__VA_ARGS__};                               \
    for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++) \
    {                                                            \
        printf("%d. %s\n", i + 1, array[i]);                     \
    }

void main()
{
    print_menu("Trang chủ", "Giới thiệu", "Sản phẩm", "Liên hệ", "Cài đặt");
}