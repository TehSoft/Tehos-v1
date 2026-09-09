#ifndef TEHLANG_HH
#define TEHLANG_HH

#include <tehos.hh>
#include <tehio.hh>

namespace teh::lang {
    enum class deftype : uint8 {
        NUM,
        CHAR,
        BOOL
    };
    struct defined {
        int64 value = 0;
        deftype type;
        defined(int64 v = 0, deftype t = deftype::NUM) : value(v), type(t) {}
    };
    void inline_tehlang(char* code);
    void line_compiler(char* code);
    void fprint(char* code);
    void fdef(char* code);
    defined var(char* code);
}

#endif // TEHLANG_HH