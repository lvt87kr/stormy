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

#include "json.h"

#define BUF_SIZE 1024

typedef struct _stormy_data {
    char *name;
    uint8_t three;
    uint8_t five;
    uint8_t *array;
} StormyData;

int main(void) {
    FILE *file;
    
    JsonNode *root, *node;
    
    long file_size;
    char buffer[BUF_SIZE];
    
    if ((file = fopen("../res/stormy.json", "rb")) == NULL) {
        fprintf(stderr, "stormy: fopen() error\n");
        return EXIT_FAILURE;
    }
    
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    
    if (fread(buffer, sizeof(char), BUF_SIZE, file) != file_size) {
        fprintf(stderr, "stormy: fread() error\n");
        return EXIT_FAILURE;
    }
    
    buffer[file_size] = '\0';
    
    root = json_decode(buffer);
    
    if (root == NULL) {
        fprintf(stderr, "stormy: json_decode() error\n");
        return EXIT_FAILURE;
    }
    
    json_foreach(node, root)
        printf("%s\n", node->key);
    
    return EXIT_SUCCESS;
}