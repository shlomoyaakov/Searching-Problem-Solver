Searching Problem Solver:
  this program open a parallel server and listen on port 5600
  you can connect to it (with parallel clients) and send a problem in the following pattern:
    matrix (line-by-line separated by commas)
    start point
    end point
    ‘end’
  the program will send back the solution path from start point to end point with the lowest cost.
  after 2 minutes without any client, the server will shut down.
  you can compile this program with the command -
  "g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread"
  and run it with the command "./a.out" 
  enjoy!

a link for the git repository:
https://github.com/danielsaraf94/ex4
