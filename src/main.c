/*
    Copyright (c) 2021 lvt87kr

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"

#define BUF_SIZE 1024

typedef struct _stormy_data {
    char *name;
    uint8_t three;
    uint8_t five;
    uint8_t *array;
} StormyData;

static StormyData stormy_data;

void load_json_file() {
    FILE *file;
    
    JsonNode *root, *current;
    JsonNode *object, *array;
    
    int array_index, input_size;
    
    char *input;
    
    input = (char *) calloc(BUF_SIZE, sizeof(char));
    
    file = fopen("../res/input.json", "rb");

    fseek(file, 0, SEEK_END);
    input_size = ftell(file);
    rewind(file);
    
    fread(input, sizeof(char), BUF_SIZE, file);
    input[input_size] = '\0';
    
    fclose(file);
    
    root = json_decode(input);    
    current = json_first_child(root);
    
    stormy_data.name = (char *) calloc(BUF_SIZE, sizeof(char));
    
    strcpy(stormy_data.name, current->string_);
    
    if (current != NULL)
        current = current->next;
    
    json_foreach(object, current)
        if (strcmp(object->key, "three") == 0)
            stormy_data.three = object->number_;
        else if (strcmp(object->key, "five") == 0)
            stormy_data.five = object->number_;
    
    if (current != NULL)
        current = current->next;
    
    stormy_data.array = (uint8_t *) calloc(9, sizeof(uint8_t));
    array_index = 0;
    
    json_foreach(array, current)
        stormy_data.array[array_index++] = array->number_;
}

void save_json_file() {
    FILE *file;
    
    JsonNode *root, *current;
    JsonNode *object, *array;
    
    char *output;
    
    root = json_mkobject();
    
    json_append_member(root, "name", json_mkstring(stormy_data.name));
    json_append_member(root, "object", json_mkobject());
    json_append_member(root, "array", json_mkarray());
    
    json_foreach(current, root) {
        if (strcmp(current->key, "object") == 0) {
            json_append_member(current, "three", json_mknumber(stormy_data.three));
            json_append_member(current, "five", json_mknumber(stormy_data.five));
        } else if (strcmp(current->key, "array") == 0) {
            for (int i = 0; i < 9; i++)
                json_append_element(current, json_mknumber(stormy_data.array[i]));
        }
    }
    
    output = json_encode(root);
    
    file = fopen("../res/output.json", "wb");
    fwrite(output, sizeof(char), strlen(output), file);
    
    fclose(file);
}

int main(void) {
    load_json_file();
    save_json_file();
    
    return EXIT_SUCCESS;
}