#include "./convertFarsi.h"

int main() {
    PersianArabicConverter converter;
    std::wstring inputString = L"سلام خانم زیبا چه خبرا اسمت چیه فریبا\r\n";
    converter.printUnicode(inputString);
    wstring outputString = converter.convertArabicForms(inputString);
    converter.printUnicode(outputString);
    return 0;
}
