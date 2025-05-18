// Chương trình này tính tổng các số có độ dài không cố định dựa vào macro variadic
// Nguyên lý: Sử dụng một mảng để lưu các đối số truyền vào, tính độ dài của mảng bằng công thức sizeof(array)/ sizeof(aray[0]) sau đó duyệt từ đầu đến cuối mảng
#include <stdio.h>
#define sum(...)                                                 \
    int array[] = {__VA_ARGS__};                                 \
    int result = 0;                                              \
    for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++) \
    {                                                            \
        result += array[i];                                      \
    }                                                            \
    printf("Tong: %d", result);

void main()
{
    sum(1, 2, 3, 4, 5, 6);
}