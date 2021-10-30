#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//változók: saját struct-szerkezet léterhozása
typedef struct
{
    int id;
    char name[30];
    char faj[30];
    int m1,m2,m3;
}STD;

STD s;

//Metódusok
void display(FILE *);
int search(FILE *,int);
void create(FILE *, int, char);
void append(FILE *, int, char);


int main(int argc, char const *argv[])
{
    //File létrehozása, megnyitása és egy for-ciklussal az adatok felvitele, majd a file bezárása.
    int i,n,id_key,opn;
    FILE *fp;
    FILE *fp1;
    int found = 0;  
    char * temp;  


//Alapadatok felvitele után file megnyitása
    //do-whilelal amíg meg van nyitva a file, a következő switch-case esetek történjenek:
    do
    {
        printf("\nVálassz menüpontot :: \n 0 - FILE LÉTREHOZÁSA \n 1 - ADATOK LISTÁZÁSA \n 2 - KERESÉS\n 3 - TÖRLÉS\n 4 - ÚJ ADAT(OK) FELVÉTELE\n 5 - ADATOK MÓDOSÍTÁSA\n 6 - KILÉPÉS\n Mi a választásod? ");
        scanf("%d",&opn);
        switch(opn)
        {
        case 0: printf(" Hozz létre egy file-t: ");
            fp=fopen("bor.txt","w");
            printf(" Mennyi adatot szeretnél most felvinni? ");
            scanf("%d",&n);
            create(fp, n, temp);
            fclose(fp);
            break;

        case 1: printf("\n Borászatok eltárolva a file-ban \n");
            fp=fopen("bor.txt","r");
            display(fp);
            fclose(fp);
            break;
//Ez az egy nem volt a kötelező feladat része.
        case 2: printf(" Melyik borászatot keresed? Adj meg egy azonosítót: ");
            fp=fopen("bor.txt","r");
            scanf("%d",&id_key);
            if(search(fp,id_key))
            {
                printf("Sikeres keresés ! Ezt a borászatot találtam:\n");
                printf("%d\t%s\t\t%d\t\t%s\t\t%d\t\t%d\n",s.id,s.name,s.m1,s.faj,s.m2,s.m3);
            }
            else{
                printf(" Sikertelen keresés!! Ezzel az azonosítóval: %d  nem találtam borászatot\n",id_key);
            }
            fclose(fp);
            break;

        case 3:  printf(" Töröld kérlek a következő azonosítóval rendelkező borászatot a listából:\n");
            fp= fopen("bor.txt","r");
            fp1= fopen("temp.txt","w");
            scanf("%d", &id_key);
            while (fread(&s,sizeof(s),1,fp)){
                if(s.id == id_key){
                    found = 1;
                }else{
                    fwrite(&s,sizeof(s),1,fp1);
                }
            }
            fclose(fp1);
            fclose(fp);
        
            if(found == 1)
            {
                fp1 = fopen("temp.txt","r");
                fp = fopen("bor.txt","w");
                while (fread(&s,sizeof(s),1,fp1)){


                    fwrite(&s,sizeof(s),1,fp);
                }
                fclose(fp1);
                fclose(fp);
            }
            else{
                printf(" Sikertelen keresés!! Ezzel az azonosítóval: %d  nem találtam borászatot\n", id_key);
            }
            break;

        case 4:  printf(" Mennyi adatot szeretnél most felvinni? ");
//A lényeg itt van: Nem "write" módban hanem "append" ("a") módban nyitom meg eleve a file-, utána pedig ugyanaz történik, minthA új filet kreálnék.
            fp = fopen("bor.txt","a");
            scanf("%d",&n);
            append(fp, n, temp);
            fclose(fp);
            break;
//A módosítás és a törlés némileg ugyanúgy történik: Egy segédfile (temp.txt) segítségével kiolvasom azt az adatot először, amire szükségem van, 
//majd addig keresem, amíg meg nem találom a szükséges azonosítót. Lényeges, hogy a found értéke ekkor 1 legyen, mert a továbbiakban
//Így fut bele a true ágba, amelyben (temp.txt) visszaírom a módosított adatot az eredeti (bor.txt) file-ba a helyes azonosítóhoz.
        case 5:  printf(" Melyik borászat adatát szeretnéd módosítani? Kérlek azonosítót adj meg!");
            fp= fopen("bor.txt","r");
            scanf("%d", &id_key);
            fp1= fopen("temp.txt","w");
            
            while (fread(&s,sizeof(s),1,fp)){
                if(s.id == id_key){
                    found = 1;
                    printf("Az adatok a borászatokról: %d (Azonosító, Borászat neve, Négyszögöl, Szőlőfajta, Liter, Cukorfok) \n",i+1);
                    printf("Azonosító (ID): ");
                    scanf("%d", &s.id);
                

                    printf("Borászat neve: ");
                    scanf("%c",&temp);
                    fgets(s.name,30,stdin);
                    s.name[strcspn(s.name, "\n")] = 0;
                    

                    printf("Négyszögöl: ");
                    scanf("%d", &s.m1);
                
                    
                    printf("Szőlő fajtája: ");
                    scanf("%c",&temp);
                    fgets(s.faj,30,stdin);
                    s.faj[strcspn(s.faj, "\n")] = 0;
                    

                    printf("Liter: ");
                    scanf("%d", &s.m2);
                    

                    printf("Cukorfok: ");
                    scanf("%d",&s.m3);
                }
                    fwrite(&s,sizeof(s),1,fp1);
                }
                fclose(fp1);
                fclose(fp);
        
            if(found == 1)
            {
                fp1 = fopen("temp.txt","r");
                fp = fopen("bor.txt","w");
                while (fread(&s,sizeof(s),1,fp1)){
                    fwrite(&s,sizeof(s),1,fp);
                }
                fclose(fp1);
                fclose(fp);
            }
            else{
                printf(" Sikertelen keresés!! Ezzel az azonosítóval: %d  nem találtam borászatot\n", id_key);
            }
            break;
        case 6:  printf(" Kilépés!\n");
            break;
        default:  printf(" Érvénytelen menüpont!!!  Próbáld újra !!!\n");
            break;
        }
    }
    while(opn != 6);
    return 0;
}



//    End of main() 

void create(FILE *fp, int n, char temp)
{

 //Sima adatfelvétel történik egy for-ciklus segítségével.
 //Az n paramétert megkapta a scanf-ből a case 0 esetnél.   
    for(int i=0; i<n ; i++)
    {
        printf("Az adatok a borászatokról: %d (Azonosító, Borászat neve, Négyszögöl, Szőlőfajta, Liter, Cukorfok) \n",i+1);
        printf("Azonosító (ID): ");
        scanf("%d", &s.id);
       
//Itt az fgets és a temporális változóra, illetve az strcspn-re a space-ek értelmezése miatt van szükség.
        printf("Borászat neve: ");
        scanf("%c",&temp);
        fgets(s.name,30,stdin);
        s.name[strcspn(s.name, "\n")] = 0;
        

        printf("Négyszögöl: ");
        scanf("%d", &s.m1);
       
        
        printf("Szőlő fajtája: ");
        scanf("%c",&temp);
        fgets(s.faj,30,stdin);
        s.faj[strcspn(s.faj, "\n")] = 0;
        

        printf("Liter: ");
        scanf("%d", &s.m2);
        

        printf("Cukorfok: ");
        scanf("%d",&s.m3);
        
        
        fwrite(&s,sizeof(s),1,fp);
    }
}

//Az append ugyanaz mint a create, igazából felesleges is külön megírni, egyszerűen lehetne használni a create fgv-t "append" módban, de az összezavaró lenne. 
void append(FILE *fp, int n, char temp)
{
    for(int i=0; i<n ; i++)
    {
        printf("Az adatok a borászatokról: %d (Azonosító, Borászat neve, Négyszögöl, Szőlőfajta, Liter, Cukorfok) \n",i+1);
        printf("Azonosító (ID): ");
        scanf("%d", &s.id);
       

        printf("Borászat neve: ");
        scanf("%c",&temp);
        fgets(s.name,30,stdin);
        s.name[strcspn(s.name, "\n")] = 0;
        

        printf("Négyszögöl: ");
        scanf("%d", &s.m1);
       
        
        printf("Szőlőfajta: ");
        scanf("%c",&temp);
        fgets(s.faj,30,stdin);
        s.faj[strcspn(s.faj, "\n")] = 0;
        

        printf("Liter: ");
        scanf("%d", &s.m2);
        

        printf("Cukorfok: ");
        scanf("%d",&s.m3);
        
        
        fwrite(&s,sizeof(s),1,fp);
    }
}

void display(FILE *fp)
{
    //Beállítjuk a file elejére a mutatót a rewind-funkcióval
    rewind(fp);
    printf("ID             |         Borászat            |           Négyszögöl            |           Szőlőfajta          |        Liter       |      Cukorfok\n");
    //Egy sima while-ciklussal pontosan úgy olvassuk vissza a file-t, ahogyan felvittük az adatokat.
    while(fread(&s,sizeof(s),1,fp))
//a \t az adatok oldalra tologatása miatt kell.
        printf("%d\t\t\t%s\t\t\t%d\t\t\t%s\t\t\t%d\t\t\t%d\n",s.id,s.name,s.m1,s.faj,s.m2,s.m3);
}


int search(FILE *fp, int id_key)
{
    //Az id alapján történő keresésnél csak megnézzük, hogy az elejétől kezdve a file-nak van-e olyan id adattag, 
    //ahol a paraméterben megadott id_key értéke megegyezik a már felvitt s.id értékkel. Ahol egyezik, azt kiírjuk.

    rewind(fp);
    while(fread(&s,sizeof(s),1,fp))
        if( s.id == id_key) return 1;
    return 0;
}
