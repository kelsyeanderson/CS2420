The code submitted is not as efficient as it could be. Because the code 
creates 12 boards every time it pops the first board off the front of 
the linked list, it reverses the move from the previous layer. To make 
it more efficient, I would have to have just the first board I check go 
through all 12 of the different moves. I would then have to have an if 
statement in the for loop that checked if the move I was currently doing 
would reverse the move made by the parent board.
