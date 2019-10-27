/*
    - PIM IV
    - Construir um programa para venda de ingressos de teatro.

    - O programa precisa ter uma tabela de preços
        1. Preço cheio R$ 100
        2. Preço meia entrada R$ 50 (Estudantes, Crianças de 0 a 12,
        adultos a partir de 60 anos e professores da rede pública).
        3. Desconto de 100% R$ 0 para crianças carentes da rede
        pública de ensino as terças-feiras.

    - Ao emitir um ingresso vendido, o sistema deve apresentar:
        1. Data / Hora
        2. Nome da peça
        3. Nr da poltrona (Não pode repetir a poltrona 
        para a mesma peça no mesmo horario)

    - Limitar em 10 poltronas disponíveis, não permitindo vender mais 
    ingressos quando o limite for atingido.

    - Apresentar o saldo de caixa (Bilheteria)
        1. Mostrar quantos ingressos foram vendidos por tipo e por peça
        2. Saldo total no caixa do dia

    ---

    - Fluxo

    1. Mostrar um cabeçalho do programa junto com as opções disponíveis
        # Ingresso Fácil 1.0 #
        1. Vender Ingressos
        2. Cancelar Ingressos
        3. Saldo de Caixa
        4. Fechar Programa
    2. Vender Ingressos
        1. Vender ingressos para a peça:
            1. Madame Tussauds
            2. Aladdin
            3. Rei Leão
        2. Ao escolher verificar poltronas vagas.
            1. Se não houver poltronas disponíveis, printa "Sold Out"
        3. Digitar poltrona:
            1. Se poltrona já estiver ocupada printa mensagem, poltrona não disponível.
        3. Tipo de ingresso:
            1. Inteira R$ 100,00
            2. Meia R$ 50,00
                1. É professor da rede pública (Sim / Não)
                2. Sim, ok vende o Ingresso
                3. Não, pergunta se é estudante (Sim / Não)
                4. Sim, ok vende o Ingresso
                5. Não, pergunta a idade do cliente:
                (se idade >= 0 e <= 12 ou >= 60) ok, vende ingresso
                6. Se não, apresenta mensagem "Não pode vender esse ingresso"
            3. Cortesia R$ 0,00
                1. Informe o dia da semana:
                    1. Domingo
                    2. Segunda
                    3. Terça
                    4. Quarta
                    5. Quinta
                    6. Sexta
                    7. Sábado
                2. Se for terça (3) pergunta se o cliente é criança carente:
                    1. Sim, ok vende ingresso.
                3. Se não, printa "Não pode vender esse ingresso"
        4. Ingresso vendido, printa na tela
            # Seu recibo #
            # Peça: Rei Leão
            # Data / Hora: 10/10/2019 20h
            # Poltrona: 10
            # Ingresso: Inteira
        5. Cancelar Ingresso
            1. Escolha o nome da peça e o numero da poltrona.
            2. Validar as informações se ingresso encontrado, cancela,
            senão printa "Ingresso não encontrado".
        6. Saldo de Caixa
            # Saldo de Caixa #
            # 
            # Peça: Madame Tussauds / 17h
            # Total de ingressos vendidos: 10
            # Inteira: 7 / Meia: 2 / Cortesia: 1
            # Valor total recebido: R$ 250
            # 
            # Peça: Aladdin / 18h
            # Total de ingressos vendidos: 10
            # Inteira: 5 / Meia: 5 / Cortesia: 0
            # Valor total recebido: R$ 220
            # 
            # Peça: Rei Leão / 19h
            # Total de ingressos vendidos: 10
            # Inteira: 9 / Meia: 1 / Cortesia: 0
            # Valor total recebido: R$ 300
            #
            # Saldo total em caixa: R$ 780,00
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_CAPACITY 20
#define TICKET_LIMIT 60

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
void sales_by_day(int show);

int main()
{
    // define shows
    strcpy(shows[0].name, "Madame Tussauds");
    shows[0].capacity = MAX_CAPACITY;
    strcpy(shows[0].hour, "17h");

    strcpy(shows[1].name, "Aladdin");
    shows[1].capacity = MAX_CAPACITY;
    strcpy(shows[1].hour, "19h");

    strcpy(shows[2].name, "Rei Leão");
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
        printf("# Ingresso Fácil 1.0#\n");
        printf("1. Vender Ingresso\n");
        printf("2. Cancelar Ingresso\n");
        printf("3. Saldo de Caixa\n");
        printf("4. Fechar Programa\n\n");

        // print instructions
        printf("Digite a opção desejada: \n");

        // get option
        scanf("%d", &cmd);

        // clear the buffer
        flush();

        // clear window options
        system("clear");

        switch (cmd)
        {
            case 1:
                sellticket();
                break;
            case 2:
                {
                    int show = 0, seat = 0;
                    printf("Informe o número da peça e acento para cancelar um ingresso\n");
                    printf("Número da peça: ");
                    scanf("%d", &show);
                    printf("Número do acento: ");
                    scanf("%d", &seat);
                    flush();

                    if (cancelticket(show, seat))
                        printf("\nIngresso cancelado.\n");
                    else
                        printf("\nIngresso não encontrado.\n");

                    pause();
                    system("clear");
                    break;
                }
            case 3: 
                printf("Saldo de Caixa\n\n");

                // Print details from show 1
                sales_by_day(0);

                // Print details from show 2
                sales_by_day(1);

                // Print details from show 3
                sales_by_day(2);

                // Pause program after print all
                pause();
                system("clear");
                break;

            case 4:
                printf("Fechar Programa\n");
                break;
            default:
                printf("Opção Inválida, tente novamente\n");
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
        system("clear");

        puts("Escolha um show:\n");

        int x, cmd = 0;
        for (x = 0; x < 3; x++)
            printf("%d %s\n", x + 1, shows[x].name);

        scanf("%d", &cmd);
        flush();

        if (cmd < 1 || cmd > 3) {
            puts("Show não encontrado, tente novamente!");
            pause();
        }
        else
        {
            system("clear");
            printf("Show selecionado: %s\n", shows[cmd-1].name);

            if (shows[cmd-1].capacity == 0) {
                puts("Não existem mais vagas disponíveis para esse show!");
                pause();
                continue;
            }

            puts("Poltronas disponíveis\n");
            for (x = 1; x <= 20; x++)
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
            
            if (seat < 1 || seat > 20)
            {
                puts("Número de poltrona não existe!");
                pause();
                continue;
            }
            else if (checkseat(cmd, seat))
            {
                puts("Poltrona não está disponível!");
                pause();
                continue;
            }
            else
            {
                system("clear");
                puts("Selecione um tipo de ingresso");
                
                for (x = 0; x < 3; x++)
                {
                    printf("%d. %s\n", x + 1, tickettypes[x].name);
                }

                int ticket = 0;
                scanf("%d", &ticket);
                flush();

                int sold = 0;
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
                        strcpy(question, "É professor da rede pública, 's' ou 'n'?");
                        if (ask(question)) {
                            sold = 1;
                            break;
                        }

                        // clear
                        system("clear");

                        // ask if client is a student
                        strcpy(question, "É estudante, 's' ou 'n'?");
                        if (ask(question)) {
                            sold = 1;
                            break;
                        }

                        // clear
                        system("clear");

                        // ask client your age
                        strcpy(question, "Você tem entre 0 as 12 anos ou mais de 60, 's' ou 'n'?");
                        if (ask(question)) {
                            sold = 1;
                            break;
                        }

                        break;
                    }
                    case 3:
                        {
                            int weekday = 0;

                            do {
                                system("clear");

                                // Show instructions
                                printf("Informe o dia da semana: \n\n");
                                printf("1. Segunda-Feira\n");
                                printf("2. Terça-Feira\n");
                                printf("3. Quarta-Feira\n");
                                printf("4. Quinta-Feira\n");
                                printf("5. Sexta-Feira\n");
                                printf("6. Sábado\n");
                                printf("7. Domingo\n");

                                scanf("%d", &weekday);
                                flush();

                                if (weekday < 1 or weekday > 7) {
                                    printf("Opção Inválida\n");
                                    pause();
                                }

                            } while(weekday < 1 or weekday > 7);

                            if (weekday == 2) {
                                char question[100];

                                // ask if client is needy-child
                                strcpy(question, "É criança carente, 's' ou 'n'?");
                                if (ask(question)) {
                                    sold = 1;
                                    break;
                                } else {
                                    puts("Cortesias só podem ser vendidas a crianças carentes!");
                                }
                            } else {
                                puts("Cortesias só podem ser vendidas nas terças-feiras!");
                            }
                        }

                        break;
                    default:
                        printf("Opção inválida\n");
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

                    system("clear");

                    // Print ticket details
                    printf("Seu recibo\n");
                    printf("==========\n");
                    printf("Peça: %s\n", shows[cmd-1].name);
                    printf("Data / Hora: %sh\n", tickets[index].date);
                    printf("Poltrona: %d\n", seat);
                    printf("Ingresso: %s\n\n", tickettypes[ticket-1].name);
                }

                pause();
                system("clear");
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

void sales_by_day(int show)
{
    float total = 0;
    int ticketid = 0, total_tickets = 0, regular = 0, promotional = 0, free = 0;

    for (int x = 0; x < TICKET_LIMIT; x++)
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

    printf("Peça: %s / %s\n", shows[show].name, shows[show].hour);
    printf("Total de ingressos vendidos: %d\n", total_tickets);
    printf("%s: %d / %s: %d / %s: %d\n", 
        tickettypes[0].name,
        regular,
        tickettypes[1].name,
        promotional,
        tickettypes[2].name,
        free);

    printf("Valor total recebido: R$ %1.5f\n\n", total);
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
            puts("Resposta inválida");
            pause(); 
            continue;
        }
    }
}