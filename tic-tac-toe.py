
# Simple Python Tic-Tac-Toe program in command line.

# Completed in an afternoon in a Raspberry Pi 2. Effectively a first draft and
# will need to be cleaned up and have more commends added at some pooint.
# May also remake it with a GUI library or in C at some point.


# Update 22-02-16
# Changed '!' separator to '|' due to having a functional keyboard now
# Changed print and raw_input functions to use Python 3 versions rather than Python 2
# Added ability for players to choose their own character rather than the default X and O
# Changed some spacing to improve readability
# Added a loop around the entire function that asks the player if they would like to play again upon completion


def print_board(board):
    # for row in board:
    #    print "!".join(row)

    print("|".join(board[0]))
    print("-+-+-")
    print("|".join(board[1]))
    print("-+-+-")
    print("|".join(board[2]))


# Gets input from player into command line. Uses "while True" loops to continually
# request input until appropriate conditions are met, at which point it breaks.
# The function then modifies the "board" it was passed, displays it, and returns
# the modified array.

# By adding "character" argument, the same function can be used for both X and O
def take_input(board, character):
    while True:
        while True:
            try:
                y = int(input(character + "'s turn, choose a row (1-3):"))
                if 0 < y < 4:
                    break
                else:
                    print("Oops, it appears that isn't a valid row (1-3)")
            except ValueError:
                print("Oops, it appears that isn't a number")

        while True:
            try:
                x = int(input("Choose a column (1-3):"))
                if 0 < x < 4:
                    break
                else:
                    print("Oops, it appears that isn't a valid column (1-3)")
            except ValueError:
                print("Oops, it appears that isn't a number")

        # x and y are now both defined
        x -= 1
        y -= 1
        if board[y][x] == " ":
            board[y][x] = character
            print_board(board)
            return board
        else:
            print("Oops, it appears that spot is taken")
            print_board(board)


def check_winner(board):
    for num in range(0,3):
        if board[0][num] == board[1][num] and board[0][num] == board[2][num] and board[0][num] != " ":
            return True

    for num in range(0,3):
        if board[num][0] == board[num][1] and board[num][0] == board[num][2] and board[num][0] != " ":
            return True

    if board[0][0] == board[1][1] and board[0][0] == board[2][2] and board[0][0] != " ":
        return True

    if board[0][2] == board[1][1] and board[0][2] == board[2][0] and board[0][2] != " ":
        return True

    return False

while True:
    board = []
    turns = 0

    # Print spaces to array in 3x3
    for x in range(0,3):
        board.append([" "] * 3)


    while True:
        player1 = input("Please enter Player 1's letter:")[0]
        if player1 != " ":
            break
        print("Error, that is not a valid character")
    while True:
        player2 = input("Please enter Player 2's letter:")[0]
        if player2 != " " and not player1 == player2:
            break
        print("Error, that is not a valid character")


    print_board(board)

    while True:
        board = take_input(board, player1)
        if check_winner(board):
            print(player1, "Wins!")
            break

        turns += 1
        if turns >= 9:
            print("It's a draw!")
            break

        board = take_input(board, player2)
        if check_winner(board):
            print(player2, "Wins!")
            break
        turns += 1
        # No need to check turns here as last turn will never be taken by player 2

    if str.lower(input("Would you like to play again? Y/N")[0]) != 'y':
        break
