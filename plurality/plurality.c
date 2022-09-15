#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        for (int y=0; y < (candidate_count - i - 1); y++)
        {
            if (candidates[y].votes > candidates[y + 1].votes)
            {
                candidate temp = candidates[y];
                candidates[y] = candidates[y + 1];
                candidates[y + 1] = temp;
            }
        }
    }

    string winners[MAX] ;
    winners[0] = candidates[candidate_count - 1].name;
    int n_winners = 1;
    for (int i = candidate_count - 2; i >= 0; i--)
    {
        if (candidates[i].votes == candidates[i + 1].votes)
        {

            winners[n_winners] = candidates[i].name;
            n_winners++;
        }
        else
        {
            break;
        }
    }
    for (int i = 0; i < n_winners; i++)
    {
        printf("%s\n", winners[i]);
    }


    return;
}