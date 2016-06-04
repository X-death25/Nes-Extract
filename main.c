#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    /**  Déclaration des fichiers*/

    FILE *fp;
    FILE *PRG_File;
    FILE *CHR_File;
    char *buffer_prg;
    char *buffer_chr;
    char *Roms_Data;
    unsigned char octetActuel=0;

    int i=0;
    int Taille_Roms=0;
    int Taille_PRG=0;
    int Taille_CHR=0;

    // Ouverture du fichier correspondant à l'argument 1

    if (argc > 1)
    {
        fp = fopen (argv[1], "rb"); /* On ouvre le fichier dont le chemin est accessible via argv[1] */
    }

    if (fp == NULL)
    {
        fprintf(stderr,"Impossible d'ouvrir le fichier : fichier introuvable\n");
        fprintf(stderr,"Fin de l'application\n");
        return 1;
    }

    else
    {
        fseek(fp,0,SEEK_END); // on amène le curseur à la fin du fichier
        Taille_Roms = ftell(fp); // on récupère la valeur de la taille du fichier et on la met dans DATA
        Roms_Data = (char*)malloc(Taille_Roms);

        // printf("Le fichier a une taille de %d \n ",Taille_Roms);

        /** on va commencer par vérifier qu'il s'agit bien d'un jeu de Nes */

        fseek(fp,0,SEEK_SET); // On repositionne le curseur à 0
        // Puis on récupère le Header
        for(i=0; i<4; i++)
        {
            fread(&octetActuel,1,1, fp); // On lit un octets
            Roms_Data[i]=octetActuel; // et on l'envoie dans le tableau
        }
        // Verif Nes
        if (Roms_Data[0] == 0x4E && Roms_Data[1] == 0x45 && Roms_Data[2] == 0x53 && Roms_Data[3] == 0x1A  )
        {
            printf("OK File is Nes/FC ROM !\n");


            fseek(fp,0,SEEK_SET); // On repositionne le curseur à 0

            // Puis on récupère le Header

            for(i=0; i<16; i++)
            {
                fread(&octetActuel,1,1, fp); // On lit un octets
                Roms_Data[i]=octetActuel; // et on l'envoie dans le tableau
                //   printf("%02hhX ", Roms_Data[i]);
            }

            /**On récupère les tailles de PRG et CHR */

            Taille_PRG=Roms_Data[4]*8192*2;
            Taille_CHR=Roms_Data[5]*8192;
            printf("La taille de la PRG est de %d octets\n",Taille_PRG);
            printf("La taille de la CHR est de %d octets\n",Taille_CHR);


            /**On alloue des buffers de PRG et CHR */

            buffer_prg = (char*)malloc(Taille_PRG);
            buffer_chr = (char*)malloc(Taille_CHR);


            /**On remplie les buffers PRG et CHR */

            fseek(fp,0,SEEK_SET); // On repositionne le curseur à 0
            for(i=0; i<16; i++)
            {
                fread(&octetActuel,1,1, fp); // On saute le header
            }
            for(i=0; i<Taille_PRG; i++) // la PRG est avant la CHR
            {
                fread(&octetActuel,1,1, fp);
                buffer_prg[i]=octetActuel; // On envoie la PRG dans le buffer
            }
            for(i=0; i<Taille_CHR; i++) // la PRG est avant la CHR
            {
                fread(&octetActuel,1,1, fp);
                buffer_chr[i]=octetActuel; // On envoie la PRG dans le buffer
            }

            /** Puis on écrit les fichiers de sortie */

            PRG_File=fopen("PRG.prg","wb");
            fwrite(buffer_prg,1,Taille_PRG,PRG_File);
            CHR_File=fopen("CHR.chr","wb");
            fwrite(buffer_chr,1,Taille_CHR,CHR_File);
            printf("Extraction des donnes avec succes !\n");

        }

        else
        {
            fprintf(stderr,"Ce fichier n'est pas une roms Nes valide\n");
            fprintf(stderr,"Fin de l'application\n");
            return 1;
        }

    }
return 0;
}


