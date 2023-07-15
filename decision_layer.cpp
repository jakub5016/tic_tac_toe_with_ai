#include <stdbool.h>
#include <stdio.h>
#include <cstdlib>

extern "C" {
    float max(float a, float b){
        if (a>b){
            return a;
        }
        else{
            return b;
        }
    }

    float min(float a, float b){
        if (a<b){
            return a;
        }
        else{
            return b;
        }
    }

    /**
     * Gets number of unused places in the board 
     * Usefull when you have to iterate 
     */
    int get_blank_board_size(int * board, int board_size){
        int size = 0;
        for (int i =0; i<(board_size*board_size) ;i++){
            if (board[i] == 0){
                size++;
            }
        } 
        return size;
    }
    /**
     * Takes an array and compute a winning conditon for tic tac toe game:
     * - returns (1) - O won
     * - retuns (0) - draw
     * - returns (-1) - X won
     */
    int win_condition(int *arr, int size){
        int status = 0;
        int pervous_status =0;
        for (int i =0; i <size; i= i +1){
            for (int j =i; j<(size*size); j= j+size){
                if (j == i){
                    status = arr[j];
                }
                if (arr[j] == status){
                    status == arr[j];
                } 
                else{
                    status =0;
                }
            }
            if (status !=0){
                
                break;
            }
        }
        
        if (status == 0){
            for (int i =0; i <(size*size); i= i +size){
                for (int j =0 ; j< size; j= j+1){
                    if (j ==0){
                        status = arr[i+j];
                    }
                    else{
                        if (arr[i+j] == status){
                            status = arr[i+j];
                        } 
                        else{
                            status =0;
                        }
                    }
                }
                if (status !=0){
                    break;
                }
        }
        }
        
        if (status == 0){
            status = arr[0];

            for (int i =0;(int((size*i)) + i) < (size * size);i++){
                if (arr[(size*i) + i] != status){
                    status =0;
                } 
            }
            
            if (status ==0){
                status = arr[size-1];
                for (int i =1; (int((size*i)) - i) < ((size * size) -1);i++){
                    if (arr[(size*i) - i] != status){
                        status =0;
                        //status = arr[(size*i) + i];
                    } 
                }
            }
        }

        return status * ((size*size)+1);
    }

    int calculate_max_depth(int size){
        int max_depth = 0;
        printf("SIZE: %d\n", size);
        if (size < 8){
            max_depth = 9;
        }
        if ((8<= size) && (size <= 15)){
            max_depth = 5;
        }
        if ((15< size) && (size <20)){
            max_depth = 4;
        }
        if ((20<= size) && (size< 30)){
            max_depth = 3;
        }
        if ((30 <= size) && (size <= 50)){
            max_depth = 2;
        }
        if (size > 50){
            max_depth = 1;
        }

        return max_depth;        
    }

    class Node {
        private:
            int *board;
            int size;
            bool turn; // O turn is 1, X turn is 0
            Node *conections;
            int score;
            int depth;
            int max_depth;

        public:
            Node();
            Node(int *arr, int size, int depth =0, int max_depth = -1);
            
            int get_score();
            bool get_turn();
            int* get_board();
            int get_max_depth();
            int get_size();
            int get_score_from_index(int index);
            int* get_board_from_index(int index);
            Node* get_conections();

            int operator- (Node second);

            void create_connections();
            void check_turn();
            void write_connections();
            
            ~Node();
    };

    Node::Node(){

    }
    Node::Node(int *array, int size, int depth, int max_depth){
        this->depth = depth;
        this->board = array;
        if (max_depth ==-1){
            this->max_depth = calculate_max_depth(get_blank_board_size(this->board, size));
            printf("\nCalculated depth: %d\n\n", this->max_depth);
        }   
        else{
            this->max_depth =max_depth;
        }
        this->size =size;
        this->score = win_condition(this->board, this->size);
        this->check_turn();
        create_connections();
    }

    Node::~Node(){
        this->board = nullptr;
        this->conections = nullptr;
    }

    void Node::check_turn(){
        if (this->size %2){
            if(get_blank_board_size(this->board, this->size) % 2 == 0){
                this->turn = false;
            }
            else{this->turn = true;}
        }
        else{
            if(get_blank_board_size(this->board, this->size) % 2 == 0){
                this->turn = true;
            }
            else{this->turn = false;}
        }
    }
    int Node::get_score(){
        return this->score;
    }

    int Node::get_size(){
        return this->size;
    }

    bool Node::get_turn(){
        return this->turn;
    }

    int * Node::get_board(){
        return this->board;
    }

    int Node::get_max_depth(){
        return this->max_depth;
    }

    int Node::operator-(Node second){
        for (int i =0; i<(get_size()*get_size()); i++){
            if ((this->board[i]) != (second.get_board()[i])){
                return i;
            }
        }
    }
    void Node::create_connections(){
        if (this->depth > this->max_depth){
            return;
        }
        int size = get_blank_board_size(this->board, this->size);
        this->conections = new Node[size];
        int j =0;
        int glebokosc = this->depth;
        for (int i =0; i<((this->size)*(this->size)) ;i++){
            if ((this->board)[i] == 0){
                int * new_board = new int[((this->size)*(this->size))];
                for (int k =0; k<((this->size)*(this->size)); k++){
                    new_board[k] = this->board[k];
                }

                if (this->turn){new_board[i] = 1;}
                else {new_board[i] = -1;}

                this->conections[j] =  Node(new_board, this->size, glebokosc+1,this->max_depth);
                j++;
            }
        }
    }

    Node* Node::get_conections(){
        return this->conections;
    }

    int Node::get_score_from_index(int index){
        return ((this->conections)[index]).get_score();
    }
    
    int* Node::get_board_from_index(int index){
        return ((this->conections)[index]).get_board();
    }

    void Node::write_connections(){
        int size = get_blank_board_size(this->board, this->size);

        for (int i =0; i<size; i++){
            printf("\n\n");
            for(int j=0; j<(get_size()*get_size()); j=j+this->size){
                printf("%d, %d, %d, %d \n", this->conections[i].get_board()[j], this->conections[i].get_board()[j+1], this->conections[i].get_board()[j+2], this->conections[i].get_board()[j+3]);
            }
        }
    }

    float minimax(Node board, int depth =0, float alpha = -1000, float beta = 1000){
        bool is_max_player = board.get_turn();

        if ((depth >(board.get_max_depth() -1)) && (board.get_score() > 0)){
            return float(board.get_score()) - depth;
        }

        if ((depth >(board.get_max_depth() -1)) && (board.get_score() < 0)){
            return float(board.get_score()) + depth;
        }

        if ((depth >(board.get_max_depth() -1)) && (board.get_score() == 0)){
            return 0;
        }

        if (board.get_score() > 0){
            return float(board.get_score()) - depth;
            
        }
        else if(board.get_score() < 0){
            return float(board.get_score()) + depth;
        }
        else if((board.get_score() == 0)&&(get_blank_board_size(board.get_board(), board.get_size()) == 0)){
            return 0;
        }

        float value;
        if (is_max_player){
            float bestVal = -1000;
            for (int i =0; i <get_blank_board_size(board.get_board(), board.get_size()); i++){
                value = minimax((board.get_conections())[i], depth+1, alpha, beta);
                bestVal = max(bestVal, value);
                alpha = max(alpha, bestVal);

                if (alpha >= beta){
                    break;
                }
            }
            return bestVal;
        }
        
        else{
            float bestVal = 1000;
            for (int i =0; i <get_blank_board_size(board.get_board(), board.get_size()); i++){
                value = minimax((board.get_conections())[i], depth+1, alpha, beta);
                bestVal = min(bestVal, value);
                beta = min(beta, bestVal);
                if (alpha >= beta){
                    break;
                }
            }
            return bestVal;
        }
    }

    int wrap_function(Node board){
        if (win_condition(board.get_board(), board.get_size()) != 0){ //Expect end of the game
            return 100;
        }
        int size = get_blank_board_size(board.get_board(), board.get_size());
        float result [size];
        int return_index = 0;

        for (int i =0; i < get_blank_board_size(board.get_board(), board.get_size()); i++){
            result[i] = minimax(board.get_conections()[i]);
            
            if ((result[i] > result[return_index]) && (board.get_turn() == true)){
                return_index = i;
            }
            
            if ((result[i] < result[return_index])  &&  (board.get_turn() == false)){
                return_index = i;
            }
            
            if (result[i] == result[return_index]){
                if (rand()%2 && rand()%3 && rand()%7){
                    return_index = i;
                }
            }
        }
        //If you have to lose, do it 
        return return_index;
    }
    /*
     *  Function that is used in python code to execute minimax algorithm 
     */
    int get_form_c(int * board_status, int size){
        Node to_comput = Node(board_status, size);
        int wsk;
        wsk = wrap_function(to_comput);
        Node prediction = to_comput.get_conections()[wsk];
        int place = prediction - to_comput;

        to_comput.~Node();
        prediction.~Node();

        return place;
    }

}

/*
*  MAIN IS JUST FOR TESTS!
*/
int main(){
    int tablica[] ={
         -1, 0, 0, -1,
         1, 0, 1, 0,
         1, 1, 0, 1,
         1, -1, -1, -1
         };
    Node first = Node(tablica, 4);
    printf("SOCORE OF THIS TABLE: %d,\n\n", first.get_score());
    int wsk;
    wsk = wrap_function(first);
    printf("%d\n", wsk);
    if (wsk == 100){
        printf("ALREADY SATISFIED\n");
        return 0;
    }
    
    if (get_blank_board_size(tablica, 4) % 2 == 0){
        printf("AAAAA");
    }
    printf("%d \n",first.get_turn());

    int* prediction = first.get_conections()[wsk].get_board();
    for (int i =0; i<16; i= i+4){
        printf("%d, %d, %d, %d \n", *(prediction + i) , *(prediction+i+1), *(prediction+i+2), *(prediction+i+3));
    }
    return 0;
}