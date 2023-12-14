#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>



const unsigned int W_S{30}; // Width_String 

int main(){
    std::srand(std::time(nullptr));
    int clients[10][3];


    //Printing a client number, their address and the bill of the order (into a file)
    std::ofstream myFile("orders.txt", std::ios::out);
    if(myFile.is_open()){
    myFile << std::setw(25) << "Order List" << std::endl;
    myFile << "----------------------------------" << std::endl;
    myFile << "Client No." << std::setw(15) << "Address" << std::setw(35) << "Bill" << std::endl;
    for(size_t i{}; i < std::size(clients); ++i){
        static int client_no{};
        clients[i][0] = client_no; 
        clients[i][2] = (std::rand() % 901) + 100; // the bill size will vary between 100 and 1000 dollars
        myFile << clients[i][0] << std::setw(W_S) << &clients[i][1] << std::setw(W_S) << clients[i][2] << std::endl;  
        client_no++;            
    }
        myFile.close();
    }else{
        std::cerr << "Error opening file!";
    }    


    //The courier distributes the orders in a random order
    char route[11]; 
    route[10] = '\0';
    route[9] = '*';
    
    do{
        static unsigned int distribution_order{};
        char rand_num = static_cast<char>(std::rand() % 10 + '0');
        if(std::strchr(route, rand_num) != nullptr){
            continue;
        }
        route[distribution_order] = rand_num;
        distribution_order++;
    }while(route[9] == '*');


    std::string route_str = route; // random distribution order variable

    //Printing a client number, their address and the bill of the order according to the random distirbution order (printing onto a console).
    //The string that contains the client info whose order bill happens to be the highest will be of a green color, and the red color accordingly.
 
    int lowest = clients[0][2];
    int highest = clients[0][2];  
    for(size_t i{}; i < std::size(clients); ++i){
        if(lowest > clients[i][2]){
            lowest = clients[i][2];
        }
        if(highest < clients[i][2]){
            highest = clients[i][2];
        }
    }

    
    for(char new_distribution_order : route_str){  
        int i = new_distribution_order - 48;     
        if(clients[i][2] == lowest){
            std::cout << "\033[1;31m" << clients[i][0] << std::setw(W_S) << &clients[i][1] << std::setw(W_S) << clients[i][2] << "\033[0m" << std::endl;
        }else if(clients[i][2] == highest){
            std::cout << "\033[32m" << clients[i][0] << std::setw(W_S) << &clients[i][1] << std::setw(W_S) << clients[i][2] << "\033[0m" << std::endl;
        }else{
            std::cout << clients[i][0] << std::setw(W_S) << &clients[i][1] << std::setw(W_S) << clients[i][2] << std::endl;
        }
    }
    
    
  
    
    //Printing the new distribution route into the file
     myFile.open("orders.txt", std::ios::app);
        if (!myFile.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return 1;
        }

        myFile << "----------------------------------" << std::endl;
        myFile << std::setw(25) << "Distribution route" << std::endl;
        myFile << std::endl;
        myFile << std::endl;
        myFile << "----------------------------------" << std::endl;
        for(char new_distribution_order : route_str){  
            int i = new_distribution_order - 48;     
            myFile << clients[i][0] << std::setw(W_S) << &clients[i][1] << std::setw(W_S) << clients[i][2] << std::endl;       
        }
    myFile.close();
    

    
    int total_bill{};
    for(char new_distribution_order : route_str){  
        int i = new_distribution_order - 48;     
        total_bill += clients[i][2];
    }
    std::cout << "Total Bill: " << total_bill << std::endl;

    
    myFile.open("orders.txt", std::ios::app);
        if(!myFile.is_open()){
            std::cerr << "Error opening file!" << std::endl;
            return 1;
        }
        myFile << "----------------------------------" << std::endl;
        myFile << "Total Bill: " << total_bill << std::endl;
        myFile << std::endl;
        myFile << std::endl;
        myFile << "----------------------------------" << std::endl;

    myFile.close();

    
    //A matrix representing the difference in the bill paid by each client compared to all others
    int diff_matrix[10][10];
    for(size_t i{}; i < std::size(clients); ++i){
        for(size_t j{}; j < std::size(diff_matrix[0]); ++j){
            diff_matrix[i][j] = clients[i][2] - clients[j][2];
        }
    }


    for(size_t i{}; i < std::size(diff_matrix); ++i){
        for(size_t j{}; j < std::size(diff_matrix[0]); ++j){
            std::cout << diff_matrix[i][j] <<  std::setw(10);
        }
        std::cout << std::setw(0) << std::endl;
    }

    
}  

   
    

