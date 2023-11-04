#include "HashTable.h"


int main()
{
    HashTable h = newHashTable( 100 );
    char buffer[300];
    char buffer2[300];
    char teamName1[50];
    char teamName2[50];
    char teamScore1[50];
    char teamScore2[50];
    char blank[100];
    int teamScore10;
    int teamScore20;
    Element* team1;
    Element* team2;
    Element e;
    int i = 0;
    FILE* fIn1;
    FILE* fIn2;
    int teamNameKey = 0;
    int teamNameHashedKey = 0;
    
    fIn1 = fopen("nbaTeamNames.csv","r");
    if (fIn1 == NULL)
    {
        return 1;
    }
    
    while (fgets(buffer, 300, fIn1) != NULL)
    {
        
        sscanf(buffer, "%[^\r\n]", e.teamName);                  
        teamNameKey = stringToInt(e.teamName);             
        teamNameHashedKey = divisionMethod(teamNameKey, h->n);       
        e.wins = 0;
        e.losses = 0;
        put (h, e);  
        
    }
    
    fIn2 = fopen("nbaData2019.csv", "r");
    
    while (fgets(buffer, 300, fIn2) != NULL)
    {
        sscanf(buffer, "%[^,],%[^,],%[^,],%[^,\n]", teamName1, teamScore1, teamName2, teamScore2);
        
        teamScore10 = atoi(teamScore1);
        teamScore20 = atoi(teamScore2);
      
        team1 = get(h,teamName1);
        team2 = get(h,teamName2);

        if (teamScore10 > teamScore20 && team1 && team2)
        {
             team1->wins++;
            team2->losses++;
        }
        
         if (teamScore10 < teamScore20 && team1 && team2)
        {
            team2->wins++;
            team1->losses++;
        }
      
    }
 
    
        rewind(fIn1);
        while (fgets(buffer2, 300, fIn1) != NULL)
        {
            
            sscanf(buffer2, "%[^\r\n]", blank);
            team1 = get(h,blank);          
            printf("%s: %d Wins - %d Losses\n", team1->teamName, team1->wins, team1->losses);
        }
        
      
        fclose(fIn1);
        fclose(fIn2);
        freeHashTable(h);
	return 0;
}


