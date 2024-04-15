#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CANDIDATES 100
#define MAX_VOTERS 100
#define MAX_CONSTITUENCY_LENGTH 50
#define MAX_DATE_LENGTH 9
#define MAX_NAME_LENGTH 50
#define MAX_PARTY_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define MAX_PASSWORD_LENGTH 20
#define MAX_DOB_LENGTH 11

#define ADMIN_USERNAME "KiranCandidate"
#define ADMIN_PASSWORD "Ronaldo@7"
#define CHECK "Kiran"

// Define structures
typedef struct {
    char Full_Name[MAX_NAME_LENGTH];
    char party[MAX_PARTY_LENGTH];
    char constituency[MAX_CONSTITUENCY_LENGTH];
    int voteCount;
} Candidate;

typedef struct {
    int sno;
    char Full_Name[MAX_NAME_LENGTH];
    char Date_of_Birth[MAX_DOB_LENGTH];  // yyyy/mm/dd
    char Full_Address[MAX_ADDRESS_LENGTH];
    char Password[MAX_PASSWORD_LENGTH];
} Voter;

// Function prototypes
void setElectionSchedule();
void addCandidate();
void updateCandidate();
void deleteCandidate();
void registerVoter();
void updateVoterDetails();
void searchVoterDetails();
void castVote();
void displayVoteResults();

void authenticated();
bool adminLogin();

int main() {
    int choice;
    printf("\n===== Voting System Menu =====\n");
reprompt:
    printf("1. Admin Login\n");
    printf("2. Cast a vote\n");
    printf("3. Logout\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (adminLogin()) {
                authenticated();
            }
            break;
        case 2:
            castVote();
            break;
        default:
            break;
    }

    return 0;
}
 

bool adminLogin() {
    char username[MAX_NAME_LENGTH];
    char Password[MAX_PASSWORD_LENGTH];
    printf("Admin login\n");

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", Password);

    if (strcmp(username, ADMIN_USERNAME) == 0 &&
        strcmp(Password, ADMIN_PASSWORD) == 0) {
        return true;
    } else {
        return false;
    }
}

void authenticated() {
    int choice;
    do {
           printf("\n=====================\n");
    printf("==    Voting System Menu  ==\n");
    printf("=============================\n");
    printf("==1.  Set Election Schedule=\n");
    printf("==2.  Add Candidate       ==\n");
    printf("==3.  Update Candidate    ==\n");
    printf("==4.  Delete Candidate    ==\n");
    printf("==5.  Register Voter      ==\n");
    printf("==6.  Update Voter Details==\n");
    printf("==7.  Search Voter Details==\n");
    printf("==8.  Cast Vote           ==\n");
    printf("==9.  Display Vote Results==\n");
    printf("==10. Exit                ==\n");
    printf("=============================\n");

        
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                setElectionSchedule();
                break;
            case 2:
                addCandidate();
                break;
            case 3:
                updateCandidate();
                break;
            case 4:
                deleteCandidate();
                break;
            case 5:
                registerVoter();
                break;
            case 6:
                updateVoterDetails();
                break;
            case 7:
                searchVoterDetails();
                break;
            case 8:
                castVote();
                break;
            case 9:
                displayVoteResults();
                break;
            case 10:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 10);
}

void setElectionSchedule() {
    char constituency[MAX_CONSTITUENCY_LENGTH];
    char date[MAX_DATE_LENGTH];
    FILE *file = fopen("schedule.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Constituency: ");
    scanf("%s", constituency);
    printf("Enter Date of Election (yyyymmdd): ");
    scanf("%s", date);

    fprintf(file, "%s\t%s\n", constituency, date);
    fclose(file);
    printf("Election schedule set successfully.\n");
}

void addCandidate() {
    Candidate candidate;
    FILE *file = fopen("candidatelist.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Name of Candidate: ");
     fgets(candidate.Full_Name, MAX_NAME_LENGTH, stdin);
    scanf("%s", candidate.Full_Name);
    printf("Enter Political Party: ");
        fgets(candidate.party, MAX_PARTY_LENGTH, stdin);

    scanf("%s", candidate.party);
    printf("Enter Constituency: ");
    fgets(candidate.constituency, MAX_CONSTITUENCY_LENGTH, stdin);

    scanf("%s", candidate.constituency);

    fprintf(file, "%s\t%s\t%s\n", candidate.Full_Name, candidate.party,
            candidate.constituency);
    fclose(file);
    printf("Candidate added successfully.\n");
}

void updateCandidate() {
    Candidate candidate;
    FILE *file = fopen("candidatelist.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char nameToUpdate[MAX_NAME_LENGTH];
    printf("Enter the Full_Name of the candidate to update: ");
    scanf("%s", nameToUpdate);

    int found = 0;
    while (fscanf(file, "%s %s %s", candidate.Full_Name, candidate.party,
                  candidate.constituency) != EOF) {
        if (strcmp(candidate.Full_Name, nameToUpdate) == 0) {
            found = 1;
            printf("Enter New Name of Candidate: ");
             fgets(candidate.Full_Name, MAX_NAME_LENGTH, stdin);
            scanf("%s", candidate.Full_Name);
            printf("Enter New Political Party: ");
            fgets(candidate.party, MAX_PARTY_LENGTH, stdin);

            scanf("%s", candidate.party);
            printf("Enter New Constituency: ");
            fgets(candidate.constituency, MAX_CONSTITUENCY_LENGTH, stdin);

            scanf("%s", candidate.constituency);
            fseek(file,
                  -strlen(candidate.Full_Name) - strlen(candidate.party) -
                      strlen(candidate.constituency) - 2,
                  SEEK_CUR);
            fprintf(file, "%s\t%s\t%s\n", candidate.Full_Name, candidate.party,
                    candidate.constituency);
            break;
        }
    }

    if (!found) {
        printf("Candidate not found.\n");
    } else {
        printf("Candidate details updated successfully.\n");
    }

    fclose(file);
}

void deleteCandidate() {
    Candidate candidate;
    FILE *file = fopen("candidatelist.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char nameToDelete[MAX_NAME_LENGTH];
    printf("Enter the Full_Name of the candidate to delete: ");
    scanf("%s", nameToDelete);

    int found = 0;
    long int offset = 0;

    while (fscanf(file, "%s %s %s", candidate.Full_Name, candidate.party,
                  candidate.constituency) != EOF) {
        if (strcmp(candidate.Full_Name, nameToDelete) == 0) {
            found = 1;
            break;
        }
        offset = ftell(file);
    }

    if (found) {
        fseek(file, offset, SEEK_SET);
        fprintf(file, "                    ");
        printf("Candidate deleted successfully.\n");
    } else {
        printf("Candidate not found.\n");
    }

    fclose(file);
}

void registerVoter() {
    Voter voter;
    FILE *file = fopen("voterlist.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter SNO of Voter: ");
    scanf("%d", &voter.sno);
    printf("Enter Name of Voter: ");
    fgets(voter.Full_Name, MAX_NAME_LENGTH, stdin);
    scanf("%s", voter.Full_Name);
    printf("Enter Date of Birth (yyyy/mm/dd): ");
    fgets(voter.Date_of_Birth, sizeof(voter.Date_of_Birth), stdin);

    scanf("%s", voter.Date_of_Birth);
    printf("Enter Address: ");
    fgets(voter.Full_Address, MAX_ADDRESS_LENGTH, stdin);

    scanf("%s", voter.Full_Address);
    printf("Enter Password: ");
        fgets(voter.Password, MAX_PASSWORD_LENGTH, stdin);

    scanf("%s", voter.Password);

    fprintf(file, "%d\t%s\t%s\t%s\t%s\n", voter.sno, voter.Full_Name, voter.Date_of_Birth,
            voter.Full_Address, voter.Password);
    fclose(file);
    printf("Voter registered successfully.\n");
}

void updateVoterDetails() {
    int sno;
    printf("Enter Voter SNO to update: ");
    scanf("%d", &sno);

    FILE *file = fopen("voterlist.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[1024];
    char newDetails[1024];
    int found = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int currentSno;
        sscanf(buffer, "%d", &currentSno);
        if (currentSno == sno) {
            printf("Enter New Name of Voter: ");
            scanf("%s", newDetails);
            fseek(file, -strlen(buffer), SEEK_CUR);
            fprintf(file, "%d\t%s\n", sno, newDetails);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Voter not found.\n");
    } else {
        printf("Voter details updated successfully.\n");
    }

    fclose(file);
}

void searchVoterDetails() {
    int sno;
    printf("Enter the SNO of the voter to search: ");
    scanf("%d", &sno);

    FILE *file = fopen("voterlist.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    int found = 0;
    Voter voter;

    while (fscanf(file, "%d %s %s %s %s", &voter.sno, voter.Full_Name, voter.Date_of_Birth,
                  voter.Full_Address, voter.Password) != EOF) {
        if (voter.sno == sno) {
            found = 1;
            printf("Voter SNO: %d\n", voter.sno);
            printf("Name: %s\n", voter.Full_Name);
            printf("Date of Birth: %s\n", voter.Date_of_Birth);
            printf("Address: %s\n", voter.Full_Address);
            printf("Password: %s\n", voter.Password);
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Voter not found.\n");
    }
}

void castVote() {
    int sno;
    char Password[MAX_PASSWORD_LENGTH];

    printf("Enter your SNO: ");
    scanf("%d", &sno);
    printf("Enter your Password: ");
    scanf("%s", Password);

    FILE *voterFile = fopen("voterlist.txt", "r");
    if (voterFile == NULL) {
        printf("Error opening voter list file\n");
        return;
    }

    Voter voter;
    int found = 0;
    while (fscanf(voterFile, "%d %s %s %s %s", &voter.sno, voter.Full_Name,
                  voter.Date_of_Birth, voter.Full_Address, voter.Password) == 5) {
        if (voter.sno == sno && strcmp(Password, voter.Password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(voterFile);

    if (!found) {
        printf("Voter not found or incorrect Password\n");
        return;
    }

    printf("Candidate List:\n");

    FILE *candidateFile = fopen("candidatelist.txt", "r");
    if (candidateFile == NULL) {
        printf("Error opening candidate list file\n");
        return;
    }

    Candidate candidate;
    while (fscanf(candidateFile, "%s %s %s", candidate.Full_Name, candidate.party,
                  candidate.constituency) == 3) {
        printf("%s\t%s\t%s\n", candidate.Full_Name, candidate.party,
               candidate.constituency);
    }
    fclose(candidateFile);

    char chosenCandidate[MAX_NAME_LENGTH];
    printf("\nEnter the Full_Name of the candidate you want to vote for: ");
    scanf("%s", chosenCandidate);

    FILE *voteFile = fopen("votecount.txt", "a");
    if (voteFile == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    fprintf(voteFile, "%d\t%s\n", sno, chosenCandidate);
    fclose(voteFile);

    printf("Vote cast successfully\n");
}

void displayVoteResults() {
    // Read all candidates from file into an array
    Candidate candidates[MAX_CANDIDATES] = {0};
    int numCandidates = 0;
    int i;
    FILE *fp = fopen("candidatelist.txt", "r");
    if (fp == NULL) {
        printf("Error opening candidatelist.txt file\n");
        exit(1);
    }
    while (numCandidates < MAX_CANDIDATES &&
           fscanf(fp, "%s %s %s", candidates[numCandidates].Full_Name,
                  candidates[numCandidates].party,
                  candidates[numCandidates].constituency) == 3) {
        candidates[numCandidates].voteCount = 0;
        numCandidates++;
    }
    fclose(fp);

    // Read all votes from file and update the vote count for each candidate
    FILE *fq = fopen("votecount.txt", "r");
    if (fq == NULL) {
        printf("Error opening votecount.txt file\n");
        exit(1);
    }
    int voterId;
    char chosenCandidate[MAX_NAME_LENGTH];
    while (fscanf(fq, "%d %s", &voterId, chosenCandidate) == 2) {
        // Find the candidate with the given Full_Name in the array
        int candidateIndex = -1;
        for (i = 0; i < numCandidates; i++) {
            if (strcmp(candidates[i].Full_Name, chosenCandidate) == 0) {
                candidateIndex = i;
                break;
            }
        }
        if (candidateIndex != -1) {
            candidates[candidateIndex].voteCount++;
        }
    }
    fclose(fq);

    // Display the results
    printf("Name\t\tParty\t\tConstituency\t\tVoteCount\n");
    for (i = 0; i < numCandidates; i++) {
        printf("%s\t\t%s\t\t%s\t\t\t%d\n", candidates[i].Full_Name, candidates[i].party,
               candidates[i].constituency, candidates[i].voteCount);
    }

    // Find the winner
    int highestVoteCount = 0;
    int winnerIndex = -1;
    for (i = 0; i < numCandidates; i++) {
        if (candidates[i].voteCount > highestVoteCount) {
            highestVoteCount = candidates[i].voteCount;
            winnerIndex = i;
        }
    }
    if (winnerIndex != -1) {
        printf("\nThe winner is %s from %s with %d votes\n",
               candidates[winnerIndex].Full_Name,
               candidates[winnerIndex].constituency,
               candidates[winnerIndex].voteCount);
    }
}