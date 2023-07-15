import pygame
import os   
import ctypes
from time import sleep
################### C-LIB DECLARATION ###########################
clib = ctypes.CDLL("/home/jakub/PAMSI/Projekt3/decison_layer.so")

win_condition = clib.win_condition
get_form_c = clib.get_form_c
############## GAME SETUP #######################################

WIDTH = HEIGHT = 900

WINDOW = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Tic tac toe")

BACKGROUND = pygame.image.load(os.path.join('Board.png'))

#MAX 20
SIZE = 5

X_IMG = pygame.image.load(os.path.join('X.png'))
X_IMG = pygame.transform.scale(X_IMG, (WIDTH/SIZE, HEIGHT/SIZE))

O_IMG = pygame.image.load(os.path.join('O.png'))
O_IMG = pygame.transform.scale(O_IMG, (WIDTH/SIZE, HEIGHT/SIZE))

BACKGROUND = pygame.transform.scale(BACKGROUND, ((O_IMG.get_rect()[2])*3, (O_IMG.get_rect()[3])*3))

pygame.font.init() 
if SIZE > 3:
    for i in range(0, WIDTH+1 ,BACKGROUND.get_rect()[2]):
        for j in range(0, HEIGHT+1, BACKGROUND.get_rect()[3]):
            WINDOW.blit(BACKGROUND, (i,j))
else:
    WINDOW.blit(BACKGROUND, (0,0))
pygame.display.update()

##################################################################

class Board:
    positions = []
    for i in range(int(HEIGHT/SIZE) ,HEIGHT+1, int(HEIGHT/SIZE) ):
        for j in range(int(WIDTH/SIZE) ,WIDTH+1, int(WIDTH/SIZE) ):
            positions.append([0, [j- WIDTH/SIZE,j], [i - HEIGHT/SIZE, i]])
    
    def draw(self):
        if SIZE > 3:
            for i in range(0, WIDTH+1 ,BACKGROUND.get_rect()[2]):
                for j in range(0, HEIGHT+1, BACKGROUND.get_rect()[3]):
                    WINDOW.blit(BACKGROUND, (i,j))
        else:
            WINDOW.blit(BACKGROUND, (0,0))
        for i in self.positions:
            if i[0] == 1:
                WINDOW.blit(O_IMG, (i[1][0],  i[2][0]))
            elif i[0] == -1:
                WINDOW.blit(X_IMG, (i[1][0],  i[2][0]))
        
        pygame.display.update()

    def check_and_append(self, player=1):
        mouse = pygame.mouse.get_pos()
        index_x =0
        index_y =0

        for i in self.positions:
            if index_x < 3:
                index_x = index_x +1
            else:
                index_x = 0

            if index_y < 3:
                index_y = index_y +1
            else:
                index_y = 0

            if i[1][0] < mouse[0] <i[1][1]:
                if i[2][0] < mouse[1] < i[2][1]:
                    if i[0] == 0:
                        i[0] = player
                        self.draw()
                        return True
        return False

    def win_condition(self):
        to_c =(ctypes.c_int32*(SIZE*SIZE))()
        j = 0
        while j < len(to_c):
            to_c[j] = self.positions[j][0]
            j = j +1
        
        contition_result = win_condition(to_c, SIZE)
        return contition_result
    
    def execute_ai_movment(self, player):
        to_c =(ctypes.c_int32*(SIZE*SIZE))()
        j = 0
        while j < len(to_c):
            to_c[j] = self.positions[j][0]
            j = j +1
        movment_index_got = get_form_c(to_c, SIZE)

        self.positions[movment_index_got][0] = player

        self.draw()
        return True

if __name__ == "__main__":
    game_board = Board()
    run = True
    keys_pressed = pygame.key.get_pressed()
    player = 1
    
    while run:
        if player == 1:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    run = False
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if game_board.check_and_append(player=player):
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