#include <iostream>
#include <iomanip>
#include <string>
#include <locale>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class PersianArabicConverter
{
protected:
    unordered_set<wchar_t> terminators = {L' ', L'.', L',', L'!', L'?', L';', L':', L'\n', L'\t', L'\xA0',
                                          L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H', L'I', L'J',
                                          L'K', L'L', L'M', L'N', L'O', L'P', L'Q', L'R', L'S', L'T',
                                          L'U', L'V', L'W', L'X', L'Y', L'Z', L'a', L'b', L'c', L'd',
                                          L'e', L'f', L'g', L'h', L'i', L'j', L'k', L'l', L'm', L'n',
                                          L'o', L'p', L'q', L'r', L's', L't', L'u', L'v', L'w', L'x',
                                          L'y', L'z', L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7',
                                          L'8', L'9', L'\x2009', L'٠', L'١', L'٢', L'٣', L'٤', L'٥',
                                          L'٦', L'٧', L'٨', L'٩'};

    unordered_set<wchar_t> breakers = {L'ر', L'ز', L'ژ', L'د', L'ذ', L'ا', L'و'};

    class PersianArabicLetter
    {
    public:
        int initial;
        int medial;
        int final;
        int standalone;
    };
    unordered_map<wchar_t, PersianArabicLetter> persianArabicLetters = {
        {L'ا', {0x0627, 0x0627, 0xFE8E, 0x0627}},
        {L'ب', {0xFE91, 0xFE92, 0xFE90, 0x0628}},
        {L'پ', {0xFB58, 0xFB59, 0xFB57, 0xFB56}},
        {L'ت', {0xFE97, 0xFE98, 0xFE96, 0x062A}},
        {L'ث', {0xFE9B, 0xFE9C, 0xFE9A, 0x062B}},
        {L'ج', {0xFE9F, 0xFEA0, 0xFE9E, 0x062C}},
        {L'چ', {0xFB7C, 0xFB7D, 0xFB7B, 0x0686}},
        {L'ح', {0xFEA3, 0xFEA4, 0xFEA2, 0x062D}},
        {L'خ', {0xFEA7, 0xFEA8, 0xFEA6, 0x062E}},
        {L'د', {0x062F, 0xFEAA, 0xFEAA, 0x062F}},
        {L'ذ', {0x0630, 0xFEAC, 0xFEAC, 0x0630}},
        {L'ر', {0x0631, 0xFEAE, 0xFEAE, 0x0631}},
        {L'ز', {0x0632, 0xFEB0, 0xFEB0, 0x0632}},
        {L'ژ', {0x0698, 0xFB8B, 0xFB8B, 0x0698}},
        {L'س', {0xFEB3, 0xFEB4, 0xFEB2, 0x0633}},
        {L'ش', {0xFEB7, 0xFEB8, 0xFEB6, 0x0634}},
        {L'ص', {0xFEBB, 0xFEBC, 0xFEBA, 0x0635}},
        {L'ض', {0xFEBF, 0xFEC0, 0xFEBE, 0x0636}},
        {L'ط', {0xFEC3, 0xFEC2, 0xFEC4, 0x0637}},
        {L'ظ', {0xFEC7, 0xFEC6, 0xFEC8, 0x0638}},
        {L'ع', {0xFECB, 0xFECC, 0xFECA, 0x0639}},
        {L'غ', {0xFECF, 0xFED0, 0xFECE, 0x063A}},
        {L'ف', {0xFED3, 0xFED4, 0xFED2, 0x0641}},
        {L'ق', {0xFED7, 0xFED8, 0xFED6, 0x0642}},
        {L'ک', {0xFEDB, 0xFEDC, 0xFEDA, 0x06A9}},
        {L'گ', {0xFB94, 0xFB95, 0xFB93, 0x06AF}},
        {L'ل', {0xFEDF, 0xFEE0, 0xFEDE, 0x0644}},
        {L'م', {0xFEE3, 0xFEE4, 0xFEE2, 0x0645}},
        {L'ن', {0xFEE7, 0xFEE8, 0xFEE6, 0x0646}},
        {L'و', {0x0648, 0xFEED, 0xFEEE, 0x0648}},
        {L'ه', {0xFEEB, 0xFEEC, 0xFEEA, 0x0647}},
        {L'ی', {0xFEF3, 0xFEF4, 0xFEF0, 0x06CC}}};

    bool isTerminator(wchar_t c)
    {
        return terminators.count(c) > 0;
    }
    bool isBreaker(wchar_t c)
    {
        return breakers.count(c) > 0;
    }

public:

    wstring getUnicodeRepresentation(const wstring &str)
    {
        wstring unicodeString;
        for (wchar_t c : str)
        {
            wchar_t unicodeChar[7];
            swprintf(unicodeChar, L"\\u%04X", static_cast<int>(c));
            unicodeString += unicodeChar;
        }
        return unicodeString;
    }

    void printUnicode(const wstring &str)
    {
        wcout << getUnicodeRepresentation(str);     
        wcout << endl;
    }
    // Arabic (0600–06FF)
    // Arabic Supplement (0750–077F)
    // Arabic Extended-A (08A0–08FF)
    // Arabic Presentation Forms-A (FB50–FDFF)
   wstring convertArabicForms(wstring &inputStr)
{
    std::wstring str(inputStr);
    if (inputStr.length() <= 1){
        return str;
    }    
    for (int i = 0; i < inputStr.length(); i++)
    {
        auto it = persianArabicLetters.find(inputStr[i]);

        if (it != persianArabicLetters.end())
        {
            PersianArabicLetter currentLetter = it->second;
            bool hasComeAfterBreaker = (i > 0) ? isBreaker(inputStr[i - 1]) : true;

            if (i == 0 || (i > 0 && isTerminator(inputStr[i - 1])))
            {
                str[i] = currentLetter.initial;
            }
            else if (i < inputStr.length() - 1 && !isTerminator(inputStr[i + 1]))
            {
                str[i] = hasComeAfterBreaker ? currentLetter.initial : currentLetter.medial;
            }
            else if ((i == inputStr.length() - 1 || isTerminator(inputStr[i + 1])) && !hasComeAfterBreaker)
            {
                str[i] = currentLetter.final;
            }
            else
            {
                str[i] = currentLetter.standalone;
            }
        }
    }
    return str;
}
};