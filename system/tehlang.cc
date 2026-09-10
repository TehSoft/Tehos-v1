#include "tehlang.hh"

namespace teh::lang {
    #pragma region változók
    defined vals[26] = { 0 };
    volatile int64 test_vals[26] = { 0 };

    defined var(char* code) { // kezelni kell minden lehetőséget
        if (code == nullptr) {
            return {0, deftype::NUM };
        }
        code = trim_string(code);
        if (*code == '\0') {
            return { 0, deftype::NUM };
        }
        /*defined tempdata[16] = { 0, deftype::NUM };*/
        if(code[0] == '\'' && code[2] == '\'' && code[3] == '\0') {
            return { (int64)code[1], deftype::CHAR };
        }
        elif (code[0] >= 'a' && code[0] <= 'z' && code[1] == '\0') {
            return vals[code[0] - 'a'];
        }
        elif (strcmp(code, "true")) {
            return { 1, deftype::BOOL };
        }
        elif (strcmp(code, "false")) {
            return { 0, deftype::BOOL };
        }
        else {
            int64 value = 0;
            while (*code != '\0') {
                if (*code < '0' || *code > '9') {
                    return { 0, deftype::NUM };
                }
                value = value * 10 + (*code - '0');
                code++;
            }
            return { value, deftype::NUM };
        }
    }

    void fdef(char* code) {
        if (code == nullptr) {
            return;
        }
        code = trim_string(code);
        if (!(code[0] >= 'a' && code[0] <= 'z')) {
            return;
        }
        else code++;
        char name = code[-1];
        code = trim_string(code);
        if(*code != '=') {
            return;
        }
        else code ++;
        code = trim_string(code);
        defined temp = var(code);
        vals[name - 'a'].value = temp.value;
        vals[name - 'a'].type = temp.type;

    }
    #pragma endregion

    void fprint(char* code) {
        if (code == nullptr) {
            return;
        }
        code = trim_string(code);
        defined value = var(code);
        switch (value.type) {
        case deftype::NUM:
            teh::print((int64)value.value);
            break;
        case deftype::CHAR:
            teh::print((char)value.value);
            break;
        case deftype::BOOL:
            teh::print(value.value == 1 ? "true" : "false");
            break;
        default:
            break;
        }
    }
    void line_compiler(char* code) {
        if (code == nullptr)
            return;

        code = trim_string(code);

        if (strcmp(code, "print", false)) {
            fprint(code + 5);
        }
        else if (strcmp(code, "def", false)) {
            fdef(code + 3);
        }
    }
    void inline_tehlang(char* code) {
        if (code == nullptr) {
            return;
        }
        code = trim_string(code);
        char* line_start = code;
        for (int i = 0; code[i] != '\0'; i++) {
            if (code[i] == '\n' || code[i] == ';') {
                code[i] = '\0';
                line_compiler(line_start);
                line_start = code + i + 1;
            }
        }
        if (*line_start != '\0') {
            line_compiler(line_start);
        }
    }
}