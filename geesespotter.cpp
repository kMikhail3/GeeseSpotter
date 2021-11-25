#include <iostream>
#include "geesespotter_lib.h"


int main();
char *createBoard(std::size_t xdim, std::size_t ydim);
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim);
void hideBoard(char *board, std::size_t xdim, std::size_t ydim);
void cleanBoard(char *board);
void printBoard(char *board, std::size_t xdim, std::size_t ydim);
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc);
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim);

/* void spreadGeese(char * board, std::size_t xdim, std::size_t ydim, unsigned int numgeese)
{
  if (board != NULL)
  {
    for (unsigned int gen_goose {0}; gen_goose < numgeese; gen_goose++)
    {
      std::size_t try_position {0};
      do {
         try_position = rand() % (xdim * ydim);
      } while (board[try_position] != 0);

      board[try_position] = 9;
    }
  }
} */

char *createBoard(std::size_t xdim, std::size_t ydim){
    char *boardDim{new char[xdim*ydim]{}};
    for (int j {0}; j<(xdim*ydim); j++) {
        boardDim[j]=0x00;
    }   
    
    return boardDim;
}
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim);
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){
    for (int i{0}; i<ydim; i++) {  
        for (int k{0}; k<xdim; k++) {
            int index = k+(i*xdim);
         
            if (board[index]==0x09) {
            
                //far left column k == 0
                if(k == 0) {
                    // if the r
                    if (i>0) {
                        if (board[index-xdim] != 0x09) {
                            board[index-xdim]+= 0x01;
                        }
                        if (board[index-xdim+1] != 0x09) {
                            board[index-xdim+1] += 0x01;
                        }
                    }
                    if (i+1< ydim) {
                        if (board[index+xdim] != 0x09) {
                            board[index+xdim]+= 0x01;
                        }
                        if (board[index+xdim+1] != 0x09) {
                            board[index+xdim+1]+= 0x01;
                        }
                    }
                    if (board[index+1] != 0x09) {
                        board[index+1] += 0x01;
                    }
                }
                else if (k == xdim-1) {
                    if (i>0) {
                        if (board[index-xdim] != 0x09) {
                            board[index-xdim] += 0x01;
                        }
                        if (board[index-xdim-1] != 0x09) {
                            board[index-xdim-1] += 0x01;
                        }
                    }
                    if(i+1<ydim) {
                        if (board[index+xdim] != 0x09) {
                            board[index+xdim] += 0x01;
                        }
                        if (board[index+xdim-1] != 0x09) {
                            board[index+xdim-1] += 0x01;
                        }
                    }  
                    if (board[index-1] != 0x09) {
                        board[index-1]+=0x01;
                    }
                }
                else {
                    if (i>0) { //bckwards
                        if (board[index-xdim+1] != 0x09) {
                            board[index-xdim+1] += 0x01;
                        }
                        if (board[index-xdim] != 0x09) {
                            board[index-xdim] += 0x01;
                        }
                        if (board[index-xdim-1] != 0x09) {
                            board[index-xdim-1] += 0x01;
                        }
                    }
                    if (i+1<ydim) { //fwd
                        if (board[index+xdim-1] != 0x09) {
                            board[index+xdim-1] += 0x01;
                        }
                        if (board[index+xdim] != 0x09) {
                            board[index+xdim] += 0x01;
                        }
                        if (board[index+xdim+1] != 0x09) {
                            board[index+xdim+1] += 0x01;
                        }
                    }
                    if (board[index-1] != 0x09) {
                        board[index-1]+=0x01;
                    }
                    if (board[index+1] != 0x09) {
                        board[index+1]+=0x01;
                    }
                }
            }
        }
    } 
}
void hideBoard(char *board, std::size_t xdim, std::size_t ydim){
    for(int j{}; j<(xdim*ydim); j++) {
        board[j] += 0x20;
    }
}
void cleanBoard(char *board){
    delete[] board;
    board = nullptr;
}
void printBoard(char *board, std::size_t xdim, std::size_t ydim){
    char valueIndex;
    for (int i {0}; i<(ydim); i++) { 
            for (int k{0}; k<(xdim); k++) {
                if (board[k+(i*xdim)]&0x10) {
                    std::cout<<"M";
                }
                else if (board[k+(i*xdim)]&0x20) {
                    std::cout<<"*";
                }
                else {
                    valueIndex = board[k+(i*xdim)];
                    valueIndex += 48;
                    std::cout<<valueIndex;
                }
            }
            std::cout<<"\n"; 
    
  /*   for (int j{}; j<xdim*ydim;j++) {
        std::cout<<"["<<j<<","<<int(board[j])<<"]"<<std::endl; */
    }
    
}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    for (int i{0}; i<ydim; i++) {  
        for (int k{0}; k<xdim; k++) {

            if (i==yloc && k==xloc) {
                if(board[i+(k*xdim)]&0x10) {
                    board[i+(k*xdim)] -=0x10;
                    return 2;
                }
                else {
                    board[i+(k*xdim)]+=0x10;
                    return 0;
                }
                
            }
        } 
    }
    return 0;
}
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){
    int initialGeese{0};
    int revealedSpots{0};

    for (int i{0}; i<(xdim*ydim); i++) {
        if (board[i] == 0x09 || board[i] == 0x29 || board[i] == 0x39) {
            initialGeese++;
        }
    }
    for (int j{0}; j<(xdim*ydim); j++) {
        if (board[j]<0x20){
            revealedSpots++;
        }
    }

    if ((xdim*ydim)-revealedSpots==initialGeese) {
        return true;
    } 
    else {
        return false;
    }
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    for (int i{0}; i<ydim; i++) {  
        for (int k{0}; k<xdim; k++) {
            int index = k+(i*xdim);
            if (i==yloc && k==xloc) {
                if (board[index]&0x10) {
                    return 1;
                }
                else if (board[index]<0x20) {
                    return 2;
                }
                else if (board[index]==0x29) {
                    board[index]-=0x20;
                    return 9;
                }
              
                if (board[index]==0x20) {
                    board[index]-=0x20;
                    if(k == 0) {
                    if (i>0) {
                        if ((board[index-xdim] != 0x29 || board[index-xdim] != 0x39) && board[index-xdim]>=0x20) {
                            board[index-xdim]-= 0x20;
                        }
                        if ((board[index-xdim+1] != 0x29 || board[index-xdim+1] != 0x39) && board[index-xdim+1]>=0x20) {
                            board[index-xdim+1] -= 0x20;
                        }
                    }
                    if (i+1< ydim) {
                        if ((board[index+xdim] != 0x29 || board[index+xdim] != 0x39) && board[index+xdim] >=0x20) {
                            board[index+xdim] -= 0x20;
                        }
                        if ((board[index+xdim+1] != 0x29 || board[index+xdim+1] != 0x39) && board[index+xdim+1]>=0x20) {
                            board[index+xdim+1] -= 0x20;
                        }
                    }
                    if ((board[index+1] != 0x29 || board[index+1] != 0x39) && board[index+1]>=0x20) {
                        board[index+1] -= 0x20;
                    }
                }
                else if (k == xdim-1) {
                    if (i>0) {
                        if ((board[index-xdim] != 0x29 || board[index-xdim] != 0x39)&& board[index-xdim]>=0x20) {
                            board[index-xdim] -= 0x20;
                        }
                        if ((board[index-xdim-1] != 0x29 || board[index-xdim-1] != 0x39) && board[index-xdim-1]>=0x20) {
                            board[index-xdim-1] -= 0x20;
                        }
                    }
                    if(i+1<ydim) {
                        if ((board[index+xdim] != 0x29 || board[index+xdim] != 0x39) && board[index+xdim]>=0x20) {
                            board[index+xdim] -= 0x20;
                        }
                        if ((board[index+xdim-1] != 0x29 || board[index+xdim-1] != 0x39)&& board[index+xdim-1]>=0x20) {
                            board[index+xdim-1] -= 0x20;
                        }
                    }  
                    if ((board[index-1] != 0x29 || board[index-1] != 0x39)&& board[index-1]>=0x20)  {
                        board[index-1] -= 0x20;
                    }
                }
                else {
                    if (i>0) { //bckwards
                        if ((board[index-xdim+1] != 0x29 || board[index-xdim+1] != 0x39) && board[index-xdim+1]>=0x20) {
                            board[index-xdim+1]  -= 0x20;
                        }
                        if ((board[index-xdim] != 0x29 || board[index-xdim] != 0x39)&& board[index-xdim]>=0x20) {
                            board[index-xdim]  -= 0x20;
                        }
                        if ((board[index-xdim-1] != 0x29 || board[index-xdim-1] != 0x39) && board[index-xdim-1]>=0x20) {
                            board[index-xdim-1]  -= 0x20;
                        }
                    }
                    if (i+1<ydim) { //fwd
                        if ((board[index+xdim-1] != 0x29 || board[index+xdim-1] != 0x39) && board[index+xdim-1]>=0x20) {
                            board[index+xdim-1] -= 0x20;
                        }
                        if ((board[index+xdim] != 0x29 || board[index+xdim] != 0x39)&& board[index+xdim]>=0x20) {
                            board[index+xdim] -= 0x20;
                        }
                        if ((board[index+xdim+1] != 0x29 || board[index+xdim+1] != 0x39)&& board[index+xdim+1]>=0x20) {
                            board[index+xdim+1] -= 0x20;
                        }
                    }
                    if ((board[index-1] != 0x29 || board[index-1] != 0x39)&& board[index-1]>=0x20) {
                        board[index-1] -= 0x20;
                    }
                    if ((board[index+1] != 0x29 || board[index+1] != 0x39)&& board[index+1]>=0x20) {
                        board[index+1] -= 0x20;
                    }

                }
                }   else {
                    board[index] -=0x20; 
                }
            }
        } 
    } return 0;
} 



/* int main(){
    int x, y, numGeese;
    char *board;
    std::cout<<"Welcome to GeeseSpotter!"<<std::endl;
    std::cout<<"Please enter the x dimension: ";
    std::cin>>x;
    std::cout<<"Please enter the y dimension: ";
    std::cin>>y;
    std::cout<<"Please enter the number of geese: ";
    std::cin>>numGeese;
    board = createBoard(x,y);
    
    spreadGeese(board,x,y,numGeese); 
    //printBoard(board,x,y) ;
    computeNeighbors(board,x,y); */
   
/* 
    hideBoard(board, x,y); 
    reveal(board,x,y,1,3); */
    /* mark(board,x,y,2,2); 

/*      for (int ye{};ye<6;ye++) {
        for(int xe{};xe<9;xe++) {
            mark(board, x,y,xe,ye);
            std::cout<<"-----------"<<std::endl;
            printBoard(board,x,y);
        }
    }
    int output{};
    int counter{};
    for (int ye{};ye<6;ye++) {
        for(int xe{};xe<9;xe++) {
            output= mark(board, x,y,xe,ye);
            if (output==2) {
                counter++;
            }
        }
    } */


    //mark(board, x,y,1,2);
    //mark(board, x,y,5,5); 
    //std::cout<<mark(board,x,y,5,5);   


  /*   mark(board,x,y,2,2);
    printBoard(board,x,y) ; 
    cleanBoard(board); 
    
    return 0;
}  */