
/**
* File compressor and decompressor project created for the data structure discipline.
* Federal University of Alagoas - Campus A.C.Simões
*
* @author  MATHEUS ALMEIDA SOUZA
* @version 1.0
* @since   04-12-2023 
*/

#include "zip.h"
#include "unzip.h"

//pega o nome do arquivo
/**
* Pega o nome do arquivo
* a funcao get_name() recebe o nome do arquivo a ser compactado ou descompactado. Ela ainda verifica se o tamanho maximo do nome digitado,
* se o arquivo exite no diretorio do programa e se ele e .huff.
*
* @param     archive_name     Um ponteiro para o vetor de nome do arquivo
* @param      opc_check       Se esta compactando ou descompactando
*/
void get_name(char *archive_name, int opc_check)
{
    int i = 0, archive_name_size;
    char a;
    FILE *archive_test = NULL;
    //se for compactar
    if(opc_check == 1)
    {
        printf("\nEnter the name and type of the file to be compressed with a maximum of 100 characters.\nexemple: archive.type\n>");
        while(archive_test == NULL)
        {
            i = 0;
            scanf(" %c", &a);
            while(a != '\n')
            {
                archive_name[i++] = a;
                if(i == 100)
                {
                    printf("\n\033[31mPlease enter file name up to 100 characters\n\033[0m>");
                    break;
                }
                scanf("%c", &a);
            }
            if(i == 100)
            {
                //limpando a entrada
                while(a != '\n')
                {
                    scanf("%c", &a);
                }
            }
            else
            {
                archive_name[i] = '\0';
                archive_test = fopen(archive_name, "rb");
                if(archive_test == NULL)
                {
                    printf("\n\033[31mFile not found, please enter a valid file\n\033[0m>");
                } 
            }
        }
        fclose(archive_test);
    }
    //se for descompactar
    else
    {
        printf("\nenter the name of the huffman type file to be unzipped with a maximum of 106 characters\nexemple: archive.type.huff\n>");
        while(archive_test == NULL)
        {
            i = 0;
            scanf(" %c", &a);
            while(a != '\n')
            {
                archive_name[i++] = a;
                if(i == 100)
                {
                    printf("\n\033[31mPlease enter file name up to 100 characters\n\033[0m>");
                    break;
                }
                scanf("%c", &a);
            }
            if(i == 100)
            {
                //limpando a entrada
                while(a != '\n')
                {
                    scanf("%c", &a);
                }
            }
            else
            {
                archive_name[i] = '\0';
                archive_name_size = strlen(archive_name);
                if(archive_name[archive_name_size - 1] != 'f' || archive_name[archive_name_size - 2] != 'f' || archive_name[archive_name_size - 3] != 'u' || archive_name[archive_name_size - 4] != 'h' || archive_name[archive_name_size - 5] != '.')
                {
                    printf("\n\033[31mPlease insert only .huff files\n\033[0m>");
                }
                else
                {
                    archive_test = fopen(archive_name, "rb");
                    if(archive_test == NULL)
                    {
                        printf("\n\033[31mFile not found, please enter a valid file\n\033[0m>");
                    }
                }
            }
        }
        fclose(archive_test);
    }

    return;
}


int main()
{
    //APRESENTACAO DO PROGRAMA E OPCOES
    printf("\033[33m");
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
    printf("\033[0m");
    printf("Create by: Wolfshohle, joaopedrosss, carlosvscs\n");
    int opc = 0;
    sleep(1);
    while(opc != 3)
    {
        printf("\033[34m -----------------------------\n\033[34m|\033[0m SELECT ANY OF THE OPTIONS:  \033[34m|\n -----------------------------\n\033[34m|\033[0m 1. compress                 \033[34m|\n|\033[0m 2. unzip                    \033[34m|\n|\033[0m 3. exit                     \033[34m|\n -----------------------------\n\033[0m");
        scanf("%d", &opc);
        char archive_name[106];
        switch (opc)
        {
        case 1:
            get_name(archive_name, 1);
            printf("\n\033[32mstarting file compression\033[0m\n");
            compress(archive_name);
            break;
        case 2:
            get_name(archive_name, 2);
            printf("\n\033[32mstarting to unzip\033[0m\n");
            descompressed(archive_name);
            break;
        case 3:
            printf("Thanks for using the script fox!!\n");
            break;
        default:
            printf("033[31mInvalid option!033[0m\n");
            break;
        }
    }

    return 0;
}
