#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>


void print_line_slowly(const char* line, unsigned int delay);
void print_line_dialog(const char* line, unsigned int delay);
int spawn_enemy = 0;
bool loot;
int rtn_life = 0;
int count;
int inicial;

typedef struct
{
    int savegame;
    char name[15];
    int attribute[4];
    // level; attribute[3]
    int inventory[2];
    char local[3];
    int boss[2];
  //  int gold; inventory[0]
  //  int keys; inventory[1]
} PLAYER;

PLAYER p1;

typedef struct
{
    int vida;
    int forca;
    int sorte;
    int inventory;
} MONSTER;

typedef struct
{
    int vida;
    int forca;
    int sorte;
} BOSS;
BOSS b1 = {2700, 18, 2};
BOSS b2 = {2500, 14, 4};

void fight_bed()
{  
    if (p1.boss[0] == 1)
    {
        printf("\nVoce ja matou Bed of Chaos.\n");
        printf("\nAperte ENTER para continuar.\n");
        getchar();
        system("clear");
        bed_of_chaos();
    }
    //personagem nivel 30
    int j;
    int k;
    p1.local[0] = '0';
    p1.local[1] = '5';
    p1.local[2] = 'L';
    count = 0;
    int life_base = p1.attribute[0];

    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("bed_fase1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);

    printf("O combate vai comecar, entao se prepare!\n");
    printf("\nsua vida [%d]\n", p1.attribute[0]);
    printf("vida do BOSS [%d]\n", b1.vida);//2700 de vida = 10 rounds aproximados
    printf("\n\n|Aperte ENTER para atacar:| ");
    getchar();
    system("clear");

    while((p1.attribute[0] > 0) && (b1.vida > 1300))
    {
        j = rand()%6+p1.attribute[2];
        int p_dano = (p1.attribute[1] * j)/2;
        printf("\nseu ataque deu [%d] de dano\n\n", (p1.attribute[1] * j)/2);
        b1.vida -= p_dano;
        k = rand()%6+b1.sorte;
        int b1_dano = (b1.forca * k)/5;
        printf("o ataque dele deu [%d] de dano\n\n", (b1.forca * k)/5);
        p1.attribute[0] -= b1_dano;
        printf("\n\n|Aperte ENTER para atacar:| ");
        getchar();
        system("clear");

    }

    if (b1.vida <= 1300)
    {
        system("clear");
        FILE *file;
        char buffer[256];
        unsigned int delay = 120; //40 ms.

        file = fopen("bed_fase2.txt", "r");
        if (file == NULL) 
        {
            fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
            exit(1); 
        }
        while (fgets(buffer, sizeof(buffer), file) != NULL) 
        {
            print_line_dialog(buffer, delay);
        }
        fclose(file);
        printf("\naperte enter para prosseguir:\n");
        getchar();
    }

    while ((b1.vida > 0) && (p1.attribute[0] > 0))
    {
        j = rand()%6+p1.attribute[2];
        int p_dano = (p1.attribute[1] * j)/2;
        printf("\nseu ataque deu [%d] de dano\n\n", (p1.attribute[1] * j)/2);
        b1.vida -= p_dano;
        k = rand()%6+b1.sorte;
        int b1_dano = (b1.forca * k)/5;
        printf("o ataque dele deu [%d] de dano\n\n", (b1.forca * k)/5);
        p1.attribute[0] -= b1_dano;
        printf("\n\n|Aperte ENTER para atacar:| ");
        getchar();
        system("clear");
    
    }
        if (p1.attribute[0] <= 0)
        {
            printf("\nvoce morreu...\n");
            printf("\nvida do BOSS [%d]\n", b1.vida);
            printf("\naperte ENTER para continuar\n");
            getchar();
            system("clear");
            death();            
        }

        if ( b1.vida <= 0)
        {
            system("clear");
            FILE *file;
            char buffer[256];
            unsigned int delay = 120; //40 ms.

            file = fopen("bed_morto.txt", "r");
            if (file == NULL) 
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                exit(1); 
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL) 
            {
                print_line_dialog(buffer, delay);
            }
            fclose(file);
            printf("\n Sua vida [%d]", p1.attribute[0]);
            rtn_life = (life_base - p1.attribute[0]);
            printf("\naperte ENTER para prosseguir\n");
            getchar();
            system("clear");
            printf("pegue a primeira chave para ajuda-lo a completar o jogo.  <ENTER>\n");
            getchar();
            system("clear");
            p1.boss[0] = 1;
            p1.inventory[1]++;
        }  
    update_save();
    bed_of_chaos();
}

void fight_twin()
{
    if (p1.boss[1] == 1)
    {
        printf("\nVoce ja matou Twin Gargoyles.\n");
        printf("\nAperte ENTER para continuar.\n");
        getchar();
        system("clear");
        twin_gargoyles();
    }
    //personagem nivel 30
    p1.local[0] = '0';
    p1.local[1] = '4';
    p1.local[2] = 'R';
    count = 0;
    int life_base;

    int k;
    int j;

    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("twin_fase1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);

    printf("O combate vai comecar, entao se prepare!\n");
    printf("\nsua vida [%d]\n", p1.attribute[0]);
    printf("vida do BOSS [%d]\n", b2.vida);//2700 de vida = 10 rounds aproximados
    printf("\n\n|Aperte ENTER para atacar:| ");
    getchar();
    system("clear");

    while((p1.attribute[0] > 0) && (b2.vida > 1300))
    {
        j = rand()%6+p1.attribute[2];
        int p_dano = (p1.attribute[1] * j)/2;
        printf("\nseu ataque deu [%d] de dano\n\n", (p1.attribute[1] * j)/2);
        b2.vida -= p_dano;
        k = rand()%6+b2.sorte;
        int b2_dano = (b2.forca * k)/5;
        printf("o ataque dele deu [%d] de dano\n\n", (b2.forca * k)/5);
        p1.attribute[0] -= b2_dano;
        printf("\n\n|Aperte ENTER para atacar:| ");
        getchar();
        system("clear");

    }

    if (b2.vida <= 1300)
    {
        system("clear");
        FILE *file;
        char buffer[256];
        unsigned int delay = 120; //40 ms.

        file = fopen("twin_fase2.txt", "r");
        if (file == NULL) 
        {
            fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
            exit(1); 
        }
        while (fgets(buffer, sizeof(buffer), file) != NULL) 
        {
            print_line_dialog(buffer, delay);
        }
        fclose(file);
        printf("\naperte enter para prosseguir:\n");
        getchar();
    }

    while ((b2.vida > 0) && (p1.attribute[0] > 0))
    {
        j = rand()%6+p1.attribute[2];
        int p_dano = (p1.attribute[1] * j)/2;
        printf("\nseu ataque deu [%d] de dano\n\n", (p1.attribute[1] * j)/2);
        b2.vida -= p_dano;
        k = rand()%6+b2.sorte;
        int b2_dano = (b2.forca * k)/5;
        printf("o ataque dele deu [%d] de dano\n\n", (b2.forca * k)/5);
        p1.attribute[0] -= b2_dano;
        printf("\n\n|Aperte ENTER para atacar:| ");
        getchar();
        system("clear");
    }

        if (p1.attribute[0] <= 0)
        {
            printf("\nvoce morreu...\n");
            printf("\nvida do BOSS [%d]\n", b2.vida);
            printf("\naperte ENTER para continuar\n");
            getchar();
            system("clear");
            death();
            
        }

        if ( b2.vida <= 0)
        {
            system("clear");
            FILE *file;
            char buffer[256];
            unsigned int delay = 120; //40 ms.

            file = fopen("bed_morto.txt", "r");
            if (file == NULL) 
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                exit(1); 
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL) 
            {
                print_line_dialog(buffer, delay);
            }
            fclose(file);
            printf("\n Sua vida [%d]", p1.attribute[0]);
            rtn_life = (life_base - p1.attribute[0]);
            printf("\naperte ENTER para prosseguir\n");
            getchar();
            system("clear");
            printf("pegue a primeira chave para ajuda-lo a completar o jogo.  <ENTER>\n");
            getchar();
            system("clear");
            p1.boss[1] = 1;
            p1.inventory[1]++;
        }
    update_save();
    twin_gargoyles();
}


void show_texts()
{
    FILE *file;
    char buffer[256];
    unsigned int delay = 40; //40 ms.

    printf("\n\nDeseja ver a descricao de algum local?  (s\n)\n\n");
    char answer;
    answer = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    if (answer == 'n')
    {
        system("clear");
        if (inicial == 0)
        {
            tutorial();
        }
        else if (inicial == 1)
        {
            bonfire();
        }
    }
    if (answer == 's')
    {
        file = fopen("map_options.txt", "r");
        if (file == NULL) 
        {
            fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
            exit(1); 
        }
        while (fgets(buffer, sizeof(buffer), file) != NULL) 
        {
            print_line_dialog(buffer, delay);
        }
        fclose(file); 

        char option;
        option = getchar();
        while (getchar() != '\n'); // Limpar buffer de entrada

        switch(option)
        {
            case '0': // firelink
                system("clear");
                file = fopen("00C_0.txt", "r");
                if (file == NULL) 
                {
                    fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                    exit(1); 
                }
                while (fgets(buffer, sizeof(buffer), file) != NULL) 
                {
                    print_line_dialog(buffer, delay);
                }
                fclose(file);
                break;
            case '1': // undead burg
                system("clear");
                file = fopen("01R_0.txt", "r");
                if (file == NULL) 
                {
                    fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                    exit(1); 
                }
                while (fgets(buffer, sizeof(buffer), file) != NULL) 
                {
                    print_line_dialog(buffer, delay);
                }
                fclose(file);
                break;
            case '2': // undead parish
                system("clear");
                file = fopen("02R_0.txt", "r");
                if (file == NULL) 
                {
                    fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                    exit(1); 
                }
                while (fgets(buffer, sizeof(buffer), file) != NULL) 
                {
                    print_line_dialog(buffer, delay);
                }
                fclose(file);
                break;
            case '3': // undead bridge
                system("clear");
                file = fopen("03R_0.txt", "r");
                if (file == NULL) 
                {
                    fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                    exit(1); 
                }
                while (fgets(buffer, sizeof(buffer), file) != NULL) 
                {
                    print_line_dialog(buffer, delay);
                }
                fclose(file);
                break;
            case '4': // twin gargoyles
                system("clear");
                file = fopen("04R_0.txt", "r");
                if (file == NULL) 
                {
                    fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                    exit(1); 
                }
                while (fgets(buffer, sizeof(buffer), file) != NULL) 
                {
                    print_line_dialog(buffer, delay);
                }
                fclose(file);
                break;
            case '5': // new londo
                system("clear");
                file = fopen("01L_0.txt", "r");
                if (file == NULL) 
                {
                    fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                    exit(1); 
                }
                while (fgets(buffer, sizeof(buffer), file) != NULL) 
                {
                    print_line_dialog(buffer, delay);
                }
                fclose(file);
                break;
            case '6': // drake valley
                system("clear");
                file = fopen("02L_0.txt", "r");
                if (file == NULL) 
                {
                    fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                    exit(1); 
                }
                while (fgets(buffer, sizeof(buffer), file) != NULL) 
                {
                    print_line_dialog(buffer, delay);
                }
                fclose(file);
                break;
            case '7': // darkroot
                system("clear");
                file = fopen("03L_0.txt", "r");
                if (file == NULL) 
                {
                    fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                    exit(1); 
                }
                while (fgets(buffer, sizeof(buffer), file) != NULL) 
                {
                    print_line_dialog(buffer, delay);
                }
                fclose(file);
                break;
            case '8': // lost izalith
                system("clear");
                file = fopen("04L_0.txt", "r");
                if (file == NULL) 
                {
                    fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                    exit(1); 
                }
                while (fgets(buffer, sizeof(buffer), file) != NULL) 
                {
                    print_line_dialog(buffer, delay);
                }
                fclose(file);
                break;
            case '9': // bed of chaos
                system("clear");
                file = fopen("05L_0.txt", "r");
                if (file == NULL) 
                {
                    fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                    exit(1); 
                }
                while (fgets(buffer, sizeof(buffer), file) != NULL) 
                {
                    print_line_dialog(buffer, delay);
                }
                fclose(file);
                break;
            default:
                break;
        }
    }
}

void show_map()
{
    FILE *file;
    char buffer[256];
    unsigned int delay = 80; //80 ms.

    file = fopen("map.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        print_line_slowly(buffer, delay);
    }
    fclose(file);
    
    show_texts();
    printf("Aperte qualquer tecla para continuar.");
    getchar();
    system("clear");
    if (inicial == 0)
    {
        tutorial();
    }
    else if (inicial == 1)
    {
        bonfire();
    }
}
//tirei o while q pegava os 2 ifs pra testar
void fight()
{
    MONSTER m1 = {55, 5, 1, 12};
    MONSTER m2 = {48, 7, 2, 15};
    MONSTER m3 = {50, 6, 3, 21};
        
    FILE *file;
    char buffer[256];
    unsigned int delay = 40; //40 ms.
    int life_base = p1.attribute[0] + rtn_life; 

    srand((unsigned)time(NULL));
    int i = rand()%3+1;
    int j;
    int k;
    switch(i)
    {
        case (1):
            printf("\n\nCUIDADO! um morto-vivo quer te atacar!\n");
            printf("O combate vai comecar, entao se prepare!\n");

            file = fopen("morto-vivo.txt", "r");
            if (file == NULL) 
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                exit(1); 
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL) 
            {
                print_line_dialog(buffer, delay);
            }
            fclose(file);

            printf("\nsua vida [%d]\n", p1.attribute[0]);
            printf("vida do morto-vivo [%d]\n", m1.vida);

            printf("\n\n|Aperte ENTER para atacar:| ");
            getchar();
            system("clear");

            while((p1.attribute[0] > 0) && (m1.vida > 0))
            {
                j = rand()%6+p1.attribute[2];
                int p_dano = (p1.attribute[1] * j)/10;
                    printf("\nseu ataque deu [%d] de dano\n\n", (p1.attribute[1] * j)/10);
                    m1.vida -= p_dano;
                k = rand()%6+m1.sorte;
                int m_dano = (m1.forca * k)/10;
                    printf("o ataque dele deu [%d] de dano\n\n", (m1.forca * k)/10);
                    p1.attribute[0] -= m_dano;
                    printf("\n\n|Aperte ENTER para atacar:| ");
                    getchar();
                    system("clear");
            }
            if (m1.vida <= 0)
            {
                printf("voce derrotou o morto-vivo...\n");
                printf("voce ganhou 12 moedas \n");
                p1.inventory[0] += 12;
                printf("sua vida [%d]\n", p1.attribute[0]);
                rtn_life = (life_base - p1.attribute[0]);
                printf("\n\n Insira qualquer caractere para continuar.");
                getchar();
                system("clear");
                if (strcmp(p1.local, "01L") == 0)
                {
                    new_londo();
                }
                else if (strcmp(p1.local, "02L") == 0)
                {
                    drake_valley();
                }
                else if (strcmp(p1.local, "03L") == 0)
                {
                    darkroot_garden();
                } 
                else if (strcmp(p1.local, "04L") == 0)
                {
                    lost_izalith();
                }
                else if (strcmp(p1.local, "01R") == 0)
                {
                    undead_burg();
                }
                else if (strcmp(p1.local, "02R") == 0)
                {
                    undead_parish();
                }
                else if (strcmp(p1.local, "03R") == 0)
                {
                    undead_bridge();
                } 
                exit(1);               
            }
        
            if (p1.attribute[0] <= 0)
            {
                printf("voce morreu...");
                printf("vida do morto-vivo [%d]\n", m1.vida);
                death();
            }
 
            break;
        case (2):
            printf("\n\nCUIDADO! um cavaleiro negro quer te atacar!\n");
            printf("A batalha vai comecar, entao se prepare!\n");

            file = fopen("cavaleiro_negro.txt", "r");
            if (file == NULL) 
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                exit(1); 
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL) 
            {
                print_line_dialog(buffer, delay);
            }
            fclose(file);

            printf("\nsua vida [%d]\n", p1.attribute[0]);
            printf("vida do cavaleiro negro [%d]\n", m2.vida);

            printf("\n\n|Aperte ENTER para atacar:| ");
            getchar();
            system("clear");
        
             while((p1.attribute[0] > 0) || (m2.vida > 0))
            {
                j = rand()%6+p1.attribute[2];
                int p_dano = (p1.attribute[1] * j)/10;
                    printf("\nseu ataque deu [%d]de dano\n", (p1.attribute[1] * j)/10);
                    m2.vida -= p_dano;
                k = rand()%6+m2.sorte;
                int m_dano = (m2.forca * k)/10;
                    printf("o ataque dele deu [%d] de dano\n", (m2.forca * k)/10);
                    p1.attribute[0] -= m_dano;
                    printf("\n\n|Aperte ENTER para atacar:| ");
                    getchar();    
                    system("clear");
            }
                if (m2.vida <= 0)
                {
                    printf("voce derrotou o cavaleiro negro...\n");
                    printf("voce ganhou 15 moedas\n");
                    p1.inventory[0] += 15;
                    printf("sua vida [%d]\n", p1.attribute[0]);
                    rtn_life = (life_base - p1.attribute[0]);
                    printf("\n\n Insira qualquer caractere para continuar.");
                    getchar();
                    system("clear");
                    if (strcmp(p1.local, "01L") == 0)
                    {
                        new_londo();
                    }
                    else if (strcmp(p1.local, "02L") == 0)
                    {
                        drake_valley();
                    }
                    else if (strcmp(p1.local, "03L") == 0)
                    {
                        darkroot_garden();
                    } 
                    else if (strcmp(p1.local, "04L") == 0)
                    {
                        lost_izalith();
                    }
                    else if (strcmp(p1.local, "01R") == 0)
                    {
                        undead_burg();
                    }
                    else if (strcmp(p1.local, "02R") == 0)
                    {
                        undead_parish();
                    }
                    else if (strcmp(p1.local, "03R") == 0)
                    {
                        undead_bridge();
                    } 
                    exit(1);
                }

                if (p1.attribute[0] <= 0)
                {
                    printf("voce morreu...");
                    printf("vida do cavaleiro negro [%d]\n", m2.vida);
                    death();
                    
                }
    
            break; 
        case (3):
            printf("\n\nCUIDADO! um necromante quer te atacar!\n");
            printf("A batalha vai comecar, entao se prepare!\n");

            file = fopen("necromante.txt", "r");
            if (file == NULL) 
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                exit(1); 
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL) 
            {
                print_line_dialog(buffer, delay);
            }
            fclose(file);

            printf("\nsua vida [%d]\n", p1.attribute[0]);
            printf("vida do necromante [%d]\n", m3.vida);

            printf("\n\n|Aperte ENTER para atacar:| ");
            getchar();
            system("clear");
        
            while((p1.attribute[0] > 0) && (m3.vida > 0))
            {
                j = rand()%6+p1.attribute[2];
                int p_dano = (p1.attribute[1] * j)/10;
                    printf("\nseu ataque deu [%d] de dano\n", (p1.attribute[1] * j)/10);
                    m3.vida -= p_dano;
                k = rand()%6+m3.sorte;
                int m_dano = (m3.forca * k)/10;
                    printf("o ataque dele deu [%d] de dano\n", (m3.forca * k)/10);
                    p1.attribute[0] -= m_dano;
                    printf("\n\n|Aperte ENTER para atacar:| ");
                    getchar();   
                    system("clear");
            }
                if (m3.vida <= 0)
                {
                    printf("voce derrotou o necromante...\n");
                    printf("voce ganhou 21 moedas\n");
                    p1.inventory[0] += 21;
                    printf("sua vida [%d]\n", p1.attribute[0]);
                    rtn_life = (life_base - p1.attribute[0]);
                    printf("\n\n Insira qualquer caractere para continuar.");
                    getchar();
                    system("clear");
                    if (strcmp(p1.local, "01L") == 0)
                    {
                        new_londo();
                    }
                    else if (strcmp(p1.local, "02L") == 0)
                    {
                        drake_valley();
                    }
                    else if (strcmp(p1.local, "03L") == 0)
                    {
                        darkroot_garden();
                    } 
                    else if (strcmp(p1.local, "04L") == 0)
                    {
                        lost_izalith();
                    }
                    else if (strcmp(p1.local, "01R") == 0)
                    {
                        undead_burg();
                    }
                    else if (strcmp(p1.local, "02R") == 0)
                    {
                        undead_parish();
                    }
                    else if (strcmp(p1.local, "03R") == 0)
                    {
                        undead_bridge();
                    } 
                    exit(1);
                }

                if (p1.attribute[0] <= 0)
                {
                    printf("voce morreu...");
                    printf("vida do necromante[%d]\n", m3.vida);
                    death();

                }
            break;
        default:  
            break;      
    }
} 

void update_save()
{
    FILE *file;
    char buffer[256];
    file = fopen("player.txt", "w");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }

    fprintf(file,"Localizacao: (%s)\n", p1.local);
    fprintf(file,"Jogador: %s\n", p1.name);
    fprintf(file,"Nivel[%d]\n", p1.attribute[3]);
    fprintf(file,"Vida [%d]\n", p1.attribute[0]);
    fprintf(file,"Forca [%d]\n", p1.attribute[1]);
    fprintf(file,"Sorte [%d]\n", p1.attribute[2]);
    fprintf(file,"Moedas [%d]\n", p1.inventory[0]);
    fprintf(file,"Chaves [%d]\n", p1.inventory[1]);
    fclose(file);
    savegame(&p1);
}

void savegame(PLAYER *p1)
{
    
    FILE *file = fopen("savegame.dat", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para salvar");
        return;
    }

    fwrite(p1, sizeof(PLAYER), 1, file);
    fclose(file);
}

void bonfire()
{
    if (rtn_life > 0 && count != 1)
    {
        p1.attribute[0] += rtn_life;
        rtn_life = 0;   
    }
    update_save();
    FILE *file;
    char buffer[256];
    unsigned int delay = 40; //40 ms.

    file = fopen("bonfire.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    char option;
    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch(option)
    {
        case '1': // subir de nivel
            system("clear");
            fclose(file);
            update_level();
            break;
        case '2': // ver atributos
            system("clear");
            show_attribute();
            break;
        case '3': // ver inventario
            system("clear");
            show_inventory();
            break;
        case '4':
            system("clear");
            show_map();
            break;
        case '5': // sair
            system("clear");
            if (strcmp(p1.local, "00C") == 0)
            {
            firelink_shrine();
            }
            else if (strcmp(p1.local, "02L") == 0)
            {
                drake_valley();
            } 
            else if (strcmp(p1.local, "05L") == 0)
            {
                bed_of_chaos();
            } 
            else if (strcmp(p1.local, "04R") == 0)
            {
                twin_gargoyles();
            } 
            else if (strcmp(p1.local, "02R") == 0)
            {
                undead_parish();
            } 
            else if (strcmp(p1.local, "04L") == 0)
            {
                lost_izalith();
            }
            break;
        default:
            break;
    }
}
void update_level()
{
    FILE *file;
    char buffer[256];
    unsigned int delay = 40; //40 ms.
    int price = ((p1.attribute[3]-1) * 10) + 20; 

    file = fopen("update_level.txt", "w");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    fprintf(file,"\n\n+=======================+\n");
    fprintf(file,"\nnivel atual [%d]\n", p1.attribute[3]);
    fprintf(file,"\nmoedas: %d\n", p1.inventory[0]);
    fprintf(file,"\nproximo nivel [%d]\n", p1.attribute[3]+1);
    fprintf(file,"\nmoedas necessarias: %d\n", price);
    fprintf(file,"\n+=======================+\n\n\n");
    fclose(file);
    file = fopen("update_level.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file); 
    if (p1.inventory[0] >= price)
    {
        printf("\n\nDesejas subir de nivel?  (s/n)\n");
        char option = getchar();
        while (getchar() != '\n'); // Limpar buffer de entrada
        switch(option)
        {
            case 's':
                system("clear");
                while (p1.inventory[0] >= price)
                {
                p1.inventory[0] -= price; //ele paga o preco pra upar de nivel
                p1.attribute[3]++; // ele upa de nivel
                p1.attribute[0] += 5;
                p1.attribute[1] += 2;
                }
                bonfire();
                break;
            case 'n':
                system("clear");
                bonfire();
                break;
            default:
                break;
        }
    }
    else
    {
        printf("\nVoce nao tem moedas o suficiente.\n");
        printf("\n\n Insira qualquer caractere para continuar.");
        getchar();
        system("clear");
        bonfire();
    }
} 

void show_attribute()
{
    FILE *file;
    char buffer[256];

    file = fopen("attribute_status.txt", "w"); //atualizar o arquivo de atributos
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    fprintf(file,"\n\n+============+\n");
    fprintf(file,"\n Nivel [%d]\n", p1.attribute[3]);
    fprintf(file,"\n Vida [%d]\n", p1.attribute[0]);
    fprintf(file,"\n Forca [%d]\n", p1.attribute[1]);
    fprintf(file,"\n Sorte [%d]\n", p1.attribute[2]);
    fprintf(file,"\n+============+\n\n\n");
    fclose(file);

    unsigned int delay = 40; //40 ms.
    file = fopen("attribute_status.txt", "r"); //mostrar o arquivo de atributos
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    } 
    printf("Aperte qualquer tecla para continuar.");
    getchar();
    system("clear");
    count = 1;
    bonfire();
} 

void print_prologue()
{
    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("prologo.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);    

    printf("\n\n Insira qualquer caractere para continuar.");
    
    getchar();
    //while (getchar() != '\n'); // Limpar buffer de entrada
    system("clear");
}

void firelink_shrine() //00C 
{
    p1.local[0] = '0';
    p1.local[1] = '0';
    p1.local[2] = 'C';
    count = 0;

    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("00C_1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);

    char option;
    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch (option) 
    {
        case '1':
            system("clear");
            bonfire();
            break;
        case '2':
            system("clear");
            porta_check();
            break;
        case '3':
            system("clear");
            new_londo();
            break;
        case '4':
            system("clear");
            undead_burg();
            break;           
        default:
            break;
    }
}

const char* check_playerlocation(){
    if (strcmp(p1.local, "00C") == 0){
        return "00C.txt";
    } else if (strcmp(p1.local, "01L") == 0){
        return "01L.txt";
    } else if (strcmp(p1.local, "02L") == 0){
        return "02L.txt";
    } else if (strcmp(p1.local, "03L") == 0){
        return "03L.txt";
    } else if (strcmp(p1.local, "04L") == 0){
        return "04L.txt";
    } else if (strcmp(p1.local, "05L") == 0){
        return "05L.txt";
    } else if (strcmp(p1.local, "01R") == 0){
        return "01R.txt";
    } else if (strcmp(p1.local, "02R") == 0){
        return "02R.txt";
    } else if (strcmp(p1.local, "03R") == 0){
        return "03R.txt";
    } else if (strcmp(p1.local, "04R") == 0){
        return "04R.txt";
    } else if (strcmp(p1.local, "00F") == 0){
        return "00F.txt";
    }       
}

void tela_fim()
{

}

void death()
{
    printf("\nRenascendo na ultima fogueira\n");
    for (int i = 0; i < 3; i++)
    {
        printf(". ");
        fflush(stdout);
        sleep(1);
    }
    bonfire();
}

void explore()
{
    char path[256];
    snprintf(path, sizeof(path), "expl_%s.txt", p1.local); // Construir o caminho completo do arquivo
    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo %s\n", path);
        exit(1);
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        print_line_dialog(buffer, delay);
    }
    fclose(file);

    printf("\n\n\n\n");

    for (int i = 0; i < 3; i++)
    {
        printf(". ");
        fflush(stdout);
        sleep(1);
    }

    int dinheiro = rand()%100 + 100;

    printf("\n\n Voce coletou [%d] moedas!", dinheiro);

    printf("\n\nAperte qualquer tecla para prosseguir");

    p1.inventory[0] += dinheiro;

    getchar();

    system("clear");
    loot = 0;
    if (strcmp(p1.local, "01L") == 0)
    {
        new_londo();
    }
    else if (strcmp(p1.local, "02L") == 0)
    {
        drake_valley();
    }
    else if (strcmp(p1.local, "03L") == 0)
    {
        darkroot_garden();
    } 
    else if (strcmp(p1.local, "04L") == 0)
    {
        lost_izalith();
    }
    else if (strcmp(p1.local, "01R") == 0)
    {
        undead_burg();
    }
    else if (strcmp(p1.local, "02R") == 0)
    {
        undead_parish();
    }
    else if (strcmp(p1.local, "03R") == 0)
    {
        undead_bridge();
    }
}

void show_inventory()
{
    FILE *file;
    char buffer[256];

    file = fopen("inventory_status.txt", "w"); //atualizar o arquivo de atributos
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    fprintf(file,"\n\n+============+\n");
    fprintf(file,"\nMoedas [%d]\n", p1.inventory[0]);
    fprintf(file,"\nChaves [%d]\n", p1.inventory[1]);
    fprintf(file,"\n+============+\n\n\n");
    fclose(file);
    
    unsigned int delay = 40; //40 ms.
    file = fopen("inventory_status.txt", "r"); //mostrar o arquivo de atributos
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    } 
    printf("Aperte qualquer tecla para continuar.");
    getchar();
    system("clear");
    bonfire();   
}

void new_londo () //01L 
{   
    spawn_enemy = rand()%6;
    bool loot = 1;
    p1.local[0] = '0';
    p1.local[1] = '1';
    p1.local[2] = 'L';
    
    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("01L_1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);    

    char option; //decisao do q fazer na sala
    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch (option)
    {
        case '1':
            system("clear");
            drake_valley();
            break;
        case '2' :
            system("clear");
            firelink_shrine();
            break;
        case '3':
            system("clear");
            explore();
            break;
        case '4':
            system("clear");
            if (p1.attribute[2] >= spawn_enemy)
            {
                printf("Nao ha monstros nessas ruinas.\n");
                new_londo();
            }
            else
            {
                fight();
            }
            break;
        default:
            break;                
    }
}


void drake_valley() //02L 
{
    spawn_enemy = rand()%6;
    bool loot = 1;
    p1.local[0] = '0';
    p1.local[1] = '2';
    p1.local[2] = 'L';
    count = 0;
    
    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("02L_1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);    
    
    char option; //decisao do q fazer na sala
    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch (option)
    {
        case '1':
            system("clear");
            darkroot_garden();
            break;
        case '2' :
            system("clear");
            new_londo();
            break;
        case '3':
            system("clear");
            bonfire();
            break;
        case '4':
            system("clear");
            explore();
            break;
        case '5':
            system("clear");
            if (p1.attribute[2] >= spawn_enemy)
            {
                printf("Nao ha monstros nessas ruinas.\n");
                drake_valley();
            }
            else
            {
                fight();
            }
            break;
        default:
            break;                
    }
}

void darkroot_garden() // 03L loc[1][2]
{
    spawn_enemy = rand()%6;
    bool loot = 1;
    p1.local[0] = '0';
    p1.local[1] = '3';
    p1.local[2] = 'L';
    
    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("03L_1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);    
    
    char option; //decisao do q fazer na sala
    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch (option)
    {
        case '1':
            system("clear");
            lost_izalith();
            break;
        case '2' :
            system("clear");
            drake_valley();
            break;
        case '3':
            system("clear");
            explore();
            break;
        case '4':
            system("clear");
            if (p1.attribute[2] >= spawn_enemy)
            {
                printf("Nao ha monstros nessas ruinas.\n");
                darkroot_garden();
            }
            else
            {
                fight();
            }
            break;
        default:
            break;                
    }
    
}

void lost_izalith() // 04L loc[1][3]
{
    spawn_enemy = rand()%6;
    bool loot = 1;
    p1.local[0] = '0';
    p1.local[1] = '4';
    p1.local[2] = 'L';
    count = 0;
    
    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("04L_1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);    
    
    char option; //decisao do q fazer na sala

    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch (option)
    {
        case '1':
            system("clear");
            bed_of_chaos();
            break;
        case '2' :
            system("clear");
            darkroot_garden();
            break;
        case '3':
            system("clear");
            bonfire();
            break;
        case '4':
            system("clear");
            explore();
            break;
        case '5':
            system("clear");
            if (p1.attribute[2] >= spawn_enemy)
            {
                printf("Nao ha monstros nessas ruinas.\n");
                lost_izalith();
            }
            else
            {
                fight();
            }
            break;
        default:
            break;                
    }
    
}

void bed_of_chaos() // 05L loc[1][4]
{
    p1.local[0] = '0';
    p1.local[1] = '5';
    p1.local[2] = 'L';
    count = 0;

    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("05L_1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);

    char option; //decisao do q fazer na sala
    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch (option)
    {
        case '1':
            system("clear");
            fight_bed();
            break;
        case '2' :
            system("clear");
            lost_izalith();
            break;
        case '3':
            system("clear");
            bonfire();
            break;
        default:
            break;                
    }
}

void undead_burg() // 01R loc[0][1]
{
    spawn_enemy = rand()%6;
    bool loot = 1;
    p1.local[0] = '0';
    p1.local[1] = '1';
    p1.local[2] = 'R';

    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("01R_1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);    

    char option; //decisao do q fazer na sala
    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch (option)
    {
        case '1':
            system("clear");
            undead_parish();
            break;
        case '2' :
            system("clear");
            firelink_shrine();
            break;
        case '3':
            system("clear");
            explore();
            break;
        case '4':
            system("clear");
            if (p1.attribute[2] >= spawn_enemy)
            {
                printf("Nao ha monstros nessas ruinas.\n");
                undead_burg();
            }
            else
            {
                fight();
            }
            break;
        default:
            break;                
    }
}

void undead_parish() // 02R loc[0][2]
{
    spawn_enemy = rand()%6;
    bool loot = 1;
    p1.local[0] = '0';
    p1.local[1] = '2';
    p1.local[2] = 'R';
    count = 0;

    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("02R_1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);    
    
    char option; //decisao do q fazer na sala
    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch (option)
    {
        case '1':
            system("clear");
            undead_bridge();
            break;
        case '2' :
            system("clear");
            undead_burg();
            break;
        case '3':
            system("clear");
            bonfire();
            break;
        case '4':
            system("clear");
            explore();
            break;
        case '5':
            system("clear");
            if (p1.attribute[2] >= spawn_enemy)
            {
                printf("Nao ha monstros nessas ruinas.\n");
                drake_valley();
            }
            else
            {
                fight();
            }
            break;
        default:
            break;                
    }
}

void undead_bridge() // 03R loc[0][3]
{
    spawn_enemy = rand()%6;
    bool loot = 1;
    p1.local[0] = '0';
    p1.local[1] = '3';
    p1.local[2] = 'R';

    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("03R_1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);    

    char option; //decisao do q fazer na sala
    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch (option)
    {
        case '1':
            system("clear");
            twin_gargoyles();
            break;
        case '2' :
            system("clear");
            undead_parish();
            break;
        case '3':
            system("clear");
            explore();
            break;
        case '4':
            system("clear");
            if (p1.attribute[2] >= spawn_enemy)
            {
                printf("Nao ha monstros nessas ruinas.\n");
                undead_burg();
            }
            else
            {
                fight();
            }
            break;
        default:
            break;                
    }
}

void twin_gargoyles() // 04R
{
    p1.local[0] = '0';
    p1.local[1] = '4';
    p1.local[2] = 'R';
    count = 0;

    FILE *file;
    char buffer[256];
    unsigned int delay = 120; //40 ms.

    file = fopen("04R_1.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1); 
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_dialog(buffer, delay);
    }
    fclose(file);

    char option; //decisao do q fazer na sala
    option = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    switch (option)
    {
        case '1':
            system("clear");
            fight_twin();
            break;
        case '2' :
            system("clear");
            undead_bridge();
            break;
        case '3':
            system("clear");
            bonfire();
            break;
        default:
            break;                
    }
}

void porta_check (){
    char dec;
    if (p1.boss[0] == 0 && p1.boss[1] == 0) 
    {
        printf ("A sua frente, uma porta de pedra com o dobro da sua altura.\n");
        printf ("Ambas as tochas em cada lado da porta estao apagadas.\n\n\n");
        printf ("Talvez voce devesse voltar aqui em breve.\n");

        printf ("\nAperte qualquer tecla para voltar.\n");

        dec = getchar();
        system("clear");

        firelink_shrine();
    } 
    else if (p1.boss[0] == 1 && p1.boss[1] == 0) 
    {
        printf ("A sua frente, uma porta de pedra com o dobro da sua altura.\n");
        printf ("A tocha ao lado esquerdo da porta esta acesa, ela te traz conforto.\n\n\n");
        printf ("Talvez voce devesse voltar aqui em breve.\n");

        printf ("\nAperte qualquer tecla para voltar.\n");

        dec = getchar();
        system("clear");

        firelink_shrine();

    } 
    else if (p1.boss[0] == 0 && p1.boss[1] == 1) 
    {
        printf ("A sua frente, uma porta de pedra com o dobro da sua altura.\n");
        printf ("A tocha ao lado direito da porta esta acesa, ela te deixa triste.\n\n\n");
        printf ("Talvez voce devesse voltar aqui em breve.\n");

        printf ("\nAperte qualquer tecla para voltar.\n");

        dec = getchar();
        system("clear");
        while (getchar() != '\n'); // Limpar buffer de entrada

        firelink_shrine();

    } 
    else if (p1.boss[0] == 1 && p1.boss[1] == 1) 
    {
        printf ("A sua frente, uma porta de pedra com o dobro da sua altura.\n");
        printf ("Com ambas as tochas acesas, voce sente uma sensacao de pavor repentina.\n\n\n");
        printf ("Esse deve ser o fim caso entre por essa porta.\n");

        printf ("\n%s, deseja entrar pela porta? (s/n).\n", p1.name);

        dec = getchar();
        system("clear");
        while (getchar() != '\n'); // Limpar buffer de entrada

        switch (dec) {
            case 's':
                tela_fim();
                break;
            case 'n':
                system("clear");
                firelink_shrine();
                break;
            default:
                break;
        }
    }
    
}

void create_newgame() // funcao que cria um novo perfil do zero
{
    count = 0;
    inicial = 1;

    while (count == 0)
    {
        
        FILE *file;
        char buffer[256];
        unsigned int delay = 40; //40 ms.

        file = fopen("criar_classe.txt", "r");
        if (file == NULL) 
        {
            fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
            exit(1);
        }
        while (fgets(buffer, sizeof(buffer), file) != NULL) 
        {
            print_line_slowly(buffer, delay);
        }
        fclose(file);

        char personagem;
        personagem = getchar();
        system("clear");
        while (getchar() != '\n'); // Limpar buffer de entrada

        p1.boss[0] = 0;
        p1.boss[1] = 0;
        p1.attribute[3] = 1; // level
        p1.inventory[0] = 0; // gold
        p1.inventory[1] = 0; // keys       

        switch (personagem) 
        {
        case '1': // mostra o painel de guerreiro
            p1.attribute[0] = 100;
            p1.attribute[1] = 9;
            p1.attribute[2] = 1;
            p1.inventory[0] = 0;

            file = fopen("perfil_1.txt", "r");
            if (file == NULL) 
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                exit(1); 
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL) 
            {      
                print_line_dialog(buffer, delay);
            }
            fclose(file);
            break;

        case '2': // mostra o painel de cavaleiro
            p1.attribute[0] = 110;
            p1.attribute[1] = 7;
            p1.attribute[2] = 1;
            p1.inventory[0] = 0; 

            file = fopen("perfil_2.txt", "r");
            if (file == NULL) 
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                exit(1); 
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL) 
            {   
                print_line_dialog(buffer, delay);
            }
            fclose(file);   
            break;

        case '3': // mostra o painel de feiticeiro
            p1.attribute[0] = 90;
            p1.attribute[1] = 8;
            p1.attribute[2] = 2;    
            p1.inventory[0] = 15000;

            file = fopen("perfil_3.txt", "r");
            if (file == NULL) 
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                exit(1); 
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL) 
            {
                print_line_dialog(buffer, delay);
            }
            fclose(file);
            break;

        default:
            break;
        }

        printf("\n\n\n Qual sera o nome do seu personagem?\n\n\n");
        scanf("%s", p1.name);
        while (getchar() != '\n'); // Limpar buffer de entrada

        printf("Deseja confirmar a criacao do seu personagem?  (s/n)\n\n");
        char option;
        option = getchar();
        system("clear");
        while (getchar() != '\n'); // Limpar buffer de entrada

        switch (option)
        {
        case 's':
            p1.local[0] = '0';
            p1.local[1] = '0';
            p1.local[2] = 'C';
            p1.boss[0] = 0;
            p1.boss[1] = 0;

            FILE *file;
            char buffer[256];
            file = fopen("player.txt", "w");
            if (file == NULL) 
            {
                fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
                exit(1); 
            }
            
            fprintf(file,"Localizacao: (%s)\n", p1.local);
            fprintf(file,"Jogador: %s\n", p1.name);
            fprintf(file,"Nivel[%d]\n", p1.attribute[3]);
            fprintf(file,"Vida [%d]\n", p1.attribute[0]);
            fprintf(file,"Forca [%d]\n", p1.attribute[1]);
            fprintf(file,"Sorte [%d]\n", p1.attribute[2]);
            fprintf(file,"Moedas [%d]\n", p1.inventory[0]);
            fprintf(file,"Chaves [%d]\n", p1.inventory[1]);
            fclose(file);

            //player_savefile();//funcao que salva o perfil do jogador
            print_prologue();
            update_save();//mostra o arquivo do jogador e o sobrescreve
            firelink_shrine();
            break;
        case 'n':
            break;
        default:
            break;
        }
        count++;      
    }   
}

int load_savegame(PLAYER *p1) 
{

    FILE *file = fopen("savegame.dat", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para carregar");
        return 0;  // Retorna 0 para indicar falha
    }

    fread(p1, sizeof(PLAYER), 1, file);
    fclose(file);
    return 1;  // Retorna 1 para indicar sucesso
}

int credits_screen()
{
    FILE *file;
    char buffer[256];
    unsigned int delay = 80; //80 ms.

    file = fopen("creditos.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        print_line_slowly(buffer, delay);
    }
    fclose(file);
}

void print_line_dialog(const char* line, unsigned int delay) 
{
    printf("%s", line);
    usleep(25 * 1000);
}

void print_line_slowly(const char* line, unsigned int delay) 
{
    printf("%s", line);
    fflush(stdout);
    usleep(delay * 1000);
}

void tutorial()
{
    inicial = 0;
    FILE *file;
    char buffer[256];
    unsigned int delay = 80; //120 ms.
    system("clear");
    file = fopen("help_1.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        exit(1);
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_slowly(buffer, delay);
    }
    fclose(file);
    char answer;
    answer = getchar();
    while (getchar() != '\n'); // Limpar buffer de entrada

    if (answer == '1')
    {
        system("clear");
        show_map();
    }
    if (answer == '2')
    {
        system("clear");
        printf("\n\nO que deseja fazer?\n\n");
        printf("\nOBS: após escolher sua opcao, abra o jogo novamente!\n\n");
        printf("[1] Tutorial Luta\n\n");
        printf("[2] Sair do Tutorial\n\n");

        char option;
        option = getchar();
        while (getchar() != '\n'); // Limpar buffer de entrada

        switch (option)
        {
        case '1':
            system("clear");
            file = fopen("help_2.txt", "r");
            if (file == NULL) {
            fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
            exit(1);
            }
            while (fgets(buffer, sizeof(buffer), file) != NULL) 
            {
                print_line_slowly(buffer, delay);
            }
                fclose(file);
            break;
        case '2':
            system("clear");
            break;
        default:
            break;
        }
    }
    
}

int main() 
{
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    FILE *file;
    char buffer[256];
    unsigned int delay = 80; //120 ms.
    system("clear");
    file = fopen("titulo.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_slowly(buffer, delay);
    }
    fclose(file);
    
    printf("\n\n Insira qualquer caractere para continuar.");
    getchar();
    system("clear");

    file = fopen("menuprincipal.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Nao foi possivel abrir o arquivo titulo.txt\n");
        return 1;
    }
    delay = 35; //35 ms.
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        print_line_slowly(buffer, delay);
    }
    fclose(file);
    char menu;
    menu = getchar();
    system("clear");
    while ((getchar()) != '\n'); // Limpar buffer de entrada

    switch (menu)
    {
    case '1':
        create_newgame();
        break;
    case '2':
        if (load_savegame(&p1) == 1)
        {
            printf("\n\n\nJogo carregado com sucesso!\n\n\n");
            bonfire();
        }
        else
        {
            printf("\n\n\nFalha ao carregar o jogo.\n\n\n");
        }   
        break;
    case '3':
        tutorial();
        break;
    case '4':
        credits_screen();
        break;    
    case '5':
        exit(0);          
    default:
        break;
    }
    return 0;
}