#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "txtconv.h"

struct Character charmap[181] = {
    {"0", {0x0, NULL}}, {"{65296}", {0x0, NULL}}, {"1", {0x1, NULL}}, {"{65297}", {0x1, NULL}}, {"2", {0x2, NULL}}, {"{65298}", {0x2, NULL}}, {"3", {0x3, NULL}}, {"{65299}", {0x3, NULL}}, {"4", {0x4, NULL}}, 
    {"{65300}", {0x4, NULL}}, {"5", {0x5, NULL}}, {"{65301}", {0x5, NULL}}, {"6", {0x6, NULL}}, {"{65302}", {0x6, NULL}}, {"7", {0x7, NULL}}, {"{65303}", {0x7, NULL}}, {"8", {0x8, NULL}}, {"{65304}", {0x8, NULL}}, 
    {"9", {0x9, NULL}}, {"{65305}", {0x9, NULL}}, {"A", {0xa, NULL}}, {"{65313}", {0xa, NULL}}, {"B", {0xb, NULL}}, {"{65314}", {0xb, NULL}}, {"C", {0xc, NULL}}, {"{65315}", {0xc, NULL}}, {"D", {0xd, NULL}}, 
    {"{65316}", {0xd, NULL}}, {"E", {0xe, NULL}}, {"{65317}", {0xe, NULL}}, {"F", {0xf, NULL}}, {"{65318}", {0xf, NULL}}, {"G", {0x10, NULL}}, {"{65319}", {0x10, NULL}}, {"H", {0x11, NULL}}, {"{65320}", {0x11, NULL}}, 
    {"I", {0x12, NULL}}, {"{65321}", {0x12, NULL}}, {"J", {0x13, NULL}}, {"{65322}", {0x13, NULL}}, {"K", {0x14, NULL}}, {"{65323}", {0x14, NULL}}, {"L", {0x15, NULL}}, {"{65324}", {0x15, NULL}}, {"M", {0x16, NULL}}, 
    {"{65325}", {0x16, NULL}}, {"N", {0x17, NULL}}, {"{65326}", {0x17, NULL}}, {"O", {0x18, NULL}}, {"{65327}", {0x18, NULL}}, {"P", {0x19, NULL}}, {"{65328}", {0x19, NULL}}, {"Q", {0x1a, NULL}}, {"{65329}", {0x1a, NULL}}, 
    {"R", {0x1b, NULL}}, {"{65330}", {0x1b, NULL}}, {"S", {0x1c, NULL}}, {"{65331}", {0x1c, NULL}}, {"T", {0x1d, NULL}}, {"{65332}", {0x1d, NULL}}, {"U", {0x1e, NULL}}, {"{65333}", {0x1e, NULL}}, {"V", {0x1f, NULL}}, 
    {"{65334}", {0x1f, NULL}}, {"W", {0x20, NULL}}, {"{65335}", {0x20, NULL}}, {"X", {0x21, NULL}}, {"{65336}", {0x21, NULL}}, {"Y", {0x22, NULL}}, {"{65337}", {0x22, NULL}}, {"Z", {0x23, NULL}}, {"{65338}", {0x23, NULL}}, 
    {"a", {0x24, NULL}}, {"{65345}", {0x24, NULL}}, {"b", {0x25, NULL}}, {"{65346}", {0x25, NULL}}, {"c", {0x26, NULL}}, {"{65347}", {0x26, NULL}}, {"d", {0x27, NULL}}, {"{65348}", {0x27, NULL}}, {"e", {0x28, NULL}}, 
    {"{65349}", {0x28, NULL}}, {"f", {0x29, NULL}}, {"{65350}", {0x29, NULL}}, {"g", {0x2a, NULL}}, {"{65351}", {0x2a, NULL}}, {"h", {0x2b, NULL}}, {"{65352}", {0x2b, NULL}}, {"i", {0x2c, NULL}}, {"{65353}", {0x2c, NULL}}, 
    {"j", {0x2d, NULL}}, {"{65354}", {0x2d, NULL}}, {"k", {0x2e, NULL}}, {"{65355}", {0x2e, NULL}}, {"l", {0x2f, NULL}}, {"{65356}", {0x2f, NULL}}, {"m", {0x30, NULL}}, {"{65357}", {0x30, NULL}}, {"n", {0x31, NULL}}, 
    {"{65358}", {0x31, NULL}}, {"o", {0x32, NULL}}, {"{65359}", {0x32, NULL}}, {"p", {0x33, NULL}}, {"{65360}", {0x33, NULL}}, {"q", {0x34, NULL}}, {"{65361}", {0x34, NULL}}, {"r", {0x35, NULL}}, {"{65362}", {0x35, NULL}}, 
    {"s", {0x36, NULL}}, {"{65363}", {0x36, NULL}}, {"t", {0x37, NULL}}, {"{65364}", {0x37, NULL}}, {"u", {0x38, NULL}}, {"{65365}", {0x38, NULL}}, {"v", {0x39, NULL}}, {"{65366}", {0x39, NULL}}, {"w", {0x3a, NULL}}, 
    {"{65367}", {0x3a, NULL}}, {"x", {0x3b, NULL}}, {"{65368}", {0x3b, NULL}}, {"y", {0x3c, NULL}}, {"{65369}", {0x3c, NULL}}, {"z", {0x3d, NULL}}, {"{65370}", {0x3d, NULL}}, {"'", {0x3e, NULL}}, {"{65287}", {0x3e, NULL}}, 
    {".", {0x3f, NULL}}, {"{65294}", {0x3f, NULL}}, {",", {0x6f, NULL}}, {"{65292}", {0x6f, NULL}}, {"-", {0x9f, NULL}}, {"{65293}", {0x9f, NULL}}, {"(", {0xe1, NULL}}, {"{65288}", {0xe1, NULL}}, {")(", {0xe2, NULL}}, 
    {"）（", {0xe2, NULL}}, {")", {0xe3, NULL}}, {"{65289}", {0xe3, NULL}}, {"+", {0xe4, NULL}}, {"{65291}", {0xe4, NULL}}, {"&", {0xe5, NULL}}, {"{65286}", {0xe5, NULL}}, {":", {0xe6, NULL}}, {"{65306}", {0xe6, NULL}}, 
    {"!", {0xf2, NULL}}, {"{65281}", {0xf2, NULL}}, {"%", {0xf3, NULL}}, {"{65285}", {0xf3, NULL}}, {"?", {0xf4, NULL}}, {"{65311}", {0xf4, NULL}}, {"~", {0xf7, NULL}}, {"{65374}", {0xf7, NULL}}, {" ", {0x9e, NULL}}, 
    {"{12288}", {0x9e, NULL}}, {"\n", {0xfe, NULL}}, {"{12443}", {0xf0, NULL}}, {"{12444}", {0xf1, NULL}}, {"{12302}", {0xf5, NULL}}, {"{12303}", {0xf6, NULL}}, {"{08230}", {0xf8, NULL}}, {"{08596}", {0xe4, NULL}}, {"$", {0xf9, NULL}}, 
    {"{09733}", {0xfa, NULL}}, {"{00215}", {0xfb, NULL}}, {"{12539}", {0xfc, NULL}}, {"{09734}", {0xfd, NULL}}, {"^", {0x50, NULL}}, {"|", {0x51, NULL}}, {"<", {0x52, NULL}}, {">", {0x53, NULL}}, {"[%]", {0xe0, NULL}}, 
    {"[A]", {0x54, NULL}}, {"[B]", {0x55, NULL}}, {"[C]", {0x56, NULL}}, {"[Z]", {0x57, NULL}}, {"[R]", {0x58, NULL}}, {"/", {0xd0, NULL}}, {"the", {0xd1, NULL}}, {"you", {0xd2, NULL}}, {"{09786}", {0x40, 0x41}}, 
    {"{", {0x7b, NULL}}
};

struct Character getCharacter(char *ch){
    struct Character tmp = {NULL, {NULL, NULL}};
    for(s32 cmid = 0; cmid < sizeof(charmap) / sizeof(struct Character); cmid++){
        if(charmap[cmid].txt != NULL){
            if(strncmp(charmap[cmid].txt, ch, strlen(charmap[cmid].txt)) == 0) {
                tmp = charmap[cmid];
                break;
            }
        }
    }
    return tmp;
}

u8 *getTranslatedText(char  *txt){

    txt = (txt == NULL ? "" : txt);

    s32 cid = 0;
    s32 shiftArr = 0;
    s32 strSize = strlen(txt);

    u8 *tmp = malloc((strSize + 1) * sizeof(u8));
    u8 icon = FALSE;

    char tmpIcon[3];
    char tmpSpecialChar[7];

    memset(tmpIcon, 0, sizeof(tmpIcon));
    memset(tmpSpecialChar, 0, sizeof(tmpSpecialChar));

    for(cid = 0; cid < strSize; cid++){
    char ch = txt[cid];
    
        if(ch == '['){
            tmpIcon[0] = ch;
            tmpIcon[1] = txt[cid + 1];
            tmpIcon[2] = txt[cid + 2];
            struct Character ctm = getCharacter(tmpIcon);
            if(ctm.txt != NULL){
                shiftArr += 2;
                cid += 2;
                for(int cl = 0; cl < 2; cl++){
                    if(ctm.value[cl] != NULL){
                        tmp[cid - shiftArr + cl] = ctm.value[cl];
                        shiftArr-=cl;
                    }
                }
                memset(tmpIcon, 0, sizeof(tmpIcon));
            }
        } else if(ch == ')'){

            struct Character ctm;

            // case: ')' at end of string
            if (cid == (strSize - 1)) {
                ctm = getCharacter(")");
                if(ctm.txt != NULL){
                    tmp[cid - shiftArr] = ctm.value[0];
                }
                break; // avoids out of bounds read/write
            }

            char tmpIcon[2];
            tmpIcon[0] = ch;
            tmpIcon[1] = txt[cid + 1];

            // case: ')(' contained in string
            if (tmpIcon[1] == '(') {
                ctm = getCharacter(")(");
                shiftArr += 1;
                cid += 1;
                for(int cl = 0; cl < 2; cl++){
                    if(ctm.value[cl] != NULL){
                        tmp[cid - shiftArr + cl] = ctm.value[cl];
                        shiftArr-=cl;
                    }
                }
            // case: ')' contained in string
            } else {
                ctm = getCharacter(")");
                if(ctm.txt != NULL){
                    tmp[cid - shiftArr] = ctm.value[0];
                }
            }
            memset(tmpIcon, 0, sizeof(tmpIcon));

        } else if(ch == '{'){
            tmpSpecialChar[0] = ch;
            tmpSpecialChar[1] = txt[cid + 1];
            tmpSpecialChar[2] = txt[cid + 2];
            tmpSpecialChar[3] = txt[cid + 3];
            tmpSpecialChar[4] = txt[cid + 4];
            tmpSpecialChar[5] = txt[cid + 5];
            tmpSpecialChar[6] = txt[cid + 6];

            struct Character ctm = getCharacter(tmpSpecialChar);
            if (ctm.txt == "{") {
                for (int cl = 0; cl < 2; cl++) {
                    if (ctm.value[cl] != NULL) {
                        tmp[cid - shiftArr + cl] = ctm.value[cl];
                        shiftArr -= cl;
                    }
                }
            }

            else {
                if (ctm.txt != NULL) {
                    shiftArr += 5;
                    cid += 5;
                    for (int cl = 0; cl < 2; cl++) {
                        if (ctm.value[cl] != NULL) {
                            tmp[cid - shiftArr + cl] = ctm.value[cl];
                            shiftArr -= cl;
                        }
                    }
                }
            }
            memset(tmpSpecialChar, 0, sizeof(tmpSpecialChar));
        } else {
            char findTxt[1] = {ch};

            struct Character ctm = getCharacter(findTxt);
            if(ctm.txt != NULL){
                tmp[cid - shiftArr] = ctm.value[0];
            }else{
                tmp[cid - shiftArr] = 0x9E;
            }
        }
    }

    tmp = realloc(tmp, (strSize - shiftArr + 1) * sizeof(u8));
    tmp[strSize - shiftArr] = 0xFF;

    return tmp;
}
