#include <cs50.h>
#include <stdio.h>
#include<string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    //check the name and update corrosponding candidate in preference table
    //we cannot use i as its already in use
    //values are always assigned from right to left
    int i = voter;
    int j = rank;
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(name, candidates[k].name) == 0)
        {
            //as preferences stores int we need to store index of corrosponding candidate.
            preferences[i][j] = k;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //it updates candidate votes if not eliminated according to preferences
    //initially j = 0 and changes if top prefernces gets elminated
    //n is going to be the candidates index we get from prefernces[i][j]
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int n = preferences[i][j];
            //it will keep checking for non eliminated candidate.
            if (candidates[n].eliminated == false)
            {
                candidates[n].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //we need to find min votes to win (50% votes+1)
    //we need to have max vote variable = m
    int n = voter_count / 2 + 1;
    int m = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (m < candidates[i].votes)
        {
            m = candidates[i].votes;
        }
    }
    if (m >= n)
    {
        //change i to j if  error
        for (int j = 0; j < candidate_count; j++)
        {
            if (m == candidates[j].votes)
            {
                printf("%s\n", candidates[j].name);
                return true;
            }
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //m = min votes of remaining candidates
    //min must start from a high value, if it is 0 we are always going to return 0
    //m = MAX_VOTERS initially
    int m = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            //update lowest vote
            if (m > candidates[i].votes)
            {
                m = candidates[i].votes;
            }
        }
    }
    return m;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //check if all remaining candidates have same votes
    //we need to keep updating a variable and compare it with another variable which counts not eliminated candidates
    //m = not elimimnated cand. and n = cad. with min votes.
    int m = 0;
    int n = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            m++;
        }
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == min)
        {
            n++;
        }
    }
    if (m == n)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //simple just change the status of min candidate
    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}