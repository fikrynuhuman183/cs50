#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string cipher(string s, string key);

int main(int argc, string argv[])
{
    string key = argv[1];
    //check for validity of argv
    //check whether only one argv is used
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //check whether key contains only alphabets
    for (int i = 0; i < strlen(key); i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    //check whther key contains any duplicates
    for (int x = 0; x < strlen(key); x++)
    {
        for (int y = x + 1; y < strlen(key); y++)
        {
            if(key[x] == key[y])
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (strlen(key) == 26)
    {
        string plain_text = get_string("plain text: ");
        string h = cipher(plain_text, key);
        printf("ciphertext: %s\n", h);
    }
    return 0;
}
//create function cipher
string cipher(string s, string k)
{
    long counter = strlen(s);
    for (int i = 0; i < counter; i++)
    {
        if (isalpha(s[i]) != 0)
        {
            if (islower(s[i]) != 0)
            {
                s[i] = tolower(k[s[i] - 97]);
            }
            if (isupper(s[i]) != 0)
            {
                s[i] = toupper(k[s[i] - 65]);
            }
        }
    }

    return s;
}