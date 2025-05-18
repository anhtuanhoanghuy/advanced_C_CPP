// Chương trình này sử dụng macro variadic để thực hiện một chức năng được khi chọn option trong menu
#include <stdio.h>
#define print_menu(...)                                              \
    do                                                               \
    {                                                                \
        char *array[] = {__VA_ARGS__};                               \
        for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++) \
        {                                                            \
            printf("%d. %s\n", i + 1, array[i]);                     \
        }                                                            \
    } while (0);

#define case_option(number, function) \
    case number:                      \
        function;                     \
        break;

#define switch_handle(option, ...) \
    switch (option)                \
    {                              \
        __VA_ARGS__;               \
    default:                       \
        break;                     \
    }
void feature1()
{
    printf("Đã mở Trang chủ\n");
}
void feature2()
{
    printf("Đã mở Giới thiệu\n");
}
void feature3()
{
    printf("Đã mở Sản phẩm\n");
}
void feature4()
{
    printf("Đã mở Liên hệ\n");
}
void feature5()
{
    printf("Đã mở Cài đặt\n");
}
int main()
{
    print_menu("Trang chủ", "Giới thiệu", "Sản phẩm", "Liên hệ", "Cài đặt");
    int item;
    printf("Chọn chức năng: ");
    scanf("%d", &item);
    switch_handle(item,
        case_option(1, feature1())
        case_option(2, feature2())
        case_option(3, feature3())
        case_option(4, feature4())
        case_option(5, feature5()));
    // switch (item)
    // {
    // case 1:
    //     feature1();
    //     break;
    // case 2:
    //     feature2();
    //     break;
    // case 3:
    //     feature3();
    //     break;
    // case 4:
    //     feature4();
    //     break;
    // case 5:
    //     feature5();
    //     break;
    // default:
    //     break;
    // }
    // return 0;
}
