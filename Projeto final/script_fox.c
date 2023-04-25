#include "compress.h"


//modificar essa função depois
//localiza o arquivo com base no nome, caso o arquivo esteja dentro da mesma pasta que o codigo
void* get_archive_name_and_open(FILE **archive)
{
    char archive_name[106], letter;
    size_t i, j, cont = 0;
    printf("\nEnter a file name with file type with a maximum of 100 characters\nExemple: archive.txt\n> ");
    while(*archive == NULL)
    {
        i = 0;
        *archive = NULL;
        if(archive_name == NULL)
        {
            printf("\nError allocating memory for archive name\n\n");
            exit(1);
        }
        scanf(" %c", &letter);
        while(letter != '\n' && i < 100)
        {
            archive_name[i++] = letter;
            scanf("%c", &letter);
        }
        //caso estoure o limite de 100 caracteres nos mandamos uma mensagem de erro e zeramos a entrada para que seja inserida uma nova
        if(i >= 100)
        {
            printf("\nMaximum number of characters reached\nPlease enter an archive name with a maximum of 100 characters\n> ");
            while(scanf("%c", &letter) != EOF && letter != '\n');
        }
        //caso a entrada não estoure o limite prosseguimos
        else
        {
            archive_name[i] = '\0';
            *archive = fopen(archive_name, "rb");
            //caso o arquivo nao seja encontrado retornamos um erro
            if(*archive == NULL)
            {
                printf("\nUnable to locate archive: %s\nPlease enter the name of a valid archive\n> ", archive_name);
            }
        }
    }

    //retornando o nome do arquivo para usarmos na hora que formos gravar os dados da compactacao
    return archive_name;
}


int main()
{
    //APRESENTACAO DO PROGRAMA E OPCOES
    printf(" ==================================================================================================================================================\n");
    printf("| __          __         _                                       _                _____                 _           _       ______                 |\n");
    printf("| \\ \\        / /        | |                                     | |              / ____|               (_)         | |     |  ____|                |\n");
    printf("|  \\ \\  /\\  / /    ___  | |   ___    ___    _ __ ___     ___    | |_    ___     | (___     ___   _ __   _   _ __   | |_    | |__      ___   __  __ |\n");
    printf("|   \\ \\/  \\/ /    / _ \\ | |  / __|  / _ \\  | '_ ` _ \\   / _ \\   | __|  / _ \\     \\___ \\   / __| | '__| | | | '_ \\  | __|   |  __|    / _ \\  \\ \\/ / |\n");
    printf("|    \\  /\\  /    |  __/ | | | (__  | (_) | | | | | | | |  __/   | |_  | (_) |    ____) | | (__  | |    | | | |_) | | |_    | |      | (_) |  >  <  |\n");
    printf("|     \\/  \\/      \\___| |_|  \\___|  \\___/  |_| |_| |_|  \\___|    \\__|  \\___/    |_____/   \\___| |_|    |_| | .__/   \\__|   |_|       \\___/  /_/\\_\\ |\n");
    printf("|                                                                                                          | |                                     |\n");
    printf("|                                                                                                          |_|                                     |\n");
    printf(" ==================================================================================================================================================\n");
    printf("Create by: Wolfshohle\n");
    int opc = 0;
    sleep(1);
    while(opc != 3)
    {
        printf(" -----------------------------\n| SELECT ANY OF THE OPTIONS:  |\n -----------------------------\n| 1. compress                 |\n| 2. unzip                    |\n| 3. exit                     |\n -----------------------------\n");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            FILE *archive = NULL;
            void *archive_name;
            //pegando o arquivo e o nome dele
            archive_name = get_archive_name_and_open(&archive);
            printf("\nstarting file compression\n");
            compress_archive(archive_name);
            break;
        case 2:
            unzip();
            break;
        case 3:
            printf("Thanks for using the fox script!!\n");
            break;
        default:
            printf("Invalid option!\n");
            break;
        }
    }

    return 0;
}