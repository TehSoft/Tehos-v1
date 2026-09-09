#include "tehos.hh"

bool strcmp(const char* a, const char* b, bool size_eq) {
    if (a == nullptr || b == nullptr) return a == b;
    if (*a == '\0' || *b == '\0') return false;

    uint32 i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    if (size_eq) {
        return a[i] == b[i];
    }
    return (b[i] == '\0');
}

char* trim_string(char* str) {
    if (str == nullptr) {
        return nullptr;
    }

    while (*str == ' ') {
        str++;
    }

    int size = 0;
    while (str[size] != '\0') {
        size++;
    }

    while (size > 0 && str[size - 1] == ' ') {
        str[size - 1] = '\0';
        size--;
    }

    return str;
}