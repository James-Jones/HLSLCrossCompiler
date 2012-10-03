#ifndef LANGUAGES_H
#define LANGUAGES_H

typedef enum
{
    LANG_DEFAULT,// Depends on the HLSL shader model.
    LANG_ES_100,
    LANG_ES_300,
    LANG_120,
    LANG_130,
    LANG_140,
    LANG_150,
    LANG_330,
    LANG_400,
    LANG_410,
    LANG_420,
    LANG_430
} GLLang;

#endif
