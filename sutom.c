#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LEN_LIST 336531 //taille de la liste de mots (words.txt)

//Structure de la grille
struct Grid {
    char line[6][30];
    char sutom[30];
    long sutomIndex;
    int length;
    int step;
};

//Stocke dans word le mot numero line
void getWord(FILE *file, char *word, long line) {
    rewind(file);
    if (file != NULL || line > 0) {
        char temp;
        int cpt = 0;
        for (int i=0;i<line-1;i++) {
            do {
                temp = getc(file);
            } while (temp != '\n');
        }
        temp = getc(file);
        while (temp != '\n') {
            *(word+cpt) = temp;
            temp = getc(file);
            cpt++;
        }
        *(word+cpt) = '\0';
    }
}

//Débararsse le mot des accents et le met en majuscule
void cleanWord(FILE *file, unsigned char *word) {
    for (int i=0;i<strlen(word);i++) {
        if (*(word+i)==195) {
            switch (*(word+i+1))
            {
                case 160:   //à
                    *(word+i) = 'a';
                    break;
                case 162:   //â
                    *(word+i) = 'a';
                    break;
                case 164:   //ä
                    *(word+i) = 'a';
                    break;
                case 167:   //ç
                    *(word+i) = 'c';
                    break;
                case 168:   //è
                    *(word+i) = 'e';
                    break;
                case 169:   //é
                    *(word+i) = 'e';
                    break;
                case 170:   //ê
                    *(word+i) = 'e';
                    break;
                case 171:   //ë
                    *(word+i) = 'e';
                    break;
                case 174:   //î
                    *(word+i) = 'i';
                    break;
                case 175:   //ï
                    *(word+i) = 'i';
                    break;
                case 180:   //ô
                    *(word+i) = 'o';
                    break;
                case 182:   //ö
                    *(word+i) = 'o';
                    break;
                case 185:   //ù
                    *(word+i) = 'u';
                    break;
                case 187:   //û
                    *(word+i) = 'u';
                    break;
                case 188:   //ü
                    *(word+i) = 'u';
                    break;
                default:    //erreur
                    *(word+i) = '!';
                    break;
            }
            for (int j=i+1;j<strlen(word);j++) {
                *(word+j) = *(word+j+1);
            }
            *(word+strlen(word)) = '\0';
        }
        *(word+i) -= 'a'-'A';
    }
}

//Retourne un entier long (max 2^32) allant de 1 à 336531. rand() vaut max 32767
long rangeAleaInt() {
    long aleaInt;
    do {
        aleaInt = ((rand()+1)*(rand()+1))%LEN_LIST;
    } while (aleaInt>LEN_LIST);
    return aleaInt;
}

//Retourne la taille de la liste de mots
long getListSize(FILE *file) {
    rewind(file);
    long i = 0;
    char temp = 'a';
    while (temp!=EOF) {
        temp = getc(file);
        if (temp=='\n') {
            i++;
        }
    }
    return i+1;
}

//Initialise la grille
void initGrid(FILE* wordFile, struct Grid *G) {
    //Sélection du mot mystère
    (*G).sutomIndex = rangeAleaInt();
    getWord(wordFile,(*G).sutom,(*G).sutomIndex);
    cleanWord(wordFile,(*G).sutom);
    (*G).length = strlen((*G).sutom);
    for (int i=0;i<6;i++) {
        for (int j=0;j<(*G).length;j++) {
           (*G).line[i][j] = '.';
        }
    }
    (*G).line[0][0] = (*G).sutom[0];
}

void printGrid(struct Grid *G) {
    for (int i=0;i<6;i++) {
        for (int j=0;j<(*G).length;j++) {
            printf("%c ",(*G).line[i][j]);
        }
        printf("\n");
    }
}

//Affiche le logo SUTOM
void printLogo(FILE *graphicsFile) {
    char graphicsTemp[100] = "";
    while (fgets(graphicsTemp,100,graphicsFile) != NULL) {
        printf("%s",graphicsTemp);
    }
}

int main() {
    srand(time(NULL));

    //Ouverture des fichiers (mots et graphismes)
    FILE *wordsList = NULL;
    FILE *graphics = NULL;
    wordsList = fopen("words.txt","r+");
    graphics = fopen("graphics2.txt","r");

    if (wordsList != NULL && graphics != NULL) {
        printLogo(graphics);
        getchar();
        struct Grid game;
        initGrid(wordsList,&game);
        printGrid(&game);
        printf("Mot %-6d : %s\n",game.sutomIndex,game.sutom);        
    }
    else {
        printf("Erreur: Fichier words.txt ou graphics.txt introuvables. Placez-les au m%cme niveau que l'ex%ccutable.\n",136,130);
        return 1;
    }
    return 0;
}

/*for (int i=0;i<20;i++) {
    alea = rangeAleaInt();
    getWord(fichier,mot,sutomIndex);
    cleanWord(fichier,mot);
    printf("Mot %-6d : %s\n",sutomIndex,mot);
}*/

/*
        //Test de distribution du générateur de nb aléa: semble uniforme (testé avec i=100000)
        int z1=0,z2=0,z3=0,z4=0,z5=0,z6=0,z7=0;
        printf("Mot %-6d : %s\n",game.sutomIndex,game.sutom);
        for (int i=0;i<100000;i++) {
            long aleeea = rangeAleaInt();
            printf("%d\n",aleeea);
            if (aleeea>300000) {
                z7++;
            }
            else if (aleeea>250000) {
                z6++;
            }
            else if (aleeea>200000) {
                z5++;
            }
            else if (aleeea>150000) {
                z4++;
            }
            else if (aleeea>100000) {
                z3++;
            }
            else if (aleeea>50000) {
                z2++;
            }
            else {
                z1++;
            }
        }
        printf("\n0-50: %d\n50-100: %d\n100-150: %d\n150-200: %d\n200-250: %d\n250-300: %d\n300    : %d\n",z1,z2,z3,z4,z5,z6,z7);*/