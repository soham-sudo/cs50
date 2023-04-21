#include <cs50.h>
#include <stdio.h>
#include<string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //tough nasty code we find the candidate name for the jth rank and store it's index number in ranks array
    int j = rank;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[j] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = i; j < candidate_count; j++)
        {
            int n = ranks[i];
            int m = ranks[j];
            if(i == j)
            {
              preferences[n][m] = 0;
            }
            else if (i < j)
            //i is the preference before j
            {
                preferences[n][m]++;
            }

        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //int pair_count = 0 already declared in main
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(preferences[i][j] > preferences[j][i])
            {
                //pair count should be at last so that we can start from 0 index for pairs
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //create win strenght array from pairs which is k and k is 0 indexed
    //we are going to use selection sort, first find the max then change the indexces
    int k[pair_count];
    for(int i = 0; i < pair_count; i++)
    {
        int n = pairs[i].winner;
        int m = pairs[i].loser;
        k[i] = preferences[n][m] - preferences[m][n];
    }

    for(int a = 0; a < pair_count; a++)
    {
        //finding max present after a
        int max_strength = 0;
        int starting = a;
        int largest = 0;
        for(int b = a; b < pair_count; b++)
        {
            if(max_strength < k[b])
            {
                max_strength = k[b];
                largest = b;
                //changing values in highest and lowest indexes of a with b
                //need to change here as we cannot store b in a variable outside 2nd for loop
                //pair is data type, pairs is name of a variable array with pair data type
                //pair temp = pairs[a];
                //pairs[a] = pairs[b];
                //pairs[b] = temp;
            }
        }
        pair temp = pairs[starting];
        pairs[starting] = pairs[largest];
        pairs[largest] = temp;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
//really hard not going to happen
{
    //we need to make 2 arrays winner and loser if 1st winnner goes to loser, cycle creates or if a person already present in winner goes to loser list
    for(int i = 0; i < pair_count; i++)
    {
        //int n = pairs[i].winner;
        //int m = pairs[i].loser;
        int a = 0;
        int b = 0;
        locked[pairs[i].winner][pairs[i].loser] = true;
        //1st winner becomes loser
        //does not overcome 4th illustration in tideman
        if(pairs[i].loser == pairs[0].winner)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
            break;
        }
        for(int j = 1; j < i; j++)
        {
            //if recent loser was earlier winner then cycle except first
            if(pairs[i].loser == pairs[j].winner)
            {
                a++;
                break;
            }
        }
        for (int k = 0; k < i; k++)
        {
            //recent loser was also earlier a loser
            if (pairs[i].loser == pairs[k].loser)
            {
                b++;
                break;
            }
        }
        if(a == b & a != 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int n = pairs[0].winner;
    printf("%s\n", candidates[n]);
    return;
}