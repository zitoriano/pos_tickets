#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#define MAX_CAPACITY 10
#define TICKET_LIMIT 30

struct show {
    char name[16];
    int capacity;
    char hour[3];
};

struct show shows[3];

struct ticket {
    int show;
    char date[16];
    int type;
    int chair;
};

struct ticket tickets[TICKET_LIMIT];

struct tickettype {
    char name[15];
    float price;
};

struct tickettype tickettypes[3];

// pause program
void pause();

// clear the buffer
void flush();

// sell ticket
void sellticket();

// cancel ticket
int cancelticket(int show, int seat);

// check seat
int checkseat(int show, int seat);

// show time
void showtime(char hour[], char *date);

// ask (y or n)
int ask(char *question);

// sales by day
float sales_by_day(int show);

int main()
{
	setlocale(LC_ALL, "Portuguese");
	
    // define shows
    strcpy(shows[0].name, "Madame Tussauds");
    shows[0].capacity = MAX_CAPACITY;
    strcpy(shows[0].hour, "17h");

    strcpy(shows[1].name, "Aladdin");
    shows[1].capacity = MAX_CAPACITY;
    strcpy(shows[1].hour, "19h");

    strcpy(shows[2].name, "Rei Le�o");
    shows[2].capacity = MAX_CAPACITY;
    strcpy(shows[2].hour, "22h");

    // define ticket types
    strcpy(tickettypes[0].name, "Inteiro");
    tickettypes[0].price = 100;

    strcpy(tickettypes[1].name, "Meia");
    tickettypes[1].price = 50;

    strcpy(tickettypes[2].name, "Cortesia");
    tickettypes[2].price = 0;

    int cmd = 0;

    do
    {
        // print program options
        printf("# Ingresso F�cil 1.0#\n\n");
        printf("1. Vender Ingresso\n");
        printf("2. Cancelar Ingresso\n");
        printf("3. Saldo de Caixa\n");
        printf("4. Fechar Programa\n\n");

        // print instructions
        printf("Digite a op��o desejada: \n");

        // get option
        scanf("%d", &cmd);

        // clear the buffer
        flush();

        // clear window options
        system("cls");

        switch (cmd)
        {
            case 1:
                sellticket();
                break;
            case 2:
                {
                    int show = 0, seat = 0;
                    printf("Informe o n�mero da pe�a e acento para cancelar um ingresso\n\n");
                    printf("N�mero da pe�a: ");
                    scanf("%d", &show);
                    printf("N�mero do acento: ");
                    scanf("%d", &seat);
                    flush();

                    if (cancelticket(show, seat))
                        printf("\nIngresso cancelado.\n");
                    else
                        printf("\nIngresso n�o encontrado.\n");

                    pause();
                    system("cls");
                    break;
                }
            case 3: 
                {
                    printf("Saldo de Caixa\n\n");

                    float total = 0;

                    // Print details from show 1
                    total = total + sales_by_day(0);

                    // Print details from show 2
                    total = total + sales_by_day(1);

                    // Print details from show 3
                    total = total + sales_by_day(2);

                    // Print total
                    printf("Total de caixa do dia: R$ %1.5f\n\n", total);

                    // Pause program after print all
                    pause();
                    system("cls");
                    break;
                }

            case 4:
                printf("Fechar Programa\n");
                break;
            default:
                printf("Op��o Inv�lida, tente novamente\n");
        }

    } while (cmd != 4);

    return 0;
}

void pause()
{
    puts("Pressione ENTER ...");
    while(getchar() != 10);
}

void flush()
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

void sellticket()
{
    while(1)
    {
        system("cls");

        puts("Escolha um show:\n");

        int x, cmd = 0;
        for (x = 0; x < 3; x++)
            printf("%d %s\n", x + 1, shows[x].name);

        scanf("%d", &cmd);
        flush();

        if (cmd < 1 || cmd > 3) {
            puts("Show n�o encontrado, tente novamente!");
            pause();
        }
        else
        {
            system("cls");
            printf("Show selecionado: %s\n", shows[cmd-1].name);

            if (shows[cmd-1].capacity == 0) {
                puts("N�o existem mais vagas dispon�veis para esse show!");
                pause();
                system("cls");
                break;
            }

            puts("Poltronas dispon�veis\n");
            for (x = 1; x <= MAX_CAPACITY; x++)
            {
                if(checkseat(cmd, x))
                    printf("X, ");
                else
                    printf("%d, ", x);
            }

            int seat = 0;
            printf("\nEscolha uma poltrona livre: ");
            scanf("%d", &seat);
            flush();
            
            int sold = 0;
            int weekday = 0;
            int ticket = 0;
            
            if (seat < 1 || seat > MAX_CAPACITY)
            {
                puts("N�mero de poltrona n�o existe!");
                pause();
                system("cls");
                break;
            }
            else if (checkseat(cmd, seat))
            {
                puts("Poltrona n�o est� dispon�vel!");
                pause();
                system("cls");
                break;
            }
            else
            {
                system("cls");
                puts("Selecione um tipo de ingresso\n");
                
                for (x = 0; x < 3; x++)
                {
                    printf("%d. %s\n", x + 1, tickettypes[x].name);
                }

                scanf("%d", &ticket);
                flush();
                
                switch(ticket)
                {
                              
                    case 1:
                    {
                        sold = 1;
                        break;
                    }  
                    case 2:
                    {
                        char question[100];

                        // ask if client is a teacher/professor
                        strcpy(question, "� professor da rede p�blica, 's' ou 'n'?");
                        if (ask(question)) {
                            sold = 1;
                            break;
                        }

                        // clear
                        system("cls");

                        // ask if client is a student
                        strcpy(question, "� estudante, 's' ou 'n'?");
                        if (ask(question)) {
                            sold = 1;
                            break;
                        }

                        // clear
                        system("cls");

                        // ask client your age
                        strcpy(question, "Voce tem entre 0 as 12 anos ou mais de 60, 's' ou 'n'?");
                        if (ask(question)) {
                            sold = 1;
                            break;
                        }
                    }
                    break;
                    case 3:
                    {
                        do {
                            system("cls");

                            // Show instructions
                            printf("Informe o dia da semana: \n\n");
                            printf("1. Segunda-Feira\n");
                            printf("2. Ter�a-Feira\n");
                            printf("3. Quarta-Feira\n");
                            printf("4. Quinta-Feira\n");
                            printf("5. Sexta-Feira\n");
                            printf("6. S�bado\n");
                            printf("7. Domingo\n");

                            scanf("%d", &weekday);
                            flush();

                            if (weekday < 1 || weekday > 7) {
                                printf("Op��o Inv�lida\n");
                                pause();
                            }

                        } while(weekday < 1 || weekday > 7);

                        if (weekday == 2) {
                            char question[100];

                            // ask if client is needy-child
                            strcpy(question, "� crian�a carente, 's' ou 'n'?");
                            if (ask(question)) {
                                sold = 1;
                                break;
                            } else {
                                puts("Cortesias s� podem ser vendidas a crian�as carentes!");
                            }
                        } else {
                            puts("Cortesias s� podem ser vendidas nas ter�as-feiras!");
                        }
                        
                    }
                    break;
                    default:
                        printf("Op��o inv�lida\n");
                }

                if(sold)
                {
                    // get free index
                    int index = -1;
                    for (x = 0; x < TICKET_LIMIT; x++)
                        if (tickets[x].show == 0) {
                            index = x;
                            break;
                        }

                    // get show date
                    char date[16];
                    showtime(shows[cmd-1].hour, date);

                    tickets[index].show = cmd;
                    strcpy(tickets[index].date, date);
                    tickets[index].type = ticket-1;
                    tickets[index].chair = seat;

                    // Decrease available chairs
                    shows[cmd-1].capacity = shows[cmd-1].capacity - 1;

                    system("cls");

                    // Print ticket details
                    printf("Seu recibo\n");
                    printf("==========\n\n");
                    printf("Pe�a: %s\n", shows[cmd-1].name);
                    printf("Data / Hora: %sh\n", tickets[index].date);
                    printf("Poltrona: %d\n", seat);
                    printf("Ingresso: %s\n\n", tickettypes[ticket-1].name);
                }

                pause();
                system("cls");
                break;
            }
        }
    }
}

int cancelticket(int show, int seat)
{
    int i, found = 0;
    for (i = 0; i < TICKET_LIMIT; i++)
    {
        if (tickets[i].show == show && tickets[i].chair == seat)
        {
            found = 1;
            tickets[i].show = 0;
            tickets[i].type = 0;
            tickets[i].chair = 0;

            // increase available chairs
            shows[show-1].capacity = shows[show-1].capacity + 1;

            break;
        }
    }

    if(found)
        return 1;
    else
        return 0;
}

int checkseat(int show, int seat)
{
    int i, found = 0;
    for (i = 0; i < TICKET_LIMIT; i++)
    {
        if (tickets[i].show == show && tickets[i].chair == seat)
        {
            found = 1;
            break;
        }
    }

    if(found)
        return 1;
    else
        return 0;
}

void showtime(char hour[], char *date)
{
    // define Timezone
    char tz[21] = "TZ=America/Sao_Paulo";
    putenv(tz);

    // define time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(date, "%d/%d/%d as %s", 
        tm.tm_mday, 
        tm.tm_mon + 1, 
        tm.tm_year + 1900,
        hour);
}

float sales_by_day(int show)
{
    float total = 0;
    int x = 0, ticketid = 0, total_tickets = 0, regular = 0, promotional = 0, free = 0;

    for (x = 0; x < TICKET_LIMIT; x++)
    {
        if (tickets[x].show == show + 1 && tickets[x].chair > 0)
        {
            ticketid = tickets[x].type;

            total_tickets = total_tickets + 1;
            total = total + tickettypes[ticketid].price;

            switch (ticketid)
            {
                case 0:
                    regular = regular + 1; break;
                case 1:
                    promotional = promotional + 1; break;
                case 2:
                    free = free + 1; break;
                default:
                    break;
            }
        }
    }

    printf("Pe�a: %s / %s\n", shows[show].name, shows[show].hour);
    printf("Total de ingressos vendidos: %d\n", total_tickets);
    printf("%s: %d / %s: %d / %s: %d\n", 
        tickettypes[0].name,
        regular,
        tickettypes[1].name,
        promotional,
        tickettypes[2].name,
        free);

    printf("Valor total recebido: R$ %1.5f\n\n", total);

    return total;
}

int ask(char *question)
{
    while(1)
    {
        char ans;
        printf("%s\n", question);
        scanf("%c", &ans);
        flush();

        if(ans == 's' || ans == 'n')
        {
            return (ans == 's');
        }
        else
        {
            puts("Resposta inv�lida");
            pause(); 
            continue;
        }
    }
}
