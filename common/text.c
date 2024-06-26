#include "text.h"

static u64 s_textLanguageCode = 0;

#ifdef __SWITCH__
static int s_textLang = SetLanguage_KO;
#else
static int s_textLang = 7;
#endif

Result textInit(void) {
    #ifdef __SWITCH__
    SetLanguage Language=SetLanguage_KO;

    s_textLang = Language;

    Result rc = setInitialize();
    if (R_SUCCEEDED(rc)) rc = setGetSystemLanguage(&s_textLanguageCode);
    if (R_SUCCEEDED(rc)) rc = setMakeLanguage(s_textLanguageCode, &Language);
    //if (R_SUCCEEDED(rc) && Language < 17) s_textLang = Language;//TODO: Re-enable this once language.c supports all used languages.
    setExit();
    if (R_FAILED(rc)) return rc;
    #else
    s_textLang = 7;
    #endif

    return 0;
}

int textGetLang(void) {
    return s_textLang;
}

const char* textGetString(StrId id) {
    const char* str = g_strings[id][s_textLang];
    #ifdef __SWITCH__
    if (!str) str = g_strings[id][SetLanguage_KO];
    #else                              
    if (!str) str = g_strings[id][7];
    #endif
    return str;
}

u64 textGetLanguageCode(void) {
    return s_textLanguageCode;
}
