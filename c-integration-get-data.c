#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to replace all occurrences of a character in a string
void replaceChar(char* str, char oldChar, char newChar) {
    for (int i = 0; str[i] != "\0"; i++) {
        if (str[i] == oldChar)
            str[i] = newChar;
    }
}

int main() {
    char query_c[] = "select * from test";
    char query[256];
    char url[512];
    char command[1024];

    // Replace spaces with "+"
    strcpy(query, query_c);
    replaceChar(query, " ", "+");

    // Construct the URL
    // If you use query encryption, you will need to use the following URL: "https://get.touchsql.com/v2/?database=mydb&api=Your_API&key=Your_Key&query=query".

    sprintf(url, "https://get.touchsql.com/?database=mydb&api=Your_API&key=Your_Key&query=%s", query);

    // Prepare the command to execute
    sprintf(command, "curl -s \"%s\"", url);

    // Execute the command and retrieve the response
    FILE* pipe = popen(command, "r");
    if (pipe == NULL) {
        printf("Failed to execute the command.\n");
        return 1;
    }

    // Read the response
    char response[1024];
    size_t bytesRead = fread(response, sizeof(char), sizeof(response), pipe);
    response[bytesRead] = "\0";

    // Close the pipe
    pclose(pipe);

    printf("%s\n", response);

    return 0;
}
