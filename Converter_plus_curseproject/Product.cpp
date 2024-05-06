#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdint.h>

int argv_check(char* argv)
{
    int j = 0, i = 0;
    while (true)
    {
        if (argv[i] == '.')
        {
            j += 1;
            if (argv[i + 1] == 't')
            {
                if (argv[i + 2] == 'x')
                {
                    if (argv[i + 3] == 't')
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        if (argv[i] == '\0' && j == 0)
        {
            return 0;
        }
        i++;
    }
}

char converter(FILE* f)
{
    uint8_t sym1, sym = fgetc(f);
    if ((sym & 224) == 192)
    {
        if ((sym == 208) || (sym == 209))
        {
            sym1 = fgetc(f);
            if ((sym == 208 && sym1 == 129) || (sym == 209 && sym1 == 145))
            {
                sym1 += 39;
                return sym1;
            }
            else if (sym1 >= 128 && sym1 <= 143)
            {
                sym1 += 112;
                return sym1;
            }
            else if (sym1 >= 144 && sym1 <= 191)
            {
                sym1 += 48;
                return sym1;
            }
        }
    }
    return sym;
}

int main(int argc, char* argv[])
{
    setlocale(LC_CTYPE, "");
    int STR_LEN = atoi(argv[1]);
    if (STR_LEN <= 1)
    {
        printf("\nПроверьте значение введенной максимальной длины.");
        printf("\nНАПОМИНАНИЕ:");
        printf("\nЗначение максимальной длины строки не может быть мешьше .\n");
        if (int exists = argv_check(argv[2]) == 0)
        {
            printf("\nПроверьте введенное название исходного файла");
            printf("\nНАПОМИНАНИЕ:");
            printf("\nВведенное значение должно сожержать формат текстового документа. НАПРИМЕР: 123.txt\n");
        }
        if (int exists = argv_check(argv[3]) == 0)
        {
            printf("\nПроверьте введенное название выходного файла");
            printf("\nНАПОМИНАНИЕ:");
            printf("\nВведенное значение должно сожержать формат текстового документа. НАПРИМЕР: 321.txt\n");
        }
        return 0;
    }
    else
    {
        if (int exists = argv_check(argv[2]) == 0)
        {
            printf("\nПроверьте введенное название исходного файла");
            printf("\nНАПОМИНАНИЕ:");
            printf("\nВведенное значение должно сожержать формат текстового документа. НАПРИМЕР: 123.txt\n");
            if (int exists = argv_check(argv[3]) == 0)
            {
                printf("\nПроверьте введенное название выходного файла");
                printf("\nНАПОМИНАНИЕ:");
                printf("\nВведенное значение должно сожержать формат текстового документа. НАПРИМЕР: 321.txt\n");
            }
            return 0;
        }
        if (int exists = argv_check(argv[3]) == 0)
        {
            printf("\nПроверьте введенное название выходного файла");
            printf("\nНАПОМИНАНИЕ:");
            printf("\nВведенное значение должно сожержать формат текстового документа. НАПРИМЕР: 321.txt\n");
            return 0;
        }
    }
	FILE* file = fopen(argv[2], "rb");
    FILE* out_file = fopen(argv[3], "wb");
	uint8_t c;
    int counter = 0;
    while (true)
    {
        c = converter(file);
        counter++;
        if (!feof(file))
        {
            if (c == '\n')
            {
                fprintf(out_file,"\n\n");
                counter = 0;
                continue;
            }
            if (c == ' ' && counter == 1)
            {
                counter = 0;
                continue;
            }
            fprintf(out_file,"%c", c);
            if (counter == STR_LEN - 1)
            {
                long current_pos = ftell(file);
                int pos1 = fgetc(file);
                int pos2 = fgetc(file);
                if (!feof(file))
                {
                    if (pos1 > ' ' && pos2 > ' ')
                    {
                        if (c > ' ')
                        {
                            fprintf(out_file,"-");
                            counter++;
                        }
                        else if (c == ' ')
                        {
                            fprintf(out_file," ");
                            counter++;
                        }
                    }
                }
                fseek(file, current_pos, SEEK_SET);
            }
            if (counter == STR_LEN)
            {
                fprintf(out_file, "\n");
                counter = 0;
            }
        }
        
        else
        {
            break;
        }
    }
    fclose(file);
    printf("\n----END----\n");
    return 0;
}
