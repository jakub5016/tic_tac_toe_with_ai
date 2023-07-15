import tic_tac_toe
from tic_tac_toe import Board
from time import sleep
import pygame

if __name__ == "__main__":
    game_board = Board()
    run = True
    keys_pressed = pygame.key.get_pressed()
    player = 1
    
    while run:
        if player == 1:
            if game_board.execute_ai_movment(player=player):
                player = -1

        else:
            if game_board.execute_ai_movment(player=player):
                player = 1

        if game_board.win_condition() != False:
            run = False

        not_full = False
        for i in game_board.positions:
            if i[0] ==0:
                not_full = True

        if not_full == False:
            run = False

    if game_board.win_condition()/10 > 0 :
        print(f"PLAYER \"O\" WINS!") 
    elif game_board.win_condition()/10 <0 :
         print(f"PLAYER \"X\" WINS!") 
    else:
        print("DRAW")
    sleep(3)