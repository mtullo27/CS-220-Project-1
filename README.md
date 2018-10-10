#CS-220-Project-1
CS220 - Computer System II Project 1
Due: 10/19/2018, 11:59pm
Teams size ≤ 2.
Team memberships due by (email all 3 TAs): 09/18/2018, 11:59pm. NOTE: If you don’t register teams by the deadline, you will default to working on the project alone.

1 Introduction
In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way:
• High Card: Highest value card.
• One Pair: Two cards of the same value.
• Two Pairs: Two different pairs.
• Three of a Kind: Three cards of the same value.
• Straight: All cards are consecutive values.
• Flush: All cards of the same suit.
• Full House: Three of a kind and a pair.
• Four of a Kind: Four cards of the same value.
• Straight Flush: All cards are consecutive values of same suit. • Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
The cards are valued in the order:
2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.
If two players have the same ranked hands then the rank made up of the highest value wins; for example, a pair of eights beats a pair of fives (see example 1 below). But if two ranks tie, for example, both players have a pair of queens, then highest cards in each hand are compared (see example 4 below); if the highest cards tie then the next highest cards are compared, and so on. The game is played with a single deck of 52 cards (there are 4 suits: clubs, spades, hearts and diamonds, each with 13 cards from 2 through Ace). Each player is dealt 2 random cards (called ‘hole’ cards). Then, 5 ‘community’ cards are placed on the table. The community cards are common for all the players. A player’s show-down hand is the strongest 5 card combination from the hole c ards + community cards (i.e., best 5 out of the 7 cards).
A more elaborate description of poker hand rankings can be found here:
http://www.pokerlistings.com/poker-hand-ranking

2 Goal
The goal of this project is to write a program that evaluates a winner given the hands of 3 players, and the community cards. You are guaranteed that there will not be a tie between the players.
Input: You will be provided with a plain text file that contains random hands dealt to three players. Each line of the file contains 11 cards (each card separated by a single space): the first two are Player 1’s cards, next two are Player 2’s cards and the third 2 are Player 3’s cards. The last five cards are the community cards. Each player’s best hand constitutes the best 5 cards from the player’s hole cards and the community cards combined. You can assume that all hands are valid (no invalid characters or repeated cards), and in each hand there is a clear winner.
Output: You are to generate Output.txt where each line contains the winner of the corresponding hand in the input.
3 Sample input and output 4 Instructions
• Comment your code appropriately.
• You are allowed to work in groups of no more than 2 students. If you are working in teams, all team members must be fully aware of the innerworkings of the enitre project. Further, you are to clearly demarcate contribution by commenting each students contribution in the source file.
• You are required to demonstrate your program to the TA. Create proj1.tar.gz comprising of poker.c, poker.h and the Makefile to build the program. Make an appointment with your corresponding TA and demonstrate the functioning of the program. You must show that your program will successfully build and pass the sample hands. TA will have a set of well-qualified inputs to further test your program.
• All members of the team are required to use Github for development. A regular github commit record (by all members) is necessary for full credit. Steady progress before the deadline is expected and will be verified through github commit logs.

