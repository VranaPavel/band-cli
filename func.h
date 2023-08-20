void replace_char(char *string, char torep, char new)
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == torep)
        {
            string[i] = new;
        }
    }
}