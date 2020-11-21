#include "unifont_dyn.h"
#include "libs/io_utils.h"
#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "pc/cliopts.h"
extern char *exe_location;

struct unifont_glyph *unifont_glyph_head = NULL; // This should be replaced if/when this is expanded to multiple font files.
FILE *unifont_font_file = NULL;


/*This function loads a single glyph from the given font file and adds it to a linked list pointed to by unifont_glyph_head*/
int add_glyph(FILE *font_file, u32 codepoint) {
    char *hex_buffer;
    hex_buffer = read_hex_from_file(font_file, codepoint, TRUE); // This function returns an allocated buffer that needs to be freed.
    if (!hex_buffer)
        return -1; 
    if(!add_glyph_to_list_from_hex(&unifont_glyph_head, codepoint, hex_buffer)) { free(hex_buffer); return -1;}
    free(hex_buffer);
    return 1;
}
int add_glyph_using_loaded_font(u32 codepoint){
    return add_glyph(unifont_font_file,codepoint);
}
/* Function returns a string containing (hexidecimal character) bitmap data (1bpp) for a glyph identified by its unicode code point. 
Note: In mode 1 file pointer is reset to the start of file. Do not use this mode to add a list of glyphs use batch_add_glyphs() or mode 0*/
char *read_hex_from_file(FILE *font_file, u32 codepoint, int start_from_begining_of_file) {
    char hex_str_buffer[255]; // Temporary buffer
    if (start_from_begining_of_file)
        fseek(font_file, 0, SEEK_SET); // Seek to begining of the Unifont file

    while (fgets(hex_str_buffer, 255, font_file)) { // continue to read lines until EOF or Error
        if (strtoul(hex_str_buffer, NULL, 16) == codepoint) { // check if this is the correct line.
            return strdup(strchr(hex_str_buffer, ':')+ 1); // Return a copy of the hex string from the file. The +1 starts the string at the first character after the ':'
        }
    };
    if (!*hex_str_buffer)
    {
        read_hex_from_file(font_file, codepoint, TRUE);
    }
    
}
/* Function returns a new glyph from hex string data. Height is assumed to be 16, this may be overwritten in the calling function if needed */
struct unifont_glyph *hex_string_to_unifont_glyph(char *hex_input) {

    struct unifont_glyph *new_glyph = malloc(sizeof(struct unifont_glyph)); // allocate a new unifont glyph

    new_glyph->height = 16; // all unifont characters are 16 pixels in height
    new_glyph->width = (strlen(hex_input) / new_glyph->height * 8  /2); //each hex character encodes half a byte, 1 byte encodes 8 pixels
    new_glyph->bitmap = malloc(strlen(hex_input) / 2); // each hex character is half a byte
    memset(new_glyph->bitmap,0,strlen(hex_input) / 2);
    for (int i = 0; hex_input[i] && hex_input[i]!='\n'; i++) {// this for loop cycles through the input buffer and fills the bitmap with data 

        if (hex_input[i] >= '0' && hex_input[i] <= '9') 
            new_glyph->bitmap[i / 2] += hex_input[i] - '0';
        else if (hex_input[i] >= 'A' && hex_input[i] <= 'F')
            new_glyph->bitmap[i / 2] += hex_input[i] - 'A' + 10;
        else if (hex_input[i] >= 'a' && hex_input[i] <= 'f')
            new_glyph->bitmap[i / 2] += hex_input[i] - 'a' + 10;
        else
            return NULL; //return null if input is not a hex character
        if (i % 2 ==0)
            new_glyph->bitmap[i / 2]=new_glyph->bitmap[i / 2] << 4; //shift over 4 bits if most significant nibble(4 bits)
    }
    new_glyph->visible_width = get_visible_width_from_bitmap(new_glyph->bitmap,strlen(hex_input) / 2);
    new_glyph->loaded_from_png = 0;
    return new_glyph;
}

/*Takes a pointer to a pointer to the head of the linked list of glyphs, the unicode codepoint, 
and a string containing the (hexidecimal character) bitmap data for the glyph and adds the new glyph to the list. 
If the head pointer points to a null value, it creates a new head and sets the pointer to it*/
int add_glyph_to_list_from_hex(struct unifont_glyph **unifont_glyph_head_ptr, u32 codepoint, char *buffer) {
    if (*unifont_glyph_head_ptr == NULL) {
        *unifont_glyph_head_ptr = hex_string_to_unifont_glyph(buffer);
        if(!*unifont_glyph_head_ptr) return 0;
        (*unifont_glyph_head_ptr)->codepoint = codepoint;
        (*unifont_glyph_head_ptr)->next = NULL;
    } else {
        struct unifont_glyph *cursor = (*unifont_glyph_head_ptr);
        while (codepoint != cursor->codepoint) {
            if (cursor->next == NULL) {
                cursor->next = hex_string_to_unifont_glyph(buffer);
                if(!cursor->next) return 0;
                cursor->next->codepoint = codepoint;
                cursor->next->next = NULL;
            }
            cursor = cursor->next;
            
        }
    }
    return 1;
}
/*When deleting a glyph, set the previous glyph node's next pointer to the return value of this function.
i.e. last_glyph_before_deleted_glyph->next = delete_glyph_from_list(last_glyph_before_deleted_glyph->next)
This will ensure that there are no memory leaks from a broken link*/ 
struct unifont_glyph *delete_glyph_from_list(struct unifont_glyph *glyph_to_delete) {
    struct unifont_glyph *next = glyph_to_delete->next;
    free(glyph_to_delete->bitmap);
    free(glyph_to_delete);
    return next;
}
/* Function will add an array of glyphs to linked list. This function is more efficient with a sorted array as the file cursor is not reset.*/
int batch_add_glyphs(FILE *font_file, u32 codepoint_array[], u32 size) {
    char *hex_buffer;
    for (size_t i = 0; i < size; i++) {
        hex_buffer = read_hex_from_file(font_file,codepoint_array[i], FALSE); // This function returns an allocated buffer that needs to be freed.
        if (!hex_buffer)
            return -1;
        if (!add_glyph_to_list_from_hex(&unifont_glyph_head, codepoint_array[i], hex_buffer)){
            free(hex_buffer);
        return -1;}
        free(hex_buffer);
    }
return 1;
}
/* Function returns a the pointer for the bitmap data of a glyph identified by its unicode codepoint.
Returns a null pointer if glyph is not loaded or not found.
NOTE: Glyphs must be loaded by add_glyphs() or batch_add_glyphs before using this function.  */
char *get_bitmap(u32 codepoint) {
    struct unifont_glyph *cursor =
        unifont_glyph_head; // this should be replaced when expanded to multiple fonts.
    while (cursor->codepoint != codepoint) {
        if (cursor->next == NULL) {
            return NULL;
        } else {
            cursor = cursor->next;
        }
    }
    return cursor->bitmap;
}

/* Function returns a the pointer of a glyph node identified by its unicode codepoint.
Returns a null pointer if glyph is not loaded or not found.
NOTE: Glyphs must be loaded by add_glyphs() or batch_add_glyphs before using this function.  */
struct unifont_glyph *get_unifont_glyph(u32 codepoint) {
    struct unifont_glyph *cursor = unifont_glyph_head; // this should be replaced when expanded to multiple fonts.
    while (cursor->codepoint != codepoint) {
        if (cursor->next == NULL) {
            add_glyph_using_loaded_font(codepoint);
        } else {
            cursor = cursor->next;
        }
    }
    return cursor;
}

/*This function initializes and preloads glyphs listed in unifontCodepoints.hex.
It does no error checking currently for missing files and will most likely crash if these files are missing/corrupted.
Path/filename is hard coded but should be updated to load different fonts in future. (maybe) */
void preload_codepoints() {
    char unifont_path[SYS_MAX_PATH];
    char unifont_codepoint_path[SYS_MAX_PATH];

    strcpy(unifont_path, exe_location);
    strcpy(unifont_codepoint_path, exe_location);

#ifdef WIN32
    *strrchr(unifont_codepoint_path, '\\') = 0;
    *strrchr(unifont_path, '\\') = 0;

    strcat(unifont_path, "\\res\\gfx\\textures\\unicode\\unifont.hex");
    strcat(unifont_codepoint_path, "\\res\\gfx\\textures\\unicode\\unifontCodepoints.hex");
#else
    *strrchr(unifont_codepoint_path, '/') = 0;
    *strrchr(unifont_path, '/') = 0;
    strcat(unifont_path, "/res/gfx/textures/unicode/unifont.hex");
    strcat(unifont_codepoint_path, "/res/gfx/textures/unicode/unifontCodepoints.hex");

#endif


    unifont_font_file = fopen(unifont_path, "r");
    FILE *unifont_codepoint_file = fopen(unifont_codepoint_path, "r");
    char buffer[255];
    u32 count = 0;
    while (fgets(buffer, sizeof buffer, unifont_codepoint_file)) {
        count++;
    }
    fseek(unifont_codepoint_file,0,SEEK_SET);
    u32 *codepoints_to_load = malloc(sizeof(u32) * count);
    for (u32 i = 0; i < count; i++) {
        fgets(buffer, sizeof buffer, unifont_codepoint_file);
        codepoints_to_load[i] = strtol(buffer, NULL, 10);
    }

    batch_add_glyphs(unifont_font_file, codepoints_to_load, count);
    free(codepoints_to_load);
}
/*bitmap is a 1bpp char* buffer.
 This returns the right most visible pixel. It ignores any blank space on the left of the bitmap*/
int get_visible_width_from_bitmap(char *bitmap, int size_of_bitmap) {

    int visible_width = 0;
    for (int i = 0; i < size_of_bitmap; i++) {
        for (int j = 0; j < 8; j++)
            if (bitmap[i] & 1 << j)
                visible_width =  max(8-j,visible_width);
    }
    return visible_width;
}
/*Gets the visible width from a loaded main.XXXX.png RGBA buffer. Assumes 16x8x4 buffer*/
int get_visible_width_from_main_png(u8 *RGBAbuffer) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 16; j++) {
            if (RGBAbuffer[(i * 16 * 4) + (4 * j) + 3]) {
                return 8 - i;
            }
        }
    }
}