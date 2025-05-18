
# BÀI 1: Compiler - Macros
1.1. Compiler
Quá trình biên dịch chương trình:
Bước 1: Pre-processor: tiền xử lý
    Chương trình C khi qua quá trình tiền xử lý sẽ build các file .h sang .i : loại bỏ chú thích, copy code từ các file include sang, thay thế các macro

Bước 2: Compiler:
    Chương trình sau khi qua quá trình tiền xử lý sẽ được dịch sang mã Assembly, build từ file .i sang .s

Bước 3: Assembler
    Chương trình tiép tục build từ file.s sang .o. Ở quá trình này, mã nguồn sẽ được chuyển sang mã nhị phân để máy tính có thể hiểu được.

Bước 4: Linker
    Giai đoạn này trình biên dịch sẽ liên kết các file .o lại với nhau để tạo thành một file thực thi cuối cùng .exe. Từ đây chương tình đã có thể chạy được.

1.2. Macros
    Macros là từ hay chỉ thị dùng để chỉ những thông tin được xử lý ở quá trình tiền xử lý.
    Các loại Macros:
    - #include: liên kết các thư viện, các file mã nguồn khác
    + #include <>: dùng cho thư viện chuẩn, khi trình biên dịch thấy<> thì sẽ tìm kiếm trong thư mục cài đặt
    + #include “”: tìm kiếm trong thư mục hiện tại, các file do mình tự định nghĩa
    - #define: macro dùng để định nghĩa giá trị, hàm số, không kiểm tra lỗi, không kiểm tra kiểu dữ liệu, trình biên dịch qua quá trình tiền xử lý sẽ thay thế tên được thay thế bằng giá trị, hàm thực.
    - ##: dùng để nối chuỗi
    - #: dùng để chuẩn hóa đoạn văn bản lên chuỗi
    - ...: variadic, dùng để báo hiệu tham số truyền vào có số lượng không xác định
    - __VAR_ARGS__: liệt kê các tham số 
    - #undef: hủy định nghĩa
    - #if: kiểm tra macro
    - #ifdef, #ifndef: kiểm tra macro đã được định nghĩa hay chưa
    - #endif: kết thúc định nghĩa

# BÀI 2: STDARG - ASSERT
1.1. Định nghĩa:
Thư viện stdarg cung cấp các phương thức để làm việc với các hàm số có số lượng tham sô đầu vào không cố định
1.2. Các hàm thường dùng:
- va_list: kiểu struct, khia báo một biến để chức các tham số có độ dài không xác định
- va_start: bắt buộc để khởi tạo va_list và cho phép bạn truy cập các đối số biến đổi (sau đối số cố định) trong hàm. Nếu bạn không gọi va_start, thì việc gọi va_arg sẽ truy cập vào vùng nhớ rác (undefined behavior).
- va_arg: lấy ra lần lượt giá trị của tham số sau mỗi lần gọi và ép kiểu cho tham số đó
- va_end: thu hồi, kết thúc truy cập danh sách tham số không xác định
- va_copy: Sao chép dữ liệu giữa 2 biến cùng kiểu va_list.
1.3. Các ví dụ với __VAR_ARGS__ và thư viện stdarg
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


// Chương trình này tính tổng các số có độ dài không cố định dựa vào tham số đầu tiên chỉ định độ dài của dãy số
// Nhược điểm: khi truyền đối số cần phải truyền vào độ dài của dãy số
// Nếu truyền vào độ dài count của dãy số bé hơn số phần tử của dãy số thì chương trình tính tổng sẽ chỉ tính đến số phần tử thứ count
// Nếu truyền vào độ dài count của dãy số lớn hơn số phần tử của dãy số thì chương trình tính tổng sẽ có thể bị sai do giá trị bên ngoài có thể là 0 hoặcoặc là giá trị rácrác
#include <stdio.h>
#include <stdarg.h>
int sum(int count, ...)
{
    va_list args;
    va_start(args, count);
    int result = 0;
    for (int i = 0; i < count; i++)
    {
        result += va_arg(args, int);
    }
    va_end(args);
    printf("Tong: %d", result);
}
void main()
{
    sum(5, 1, 2, 3, 4, 5);       // Hàm này chạy đúng
    sum(5, 1, 2, 3, 4, 5, 6, 7); // Hàm này chạy sai do tính thiếu giá trịtrị
    sum(7, 1, 2, 3, 4, 5);       // Hàm này chạy sai do truyền thừa số phần tử
}




// Chương trình này tính tổng các số có độ dài không cố định dựa vào thư viện stdarg và macro variadic sử dụng số 0 báo hiệu kết thúc
// Nhược điểm: nếu trong dãy số có số 0 thì sẽ tính sai do bị kết thúc khi chưa duyệt hết dãy số
#include <stdio.h>
#include <stdarg.h>
#define sum(...) tong(__VA_ARGS__, 0)
int tong(int first_number, ...)
{
    va_list args;
    va_start(args, first_number);
    int result = first_number;
    int current_value = 0;
    while ((current_value = va_arg(args, int)) != 0)
    {
        result += current_value;
    }
    va_end(args);
    printf("Tong: %d", result);
}
void main()
{
    sum(1, 2, 3, 4, 5, 6); // Hàm này chạy đúng
    sum(1, 2, 3, 0, 5, 6); // Hàm này chạy sai do có số 0 trong dãy số
}




// Chương trình này tính tổng các số có độ dài không cố định dựa vào thư viện stdarg và macro variadic sử dụng kí tự '0' báo hiệu kết thúc
// Nhược điểm: nếu trong dãy số có số là mã ascii của kí tự '0' (48) thì sẽ tính sai do bị kết thúc khi chưa duyệt hết dãy số
#include <stdio.h>
#include <stdarg.h>
#define sum(...) tong(__VA_ARGS__, '0')
int tong(int first_number, ...)
{
    va_list args;
    va_start(args, first_number);
    int result = first_number;
    int current_value = 0;
    while ((current_value = (va_arg(args, int))) != '0')
    {
        result += current_value;
    }
    va_end(args);
    printf("Tong: %d", result);
}
void main()
{
    sum(1, 2, 3, 4);  // Hàm này chạy đúng
    sum(1, 2, 48, 5); // Hàm này chạy sai do có số 48 là mã ascii của kí tụ '0'
}



// Chương trình này tính tổng các số có độ dài không cố định dựa vào thư viện stdarg và macro variadic sử dụng chuỗi "end" báo hiệu kết thúc
// Lưu ý: phải gọi va_start trước va_copy
#include <stdio.h>
#include <stdarg.h>
#define tong(...) sum(__VA_ARGS__, "end")
int sum(int first_number, ...)
{
    va_list args;
    va_list check;
    va_start(args, first_number);
    va_copy(check, args);
    int result = first_number;
    while (va_arg(check, char *) != "end")
    {
        result += va_arg(args, int);
    }
    va_end(args);
    printf("Tong: %d", result);
}
void main()
{
    sum(1, 2, 3, 4, 5);
}



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

1.4. Assert
- Định nghĩa: thư viện assert cung cấp các macro dùng để kiểm tra một điều kiện. Nếu điều kiện đúng, không có gì xảy ra và chương trình tiếp tục được thực thi. Nếu điều kiện sai, chương trình sẽ dừng lại và thông báo một thông điệp lỗi.

1.5. Ví dụ sử dụng thư viện assert
//Chương trình này sử dụng thư viện assert để kiểm tra điều kiện
#include <stdio.h>
#include <assert.h>
int divide(int a,int b){
  assert(b != 0 && "Không được chia cho 0");
    printf("result: %d",a/b);
}
void main(){
    divide(6,2); //hàm này chạy đúng và không thông báo lỗi
    divide(6,0); //hàm này chạy sai vì chia cho 0, dừng chương trình, in ra thông báo lỗi kèm dòng bị lỗi
}
# BÀI 3: BITMASK
