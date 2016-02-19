# Simple Python Tic-Tac-Toe program in command line.

# Completed in an afternoon in a Raspberry Pi 2. Effectively a first draft and
# will need to be cleaned up and have more commends added at some pooint.
# May also remake it with a GUI library or in C at some point.


def print_board(board):
    #for row in board:
    #    print "!".join(row)

    print "!".join(board[0])
    print "-+-+-"
    print "!".join(board[1])
    print "-+-+-"
    print "!".join(board[2])


def take_input(board, character):
    while True:
        while True:
            try:
                y = int(raw_input(character + "'s turn, choose a row (1-3):"))
                if y >0 and y < 4:
                    break
                else:   
                    print "Oops, it appears that isn't a valid row (1-3)"
            except ValueError:
                print "Oops, it appears that isn't a number"
                
        while True:
            try:
                x = int(raw_input("Choose a column (1-3):"))
                if x >0 and x < 4:
                    break
                else:   
                    print "Oops, it appears that isn't a valid column (1-3)"
            except ValueError:
                print "Oops, it appears that isn't a number"
                                 
        # x and y are now both defined
        x -= 1
        y -= 1 
        if board[y][x] == " ":
             board[y][x] = character
             print_board(board)
             return board
        else:
             print "Oops, it appears that spot is taken"
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
    


# Could manually print out - in each space, but this is more elegant

board = []
turns = 0

for x in range(0,3):
    board.append([" "] * 3)

print_board(board)

while True:
    board = take_input(board, "X")
    if check_winner(board) == True:
        print "X Wins!"
        break
    
    turns += 1
    if turns >= 9:
        print "It's a draw!"
        break
    
    board = take_input(board, "O")
    if check_winner(board) == True:
        print "O Wins!"
        break
    turns += 1
    # No need to check turns here as last turn will never be taken by player 2

